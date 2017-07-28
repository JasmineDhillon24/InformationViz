#pragma once
#include "vector"
#include "ofMain.h"
#include "ParallelCoordinates.h"
class Scatterplot
{
public:
	const int BRUSH_DISABLED = 0;
	const int BRUSH_ENABLED = 1;
	Scatterplot();
	~Scatterplot();
	void setup(int w, int h);
	void draw();
	


	std::vector<Column*> column_name;
	std::vector<std::vector<float*>> column_val;
	void set_column_name(std::vector<Column*> col_name);
	void set_column_val(std::vector<std::vector<float*>> col_val);


	ofTrueTypeFont	verdana1;
	ofTrueTypeFont	verdana2;
	int font_size1;
	int font_size2;
	
	int x_pos, y_pos;
	int x_label_offset= 50, y_label_offset= 50;
	void set_reference_pos(int x, int y);
	int width, height;
	
	int x_axis_col=0;
	int y_axis_col=0;
	float value;
	float x_mouse, y_mouse;
	vector<vector<int*>> brushed1;
	void set_brushed_info(vector<vector<int*>> b);

	void drop_label(int which_label);
	bool change_label_x=true;
	void clear();

	ofPoint brush_start;
	ofPoint brush_end;
	int brush_status = BRUSH_DISABLED;
	
	void brush();
	void mouseMoved(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void mousePressed(ofMouseEventArgs & args);
	void mouseReleased(ofMouseEventArgs & args);
	void mouseScrolled(ofMouseEventArgs & args);
	void mouseEntered(ofMouseEventArgs & args);
	void mouseExited(ofMouseEventArgs & args);
};

