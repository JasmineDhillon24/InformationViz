
#include "ofApp.h"

void ofApp::setup()
{
  ofBackground(255,255,255);
  ofTrueTypeFont::setGlobalDpi(72);
  verdana.load("verdana.ttf", font_size, true, true);
  verdana.setLineHeight(38.0f);
  verdana.setLetterSpacing(1.037);


 //color.addListener(this, &ofApp::on_color_clicked);
 
 //sliderx.setUpdateOnReleaseOnly(true);
 //slidery.setUpdateOnReleaseOnly(true);
 //sliderz.setUpdateOnReleaseOnly(true);

  legend_data=new float[legend_height*legend_width*3];


  plane_x.rotate(90,0,1,0);
  plane_y.rotate(90,1,0,0);

  button_bg_color.set(143, 143,143 );

  easycam.setPosition(0,0,25);
  load_file();
  
}
void ofApp::on_file_clicked(){
  if(chosen_file==F)
    chosen_file=E;
  else chosen_file=F;



  mesh.clear();
  plane_x_pos = plane_y_pos = plane_z_pos =0;
  slice_axis = -1;
  slice_val = 0.0f;
  show_slice = false;

 panel.clear();
  
  load_file();
}

void ofApp::load_file(){
  if(chosen_file==F){    
    r.read_data("fuel.vti");
  }
  else {
    r.read_data("engine.vti");
  }


  dims= r.get_dims();
  range= r.get_range();

 sliderx.addListener(this, &ofApp::move_plane_x);
 slidery.addListener(this, &ofApp::move_plane_y);
 sliderz.addListener(this, &ofApp::move_plane_z);

  panel.setup();
  ofSetColor(255,255,255);
  panel.add(sliderx.setup("Slider X",0, 0 , dims[0]));
  panel.add(slidery.setup("Slider Y",0, 0 , dims[1]));
  panel.add(sliderz.setup("Slider Z",0, 0 , dims[2]));
  panel.add(color.setup("Enable Color",false));

 plane_x.set(dims[1],dims[2]);
 plane_y.set(dims[0],dims[2]);
 plane_z.set(dims[0],dims[1]);

 plane_x.enableColors();
 plane_y.enableColors();
 plane_z.enableColors();

 plane_x_pos= 0;
 plane_y_pos= 0;
 plane_z_pos= 0;

 x_pos= -dims[0]*0.5f;
 y_pos= -dims[1]*0.5f;
 z_pos= -dims[2]*0.5f;

 

 
 mesh.setMode(OF_PRIMITIVE_POINTS);
 data=r.get_data();
 
 for(int i=0; i<dims[2];i++){
   for(int j=0; j<dims[1];j++){
     for(int k=0; k<dims[0];k++){
       if(data[ i*dims[1]*dims[0] + j*dims[0]+k ]) {
	 ofVec3f p(k,j,i);
	 mesh.addVertex(p);
     }
    }
   }
  }

}

void ofApp::update()
{
}


