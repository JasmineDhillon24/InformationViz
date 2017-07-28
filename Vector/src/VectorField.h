#pragma once

#include <string>
#include <vtkSmartPointer.h>                                                                                                       
#include <vtkImageData.h>                                                                                                          
#include <vtkXMLImageDataReader.h>                                                                                                 
#include <vtkPointData.h>                                                                                                          
#include <vtkDataArray.h>                                                                                                        
#include <vector>
#include "ofMain.h"
#include "Coordinates.h"

using namespace std;



class VectorField
{
 public:


  Coordinates* c_world;
  Coordinates* c_data;
  Coordinates* c_screen;
  inline Coordinates* get_world_coordinates() {
    return c_world;
  }
  inline Coordinates* get_data_coordinates() {
    return c_data;
  }
  inline Coordinates* get_screen_coordinates() {
    return c_screen;
  }  
  double* mag;
  double origin[3];
  double spacing[3];

  int dims[3];
  ofVec2f* data;
  int max_height, max_width;
  int width, height;
  void measure();
  void read_data(string file);
  void integrate(ofVec2f seed, double dt, int step_count);

  bool color_enabled=false;
  ofFloatColor start_color;
  ofFloatColor end_color;
  vector<ofPolyline> streamlines_world;
  ofVec2f interpolate(ofVec2f s_point);
  vector<ofPolyline> map_streamlines_to_screen();
  int start_height, start_width;
  float *img_data;
  float img_internal_x, img_internal_y;
  void remove_lines();
  inline void set_internal_points(float x, float y){
    img_internal_x=x;
    img_internal_y=y;
  }

  inline bool is_color_enabled() {
    return color_enabled;
  }
  inline void change_color(bool color_b){
    color_enabled!=color_b;
  }

  inline ofFloatColor get_start_color() {
    return start_color;
  }

  inline ofFloatColor get_end_color() {
    return end_color;
  }
  void set_color_enabled(bool enabled);
  
  vtkSmartPointer<vtkImageData> image;
  inline  vtkSmartPointer<vtkImageData> get_image_data(){
    return image;
  }

  inline double* get_mag(){
    return mag;
  }
 
  inline float* get_data(){
    return img_data;
  }
  inline int* get_dims(){
    return dims;
  }

   inline void set_max_height(int h){
     max_height=h;
  }
   inline void set_max_width(int w){
     max_width=w;
  }
    inline int get_width()
  {
    return width;
  }
  inline int get_height(){
    return height;
  }
  void zoom(float zoom_amount);
  
 
};
