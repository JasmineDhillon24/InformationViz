#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255,255,255);
	ofEnableSmoothing();
	ofTrueTypeFont::setGlobalDpi(72);
	ofSetFullscreen(true);
	
	screen_height= ofGetScreenHeight();
	screen_width = ofGetScreenWidth();
	
	verdana1.load("verdana.ttf", font_size1, true, true);
	verdana1.setLineHeight(38.0f);
	verdana1.setLetterSpacing(1.037);

	ofAddListener(pc.stplot_label, this, &ofApp::on_label_drop);


	load_file();

	
	
}

//--------------------------------------------------------------
void ofApp::update(){
	pc.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	
	if (chosen_file == CARS) {
		ofSetColor(66, 244, 0);
	}
	else {
		ofSetColor(66, 244, 255);
	}
	ofDrawRectangle(50, 50, 10, 10);
	if (chosen_file == CAMERAS) {
		ofSetColor(66, 244, 0);
	}
	else {
		ofSetColor(66, 244, 255);
	}
	ofDrawRectangle(150, 50, 10, 10);
	if (chosen_file == NUTRIENTS) {
		ofSetColor(66, 244, 0);
	}
	else {
		ofSetColor(66, 244, 255);
	}
	ofDrawRectangle(290, 50, 10, 10);
	
	ofSetColor(0,0,0);
	verdana1.drawString("SELECT A DATASET by clicking the checkbox", 45, 35);
	verdana1.drawString("Cars", 65, 60);
	verdana1.drawString("Cameras", 165, 60);
	verdana1.drawString("Nutrients", 305, 60);

	
	st.draw();
	pc.draw();
}

void ofApp::load_file()
{
	switch (chosen_file) {
	case CARS: tb.read_data("bin/data/cars.tsv");
		break;
	case CAMERAS: tb.read_data("bin/data/cameras.tsv");
		break;
	case NUTRIENTS: tb.read_data("bin/data/nutrients.tsv");
		break;
	}
	pc.setup(0, 0.4f*screen_height, screen_width, 0.60f*screen_height);
	pc.set_column_name(tb.get_column_name());
	pc.set_column_val(tb.get_column_values());

	st.setup(0.4f*screen_height,0.4f*screen_height);
	st.set_reference_pos(screen_width-0.4f*screen_height, 0);
	st.set_column_name(tb.get_column_name());
	st.set_column_val(tb.get_column_values());
	st.set_brushed_info(pc.get_brushed_info());

}

void ofApp::on_label_drop(int &which_label)
{
	st.drop_label(which_label);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if(y>=50 && y<= 60) {
		if (x >= 50 && x <= 60) {
			chosen_file = CARS;
			pc.clear();
			tb.clear();
			load_file();
		}
		else if (x >= 150 && x <= 160) {
			chosen_file = CAMERAS;
			pc.clear();
			tb.clear();
			load_file();
		}
		else if (x >= 250 && x <= 260) {
			chosen_file = NUTRIENTS;
			pc.clear();
			tb.clear();
			load_file();
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
