#include "Scatterplot.h"



Scatterplot::Scatterplot()
{
}


Scatterplot::~Scatterplot()
{
}

void Scatterplot::setup(int w, int h)
{
	ofTrueTypeFont::setGlobalDpi(72);
	ofRegisterMouseEvents(this);

    font_size1 = 12;
	font_size2 = 10;
	verdana1.load("verdana.ttf", font_size1, true, true);
	verdana1.setLineHeight(38.0f);
	verdana1.setLetterSpacing(1.037);

	verdana2.load("verdana.ttf", font_size2, true, true);
	verdana2.setLineHeight(38.0f);
	verdana2.setLetterSpacing(1.037);
	width = w;
	height = h;
}

void Scatterplot::draw()
{
	ofSetColor(255, 255, 255);
	



	ofPushMatrix();
	ofTranslate(x_pos, y_pos);
	ofSetColor(255, 255, 255);
	ofDrawRectangle(0, 0, width, height);
	ofSetColor(0, 0, 0);
	ofPoint origin;
	origin.set(x_label_offset, height-y_label_offset);
	ofPoint x_end;
	x_end.set(width-x_label_offset +30, height-y_label_offset );
	ofPoint y_end;
	y_end.set(0+y_label_offset, 0+y_label_offset -30);
	

	ofDrawArrow(origin, x_end, 5);
	verdana1.drawString(column_name[x_axis_col]->col_name, x_label_offset+110, height - y_label_offset+30);
	ofDrawArrow(origin, y_end, 5);
	ofPushMatrix();
	ofRotate(-90.0f, 0.0f, 0.0f, 1.0f);
	verdana1.drawString(column_name[y_axis_col]->col_name, y_label_offset - height +110 , x_label_offset-35 );
	ofPopMatrix();
	
	ofSetColor(0, 0, 0, 200);
	ofDrawLine(x_label_offset + 75, height - y_label_offset, 0 + y_label_offset + 75, 0 + y_label_offset);
	float tick_val1 = ofMap(75, 0, width - x_label_offset - 50, column_name[x_axis_col]->min, column_name[x_axis_col]->max);
	string str_t1 = to_string(tick_val1);
	string sub1 = str_t1.substr(0, 5);
	verdana2.drawString(sub1, x_label_offset + 75, height - y_label_offset+10);

	ofDrawLine(x_label_offset + 150, height - y_label_offset, 0 + y_label_offset + 150, 0 + y_label_offset);
	float tick_val2 = ofMap(150, 0, width - x_label_offset - 50, column_name[x_axis_col]->min, column_name[x_axis_col]->max);
	string str_t2 = to_string(tick_val2);
	string sub2 = str_t2.substr(0, 5);
	verdana2.drawString(sub2, x_label_offset + 150, height - y_label_offset+10);

	
	ofDrawLine(x_label_offset , height - y_label_offset - 75, width - x_label_offset, height - y_label_offset-75);
    float tick_val3 = ofMap(75, 0, height - y_label_offset - 50, column_name[y_axis_col]->min, column_name[y_axis_col]->max );
	string str_t3 = to_string(tick_val3);
	string sub3 = str_t3.substr(0, 5);
	verdana2.drawString(sub3, x_label_offset-30, height - y_label_offset - 75);
	
	
	ofDrawLine(x_label_offset, height - y_label_offset - 150, width - x_label_offset, height - y_label_offset - 150);
	float tick_val4 = ofMap(150, 0, height - y_label_offset - 50, column_name[y_axis_col]->min, column_name[y_axis_col]->max);
	string str_t4 = to_string(tick_val4);
	string sub4 = str_t4.substr(0, 5);
	verdana2.drawString(sub4, x_label_offset-30, height - y_label_offset - 150);
	
	

	


	for (int i = 0; i < column_val[x_axis_col].size(); i++)
	{
		if (*column_val[x_axis_col][i] >= column_name[x_axis_col]->min && *column_val[x_axis_col][i] <= column_name[x_axis_col]->max && *column_val[y_axis_col][i] >= column_name[y_axis_col]->min && *column_val[y_axis_col][i] <= column_name[y_axis_col]->max)
		{
			
			float x_scaled = ofMap(*column_val[x_axis_col][i], column_name[x_axis_col]->min, column_name[x_axis_col]->max, 0, width - x_label_offset - 50) + x_label_offset;
			float y_scaled = height - ofMap(*column_val[y_axis_col][i], column_name[y_axis_col]->min, column_name[y_axis_col]->max, 0, height - y_label_offset - 50) - y_label_offset;
			float width1 = brush_start.x - brush_end.x;
			float height1= brush_start.y - brush_end.y;
			
		    if (*brushed1[i][x_axis_col]==1 && *brushed1[i][y_axis_col]==1) {
				ofSetColor(66,244,0);
				ofDrawCircle(x_scaled, y_scaled, 3);
			}
			else {
				ofSetColor(168, 166, 166);
				ofDrawCircle(x_scaled, y_scaled, 3);
			}
		
		}

	}

	int value = 0;
	float distance_from_point = 3;
	for (int i = 0; i < column_val[x_axis_col].size(); i++) {
		if (*column_val[x_axis_col][i] >= column_name[x_axis_col]->min && *column_val[x_axis_col][i] <= column_name[x_axis_col]->max && *column_val[y_axis_col][i] >= column_name[y_axis_col]->min && *column_val[y_axis_col][i] <= column_name[y_axis_col]->max)
		{

			float x_new = ofMap(*column_val[x_axis_col][i], column_name[x_axis_col]->min, column_name[x_axis_col]->max, 0, width - x_label_offset - 50) + x_label_offset;
			float y_new = height - ofMap(*column_val[y_axis_col][i], column_name[y_axis_col]->min, column_name[y_axis_col]->max, 0, height - y_label_offset - 50) - y_label_offset;
			float near_points_distance = ofVec2f(x_new, y_new).distance(ofVec2f(x_mouse - x_pos, y_mouse - y_pos));
			if (near_points_distance < 3 && near_points_distance < distance_from_point)
			{
				value = i;
				distance_from_point = near_points_distance;

			}
		}
	}
	
	if (value != 0)
	{
		ofSetColor(168, 37, 37);
		float x_scaled1 = ofMap(*column_val[x_axis_col][value], column_name[x_axis_col]->min, column_name[x_axis_col]->max, 0, width - x_label_offset -50 ) + x_label_offset;
		float y_scaled1 = height - ofMap(*column_val[y_axis_col][value], column_name[y_axis_col]->min, column_name[y_axis_col]->max, 0, height- y_label_offset - 50 ) - y_label_offset;
		ofDrawCircle(x_scaled1, y_scaled1, 5);
		x_scaled1 = x_scaled1+ 7;
		y_scaled1 = y_scaled1 + 7;
		string x_label = to_string(*column_val[x_axis_col][value]);
		string x_label_sub = x_label.substr(0, 5);
		string y_label = to_string(*column_val[y_axis_col][value]);
		string y_label_sub = y_label.substr(0, 5);
		string point_label;
		point_label.append("x = ");
		point_label.append(x_label_sub);
		point_label.append(", y = ");
		point_label.append(y_label_sub);
		ofSetColor(128,128,128);
		int rect_size_w = 120;
		int rect_size_h = 30;
        
		ofDrawRectRounded(x_scaled1 - rect_size_w - 15, y_scaled1 - rect_size_h , rect_size_w, rect_size_h, 12);
		ofSetColor(255,255,255);
		verdana2.drawString(point_label, x_scaled1 - rect_size_w -10  , y_scaled1 - rect_size_h +17);
	}
	
	if (brush_status == BRUSH_ENABLED) {
		
		ofSetColor(0, 0, 0, 50);
		ofDrawRectangle(brush_start.x - x_pos, brush_start.y - y_pos, brush_end.x -brush_start.x , brush_end.y - brush_start.y);

	}
	ofPopMatrix();
	
	 
}


