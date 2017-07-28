
#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	ofGLWindowSettings settings;

	ofSetupOpenGL(1920,1080,OF_FULLSCREEN);
	ofApp app = ofApp();
	//  auto window = ofCreateWindow(settings);
	// auto app = make_shared<ofApp>();
	ofRunApp( &app);

	return 0;
}
