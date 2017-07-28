#include "ImageReader.h"

void ImageReader::read_data(string file){
  //Use VTK to read the .vti file                                                                                                  
  vtkSmartPointer<vtkXMLImageDataReader> reader = vtkSmartPointer<vtkXMLImageDataReader>::New();
  reader->SetFileName(ofToDataPath(file).c_str());
  //Once Update() is called, the reader actually reads the file                                                                    
  reader->Update();

  vtkSmartPointer<vtkImageData> image = reader->GetOutput();

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

  //Normalize the image values -- ofFloatImage expects a value between [0,1]                                                       
  for (int i=0; i<dims[0]*dims[1]*dims[2]; i++) {
    data[i] = (scalars->GetTuple1(i) - range[0]) / (range[1]-range[0]);
  }


}