void Scatterplot::set_column_name(std::vector<Column*> col_name)
{
	column_name = col_name;
	x_axis_col = 0;
	y_axis_col = 1;

}

void Scatterplot::set_column_val(std::vector<std::vector<float*>> col_val)
{
	column_val = col_val;
}

void Scatterplot::set_reference_pos(int x, int y)
{
	x_pos = x;
	y_pos = y;
}

void Scatterplot::set_brushed_info(vector<vector<int*>> b)
{
	brushed1 = b;
}

void Scatterplot::drop_label(int which_label)
{
	if (change_label_x) {
		x_axis_col = which_label;
	
	}
	else {
		y_axis_col = which_label;
	}
	change_label_x = !change_label_x;
}

void Scatterplot::clear()
{
	x_axis_col = 0;
	y_axis_col = 1;
	brush_status = BRUSH_DISABLED;
	change_label_x = true;
	brush_start.x=0;
	brush_start.y = 0;
	brush_end.x=0;
	brush_end.y = 0;
}




void Scatterplot::brush()
{
	ofPoint brush_start_offset_rm;
	ofPoint brush_end_offset_rm;
	
	brush_start_offset_rm.x = MIN(brush_start.x, brush_end.x) - x_label_offset - x_pos;
	brush_start_offset_rm.y = height - MAX(brush_start.y, brush_end.y) - y_label_offset + y_pos;

	brush_end_offset_rm.x = MAX(brush_start.x, brush_end.x) - x_label_offset - x_pos;
	brush_end_offset_rm.y = height - MIN(brush_start.y, brush_end.y) - y_label_offset + y_pos;
	
	float x1 = ofMap(brush_start_offset_rm.x, 0, width - x_label_offset - 50, column_name[x_axis_col]->min , column_name[x_axis_col]->max );
	float y1 = ofMap(brush_start_offset_rm.y, 0, height - y_label_offset - 50, column_name[y_axis_col]->min, column_name[y_axis_col]->max);
	float x2 = ofMap(brush_end_offset_rm.x, 0, width - x_label_offset - 50, column_name[x_axis_col]->min, column_name[x_axis_col]->max);
	float y2 = ofMap(brush_end_offset_rm.y, 0, height - y_label_offset - 50, column_name[y_axis_col]->min, column_name[y_axis_col]->max);

	for (int i = 0; i < brushed1.size(); i++) {
		if (*column_val[x_axis_col][i] >= x1 && *column_val[x_axis_col][i] <= x2 && *column_val[y_axis_col][i] >= y1 && *column_val[y_axis_col][i] <= y2) {
			*brushed1[i][x_axis_col] = 1;
			*brushed1[i][y_axis_col] = 1;
		}
		else {
			*brushed1[i][x_axis_col] = 0;
			*brushed1[i][y_axis_col] = 0;
		}
		
	}
}

