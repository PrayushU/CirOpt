#include <cmath>
#include <iostream>
// #include <chrono>
#include "CSimulator.h"
// using namespace std::chrono;

int main(int argc, char * argv[])
{

      // dummy vector. Replace in your code with the actual circuit vector.
      int vec1[] = {0, 1, 2, 3, 4, 5, 6, 0, 1, 1, 2, 2, 3, 0, 1, 0}  ;

      // dummy vector. Replace in your code with the actual circuit vector.
      int vec2[] = {0, 2, 4, 6, 0, 2, 4, 1, 3, 0, 5, 5, 3, 5, 0, 6 }  ;
      int vector[16] = {0, 1, 3, 2, 4, 4, 3, 1, 3, 6, 1, 1, 0, 5, 1, 1}; 

      double result = 0.0;
      // Test value based on stub Evaluate_Circuit function.
      // Replace with actual performance value.
      
            result = Evaluate_Circuit(1e6, 1.0e-6, 16, vector);
            std::cout << "Evaluate_Circuit(16, vector) = "<< result <<"\n";

      //compare the parallel result with serial result 
      if (std::fabs(result - 167.378)<0.001) {
                  std::cout << "pass\n";
            } else {
	        std::cout << "fail\n";
              return 1;
           }

      result =  Evaluate_Circuit(1e6, 1.0e-6, 16, vec1);
      std::cout << "Evaluate_Circuit(16, vec1) = "<< result<<"\n";

      result =  Evaluate_Circuit(1e6, 1.0e-6, 16, vec2);
      std::cout << "Evaluate_Circuit(16, vec2) = "<< result<<"\n";

	
}