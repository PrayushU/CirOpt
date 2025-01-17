import os
import matplotlib.pyplot as plt
import graphviz

class PostProcessor:
    def __init__(self):
        self.check_output_directory()

    def check_output_directory(self):
        """
        Ensures that the 'outputs' directory exists and creates it if not
        """
        if not os.path.exists('post_processing/outputs'):
            os.makedirs('post_processing/outputs')

    def create_graph(self, vector, num_units, performance, recovery, grade):
        """
        Creates a directed graph using Graphviz based on the given vector and number of units.

        Args:
            vector (list): A list representing the connections between units.
            num_units (int): The number of units in the system.

        Returns:
            None
        """
        graph = graphviz.Digraph()
        graph.attr(rankdir='LR')
        graph.attr('node', shape='rectangle', splines='ortho')

        graph.edge('Feed', f'Unit {vector[0]}',
                   color='black',
                   headport='w', tailport='e',
                   arrowhead='normal')
        
        tailings_int = num_units + 1
        concentration_int = num_units

        for i in range(num_units):
            start_index = i * 3 + 1 
            for j in range(3):
                if vector[start_index + j] == concentration_int:
                    to_unit = f'Concentration'
                elif vector[start_index + j] == tailings_int:
                    to_unit = f'Tailings'
                else:
                    to_unit = f'Unit {vector[start_index + j]}'

                from_unit = f'Unit {i}'
                # concentrate stream, intermediate stream and the tailings streams
                color = ['black', 'blue', 'red'][j]
                headport = ['w', 'n', 's'][j]
                graph.edge(from_unit, to_unit,
                           color=color,
                           style='bold',
                           headport=headport, tailport='e',
                           arrowhead='normal')

        vector_str = ', '.join(str(v) for v in vector)
        label = f'Vector: {vector_str}\nPerformance: {performance}\nRecovery: {recovery}%\nGrade: {grade}%'
        graph.attr(label=label)

        with graph.subgraph(name='cluster_legend') as c:
            c.attr(label='Key:', shape='box')
            c.node('black', 'Concentrate stream', color='black', style='bold')
            c.node('blue', 'Intermediate stream', color='blue', style='bold')
            c.node('red', 'Tailings stream', color='red', style='bold')


        graph.render('post_processing/outputs/directgraph', cleanup=True, format='png')

    def create_convergence_plot(self, best_fitness_over_time):
        """
        Creates a convergence plot using Matplotlib based on the given fitness over time.

        Args:
            best_fitness_over_time (list): A list of best fitness values over generations.

        Returns:
            None
        """
        plt.figure(figsize=(10, 6))
        plt.plot(best_fitness_over_time, label='Best Fitness')
        plt.xlabel('Generation')
        plt.ylabel('Fitness')
        plt.title('GA Convergence Plot')
        plt.legend()
        plt.grid(True)
        plt.savefig("post_processing/outputs/convergence_plot.png")

if __name__ == "__main__":
    file_path = 'post_processing/inputdata.txt'
    data_dict = {}
    with open(file_path, 'r') as file:
        lines = file.readlines()

    for line in lines:
        key, value = line.split(':')
        key = key.strip()
        value = value.strip()
        if key == "Vector":
            value = list(map(int, value.split()))
        elif key == "Fitnesses":
            value = list(map(float, value.split()))
        elif key == "Num units":
            value = int(value)
        else:
            value = float(value)
        data_dict[key] = value

    graph_creator = PostProcessor()
    graph_creator.create_graph(data_dict['Vector'], data_dict['Num units'], data_dict["Performance"], data_dict["Recovery"], data_dict["Grade"])
    graph_creator.create_convergence_plot(data_dict['Fitnesses'])
  
