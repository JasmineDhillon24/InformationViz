#pragma once

#include "ofMain.h"
#include "ImageReader.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkOpenGLRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolumeProperty.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkXMLImageDataReader.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkInteractorStyleTrackballCamera.h>



class volumeRenderThread : public ofThread {
  public:
    void setup(const char* path);
    void setupRenderer();
    void update();
    void threadedFunction();

    ImageReader ir;
    
    vtkSmartPointer<vtkXMLImageDataReader> reader;
    vtkSmartPointer<vtkImageData> image;
    vtkSmartPointer<vtkRenderWindowInteractor> iren;
    vtkSmartPointer<vtkRenderWindow> renWin;
    vtkSmartPointer<vtkOpenGLRenderWindow> oglRenWin;
    vtkSmartPointer<vtkVolumeProperty> volumeProperty;
    vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper;
    vtkSmartPointer<vtkRenderer> ren1;
    vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity;
    vtkSmartPointer<vtkColorTransferFunction> color;
    vtkSmartPointer<vtkVolume> volume;
    double range[2];
    int dims[3];
    bool updated;
};


