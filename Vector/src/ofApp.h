#pragma once

#include "ofMain.h"

#include "Coordinates.h"
#include "VectorField.h"

using namespace std;



class ofApp : public ofBaseApp {
  public:
  
  static const int CLICK=0;
  static const int DRAG=1;
  static const int NONE=-1;

  static const int S_Z=0;
  
  static const int S_S=1;
  
  static const int S_D=2;

  void setup();
  void update();
  void draw();
  void exit();



  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
    
   VectorField* vf;
  ofFloatImage image;
  int which=-1;
  int image_width;
  int image_height, image_max_width, image_max_height;
  
  ofTrueTypeFont  verdana;                                                     
  float img_w=0;
  float img_h=0;
  float img_internal_x=0;
  float img_internal_y=0;

  vector<ofPolyline> streamlines;
  
  int slider_height=300;
  int slider_width=5;
  int zoom_amount_picker_size=15;
  float zoom_amount=1;
  float zoom_x, zoom_y;

  float start_dt, end_dt;
  float start_step_num, end_step_num;
  int step_picker=15;
  int dt_picker=15;
  float dt_amount;
  float steps_num;
  float dt_x, dt_y;
  float step_x, step_y;
  float color_enabled_x=1200, color_enabled_y=50;
  float color_size=15;
  bool color_b;
  int font_size=15;

  int mouse_mode=NONE;
 
    
  ofTrueTypeFont  verdana1;                                                     
                                                                               

  int font_size1=10;

   
  int tick_count=6;
 
    
  int legend_height=20;
  int legend_width=400;


  int legend_x;
  int legend_y;
  ofFloatImage legend;
  float* legend_data;

};
