#pragma once
#include "TableReader.h"
#include <vector>
#include "ofMain.h"
class ParallelCoordinates
{
public:
	ParallelCoordinates();
	~ParallelCoordinates();

	std::vector<Column*> column_name;
	std::vector<std::vector<float*>> column_val;
	void set_column_name(std::vector<Column*> col_name);
	void set_column_val(std::vector<std::vector<float*>> col_val);
	void draw();
	void update();
	float x_offset;
	float y_offset;
	float string_width;
	float axis_offset;
	float axis_height;
	ofTrueTypeFont	verdana;
	ofTrueTypeFont	verdana1;
	vector<ofColor> line_colors;
	int font_size = 10;
	int font_size1 = 12;
	float x_pos1;
	float y_pos1; 
	float width1; 
	float height1;
	int axis_brushed = -1;
	vector<float> brushed_start_val;
	vector<float> brushed_end_val;
	
	


	vector<vector<bool>> brushed;
	vector<bool> min_max_invert;
	int label_clicked=-1;
	float label_dragged_x = 0;
	float label_dragged_y = 0;
	void setup(float x_pos, float y_pos, float width, float height);
	void clear();

	void mouseMoved(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void mousePressed(ofMouseEventArgs & args);
	void mouseReleased(ofMouseEventArgs & args);
	void mouseScrolled(ofMouseEventArgs & args);
	void mouseEntered(ofMouseEventArgs & args);
	void mouseExited(ofMouseEventArgs & args);

};