void ofApp::on_slice_clicked(){


  show_slice = true;

  float* slice_data;
  
   int i=0,j=0,k=0;
  int count=0;
  
  switch(slice_axis){

  case X:
    if(!color){

      slice_data=new float[dims[2]*dims[1]];
 for(i=0; i<dims[2];i++){
   for(j=0; j<dims[1];j++){
     
     slice_data[count]=1-data[ i*dims[1]*dims[0] + j*dims[0]+(int)slice_val ];
       count++;
   }
  }

 
 image.setFromPixels(slice_data, dims[1], dims[2], OF_IMAGE_GRAYSCALE);
 count=0;
 for(j=0;j<legend_height;j++){
   for(i=0;i<legend_width;i++){

     legend_data[count]=1-(i/(float)legend_width);
     legend_data[count+1]=1-(i/(float)legend_width);
     legend_data[count+2]=1-(i/(float)legend_width);
     count+=3;

  }

    }
 legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_COLOR);
    }

    else{
      slice_data=new float[dims[2]*dims[1]*3];
 for(i=0; i<dims[2];i++){
   for(j=0; j<dims[1];j++){
     
     slice_data[count]= (color_start[R]-(color_start[R]-color_end[R])*data[ i*dims[1]*dims[0] + j*dims[0]+(int)slice_val ])/255.0f;
     slice_data[count+1]= (color_start[G]-(color_start[G]-color_end[G])*data[ i*dims[1]*dims[0] + j*dims[0]+(int)slice_val ])/255.0f;
     slice_data[count+2]= (color_start[B]-(color_start[B]-color_end[B])*data[ i*dims[1]*dims[0] + j*dims[0]+(int)slice_val ])/255.0f;
       count+=3;
   }
  }

 image.setFromPixels(slice_data, dims[1], dims[2], OF_IMAGE_COLOR);

  count=0;
   for(j=0;j<legend_height;j++){
 for(i=0;i<legend_width;i++){

     legend_data[count]=(color_start[R]-(i/(float)legend_width)*(color_start[R]-color_end[R]))/255.0f;
     legend_data[count+1]=(color_start[G]-(i/(float)legend_width)*(color_start[G]-color_end[G]))/255.0f;
     legend_data[count+2]=(color_start[B]-(i/(float)legend_width)*(color_start[B]-color_end[B]))/255.0f;
     count+=3;

  }

    }
 legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_COLOR);

    }

  break;


  case Y:
    if(!color){
      slice_data= new float[dims[2]*dims[0]];
 for(i=0; i<dims[2];i++){
    for(k=0; k<dims[0];k++){
      slice_data[count]=1-data[ i*dims[1]*dims[0] + (int)slice_val*dims[0]+k ];
	count++;
  }
  }

 image.setFromPixels(slice_data, dims[0], dims[2], OF_IMAGE_GRAYSCALE);
 count=0;
   for(j=0;j<legend_height;j++){
 for(i=0;i<legend_width;i++){

     legend_data[count]=1-(i/(float)legend_width);
     legend_data[count+1]=1-(i/(float)legend_width);
     legend_data[count+2]=1-(i/(float)legend_width);
     count+=3;

  }

    }
 legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_COLOR);



    }
    else{
 slice_data= new float[dims[2]*dims[0]*3];
 for(i=0; i<dims[2];i++){
    for(k=0; k<dims[0];k++){
      slice_data[count]=  (color_start[R]-(color_start[R]-color_end[R])*data[ i*dims[1]*dims[0] + (int)slice_val*dims[0]+k ])/255.0f;
      slice_data[count+1]= ( color_start[G]-(color_start[G]-color_end[G])*data[ i*dims[1]*dims[0] + (int)slice_val*dims[0]+k ])/255.0f;
      slice_data[count+2]=  (color_start[B]-(color_start[B]-color_end[B])*data[ i*dims[1]*dims[0] + (int)slice_val*dims[0]+k ])/255.0f;
	count+=3;
  }
  }

 image.setFromPixels(slice_data, dims[0], dims[2], OF_IMAGE_COLOR);

  count=0;
   for(j=0;j<legend_height;j++){
 for(i=0;i<legend_width;i++){

     legend_data[count]=(color_start[R]-(i/(float)legend_width)*(color_start[R]-color_end[R]))/255.0f;
     legend_data[count+1]=(color_start[G]-(i/(float)legend_width)*(color_start[G]-color_end[G]))/255.0f;
     legend_data[count+2]=(color_start[B]-(i/(float)legend_width)*(color_start[B]-color_end[B]))/255.0f;
     count+=3;

  }

    }
 legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_COLOR);
   


    }
    break;

  case Z:
    if(!color){
    slice_data=new float[dims[1]*dims[0]]; 
   for(j=0; j<dims[1];j++){
     for(k=0; k<dims[0];k++){
       
       slice_data[count]=1-data[ (int)slice_val*dims[1]*dims[0] + j*dims[0]+k ];
	 count++;
    }
   }

 image.setFromPixels(slice_data, dims[0], dims[1], OF_IMAGE_GRAYSCALE);
 count=0;
   for(j=0;j<legend_height;j++){
 for(i=0;i<legend_width;i++){

     legend_data[count]=1-(i/(float)legend_width);
     legend_data[count+1]=1-(i/(float)legend_width);
     legend_data[count+2]=1-(i/(float)legend_width);
     count+=3;

  }

    }
 legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_COLOR);




    }
    else{
    slice_data=new float[dims[1]*dims[0]*3]; 
   for(j=0; j<dims[1];j++){
     for(k=0; k<dims[0];k++){
       
       slice_data[count]= (color_start[R]-(color_start[R]-color_end[R])*data[ (int)slice_val*dims[1]*dims[0] + j*dims[0]+k ])/255.0f;
       slice_data[count+1]= (color_start[G]-(color_start[G]-color_end[G])*data[ (int)slice_val*dims[1]*dims[0] + j*dims[0]+k ])/255.0f;
       slice_data[count+2]= (color_start[B]-(color_start[B]-color_end[B])*data[ (int)slice_val*dims[1]*dims[0] + j*dims[0]+k ])/255.0f;
	 count+=3;
    }
   }

 image.setFromPixels(slice_data, dims[0], dims[1], OF_IMAGE_COLOR);
   
  count=0;
   for(j=0;j<legend_height;j++){
 for(i=0;i<legend_width;i++){

     legend_data[count]=(color_start[R]-(i/(float)legend_width)*(color_start[R]-color_end[R]))/255.0f;
     legend_data[count+1]=(color_start[G]-(i/(float)legend_width)*(color_start[G]-color_end[G]))/255.0f;
     legend_data[count+2]=(color_start[B]-(i/(float)legend_width)*(color_start[B]-color_end[B]))/255.0f;
     count+=3;

  }

    }
 legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_COLOR);




    }
   break;
  }
  float current_image_width=image.getWidth();
  float current_image_height=image.getHeight();
  float max_image_height=500;
  float resized_width;
  float resized_height;
  float scale;
  
 
  resized_height=max_image_height;
  scale=resized_height/current_image_height;
  resized_width= scale*current_image_width; 
  image.resize(resized_height, resized_width);
  panel.clear();

}

