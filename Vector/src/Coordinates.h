#pragma once                                                                                                                                                                                                                 
                                                                                                                                                                                                                               
#include <string>                                                                                                                                                                                                              
#include <vector>                                                                                                                                                                                                              
                                                                                                                                                                                                                               
using namespace std;                                                                                                                                                                                                           
                                                                                                                                                                                                                               
                                                                                                                                                                                                                               
class Coordinates
{
public:
  double x_min, x_max;
  double y_min,y_max;


  Coordinates(double x_min, double x_max, double y_min, double y_max);
  
  
};
