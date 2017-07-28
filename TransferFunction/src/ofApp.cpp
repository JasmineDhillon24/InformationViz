

#include "ofApp.h"





//--------------------------------------------------------------
void ofApp::setup(){

ofBackground(255,255,255);                                                    
  ofTrueTypeFont::setGlobalDpi(72);                                             
  verdana.load("verdana.ttf", font_size, true, true);                           
  verdana.setLineHeight(38.0f);                                                 
  verdana.setLetterSpacing(1.037);                                              

  verdana1.load("verdana.ttf", font_size1, true, true);                           
  verdana1.setLineHeight(38.0f);                                                 
  verdana1.setLetterSpacing(1.037);                                              

  

  vr.setup(ofToDataPath("tooth.vti").c_str());
  range[0]=vr.ir.get_range()[0];
  range[1]=vr.ir.get_range()[1];
  selected_range[0]=range[0];
  selected_range[1]=range[1]; 
  aggregate_values=vr.ir.get_aggregate_values();
  agg_min=vr.ir.get_aggregate_min();
  agg_max=vr.ir.get_aggregate_max();

  color_data=new float[color_height*color_width*3];

  
  startedVTK = false;

  ofFloatColor start;
  ofFloatColor end;
  ofFloatColor middle;
 

  start.set(0.56,0.40,0.07);
  end.set(0.13, 0.58,0.58);
  middle.set(0.96,0.96,0.96);
  pair<int, ofFloatColor> start_pt, end_pt, middle_pt;
  start_pt.second=start;
  end_pt.second=end;
  middle_pt.second=middle;
  
  start_pt.first=selected_range[0];
  end_pt.first=selected_range[1];
  middle_pt.first= selected_range[0]+ ((selected_range[1]-selected_range[0])*0.5);

  color_tf_points.push_back(start_pt);
  color_tf_points.push_back(middle_pt);
  color_tf_points.push_back(end_pt);

  refresh_color_tf();

  color_refresh.load("refresh.png");
  opacity_refresh.load("refresh.png");  
  
  pair<int,float> start_op, middle_op, end_op;
  start_op.second=0.0f;
  end_op.second=1.0f;
  middle_op.second=0.5f;
  
  start_op.first=selected_range[0];
  end_op.first=selected_range[1];
  middle_op.first= selected_range[0]+ ((selected_range[1]-selected_range[0])*0.5);

  opacity_tf_points.push_back(start_op);
  opacity_tf_points.push_back(middle_op);
  opacity_tf_points.push_back(end_op);

}



//--------------------------------------------------------------
void ofApp::update(){
}