void ofApp::draw()
{
  if(!show_slice){
  
  easycam.begin();


  plane_x.setPosition(plane_x_pos+x_pos,0,0);
  plane_y.setPosition(0,plane_y_pos+y_pos,0);
  plane_z.setPosition(0,0,plane_z_pos+z_pos);


  
  ofSetColor(254,196,79,150);
  plane_x.draw();
  plane_y.draw();
  plane_z.draw();

  ofPushMatrix();
  ofTranslate(x_pos,y_pos,z_pos);

  
  ofSetColor(222,45,38,100);
  mesh.draw();
  
  ofDrawAxis(150);
  ofPopMatrix();

   easycam.end();
   panel.draw();

  ofSetColor(button_bg_color);
  ofDrawRectangle(slice_button_x, slice_button_y, slice_button_width, slice_button_height);
  ofSetColor(255, 255, 255);
  string str = "SLICE";
  float str_width = verdana.stringWidth(str);
  float str_height = verdana.stringHeight(str);
  verdana.drawString(str, slice_button_x + (slice_button_width-str_width)*0.5f, slice_button_y + slice_button_height - (slice_button_height-str_height)*0.5f);

  }
  else {

    image.draw((ofGetScreenWidth()-image.getWidth())*0.5f,((ofGetScreenHeight()-image.getHeight())*0.5f));
     float legend_x=(ofGetScreenWidth()-legend.getWidth())*0.5f;
    legend.draw(legend_x,55);
    float tick_offset=legend_width/(float)(tick_count+1);
    float range_offset=(range[1]-range[0])/(float)(tick_count+1);
     ofSetColor(0);

    for(int i=0;i<tick_count+2;i++){
      float val=range[0]+range_offset*i;
      string val_str=to_string(val);
      string sub=val_str.substr(0,5);
      float str_width=verdana.stringWidth(sub);
      verdana.drawString(sub,legend_x+tick_offset*i-str_width*0.5f,75);

    }
    
    
    
  }

  ofSetColor(button_bg_color);
  ofDrawRectangle(file_button_x, file_button_y, file_button_width, file_button_height);
  ofSetColor(255, 255, 255);
  string str = "ENGINE.vti/FUEL.vti";
  float str_width = verdana.stringWidth(str);
  float str_height = verdana.stringHeight(str);
  verdana.drawString(str, file_button_x + (file_button_width-str_width)*0.5f, file_button_y + file_button_height - (file_button_height-str_height)*0.5f);

}
void ofApp:: move_plane_x(float &new_x){

  plane_x_pos=new_x;
  plane_y_pos=0;
  plane_z_pos=0;
  slice_axis=X;
  slice_val=new_x;
}

void ofApp::move_plane_y(float &new_y){

  plane_x_pos=0;
  plane_y_pos=new_y;
  plane_z_pos=0;
  slice_axis=Y;
  slice_val=new_y;
  
}

void ofApp::move_plane_z(float &new_z){
   
  plane_x_pos=0;
  plane_y_pos=0;
  plane_z_pos=new_z;
  slice_axis=Z;
  slice_val=new_z;
}






void ofApp::exit()
{
}

void ofApp::keyPressed(ofKeyEventArgs& key)
{
}

void ofApp::keyReleased(ofKeyEventArgs& key)
{
  
}

void ofApp::mouseMoved(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseDragged(ofMouseEventArgs& mouse)
{
}

void ofApp::mousePressed(ofMouseEventArgs& mouse)
{
  if(mouse.x >= file_button_x && mouse.x <= file_button_x+file_button_width && mouse.y >= file_button_y && mouse.y <= file_button_y + file_button_height) {
    on_file_clicked();
    return;
  } else if(mouse.x >= slice_button_x && mouse.x <= slice_button_x+slice_button_width && mouse.y >= slice_button_y && mouse.y <= slice_button_y + slice_button_height) {
    on_slice_clicked();
    return;
  }
}

void ofApp::mouseReleased(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseScrolled(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseEntered(ofMouseEventArgs& mouse)
{
}

void ofApp::mouseExited(ofMouseEventArgs& mouse)
{
}

void ofApp::touchDown(ofTouchEventArgs& touch)
{
}

void ofApp::touchMoved(ofTouchEventArgs& touch)
{
}

void ofApp::touchUp(ofTouchEventArgs& touch)
{
}

void ofApp::touchDoubleTap(ofTouchEventArgs& touch)
{
}

void ofApp::touchCancelled(ofTouchEventArgs& touch)
{
}

void ofApp::windowResized(ofResizeEventArgs& window)
{
}

void ofApp::dragged(ofDragInfo& dragged)
{
}

void ofApp::messageReceived(ofMessage& message)
{
}
