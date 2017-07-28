#include "ImageReader.h"

void ImageReader::read_data(string file){
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

  //Allocate an arrow to read the data into                                                                                        
  data = new float[dims[0]*dims[1]*dims[2]];

  //Grab the .vti's data array as a vtkDoubleArray                                                                                 
  vtkSmartPointer<vtkDataArray> scalars = image->GetPointData()->GetScalars();
  //Get the scalar range (min/max) value                                                                                           

  scalars->GetRange(range);

  std::cout << "Scalar value range: [" << range[0] << "," << range[1] << "]" << std::endl;
  
  for(int i=0;i<range[1]-range[0];i++) {
    aggregate_values.push_back(0);
  }

  //Normalize the image values -- ofFloatImage expects a value between [0,1]                                                       
  for (int i=0; i<dims[0]*dims[1]*dims[2]; i++) {
    int val= (int)(scalars->GetTuple1(i) - range[0]);
    data[i] =  (scalars->GetTuple1(i) - range[0]) / (range[1]-range[0]);
    aggregate_values[val]++;
    
  }
  int min= aggregate_values[0];
  int max= aggregate_values[0];
  
  for(int i=1;i< aggregate_values.size();i++) {
    if(aggregate_values[i] < min){
      min=aggregate_values[i];
      
    }
    else if(aggregate_values[i] > max){

      max= aggregate_values[i];
    }
  }

  aggregate_min=min;
  aggregate_max=max;

}
