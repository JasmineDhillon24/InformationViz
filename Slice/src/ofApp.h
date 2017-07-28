#pragma once

#include "ofMain.h"
#include "ImageReader.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp
{
  public:

  const static int X = 0;
  const static int Y = 1;
  const static int Z = 2;
  
  const static int R = 0;
  const static int G = 1;
  const static int B = 2;

  const static int F=1;
  const static int E=2;
  
  ofTrueTypeFont  verdana;                                                                                                                                                                                       
  int font_size=10;
  int chosen_file=F;

  int legend_height=10;
  int legend_width=400;
  ImageReader r;
  ofFloatImage legend;
  float* legend_data;
  ofVboMesh mesh;
  ofFloatImage image;
  ofEasyCam easycam;
  ofPlanePrimitive plane_x;
  ofPlanePrimitive plane_y;
  ofPlanePrimitive plane_z;
  float plane_x_pos;
  float plane_y_pos;
  float plane_z_pos;

  float x_pos;
  float y_pos;
  float z_pos;

  int tick_count=5;

  float* data;
  int* dims;
  double* range;
  ofxToggle color;

  int file_button_x = 30;
  int file_button_y = 200;
  int file_button_height = 40;
  int file_button_width = 120;
  ofColor button_bg_color;

  int slice_button_x = 30;
  int slice_button_y = 290;
  int slice_button_height = 40;
  int slice_button_width = 120;

  bool show_slice = false;

  int color_start[3]={237,248,177};
  int color_end[3]={44,127,184};
  void load_file();
  void on_slice_clicked();
  int slice_axis;
  float slice_val;
  void on_file_clicked(); 
  ofxPanel panel;
  ofxPanel panel2;
  ofxFloatSlider sliderx;
  ofxFloatSlider slidery;
  ofxFloatSlider sliderz;
  void move_plane_x(float &new_x);
  void move_plane_y(float &new_y);
  void move_plane_z(float &new_z);
  

    void setup  ();
    void update ();
    void draw   ();
    void exit   ();

    void keyPressed      (ofKeyEventArgs&);
    void keyReleased     (ofKeyEventArgs&);

    void mouseMoved      (ofMouseEventArgs&);
    void mouseDragged    (ofMouseEventArgs&);
    void mousePressed    (ofMouseEventArgs&);
    void mouseReleased   (ofMouseEventArgs&);
    void mouseScrolled   (ofMouseEventArgs&);
    void mouseEntered    (ofMouseEventArgs&);
    void mouseExited     (ofMouseEventArgs&);

    void touchDown       (ofTouchEventArgs&);
    void touchMoved      (ofTouchEventArgs&);
    void touchUp         (ofTouchEventArgs&);
    void touchDoubleTap  (ofTouchEventArgs&);
    void touchCancelled  (ofTouchEventArgs&);

    void windowResized   (ofResizeEventArgs&);
    void dragged         (ofDragInfo&);
    void messageReceived (ofMessage&);
};
