#pragma once

#include <string>
#include <vtkSmartPointer.h>                                                                                                       
#include <vtkImageData.h>                                                                                                          
#include <vtkXMLImageDataReader.h>                                                                                                 
#include <vtkPointData.h>                                                                                                          
#include <vtkDataArray.h>                                                                                                        
#include <vector>
#include "ofMain.h"

using namespace std;

class ImageReader
{
 public:
 int dims[3];
 float* data;
   double range[2];
  void read_data(string file);
  int aggregate_min, aggregate_max;
  inline int get_aggregate_min()
  {
    return aggregate_min;
  }
  inline int get_aggregate_max()
  {
    return aggregate_max;
  }
  
  vector<int> aggregate_values;
  vtkSmartPointer<vtkImageData> image;
  inline  vtkSmartPointer<vtkImageData> get_image_data(){
    return image;
  }
  inline vector<int> get_aggregate_values() {
    return aggregate_values;
  }
  inline float* get_data(){
    return data;
  }
  inline int* get_dims(){
    return dims;
  }
  inline double* get_range(){
    return range;
  }
};
