#pragma once

#include "ofMain.h"
#include "TableReader.h"
#include "ParallelCoordinates.h"
class ofApp : public ofBaseApp{

	public:
		static const int CARS = 1;
		static const int CAMERAS = 2;
		static const int NUTRIENTS = 3;

		TableReader tb = TableReader();
		ParallelCoordinates pc = ParallelCoordinates();
		void setup();
		void update();
		void draw();
		float screen_width;
		ofTrueTypeFont	verdana1;
		int font_size1=15;
		int chosen_file = CARS;
		void load_file();
		float screen_height;
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
