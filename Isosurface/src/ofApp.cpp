
#include "ofApp.h"

void ofApp::setup()
{
  ofSetSmoothLighting(true);
  ofBackground(255,255,255);
  ofTrueTypeFont::setGlobalDpi(72);
  verdana.load("verdana.ttf", font_size, true, true);
  verdana.setLineHeight(38.0f);
  verdana.setLetterSpacing(1.037);


  light.setSpecularColor( ofColor(255.f, 255.f, 255.f));


  light_color.set(254,224,210 );
 
  light.setDiffuseColor(light_color); 

  button_bg_color.set(143,143,143);

  load_file();
  
}
void ofApp::on_file_clicked(){
  if(chosen_file==F)
    chosen_file=E;
  else chosen_file=F;

  mesh.clear();
  isoval_val = 0.0f;
 
  panel.clear();
  
  load_file();
}

void ofApp::load_file(){
  if(chosen_file==F){    
    r.read_data("hydrogen.vti");
  }
  else {
    r.read_data("tooth.vti");
  }

  
  dims= r.get_dims();
  range= r.get_range();

  slider_isoval.addListener(this, &ofApp::move_isoval);

  panel.setup();
  ofSetColor(255,255,255);
  panel.add(slider_isoval.setup("Slider Isovalue",range[0]+(range[1]-range[0])/2.0f, range[0] , range[1]));
  isoval_val=range[0]+(range[1]-range[0])/2.0f;

  panel.add(wireframe.setup("Enable Wireframe",false));
  panel.add(light_button.setup("Enable Light",false));

  
  x_pos= -dims[0]*0.5f;
  y_pos= -dims[1]*0.5f;
  z_pos= -dims[2]*0.5f;
  light.setPosition(x_pos,y_pos,z_pos); 
  mesh.setMode(OF_PRIMITIVE_TRIANGLES);
  mesh_dup.setMode(OF_PRIMITIVE_TRIANGLES);
 
  data=r.get_data();
  on_isoval_clicked(); 

  legend_data=new float[legend_height*legend_width*3];
  int count=0;
  
for(int j=0;j<legend_height;j++){                                                                                                                                                                                                  
  for(int i=0;i<legend_width;i++){                                                                                                                                                                                              float frac=i/(float)legend_width;   
                                                                                                                                                                                                                                
    legend_data[count]=(color_start[R]-(frac*(color_start[R]-color_end[R])))/255;                                                                                                                                                                                
    legend_data[count+1]=(color_start[G]-(frac*(color_start[G]-color_end[G])))/255;                                                                                                                                                                              
    legend_data[count+2]=(color_start[B]-(frac*(color_start[B]-color_end[B])))/255;                                                                                                                                                                              
     count+=3;                                                                                                                                                                                                                                                                                                                                                                                                                                                
  }                                                                                                                                                                                                                                                                                                                                                                                                                                                         
    }                                                                                                                                                                                                                           
 legend.setFromPixels(legend_data,legend_width,legend_height,OF_IMAGE_COLOR);                


  
}

void ofApp::update()
{
}