//--------------------------------------------------------------
void ofApp::draw() {

  ofSetColor(127,191,123);
  ofDrawRectangle(range_x,range_y,range_width,range_height);
  float min_x=ofMap(selected_range[0],range[0], range[1],0, range_width );
  float max_x=ofMap(selected_range[1],range[0], range[1],0, range_width );


  

  ofSetColor(0);
  ofDrawRectangle(range_x + min_x-0.5*range_picker, range_y+0.5*range_height-0.5*range_picker, range_picker, range_picker);
  ofDrawRectangle(range_x + max_x-0.5*range_picker, range_y+0.5*range_height-0.5*range_picker, range_picker, range_picker);
  verdana.drawString("Adjust data range",15,15 );



  
  ofSetColor(0);
  int tick_count=5;
  float tick_offset=range_width/tick_count;
  for(int i=0; i<=tick_count;i++){

    int val = ofMap(i*tick_offset,0, range_width, range[0], range[1] );
    verdana1.drawString(to_string(val), range_x+i*tick_offset, range_y+20);

  }

  
  ofSetColor(255,255,255);
  ofDrawRectangle(histogram_x, histogram_y, histogram_width, histogram_height);
  ofSetColor(0);
  ofVec3f o,x,y;
  o.x=histogram_x;
  o.y= histogram_y+histogram_height;
  o.z=0;
  x.x=histogram_x+histogram_width;
  x.y= histogram_y+histogram_height;
  x.z=0;
  y.x=histogram_x;
  y.y= histogram_y;
  y.z=0;
	
  ofDrawArrow(o,x,3.5);
  ofDrawArrow(o,y,3.5);

  if(show_log)
    ofSetColor(127,191,123);
  else
    ofSetColor(180,180,180);
  ofDrawRectangle(log_b_x, log_b_y, log_b_w, log_b_h);

  ofSetColor(0);
  verdana.drawString("Enable Log Scale", log_b_x+log_b_w+10,log_b_y+log_b_h-5);
  
  ofSetColor(127,191,123);

  float rect_width=histogram_width/(float) (selected_range[1]-selected_range[0]);
  for(int i=0; i<selected_range[1]-selected_range[0];i++)
    {
        float h;
      if(!show_log){
      h= ofMap(aggregate_values[selected_range[0]+i], agg_min, agg_max, 0, histogram_height);
    
      }
      else
	{
	  int val=aggregate_values[selected_range[0]+i];
	  if (val!=0){
	    h= ofMap(log(val), log(MAX(agg_min,1)), log(MAX(agg_max,1)), 0, histogram_height);

	  }
	  else
	    {
	      h=0;
	    }
	}
        ofDrawRectangle(o.x+i*rect_width, o.y-h, rect_width, h);
    }
  ofSetColor(0);
  float tick_x_offset= histogram_width/(tick_x_count);
  for(int i=0; i<=tick_x_count;i++){
    int val= (int)ofMap(i*tick_x_offset, 0, histogram_width, selected_range[0], selected_range[1]);
    string str= to_string(val);
    verdana1.drawString(str,histogram_x+i*tick_x_offset,histogram_y+histogram_height+10 );
  }
  float tick_y_offset= histogram_height/(tick_y_count);
 
  for(int i=0; i<=tick_y_count;i++){
    int val;
    string str;
    if(show_log)
      {
	val= (int)ofMap(i*tick_y_offset, 0, histogram_height, log(MAX(agg_min,1)), log(MAX(agg_max,1)));
	if(val==0){
	  val=1;
	}
	str= to_string(val);

      }
    else
      {
	val= (int)ofMap(i*tick_y_offset, 0, histogram_height, agg_min, agg_max);
	str= to_string(val);

      }

    verdana1.drawString(str,histogram_x-45,histogram_y+histogram_height-(i*tick_y_offset));
  }


  ofSetColor(255,255,255);
  color.draw(color_x, color_y);

  if((mouse_mode == CLICK || mouse_mode == DRAG) && who == RANGE) {
    // don't draw
  } else {
    ofSetColor(0);
    for(int i=0; i<color_tf_points.size();i++){
      float x_pos=ofMap(color_tf_points[i].first, selected_range[0], selected_range[1], color_x, color_x+ color_width);
      ofDrawRectangle(x_pos-4, color_y+0.5*color_height-4, 8,8);
    }
  }

  ofSetColor(255,255,255);
  color_refresh.draw(color_refresh_x, color_refresh_y, refresh_size, refresh_size);
  

  //opacity histogram


  
  ofSetColor(255,255,255);
  ofDrawRectangle(opacity_x, opacity_y,opacity_width, opacity_height);
  ofSetColor(0);
  // ofVec3f o,x,y;
  ofVec3f y1,o1;
  
  o.x=opacity_x;
  o.y= opacity_y+opacity_height;
  o.z=0;
  x.x=opacity_x+opacity_width;
  x.y= opacity_y+opacity_height;
  x.z=0;
  y.x=opacity_x;
  y.y= opacity_y;
  y.z=0;
  y1.x=opacity_x+opacity_width;
  y1.y=opacity_y;
  y1.z=0;

  o1.x=opacity_x+opacity_width;
  o1.y= opacity_y+opacity_height;
  o1.z=0;
 
  ofDrawArrow(o,x,3.5);
  ofDrawArrow(o,y,3.5);
  ofDrawArrow(o1,y1,3.5);

	       // ofSetColor(0,255,0);

 rect_width=opacity_width/(float) (selected_range[1]-selected_range[0]);
  for(int i=0; i<selected_range[1]-selected_range[0];i++)
    {
      ofFloatColor color;
     ofFloatColor start_color, end_color;
     int start_pt,end_pt;
     int data_pt = selected_range[0]+i;

 
     for(int k=1;k<color_tf_points.size();k++) {
       if(data_pt < color_tf_points[k].first) {
	 start_color = color_tf_points[k-1].second;
	 end_color = color_tf_points[k].second;
	 start_pt=color_tf_points[k-1].first;
	 end_pt=color_tf_points[k].first;
	 break;
       }
     }

     float ratio = (data_pt-start_pt)/(float)(end_pt-start_pt);
     if(start_color.r<end_color.r){
     color.r=start_color.r + ratio*(end_color.r-start_color.r);
     color.g=start_color.g + ratio*(end_color.g-start_color.g);
     color.b=start_color.b + ratio*(end_color.b-start_color.b);
     }
     else
       {
	 color.r=start_color.r - ratio*(start_color.r-end_color.r);
	 color.g=start_color.g - ratio*(start_color.g-end_color.g);
	 color.b=start_color.b - ratio*(start_color.b-end_color.b);
    	 
	 }

     ofSetColor(color);

      float h;
      if(!show_log){
      h= ofMap(aggregate_values[selected_range[0]+i], agg_min, agg_max, 0, opacity_height);
    
      }
      else
	{
	  int val=aggregate_values[selected_range[0]+i];
	  if (val!=0){
	    h= ofMap(log(val), log(MAX(agg_min,1)), log(MAX(agg_max,1)), 0, opacity_height);

	  }
	  else
	    {
	      h=0;
	    }
	}
        ofDrawRectangle(o.x+i*rect_width, o.y-h, rect_width, h);
    }
  ofSetColor(0);
  tick_x_offset= opacity_width/(tick_x_count);
  for(int i=0; i<=tick_x_count;i++){
    int val= (int)ofMap(i*tick_x_offset, 0, opacity_width, selected_range[0], selected_range[1]);
    string str= to_string(val);
    verdana1.drawString(str,opacity_x+i*tick_x_offset,opacity_y+opacity_height+10 );
  }
 tick_y_offset=opacity_height/(tick_y_count);
 
  for(int i=0; i<=tick_y_count;i++){
    int val;
    string str;
    if(show_log)
      {
	val= (int)ofMap(i*tick_y_offset, 0, opacity_height, log(MAX(agg_min,1)), log(MAX(agg_max,1)));
	if(val==0){
	  val=1;
	}
	str= to_string(val);

      }
    else
      {
	val= (int)ofMap(i*tick_y_offset, 0, opacity_height, agg_min, agg_max);
	str= to_string(val);

      }

    verdana1.drawString(str,opacity_x-45,opacity_y+opacity_height-(i*tick_y_offset));

    // right ticks
    float val1=tick_y_offset*i/(float)opacity_height;
    string str1= to_string(val1);
    string sub= str1.substr(0,4);
    verdana1.drawString(sub,opacity_x+opacity_width+5,opacity_y+opacity_height-(i*tick_y_offset));
    
  }
  verdana.drawString("Opacity values",opacity_x+opacity_width+25,opacity_y+opacity_height-(opacity_height*0.5));

  if((mouse_mode == CLICK || mouse_mode == DRAG) && who == RANGE) {
    // don't draw
  } else {
    ofSetColor(0);
    for(int i=0; i<opacity_tf_points.size();i++){
      float x_pos=ofMap(opacity_tf_points[i].first, selected_range[0], selected_range[1], opacity_x, opacity_x+ opacity_width);
      float y_pos=ofMap(opacity_tf_points[i].second, 0, 1, opacity_y+opacity_height, opacity_y);
      ofDrawRectangle(x_pos-4, y_pos-4, 8,8);
      if(i>0 && i<opacity_tf_points.size()){
      float x_pos1=ofMap(opacity_tf_points[i-1].first, selected_range[0], selected_range[1], opacity_x, opacity_x+ opacity_width);
      float y_pos1=ofMap(opacity_tf_points[i-1].second, 0, 1, opacity_y+opacity_height, opacity_y);

      ofDrawLine(x_pos1, y_pos1, x_pos, y_pos);

      }


    }
  }
  ofSetColor(255,255,255);
  opacity_refresh.draw(opacity_refresh_x, opacity_refresh_y,refresh_size, refresh_size);

  
  if (!startedVTK) {
    vr.setupRenderer();
    vr.startThread();
    startedVTK = true;
    updateIsovalue();
  }
 }

