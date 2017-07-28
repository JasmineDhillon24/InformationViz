#pragma once
#include "vector"
#include "BrushEventInfo.h"
#include "ofMain.h"
class Scatterplot
{
public:
	const int BRUSH_DISABLED = 0;
	const int BRUSH_ENABLED = 1;
	Scatterplot();
	~Scatterplot();
	void setup(int w, int h);
	void draw();
	float min_x;
	float min_y;
	float max_x;
	float max_y;
	float current_min_x_1;
	float current_min_y_1;
	float current_max_x_1;
	float current_max_y_1;
	void set_current_range(float x1, float x2, float y1, float y2);
	ofEvent<BrushEventInfo> brush_event;

	BrushEventInfo be;
	void setBrushEventInfo(BrushEventInfo e);
	
	std::string x_axis_name;
	std::string y_axis_name;
	ofTrueTypeFont	verdana1;
	ofTrueTypeFont	verdana2;
	int font_size1;
	int font_size2;
	float x_current, y_current;
	std::vector<float> x_data;
	std::vector<float> y_data;
	int x_pos, y_pos;
	int x_label_offset, y_label_offset;
	void set_reference_pos(int x, int y);
	int width, height;
	void set_axis_name(std::string x_name, std::string y_name);
	void set_column_val(std::vector<float> x_val, std::vector<float> y_val);
	int index;
	void set_index(int i);
	
	float value;
	float x_mouse, y_mouse;

	ofPoint brush_start;
	ofPoint brush_end;
	int brush_status = BRUSH_DISABLED;
	int other_sp_brush_status = BRUSH_DISABLED;
	void set_other_sp_brush_status(int status);
	
	void brush();
	void mouseMoved(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void mousePressed(ofMouseEventArgs & args);
	void mouseReleased(ofMouseEventArgs & args);
	void mouseScrolled(ofMouseEventArgs & args);
	void mouseEntered(ofMouseEventArgs & args);
	void mouseExited(ofMouseEventArgs & args);
};



