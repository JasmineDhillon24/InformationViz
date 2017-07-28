#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(1500, 800);
	ofBackground(0);
	ofEnableSmoothing();
		
    tr.read_data("bin/data/abalone.tsv");
	int column_count= tr.column_name.size();
	int i=0, j=0;
	
	if (column_count <= 4) {
		height = 200;
		width = 200;
	}
	else if (column_count > 4 && column_count <= 8) {
		height = 90;
		width = 90;
	}
	else {
		height = 60;
		width = 60;
	}
	
	while (i<column_count) {
		j = 0;
		while (j<column_count) {

			Scatterplot *obj = new Scatterplot();

			obj->setup(width, height);
			obj->set_reference_pos(width*i, height*j);
			obj->set_index(st_array.size());
			
			obj->set_axis_name(tr.get_column_name(i), tr.get_column_name(j));
			obj->set_column_val(tr.get_column(i), tr.get_column(j));
			ofAddListener(obj->brush_event, this, &ofApp::brush_listener);

			st_array.push_back(obj);
			j++;
			
		}
		i++;
	}


	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < st_array.size(); i++)
	{
		st_array[i]->draw();
	}

}



void ofApp::brush_listener(BrushEventInfo & event)
{
	for (int i = 0; i < st_array.size(); i++)
	{
		st_array[i]->setBrushEventInfo(event);
		if (event.sp_index != i) {
			st_array[i]->set_other_sp_brush_status(event.brush_status);
		}
	}

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