void ofApp::exit() {
  vr.stopThread();
  //::exit(0);


  vr.waitForThread();
}




//This function actually runs Marching Cubes using vtk's
//vtkMarchingCubes filter
void ofApp::updateIsovalue() {
  if (startedVTK) {
    //if (vr.lock()) {
      vr.compositeOpacity->RemoveAllPoints();
      for(int i=0;i<opacity_tf_points.size();i++){
	vr.compositeOpacity->AddPoint(opacity_tf_points[i].first,opacity_tf_points[i].second);
      }

      vr.color->RemoveAllPoints();
      for(int i=0;i<color_tf_points.size();i++){
	vr.color->AddRGBPoint(color_tf_points[i].first,color_tf_points[i].second.r,color_tf_points[i].second.g,color_tf_points[i].second.b);
      }

      vr.update();
      //vr.updated = true;
      //vr.unlock();
    //}
  }
}

void ofApp::refresh_color_tf(){
  int  count=0;
 for(int j=0;j<color_height;j++){
   for(int i=0;i<color_width;i++){

     ofFloatColor start_color, end_color;
     int start_pt,end_pt;
     int data_pt = (int)ofMap(i, 0, color_width, selected_range[0], selected_range[1]);

 
     for(int k=1;k<color_tf_points.size();k++) {
       if(data_pt < color_tf_points[k].first) {
	 start_color = color_tf_points[k-1].second;
	 end_color = color_tf_points[k].second;
	 start_pt=color_tf_points[k-1].first;
	 end_pt=color_tf_points[k].first;
	 break;
       }
     }

     float ratio = (data_pt-start_pt)/(float)(end_pt-start_pt);
     if(start_color.r<end_color.r){
     color_data[count]=start_color.r + ratio*(end_color.r-start_color.r);
     color_data[count+1]=start_color.g + ratio*(end_color.g-start_color.g);
     color_data[count+2]=start_color.b + ratio*(end_color.b-start_color.b);
     }
     else
       {
	 color_data[count]=start_color.r - ratio*(start_color.r-end_color.r);
	 color_data[count+1]=start_color.g - ratio*(start_color.g-end_color.g);
	 color_data[count+2]=start_color.b - ratio*(start_color.b-end_color.b);
    	 
	 }
     count+=3;
     
  }

    }
 color.setFromPixels(color_data,color_width,color_height,OF_IMAGE_COLOR);

}


