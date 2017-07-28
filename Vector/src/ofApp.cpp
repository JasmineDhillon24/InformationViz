

#include "ofApp.h"





//--------------------------------------------------------------
void ofApp::setup(){

  ofBackground(200,200,200);                                                    
  ofTrueTypeFont::setGlobalDpi(72);                                             
  verdana.load("verdana.ttf", font_size, true, true);                           
  verdana.setLineHeight(38.0f);                                                 
  verdana.setLetterSpacing(1.037);                                              

  verdana1.load("verdana.ttf", font_size1, true, true);                           
  verdana1.setLineHeight(38.0f);                                                 
  verdana1.setLetterSpacing(1.037);                                              

  
  vf = new VectorField();
  image_max_width= 0.8f*ofGetScreenWidth();
  image_max_height= 0.8f*ofGetScreenHeight();

  vf->set_max_height(image_max_height);
  vf->set_max_width(image_max_width);
  vf->read_data(ofToDataPath("cosine.vti").c_str());
  image_width=vf->get_width();
  image_height=vf->get_height();
  image.setFromPixels(vf->get_data(), image_width, image_height,
		      vf->is_color_enabled()?OF_IMAGE_COLOR:OF_IMAGE_GRAYSCALE);

  
  //  float dt;
  float world_coord=MAX(vf->get_world_coordinates()->x_max,vf->get_world_coordinates()->x_max);
  dt_amount=0.001*world_coord;
  steps_num=5000;
  start_dt= 0.0001f*world_coord;
  end_dt=0.01f*world_coord;
  start_step_num=1000;
  end_step_num=20000;

  dt_x=550;
  dt_y=ofGetScreenHeight()-50;
  step_x=dt_x+100+slider_height;
  step_y=ofGetScreenHeight()-50;
  zoom_x=ofGetScreenWidth()-50;
  zoom_y=(ofGetScreenHeight()/2.0f -slider_height/2.0f);

  
  img_w=image_width;
  img_h=image_height;
  img_internal_x=0;
  img_internal_y=0;
  if(img_w>image_max_width){
    img_w=image_max_width;
    img_internal_x=(image_width/2.0f-img_w/2.0f);
  }
  if(img_h>image_max_height){
    img_h=image_max_height;
    img_internal_y=(image_height/2.0f-img_h/2.0f);
  }
  vf->set_internal_points(img_internal_x,img_internal_y);

    legend_x=(ofGetScreenWidth()/2.0f)-(legend_width/2.0f)-400;
    legend_y=ofGetScreenHeight()-(3*legend_height)+15;
  if(!vf->is_color_enabled()) {

    legend_data=new float[legend_height*legend_width];

    int count=0;
    for(int j=0;j<legend_height;j++){
      for(int i=0;i<legend_width;i++){

	legend_data[count]=1-(i/(float)legend_width);
    
	count++;

      }

    }
    legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_GRAYSCALE);
  } else {

    legend_data=new float[legend_height*legend_width*3];

    int count=0;
    for(int j=0;j<legend_height;j++){
      for(int i=0;i<legend_width;i++){

	float r=1-(i/(float)legend_width);
	
	legend_data[count]=vf->get_start_color().r + r*(vf->get_end_color().r-vf->get_start_color().r);
	legend_data[count+1]=vf->get_start_color().g + r*(vf->get_end_color().g-vf->get_start_color().g);
	legend_data[count+2]=vf->get_start_color().b + r*(vf->get_end_color().b-vf->get_start_color().b);
    
	count+=3;

      }

    }
    legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_COLOR);

  }

  color_b=true;
 }



//--------------------------------------------------------------
void ofApp::update(){
}






