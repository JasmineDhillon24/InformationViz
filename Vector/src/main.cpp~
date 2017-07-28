
#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	ofGLWindowSettings settings;
  //cout << settings.glVersionMajor << " " << settings.glVersionMinor << endl;
	//settings.setGLVersion(3,2);
	settings.width = 0.45*1366;
	settings.height = 768;
	settings.setPosition(ofVec2f(0.55*1366,0));
	//settings.resizable = true;
	ofCreateWindow(settings);

  //We manually create the window above to have some control
  //over the openGL version, if needed.
	//ofSetupOpenGL(400,300,OF_WINDOW);			// <-------- setup the GL context

  shared_ptr<ofApp> ofa(new ofApp);

	// this kicks off the running of my app
	ofRunApp(ofa);
}