void ofApp::on_isoval_clicked(){

  mesh_dup.clear();
  for(int i=0; (i+grid_size)<dims[2];i+=grid_size){
    for(int j=0; (j+grid_size)<dims[1];j+=grid_size){
      for(int k=0; (k+grid_size)<dims[0];k+=grid_size){

	ofVec3f cube_vert[8];

	cube_vert[0].set(k,j,i);
	cube_vert[1].set(k+grid_size,j,i);
	cube_vert[2].set(k+grid_size,j,i+grid_size);
	cube_vert[3].set(k,j,i+grid_size);
	cube_vert[4].set(k,j+grid_size,i);
	cube_vert[5].set(k+grid_size,j+grid_size,i);
	cube_vert[6].set(k+grid_size,j+grid_size,i+grid_size);
	cube_vert[7].set(k,j+grid_size,i+grid_size);



	float cube_vert_val[8];
	cube_vert_val[0]=data[i*dims[1]*dims[0] + j*dims[0] + k];
	cube_vert_val[1]=data[i*dims[1]*dims[0] + j*dims[0] + (k+grid_size)];
	cube_vert_val[2]=data[(i+grid_size)*dims[1]*dims[0] + j*dims[0] + (k+grid_size)];
	cube_vert_val[3]=data[(i+grid_size)*dims[1]*dims[0] + j*dims[0] + k];
	 
	cube_vert_val[0]=data[i*dims[1]*dims[0] + (j+grid_size)*dims[0] + k];
	cube_vert_val[1]=data[i*dims[1]*dims[0] + (j+grid_size)*dims[0] + (k+grid_size)];
	cube_vert_val[2]=data[(i+grid_size)*dims[1]*dims[0] + (j+grid_size)*dims[0] + (k+grid_size)];
	cube_vert_val[3]=data[(i+grid_size)*dims[1]*dims[0] + (j+grid_size)*dims[0] + k];



	int cube_index=0;
	if (cube_vert_val[0] < (isoval_val-range[0])/(range[1]-range[0])) cube_index |= 1;
	if (cube_vert_val[1] < (isoval_val-range[0])/(range[1]-range[0])) cube_index |= 2;
	if (cube_vert_val[2] < (isoval_val-range[0])/(range[1]-range[0])) cube_index |= 4;
	if (cube_vert_val[3] < (isoval_val-range[0])/(range[1]-range[0])) cube_index |= 8;
	if (cube_vert_val[4] < (isoval_val-range[0])/(range[1]-range[0])) cube_index |= 16;
	if (cube_vert_val[5] < (isoval_val-range[0])/(range[1]-range[0])) cube_index |= 32;
	if (cube_vert_val[6] < (isoval_val-range[0])/(range[1]-range[0])) cube_index |= 64;
	if (cube_vert_val[7] < (isoval_val-range[0])/(range[1]-range[0])) cube_index |= 128;

	if (edgeTable[cube_index] != 0){

	  ofVec3f tri_vert[12];

	  if (edgeTable[cube_index] & 1)
	    tri_vert[0] =
	      interpolate(cube_vert[0],cube_vert[1],cube_vert_val[0],cube_vert_val[1]);
	  if (edgeTable[cube_index] & 2)
	    tri_vert[1] =
	      interpolate(cube_vert[1],cube_vert[2],cube_vert_val[1],cube_vert_val[2]);
	  if (edgeTable[cube_index] & 4)
	    tri_vert[2] =
	      interpolate(cube_vert[2],cube_vert[3],cube_vert_val[2],cube_vert_val[3]);
	  if (edgeTable[cube_index] & 8)
	    tri_vert[3] =
	      interpolate(cube_vert[3],cube_vert[0],cube_vert_val[3],cube_vert_val[0]);
	  if (edgeTable[cube_index] & 16)
	    tri_vert[4] =
	      interpolate(cube_vert[4],cube_vert[5],cube_vert_val[4],cube_vert_val[5]);
	  if (edgeTable[cube_index] & 32)
	    tri_vert[5] =
	      interpolate(cube_vert[5],cube_vert[6],cube_vert_val[5],cube_vert_val[6]);
	  if (edgeTable[cube_index] & 64)
	    tri_vert[6] =
	      interpolate(cube_vert[6],cube_vert[7],cube_vert_val[6],cube_vert_val[7]);
	  if (edgeTable[cube_index] & 128)
	    tri_vert[7] =
	      interpolate(cube_vert[7],cube_vert[4],cube_vert_val[7],cube_vert_val[4]);
	  if (edgeTable[cube_index] & 256)
	    tri_vert[8] =
	      interpolate(cube_vert[0],cube_vert[4],cube_vert_val[0],cube_vert_val[4]);
	  if (edgeTable[cube_index] & 512)
	    tri_vert[9] =
	      interpolate(cube_vert[1],cube_vert[5],cube_vert_val[1],cube_vert_val[5]);
	  if (edgeTable[cube_index] & 1024)
	    tri_vert[10] =
	      interpolate(cube_vert[2],cube_vert[6],cube_vert_val[2],cube_vert_val[6]);
	  if (edgeTable[cube_index] & 2048)
	    tri_vert[11] =
	      interpolate(cube_vert[3],cube_vert[7],cube_vert_val[3],cube_vert_val[7]);

	  int p=0;
	    
	  while(triTable[cube_index][p]!=-1){
	    mesh_dup.addVertex(tri_vert[triTable[cube_index][p]]);
	    mesh_dup.addVertex(tri_vert[triTable[cube_index][p+1]]);
	    mesh_dup.addVertex(tri_vert[triTable[cube_index][p+2]]);
	    ofVec3f u=tri_vert[triTable[cube_index][p+1]]-tri_vert[triTable[cube_index][p]];
	    ofVec3f v=tri_vert[triTable[cube_index][p+2]]-tri_vert[triTable[cube_index][p+1]];
	    ofVec3f normal;
	    normal.x= u.y*v.z-u.z*v.y;
	    normal.y= u.z*v.x-u.x*v.z;
	    normal.z= u.x*v.y-u.y*v.x;
	    mesh_dup.addNormal(normal);
	    mesh_dup.addNormal(normal);
	    mesh_dup.addNormal(normal);
	    p+=3;
	  }
	  
	}
      }
    }
  }
 mesh=mesh_dup;
   
}