//--------------------------------------------------------------
void ofApp::draw() {


  ofSetColor(255, 255, 255);
  image.drawSubsection(50,50,img_w,img_h,img_internal_x,img_internal_y);


  ofSetColor(0);
  ofDrawRectangle(zoom_x,zoom_y, slider_width, slider_height);
  float picker_pos= zoom_y+(zoom_amount-1)*slider_height;
  ofSetColor(90,180,172);
  ofDrawRectangle(zoom_x-5, picker_pos, zoom_amount_picker_size, zoom_amount_picker_size);
  ofSetColor(0);
  verdana.drawString("Slide to Zoom",zoom_x-60 ,zoom_y-40 );
  verdana1.drawString("1X",zoom_x-10 ,zoom_y-10 );
  verdana1.drawString("2X",zoom_x-5 ,zoom_y+slider_height+20 );
  


  ofSetColor(0);
  ofDrawRectangle(dt_x,dt_y, slider_height, slider_width);

  float picker_pos1= dt_x+(dt_amount-start_dt)/(end_dt-start_dt)*slider_height;
  ofSetColor(90,180,172);
  ofDrawRectangle(picker_pos1, dt_y-5, dt_picker,dt_picker);
  ofSetColor(0);
  verdana.drawString("Slide to Adjust DT",dt_x+60 ,dt_y-20 );
  verdana1.drawString("0.0001",dt_x-20 ,dt_y-5 );
  verdana1.drawString("0.01",dt_x+10+slider_height ,dt_y-5 );
  

  ofSetColor(0);
  ofDrawRectangle(step_x,step_y, slider_height, slider_width);
  float picker_pos2= step_x+(steps_num-start_step_num)/( end_step_num-start_step_num )*slider_height;
  ofSetColor(90,180,172);
  ofDrawRectangle(picker_pos2, step_y-5, step_picker,step_picker);
  ofSetColor(0);
  verdana.drawString("Slide to Adjust Steps",step_x+60 ,step_y-20 );
  verdana1.drawString("1000",step_x-20 ,step_y-5 );
  verdana1.drawString("20000",step_x+10+slider_height ,dt_y-5 );

  
  
  ofSetColor(255, 255, 255);
  
  legend.draw(legend_x,legend_y);


  ofSetColor(0);
  char s[150];
  sprintf(s,"world:<%d,%d>x<%d,%d>\nscreen<%d,%d>x<%d,%d>\ndata<%d,%d>x<%d,%d>",
	  (int)vf->get_world_coordinates()->x_min,(int)vf->get_world_coordinates()->x_max,(int)vf->get_world_coordinates()->y_min,(int)vf->get_world_coordinates()->y_max,
	  (int)vf->get_screen_coordinates()->x_min,(int)vf->get_screen_coordinates()->x_max,(int)vf->get_screen_coordinates()->y_min,(int)vf->get_screen_coordinates()->y_max,
	  (int)vf->get_data_coordinates()->x_min,(int)vf->get_data_coordinates()->x_max,(int)vf->get_data_coordinates()->y_min,(int)vf->get_data_coordinates()->y_max);
  verdana1.drawString(s, zoom_x-150,zoom_y+200);

  double* mag1;
  mag1=vf->get_mag();

  ofSetColor(0);
  float tick_offset=legend_width/(float)(tick_count+1);
  float range_offset=(float)(mag1[1]-mag1[0])/(float)(tick_count+1);

  for(int i=0;i<tick_count+2;i++){
    float val=(float)mag1[0]+range_offset*i;
    string val_str=to_string(val);
    string sub=val_str.substr(0,4);
    float str_width=verdana.stringWidth(sub);
    verdana1.drawString(sub,legend_x+tick_offset*i-str_width*0.5f,ofGetScreenHeight()-60);

  }
  if(!vf->is_color_enabled())  
    ofSetColor(0);
  
  else
    ofSetColor(90,180,172);

  ofDrawRectangle(color_enabled_x, color_enabled_y, color_size, color_size);
  ofSetColor(0);
  verdana.drawString("Change Color",color_enabled_x-50 , color_enabled_y-10);
  
  ofPushMatrix();
  ofTranslate(50,50);
  ofSetColor(255,0,0);
  for(int i=0; i<streamlines.size();i++){

    streamlines[i].draw();
    
  }
  ofPopMatrix();
  
}

void ofApp::exit() {
}






//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key==OF_KEY_LEFT || key==OF_KEY_RIGHT){
    if(image_width> image_max_width){
      if(key==OF_KEY_LEFT){
	img_internal_x-=5;
      }
      else{
	img_internal_x+=5;
      }

      if(img_internal_x>image_width-image_max_width){
	img_internal_x=image_width-image_max_width;
      }
      else if(img_internal_x<0){
	img_internal_x= 0;
      }
      vf->set_internal_points(img_internal_x,img_internal_y);
      streamlines= vf->map_streamlines_to_screen();
	  
    }

  }