void Scatterplot::mouseMoved(ofMouseEventArgs & args)
{
	x_mouse = args.x;
	y_mouse = args.y;
    
}

void Scatterplot::mouseDragged(ofMouseEventArgs & args)
{   

	if (brush_status == BRUSH_ENABLED) {
		brush_end.x = args.x;
		brush_end.y = args.y;
		brush();
	}
}

void Scatterplot::mousePressed(ofMouseEventArgs & args)
{
	float brushed_click_x = args.x - x_label_offset - x_pos;
	float brushed_click_y= height - args.y - y_label_offset + y_pos;
	
	
	if (brushed_click_x >= 0 && brushed_click_x<= width  && brushed_click_y>=0 && brushed_click_y <= height)
	{
		if (args.button == 0 || args.button == 1) {

			brush_status = BRUSH_ENABLED;
			brush_start.x = args.x;
			brush_start.y = args.y;
			brush_end.x = args.x;
			brush_end.y = args.y;
		

			for (int i = 0; i < brushed1.size(); i++) {
				*brushed1[i][x_axis_col] = 1;
				*brushed1[i][y_axis_col] = 1;
			}
		}
		else
		{
			//reset brush
			brush_status = BRUSH_DISABLED;
			brush_start.x = 0;
			brush_start.y = 0;
			brush_end.x = 0;
			brush_end.y = 0;

			for (int i = 0; i < brushed1.size(); i++) {
				*brushed1[i][x_axis_col] = 1;
				*brushed1[i][y_axis_col] = 1;
			}
		}
	}
}

void Scatterplot::mouseReleased(ofMouseEventArgs & args)
{
	if (brush_status == BRUSH_ENABLED) {
		brush_end.x = args.x;
		brush_end.y = args.y;

		brush();

		

	}
}

void Scatterplot::mouseScrolled(ofMouseEventArgs & args)
{
}

void Scatterplot::mouseEntered(ofMouseEventArgs & args)
{
}

void Scatterplot::mouseExited(ofMouseEventArgs & args)
{
}