void ofApp::toggleShading(bool& shadeOn) {
  if (startedVTK) {
    //if(vr.lock()) {

      if (shadeOn) {
        vr.volumeProperty->ShadeOn();
      } else {
        vr.volumeProperty->ShadeOff();
      }

      vr.update();
      //vr.updated = true;
      //vr.unlock();
    //}
  }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

    if(who==RANGE){
      if (which_p==MIN){
	selected_range[0]=(int)ofMap(x-range_x, 0, range_width, range[0], range[1]);

	if(selected_range[0]<range[0])
	  selected_range[0]=range[0];


	else if(selected_range[0]>selected_range[1])
	  selected_range[0]=selected_range[1]-5;
      }
      else if(which_p==MAX){

	selected_range[1]=(int)ofMap(x-range_x, 0, range_width, range[0], range[1]);
 
	if(selected_range[1]>range[1])
	  selected_range[1]=range[1];


	else if(selected_range[1]<selected_range[0])
	  selected_range[1]=selected_range[0]+5;

      }
    } else if(who==OPACITY){
      if(x<opacity_x)
	x = opacity_x;
      else if(x>opacity_x+opacity_width)
	x=opacity_x+opacity_width;
      opacity_tf_points[opacity_click_index].first=ofMap(x, opacity_x, opacity_width+opacity_x, selected_range[0], selected_range[1]);
      float opacity = ofMap(y, opacity_y+opacity_height, opacity_y,0,1);
      if(opacity < 0)
	opacity = 0.0f;
      else if(opacity > 1)
	opacity = 1.0f;

      opacity_tf_points[opacity_click_index].second=opacity;
      
    }
    else if(who==COLOR){
      if(x<color_x)
	x = color_x;
      else if(x>color_x+color_width)
	x=color_x+color_width;
      color_tf_points[color_click_index].first=ofMap(x, color_x, color_width+color_x, selected_range[0], selected_range[1]);
      refresh_color_tf();     


    }

  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

  if(x>=color_refresh_x && x<=color_refresh_x+refresh_size && y>=color_refresh_y && y<=color_refresh_y+refresh_size){
          color_tf_points.clear();

      
      ofFloatColor start;
      ofFloatColor end;
      ofFloatColor middle;
 
      start.set(0.56,0.40,0.07);
      end.set(0.13, 0.58,0.58);
      middle.set(0.96,0.96,0.96);



      pair<int, ofFloatColor> start_pt, end_pt, middle_pt;
      start_pt.second=start;
      end_pt.second=end;
      middle_pt.second=middle;
  
      start_pt.first=selected_range[0];
      end_pt.first=selected_range[1];
      middle_pt.first= selected_range[0]+ ((selected_range[1]-selected_range[0])*0.5);

      color_tf_points.push_back(start_pt);
      color_tf_points.push_back(middle_pt);
      color_tf_points.push_back(end_pt);
      updateIsovalue();

      
      //      vr.update();
      return;
  }
  if(x>=opacity_refresh_x && x<=opacity_refresh_x+refresh_size && y>=opacity_refresh_y && y<=opacity_refresh_y+refresh_size){
     
    opacity_tf_points.clear();
    pair<int,float> start_op, middle_op, end_op;
    start_op.second=0.0f;
    end_op.second=1.0f;
    middle_op.second=0.5f;
  
      start_op.first=selected_range[0];
      end_op.first=selected_range[1];
      middle_op.first= selected_range[0]+ ((selected_range[1]-selected_range[0])*0.5);

      opacity_tf_points.push_back(start_op);
      opacity_tf_points.push_back(middle_op);
      opacity_tf_points.push_back(end_op);
      //      vr.update();
      updateIsovalue();

      return;
  }

  if(x>=log_b_x && x<=log_b_x+log_b_w && y>=log_b_y && y<=log_b_y+log_b_h){
    show_log=!show_log;
    return;
  }

  float min_x=ofMap(selected_range[0],range[0], range[1],0, range_width );
  float max_x=ofMap(selected_range[1],range[0], range[1],0, range_width );
  min_x=range_x + min_x-0.5*range_picker;
  max_x=range_x + max_x-0.5*range_picker;

  float min_y=range_y+0.5*range_height-0.5*range_picker;
  float max_y= range_y+0.5*range_height-0.5*range_picker;

  if(x>=min_x && x<=min_x+range_picker && y>= min_y && y<= min_y+range_picker){

    selected_range[0]=(int)ofMap(x-range_x, 0, range_width, range[0], range[1]);
    who=RANGE;
    which_p=MIN;
    mouse_mode=CLICK;
    return;
  }

  if(x>=max_x && x<=max_x+range_picker && y>= max_y && y<= max_y+range_picker){
    selected_range[1]=(int)ofMap(x-range_x, 0, range_width, range[0], range[1]);
    mouse_mode=CLICK;
    which_p=MAX;
    who=RANGE;
    return;
    
  }

  if(x>=opacity_x && x<=opacity_x+opacity_width && y>=opacity_y && y<=opacity_y+opacity_height ){

    mouse_mode=CLICK;
    who=OPACITY;
    opacity_click_index=-1;
    for(int i=0; i<opacity_tf_points.size();i++){
      float x_pos=ofMap(opacity_tf_points[i].first, selected_range[0], selected_range[1], opacity_x, opacity_x+ opacity_width);
      float y_pos=ofMap(opacity_tf_points[i].second, 0, 1, opacity_y+opacity_height, opacity_y);
     
      if(x>=x_pos-4 && x<=x_pos+4 && y>=y_pos-4 && y<=y_pos+4){
	opacity_click_index=i;
	break;
      }	
    }
    if(opacity_click_index==-1){
      pair<int,float> newpt;
      newpt.first=ofMap(x, opacity_x, opacity_width+opacity_x, selected_range[0], selected_range[1]);
      newpt.second=ofMap(y, opacity_y+opacity_height, opacity_y,0,1);

      int pos=0;
      for(int i=0; i<opacity_tf_points.size();i++){
	if(newpt.first < opacity_tf_points[i].first) {
	  pos = i;
	  break;
	}
      }

      opacity_tf_points.insert(opacity_tf_points.begin()+pos, newpt);
      opacity_click_index = pos;

    }
    return;
  }
  
  if(x>=color_x && x<=color_x+color_width && y>=color_y && y<=color_y+color_height ){

    mouse_mode=CLICK;
    who=COLOR;
    color_click_index=-1;
    for(int i=0; i<color_tf_points.size();i++){
      float x_pos=ofMap(color_tf_points[i].first, selected_range[0], selected_range[1], color_x, color_x+ color_width);

     
      if(x>=x_pos-4 && x<=x_pos+4 && y<= color_y+color_height && y>=color_y){
	color_click_index=i;
	break;
      }	
    }
    if(color_click_index==-1){
      pair<int,ofFloatColor> newpt;
      newpt.first=ofMap(x, color_x, color_width+color_x, selected_range[0], selected_range[1]);
      

      int pos=0;
      for(int i=0; i<color_tf_points.size();i++){
	if(newpt.first < color_tf_points[i].first) {
	  pos = i;
	  break;
	}
      }

      ofFloatColor start_color=color_tf_points[pos-1].second;
      ofFloatColor end_color= color_tf_points[pos].second;
      ofFloatColor color;
      float ratio = (newpt.first-color_tf_points[pos-1].first)/(float)(color_tf_points[pos].first-color_tf_points[pos-1].first);
      if(start_color.r<end_color.r){
	color.r=start_color.r + ratio*(end_color.r-start_color.r);
	color.g=start_color.g + ratio*(end_color.g-start_color.g);
	color.b=start_color.b + ratio*(end_color.b-start_color.b);
      }
      else
	{
	  color.r=start_color.r - ratio*(start_color.r-end_color.r);
	  color.g=start_color.g - ratio*(start_color.g-end_color.g);
	  color.b=start_color.b - ratio*(start_color.b-end_color.b);
    	 
	}

      newpt.second=color;
      color_tf_points.insert(color_tf_points.begin()+pos, newpt);
      color_click_index = pos;

    }
    return;
  }
  




  
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

  if(mouse_mode==CLICK || mouse_mode==DRAG){

    
    if(who==RANGE){
      if (which_p==MIN){
	selected_range[0]=(int)ofMap(x-range_x, 0, range_width, range[0], range[1]);

	if(selected_range[0]<range[0])
	  selected_range[0]=range[0];


	else if(selected_range[0]>selected_range[1])
	  selected_range[0]=selected_range[1]-5;
      }
      else if(which_p==MAX){

	selected_range[1]=(int)ofMap(x-range_x, 0, range_width, range[0], range[1]);
 
	if(selected_range[1]>range[1])
	  selected_range[1]=range[1];


	else if(selected_range[1]<selected_range[0])
	  selected_range[1]=selected_range[0]+5;

      }

      color_tf_points.clear();

      
      ofFloatColor start;
      ofFloatColor end;
      ofFloatColor middle;
 
      start.set(0.56,0.40,0.07);
      end.set(0.13, 0.58,0.58);
      middle.set(0.96,0.96,0.96);



      pair<int, ofFloatColor> start_pt, end_pt, middle_pt;
      start_pt.second=start;
      end_pt.second=end;
      middle_pt.second=middle;
  
      start_pt.first=selected_range[0];
      end_pt.first=selected_range[1];
      middle_pt.first= selected_range[0]+ ((selected_range[1]-selected_range[0])*0.5);

      color_tf_points.push_back(start_pt);
      color_tf_points.push_back(middle_pt);
      color_tf_points.push_back(end_pt);

      opacity_tf_points.clear();
      pair<int,float> start_op, middle_op, end_op;
      start_op.second=0.0f;
      end_op.second=1.0f;
      middle_op.second=0.5f;
  
      start_op.first=selected_range[0];
      end_op.first=selected_range[1];
      middle_op.first= selected_range[0]+ ((selected_range[1]-selected_range[0])*0.5);

      opacity_tf_points.push_back(start_op);
      opacity_tf_points.push_back(middle_op);
      opacity_tf_points.push_back(end_op);

      double r[2]={(double)selected_range[0],(double)selected_range[1]};
      vr.color->AdjustRange(r);
      updateIsovalue();


    }
    else if(who==OPACITY){
      if(x<opacity_x)
	x = opacity_x;
      else if(x>opacity_x+opacity_width)
	x=opacity_x+opacity_width;
      opacity_tf_points[opacity_click_index].first=ofMap(x, opacity_x, opacity_width+opacity_x, selected_range[0], selected_range[1]);
      float opacity = ofMap(y, opacity_y+opacity_height, opacity_y,0,1);
      if(opacity < 0)
	opacity = 0.0f;
      else if(opacity > 1)
	opacity = 1.0f;
      opacity_tf_points[opacity_click_index].second=opacity;

      updateIsovalue();
      opacity_click_index=-1;
    }

    else if(who==COLOR){

      if(x<color_x)
	x = color_x;
      else if(x>color_x+color_width)
	x=color_x+color_width;

      color_tf_points[color_click_index].first=ofMap(x, color_x, color_width+color_x, selected_range[0], selected_range[1]);

      updateIsovalue();
      refresh_color_tf();
      color_click_index=-1;
		     
    }
    who = NONE;
    which_p = NONE;
    mouse_mode = NONE;
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
