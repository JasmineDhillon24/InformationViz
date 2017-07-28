#include "VectorField.h"


void VectorField::measure(){
  float frac_x= max_width/width;
  float frac_y= max_height/height;

  float frac= (frac_x*height> max_height) ? frac_y : frac_x;

  width=floor(width*frac);
  height= floor(height*frac);
  
}

void VectorField::remove_lines(){
  streamlines_world.clear();
}

void VectorField::read_data(string file){
  //Use VTK to read the .vti file                                                                                                  
  vtkSmartPointer<vtkXMLImageDataReader> reader = vtkSmartPointer<vtkXMLImageDataReader>::New();
    reader->SetFileName(ofToDataPath(file).c_str());
  //Once Update() is called, the reader actually reads the file                                                                    
  reader->Update();

  image= reader->GetOutput();

  //Get the dimensions.  Even for two-dimensional images, we need to get                                                           
  //a three-dimensional set of dimensions.  dims[2] should be 1                                                                    
 
  image->GetDimensions(dims);
  std::cout << "Image dimensions: " << dims[0] << "x" << dims[1] << "x" << dims[2] << std::endl;

  image->GetOrigin(origin);
  image->GetSpacing(spacing);
  data= new ofVec2f[dims[0]*dims[1]];
  //Allocate an arrow to read the data into                                                                                        
  // data = new float[dims[0]*dims[1]*dims[2]];

  c_data=new Coordinates(0,(double)dims[0]-1, 0, (double)dims[1]-1);
  c_world= new Coordinates((double)origin[0],(double)(origin[0]+spacing[0]*(c_data->x_max)),(double)origin[1],(double)(origin[1]+spacing[1]*(c_data->y_max)) );
  width=dims[0];
  height=dims[1];
  measure();
  start_height=height;
  start_width=width;
  c_screen=new Coordinates(0,(double)width, 0,(double)height);
 
  //Grab the .vti's data array as a vtkDoubleArray                                                                                 
  vtkSmartPointer<vtkDataArray> vectors = image->GetPointData()->GetVectors();
  end_color.r=0.56f;
  end_color.g=0.40f;
  end_color.b=0.07f;
  start_color.r=0.13f;
  start_color.g=0.58f;
  start_color.b=0.58f;

  color_enabled=true;
    
  
  mag=new double[2];
  vectors->GetRange(mag,-1);
  double* vec =new double [vectors->GetNumberOfComponents()];
  for(int i=0; i<dims[0]*dims[1];i++){
    vectors->GetTuple(i, vec);
    data[i].x = vec[0];
    data[i].y = vec[1];
  }
  delete[] vec;

  if(!color_enabled){
    img_data = new float[width*height];
    for(int y=0; y<height;y++){
      for(int x=0; x<width; x++){
	ofVec2f s_point;
	s_point.x=x;
	s_point.y=height-y-1;
	ofVec2f velocity;
	velocity = interpolate(s_point);
	int p = y*width+x;

	img_data[p]= (velocity.length()-mag[0]) / (double)(mag[1]-mag[0]);
  
      }
    }
  }
  else{
    img_data = new float[width*height*3];
    for(int y=0; y<height;y++){
      for(int x=0; x<width; x++){
	ofVec2f s_point;
	s_point.x=x;
	s_point.y=height-y-1;
	ofVec2f velocity;
	velocity = interpolate(s_point);
	int p = 3*(y*width+x);

	float r = (velocity.length()-mag[0]) / (double)(mag[1]-mag[0]);
	img_data[p]= start_color.r + r*(end_color.r-start_color.r);
	img_data[p+1]= start_color.g + r*(end_color.g-start_color.g);
	img_data[p+2]= start_color.b + r*(end_color.b-start_color.b);
  
      }
    }
  
   
  }

  
}
ofVec2f VectorField::interpolate(ofVec2f s_point){


  
  ofVec2f w_point;
  w_point.x= ofMap(s_point.x, c_screen->x_min, c_screen->x_max, c_world->x_min, c_world->x_max);
  w_point.y = ofMap(s_point.y, c_screen->y_min, c_screen->y_max, c_world->y_min, c_world->y_max );
      
  double x1= ((int) floor(w_point.x/spacing[0]))*spacing[0];
  double y1= ((int) floor(w_point.y/spacing[1]))*spacing[1];
  double x2= (((int) floor(w_point.x/spacing[0])) +1)*spacing[0];
  double y2= (((int) floor(w_point.y/spacing[1])) +1)*spacing[1];



  ofVec2f velocity ;
  if(x2<c_world->x_max && y2< c_world->y_max){

    ofVec2f p11_d, p12_d, p21_d, p22_d;
    p11_d.x= ofMap(x1, c_world->x_min, c_world->x_max, c_data->x_min, c_data->x_max);
    p11_d.y= ofMap(y1, c_world->y_min, c_world->y_max, c_data->y_min, c_data->y_max);

    p12_d.x= ofMap(x1, c_world->x_min, c_world->x_max, c_data->x_min, c_data->x_max);
    p12_d.y= ofMap(y2, c_world->y_min, c_world->y_max, c_data->y_min, c_data->y_max);

    p21_d.x= ofMap(x2, c_world->x_min, c_world->x_max, c_data->x_min, c_data->x_max);
    p21_d.y= ofMap(y1, c_world->y_min, c_world->y_max, c_data->y_min, c_data->y_max);

    p22_d.x= ofMap(x2, c_world->x_min, c_world->x_max, c_data->x_min, c_data->x_max);
    p22_d.y= ofMap(y2, c_world->y_min, c_world->y_max, c_data->y_min, c_data->y_max);

    ofVec2f p11, p12, p21, p22;
    p11= data[(int)(p11_d.y*(c_data->x_max+1) + p11_d.x)];
    p12= data[(int)(p12_d.y*(c_data->x_max+1) + p12_d.x)];
    p21= data[(int)(p21_d.y*(c_data->x_max+1) + p21_d.x)];
    p22= data[(int)(p22_d.y*(c_data->x_max+1) + p22_d.x)];

    ofVec2f r1, r2;
    r1= ((y2-w_point.y)/(y2-y1))*p11 + ((w_point.y- y1)/(y2-y1))* p12;
    r2 = ((y2-w_point.y)/(y2-y1))*p21 + ((w_point.y- y1)/(y2-y1))* p22;

    velocity = ((x2-w_point.x)/(x2-x1))*r1 + ((w_point.x-x1)/(x2-x1))*r2;
    
  }
  else {
    velocity.x=0;
    velocity.y=0;
    
  }

 return velocity;
}
void VectorField::zoom(float zoom_amount){

  width=zoom_amount*start_width;
  height=zoom_amount*start_height;
  c_screen->x_max= width;
  c_screen->y_max= height;

  if(!color_enabled) {
    img_data = new float[width*height];
    for(int y=0; y<height;y++){
      for(int x=0; x<width; x++){
	ofVec2f s_point;
	s_point.x=x;
	s_point.y=height-y-1;
	ofVec2f velocity;
	velocity = interpolate(s_point);
	int p = y*width+x;

	img_data[p]= (velocity.length()-mag[0]) / (double)(mag[1]-mag[0]);
      }
    }
  }
    else{
    img_data = new float[width*height*3];
    for(int y=0; y<height;y++){
      for(int x=0; x<width; x++){
	ofVec2f s_point;
	s_point.x=x;
	s_point.y=height-y-1;
	ofVec2f velocity;
	velocity = interpolate(s_point);
	int p = 3*(y*width+x);

	float r = (velocity.length()-mag[0]) / (double)(mag[1]-mag[0]);
	img_data[p]= start_color.r + r*(end_color.r-start_color.r);
	img_data[p+1]= start_color.g + r*(end_color.g-start_color.g);
	img_data[p+2]= start_color.b + r*(end_color.b-start_color.b);
  
      }
    }   
  }

}

