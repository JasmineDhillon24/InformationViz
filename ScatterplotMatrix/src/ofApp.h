#pragma once

#include "ofMain.h"
#include "Scatterplot.h"
#include "TableReader.h"
#include "BrushEventInfo.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		int height, width;
		
		vector<Scatterplot*> st_array;
		TableReader tr = TableReader();
		
		void brush_listener(BrushEventInfo & event);
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
