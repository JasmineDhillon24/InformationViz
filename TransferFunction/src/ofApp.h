#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "volumeRenderThread.h"
#include "ImageReader.h"

using namespace std;



class ofApp : public ofBaseApp {
  public:
  
  static const int CLICK=0;
  static const int DRAG=1;
  static const int NONE=-1;

  static const int COLOR=0;

  static const int RANGE=1;
  static const int OPACITY=2;
  static const int NO=-1;
  static const int MIN=3;
  static const int MAX=4;


    int which_p=NONE;
    void setup();
    void update();
    void draw();
    void exit();
    void updateIsovalue();
    void toggleShading(bool& shadeOn);



    double range[2];
    double selected_range[2];
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

    bool startedVTK;
    volumeRenderThread vr;

    ofEasyCam cam;

  
    ofTrueTypeFont  verdana;                                                     
                                                                               

    int font_size=13;

    float range_x=75;
    float range_y=20;
    float range_width=400;
    float range_height=5;

    float  range_picker=10;

    int mouse_mode=NONE;
    int who=NO;
    
    ofTrueTypeFont  verdana1;                                                     
                                                                               

    int font_size1=10;

    bool show_log=false;


    
    int tick_x_count=6;
    int tick_y_count=3;
    
    int agg_min;
    int agg_max;
    float histogram_width = 400;
    float histogram_height = 150;
    float histogram_x=75;
    float histogram_y=50;




    float log_b_w=20;
    float log_b_h=20;
    float log_b_x=histogram_x;
    float log_b_y=histogram_y+histogram_height+20;



    
    int color_height=20;
    int color_width=400;


    int color_x=histogram_x;
    int color_y=log_b_y+50;
    ofFloatImage color;
    float* color_data;


    int opacity_x=histogram_x;
    int opacity_y=color_y+color_height+50;
    int opacity_width=histogram_width;
    int opacity_height=histogram_height;
    int opacity_click_index=-1;
    int color_click_index=-1;
    
    ofImage color_refresh;
    ofImage opacity_refresh;
    float color_refresh_x=color_x+40+color_width;
    float color_refresh_y=color_y+(0.5*color_height)-15;
    float opacity_refresh_x=opacity_x+40+opacity_width;
    float opacity_refresh_y=opacity_y+opacity_height-30;
    int refresh_size=30;
    
    
    void refresh_color_tf();
    vector<pair<int,ofFloatColor>> color_tf_points;


    vector<pair<int,float>> opacity_tf_points;


    
    vector<int> aggregate_values;

};