void VectorField::set_color_enabled(bool enabled) {
  color_enabled = enabled;
  
  if(!color_enabled) {
    img_data = new float[width*height];
    for(int y=0; y<height;y++){
      for(int x=0; x<width; x++){
	ofVec2f s_point;
	s_point.x=x;
	s_point.y=height-y-1;
	ofVec2f velocity;
	velocity = interpolate(s_point);
	int p = y*width+x;

	img_data[p]= (velocity.length()-mag[0]) / (double)(mag[1]-mag[0]);
      }
    }
  }
    else{
    img_data = new float[width*height*3];
    for(int y=0; y<height;y++){
      for(int x=0; x<width; x++){
	ofVec2f s_point;
	s_point.x=x;
	s_point.y=height-y-1;
	ofVec2f velocity;
	velocity = interpolate(s_point);
	int p = 3*(y*width+x);

	float r = (velocity.length()-mag[0]) / (double)(mag[1]-mag[0]);
	img_data[p]= start_color.r + r*(end_color.r-start_color.r);
	img_data[p+1]= start_color.g + r*(end_color.g-start_color.g);
	img_data[p+2]= start_color.b + r*(end_color.b-start_color.b);
  
      }
    }   
  }

}

void VectorField::integrate(ofVec2f seed, double dt, int step_count){

  ofPolyline streamline;
  ofVec2f point;
  point.x= ofMap(seed.x, c_screen->x_min, c_screen->x_max, c_world->x_min, c_world->x_max);
  point.y = ofMap(c_screen->y_max-seed.y-1, c_screen->y_min, c_screen->y_max, c_world->y_min, c_world->y_max );

  streamline.addVertex(point);
  
  //  cout<<"point"<<point.x<<"   "<<point.y<<endl;
  
  for(int i=0;i<step_count; i++){
    ofVec2f velocity=interpolate(seed);
    ofVec2f a=dt*velocity;
    ofVec2f b=dt*(velocity+a/2);
    ofVec2f c=dt*(velocity+b/2);
    ofVec2f d=dt*(velocity+c);

    point += (a+2*b+2*c+d)/6.0f;

    //    cout<<"point"<<point.x<<"   "<<point.y<<endl;
    streamline.addVertex(point);    

        
    seed.x=ofMap(point.x, c_world->x_min, c_world->x_max, c_screen->x_min, c_screen->x_max );

    seed.y=ofMap(point.y, c_world->y_min, c_world->y_max, c_screen->y_min, c_screen->y_max );
    //seed.y= c_screen->y_max-1-seed.y;


  }

  streamlines_world.push_back(streamline);
  
}
vector<ofPolyline> VectorField::map_streamlines_to_screen(){

  vector<ofPolyline> streamlines_screen;
  // cout<<"w_s"<<streamlines_world.size();  
  for(int i=0;i<streamlines_world.size();i++)
    {
      
      ofPolyline streamline;
      ofPolyline l_w=streamlines_world[i];
      for(int j=0; j<l_w.size();j++){

	ofVec2f point;
	point.x= ofMap(l_w[j].x, c_world->x_min, c_world->x_max, c_screen->x_min, c_screen->x_max);
	point.y= ofMap(l_w[j].y, c_world->y_min, c_world->y_max, c_screen->y_min, c_screen->y_max);
	point.y= c_screen->y_max-1-point.y;
	point.x-=img_internal_x;
	point.y-=img_internal_y;
	//cout<<"point"<<point.x<<"   "<<point.y<<endl;
	streamline.addVertex(point);
	
      }
      streamlines_screen.push_back(streamline);
    }
  return streamlines_screen;
}