else if(key==OF_KEY_UP || key==OF_KEY_DOWN){
    if(image_height> image_max_height){
      if(key==OF_KEY_UP){
	img_internal_y-=5;
      }
      else{
	img_internal_y+=5;
      }
      
      if(img_internal_y>image_height-image_max_height){
	img_internal_y=image_height-image_max_height;
      }
      else if(img_internal_y<0){
	img_internal_y= 0;
      }
	
    }
    
    vf->set_internal_points(img_internal_x,img_internal_y);
    streamlines=vf->map_streamlines_to_screen();

 } else if(key=='r'){
  streamlines.clear();
  vf->remove_lines();
 }


  
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

  if(mouse_mode==CLICK){

    mouse_mode=DRAG;
  }

  if(mouse_mode==DRAG){
    if(which==S_Z){
    zoom_amount=1+(y-zoom_y)/(float)slider_height;

    if(zoom_amount<1){
      zoom_amount=1;
    } else if(zoom_amount>2){
      zoom_amount=2;
    }

    }
    else if(which==S_D){
      dt_amount=start_dt+((x-dt_x)/(float)slider_height)*(end_dt-start_dt);

      if(dt_amount<start_dt){
	dt_amount=start_dt;
	
      }
      else if(dt_amount>end_dt){
	dt_amount=end_dt;
      }
    }
    
    else if(which==S_S){
      steps_num=start_step_num+((x-step_x)/(float)slider_height)*(end_step_num-start_step_num);

      if(steps_num<start_step_num){
	steps_num=start_step_num;
	
      }
      else if(steps_num>end_step_num){
	steps_num=end_step_num;
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

  float picker_pos= zoom_y+(zoom_amount-1)*slider_height;
  if(x>=zoom_x-5 && x<=zoom_x-5+zoom_amount_picker_size && y>= picker_pos && y<= picker_pos + zoom_amount_picker_size){
    which=S_Z;
    mouse_mode=CLICK;
    zoom_amount=1+(y-zoom_y)/(float)slider_height;
    return;
  }

   float picker_pos1= dt_x+(dt_amount-start_dt)/(end_dt-start_dt)*slider_height;
  if(y>=dt_y && y<=dt_y+dt_picker && x>= picker_pos1 && x<= picker_pos1 + dt_picker){
    which=S_D;
    mouse_mode=CLICK;
    dt_amount=start_dt+((x-dt_x)/(float)slider_height)*(end_dt-start_dt);
  
    return;
  }

  float picker_pos2= step_x+(steps_num-start_step_num)/( end_step_num-start_step_num )*slider_height;
  if(y>=step_y && y<=step_y+step_picker && x>= picker_pos2 && x<= picker_pos2 + step_picker){
    which=S_S;
    mouse_mode=CLICK;
    steps_num=start_step_num+((x-step_x)/(float)slider_height)*(end_step_num-start_step_num);
    return;
  }

  if(x>=50 && x<=50+img_w && y>=50 && y<=50+img_h){
    ofVec2f seed;
    seed.x=x-50+img_internal_x;
    seed.y=y-50+img_internal_y;

    
    vf->integrate(seed, dt_amount, (int)steps_num);
    streamlines= vf->map_streamlines_to_screen();
  }
  if(x>=1200 && x<=1215 && y>=50 && y<=65){
    color_b=!color_b;
    vf->change_color(color_b);
    vf->set_color_enabled(color_b);
    image.setFromPixels(vf->get_data(), image_width, image_height,
		      vf->is_color_enabled()?OF_IMAGE_COLOR:OF_IMAGE_GRAYSCALE);

    if(!vf->is_color_enabled()) {

      legend_data=new float[legend_height*legend_width];

      int count=0;
      for(int j=0;j<legend_height;j++){
	for(int i=0;i<legend_width;i++){

	  legend_data[count]=1-(i/(float)legend_width);
    
	  count++;

	}

      }
      legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_GRAYSCALE);
    } else {

      legend_data=new float[legend_height*legend_width*3];

      int count=0;
      for(int j=0;j<legend_height;j++){
	for(int i=0;i<legend_width;i++){

	  float r=1-(i/(float)legend_width);
	
	  legend_data[count]=vf->get_start_color().r + r*(vf->get_end_color().r-vf->get_start_color().r);
	  legend_data[count+1]=vf->get_start_color().g + r*(vf->get_end_color().g-vf->get_start_color().g);
	  legend_data[count+2]=vf->get_start_color().b + r*(vf->get_end_color().b-vf->get_start_color().b);
    
	  count+=3;

	}

      }
      legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_COLOR);

    }

  }


  
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

  if(mouse_mode==CLICK || mouse_mode==DRAG){
    if(which==S_Z){
    zoom_amount=1+(y-zoom_y)/(float)slider_height;
    if(zoom_amount<1){
      zoom_amount=1;
    } else if(zoom_amount>2){
      zoom_amount=2;
    }

    vf->zoom(zoom_amount);
    image_width=vf->get_width();
    image_height=vf->get_height();
    image.setFromPixels(vf->get_data(), image_width, image_height,
			vf->is_color_enabled()?OF_IMAGE_COLOR:OF_IMAGE_GRAYSCALE);

    img_w=image_width;
    img_h=image_height;
    img_internal_x=0;
    img_internal_y=0;
    if(img_w>image_max_width){
      img_w=image_max_width;
      img_internal_x=(image_width/2.0f-img_w/2.0f);
    }
    if(img_h>image_max_height){
      img_h=image_max_height;
      img_internal_y=(image_height/2.0f-img_h/2.0f);
    }
    vf->set_internal_points(img_internal_x, img_internal_y);
    streamlines= vf->map_streamlines_to_screen();
    }
    else if(which==S_D){
      dt_amount=start_dt+((x-dt_x)/(float)slider_height)*(end_dt-start_dt);

      if(dt_amount<start_dt){
	dt_amount=start_dt;
	
      }
      else if(dt_amount>end_dt){
	dt_amount=end_dt;
      }
    }
    
    else if(which==S_S){
      
      steps_num=start_step_num+((x-step_x)/(float)slider_height)*(end_step_num-start_step_num);
      if(steps_num<start_step_num){
	steps_num=start_step_num;
	
      }
      else if(steps_num>end_step_num){
	steps_num=end_step_num;
      }
    }


    
    mouse_mode=NONE;
    
  
  
  }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