void ofApp::draw()
{
 
  float legend_x=(ofGetScreenWidth()-legend.getWidth())*0.5f;                                                                                                                                                                
  legend.draw(legend_x,55);                                                                                                                                                                                                  
  float tick_offset=legend_width/(float)(tick_count+1);                                                                                                                                                                          float range_offset=(range[1]-range[0])/(float)(tick_count+1);                                                                                                                                                                   ofSetColor(0);                                                                                                                                                                                                                for(int i=0;i<tick_count+2;i++){                                                                                                                                                                                                 float val=range[0]+range_offset*i;                                                                                                                                                                                             string val_str=to_string(val);                                                                                                                                                                                                 string sub=val_str.substr(0,5);                                                                                                                                                                                                float str_width=verdana.stringWidth(sub);                                                                                                                                                                                      verdana.drawString(sub,legend_x+tick_offset*i-str_width*0.5f,75);                                                                                                                                                            }           
  easycam.begin();

  ofPushMatrix();
  ofTranslate(x_pos,y_pos,z_pos);

  if(light_button){
    ofEnableLighting();
    light.enable();
    
  }
  float fraction=isoval_val/(range[1]-range[0]);
  
  ofColor mesh_color;
  mesh_color.set(color_start[R]-(fraction*(color_start[R]-color_end[R])),color_start[G]-(fraction*(color_start[G]-color_end[G])),color_start[B]-(fraction*(color_start[B]-color_end[B]))); 
  ofSetColor(mesh_color);
  mesh.draw();

  if(wireframe){
    ofSetColor(122,0,70);
    mesh.draw(OF_MESH_WIREFRAME);
  }

  if(light_button){
    ofDisableLighting();

  }
  ofDrawAxis(150);
  ofPopMatrix();

  easycam.end();
  panel.draw();
  
  ofSetColor(button_bg_color);
  ofDrawRectangle(isoval_button_x, isoval_button_y, isoval_button_width, isoval_button_height);
  ofSetColor(255, 255, 255);
  string str = "REFRESH ISOVALUE";
  float str_width = verdana.stringWidth(str);
  float str_height = verdana.stringHeight(str);
  verdana.drawString(str, isoval_button_x + (isoval_button_width-str_width)*0.5f, isoval_button_y + isoval_button_height - (isoval_button_height-str_height)*0.5f);

  

  ofSetColor(button_bg_color);
  ofDrawRectangle(file_button_x, file_button_y, file_button_width, file_button_height);
  ofSetColor(255, 255, 255);
  str = "TOOTH/HYDROGEN";
  str_width = verdana.stringWidth(str);
  str_height = verdana.stringHeight(str);
  verdana.drawString(str, file_button_x + (file_button_width-str_width)*0.5f, file_button_y + file_button_height - (file_button_height-str_height)*0.5f);

}
void ofApp:: move_isoval(float &new_isoval){

  isoval_val=new_isoval;
}

ofVec3f ofApp::interpolate(ofVec3f p, ofVec3f q,float p_val, float q_val ){

  ofVec3f vertex;
  float iso_val = range[0] + isoval_val/(range[1]-range[0]);
  
  vertex.x= (int)((q.x-p.x)*(iso_val-p_val)/(q_val-p_val)+p.x);
  vertex.y=(int)((q.y-p.y)*(iso_val-p_val)/(q_val-p_val)+p.y);
  vertex.z=(int)((q.z-p.z)*(iso_val-p_val)/(q_val-p_val)+p.z);
  return vertex;
    

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
  } else if(mouse.x >= isoval_button_x && mouse.x <= isoval_button_x+isoval_button_width && mouse.y >= isoval_button_y && mouse.y <= isoval_button_y + isoval_button_height) {
    on_isoval_clicked();
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
