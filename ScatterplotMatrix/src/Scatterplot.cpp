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
	width = w;
	height = h;
    font_size1 = 10;
	
	if (width/25 >= 8) {
		font_size2 = width/25;
	}
	else font_size2 = 8;
	x_label_offset = w / 20;
    y_label_offset = h / 20;
	verdana1.load("verdana.ttf", font_size1, true, true);
	verdana1.setLineHeight(38.0f);
	verdana1.setLetterSpacing(1.037);

	verdana2.load("verdana.ttf", font_size2, true, true);
	verdana2.setLineHeight(38.0f);
	verdana2.setLetterSpacing(1.037);
	
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
	x_end.set(width-x_label_offset +0, height-y_label_offset );
	ofPoint y_end;
	y_end.set(0+y_label_offset, 0+y_label_offset -0);
	

	ofDrawArrow(origin, x_end, width/40);
	verdana1.drawString(x_axis_name, x_label_offset + width/2, height - y_label_offset + width/6);
	ofDrawArrow(origin, y_end, width/40);
	verdana1.drawString(y_axis_name, y_label_offset - height + width/2, x_label_offset - width/6);
	ofPushMatrix();
	ofRotate(-90.0f, 0.0f, 0.0f, 1.0f);
	ofPopMatrix();
	
	ofSetColor(0, 0, 0, 200);
	if (width / 25 >= 8)
	{
		ofDrawLine(x_label_offset + width / 3, height - y_label_offset, 0 + y_label_offset + width / 3, 0 + y_label_offset);
		float tick_val1 = ofMap(width / 3, 0, width - x_label_offset - 50, min_x, max_x);
		string str_t1 = to_string(tick_val1);
		string sub1 = str_t1.substr(0, 3);
		verdana2.drawString(sub1, x_label_offset + width / 3, height - y_label_offset + width / 22);

		ofDrawLine(x_label_offset + (2 * width) / 3, height - y_label_offset, 0 + y_label_offset + (2 * width) / 3, 0 + y_label_offset);
		float tick_val2 = ofMap((2 * width) / 3, 0, width - x_label_offset - 50, min_x, max_x);
		string str_t2 = to_string(tick_val2);
		string sub2 = str_t2.substr(0, 3);
		verdana2.drawString(sub2, x_label_offset + (2 * width) / 3, height - y_label_offset + width / 22);


		ofDrawLine(x_label_offset, height - y_label_offset - width / 3, width - x_label_offset, height - y_label_offset - width / 3);
		float tick_val3 = ofMap(width / 3, 0, height - y_label_offset - 50, min_y, max_y);
		string str_t3 = to_string(tick_val3);
		string sub3 = str_t3.substr(0, 3);
		verdana2.drawString(sub3, x_label_offset - width / 13, height - y_label_offset - width / 3);


		ofDrawLine(x_label_offset, height - y_label_offset - (2 * width) / 3, width - x_label_offset, height - y_label_offset - (2 * width) / 3);
		float tick_val4 = ofMap((2 * width) / 3, 0, height - y_label_offset - 50, min_y, max_y);
		string str_t4 = to_string(tick_val4);
		string sub4 = str_t4.substr(0, 3);
		verdana2.drawString(sub4, x_label_offset - width / 13, height - y_label_offset - (2 * width) / 3);
	}
	else
	{
		
		ofDrawLine(x_label_offset + width / 3, height - y_label_offset, 0 + y_label_offset + width / 3, 0 + y_label_offset);
		float tick_val1 = ofMap(width / 3, 0, width - x_label_offset - 50, min_x, max_x);
		string str_t1 = to_string(tick_val1);
		string sub1 = str_t1.substr(0, 3);
		verdana2.drawString(sub1, x_label_offset + width / 3 , height - y_label_offset + width / 17);

		ofDrawLine(x_label_offset + (2 * width) / 3, height - y_label_offset, 0 + y_label_offset + (2 * width) / 3, 0 + y_label_offset);
		float tick_val2 = ofMap((2 * width) / 3, 0, width - x_label_offset - 50, min_x, max_x);
		string str_t2 = to_string(tick_val2);
		string sub2 = str_t2.substr(0, 3);
		verdana2.drawString(sub2, x_label_offset + (2 * width) / 3, height - y_label_offset + width / 17);


		ofDrawLine(x_label_offset, height - y_label_offset - width / 3, width - x_label_offset, height - y_label_offset - width / 3);
		float tick_val3 = ofMap(width / 3, 0, height - y_label_offset - 50, min_y, max_y);
		string str_t3 = to_string(tick_val3);
		string sub3 = str_t3.substr(0, 3);
		verdana2.drawString(sub3, x_label_offset - width / 7, height - y_label_offset - width / 3);


		ofDrawLine(x_label_offset, height - y_label_offset - (2 * width) / 3, width - x_label_offset, height - y_label_offset - (2 * width) / 3);
		float tick_val4 = ofMap((2 * width) / 3, 0, height - y_label_offset - 50, min_y, max_y);
		string str_t4 = to_string(tick_val4);
		string sub4 = str_t4.substr(0, 3);
		verdana2.drawString(sub4, x_label_offset - width / 7, height - y_label_offset - (2 * width) / 3);

	}

	
	if (brush_status == BRUSH_ENABLED || other_sp_brush_status == BRUSH_ENABLED) {
		ofSetColor(120, 92, 255);
		for (int i = 0; i <be.brushed_indexes.size(); i++) {
			int index = be.brushed_indexes[i];
			float x_scaled = ofMap(x_data[index], min_x, max_x, 0, width - x_label_offset - 50) + x_label_offset;
			float y_scaled = height - ofMap(y_data[index], min_y, max_y, 0, height - y_label_offset - 50) - y_label_offset;
			ofDrawCircle(x_scaled, y_scaled, width/66);

		}

		ofSetColor(153, 0, 0);
		for (int i = 0; i <be.unbrushed_indexes.size(); i++) {
			int index = be.unbrushed_indexes[i];
			float x_scaled = ofMap(x_data[index], min_x, max_x, 0, width - x_label_offset - 50) + x_label_offset;
			float y_scaled = height - ofMap(y_data[index], min_y, max_y, 0, height - y_label_offset - 50) - y_label_offset;
			ofDrawCircle(x_scaled, y_scaled, width/66);

		}
	}
	else {
		for (int i = 0; i < x_data.size(); i++)
		{
			ofSetColor(120, 92, 255);
			float x_scaled = ofMap(x_data[i], min_x, max_x, 0, width - x_label_offset - 50) + x_label_offset;
			float y_scaled = height - ofMap(y_data[i], min_y, max_y, 0, height - y_label_offset - 50) - y_label_offset;
			ofDrawCircle(x_scaled, y_scaled, width/66);

		}


	}

	
	
	if (brush_status == BRUSH_ENABLED) {
		float bs_x = brush_start.x - x_label_offset - x_pos;
		float bs_y = brush_start.y - y_label_offset - y_pos;
		float be_x = brush_end.x - x_label_offset - x_pos;
		float be_y = brush_end.y - y_label_offset - y_pos;
		ofSetColor(0, 0, 0, 100);
		ofDrawRectangle(bs_x + x_label_offset, bs_y + y_label_offset, be_x -bs_x , be_y - bs_y);

	}
	ofPopMatrix();
	
	 
}

void Scatterplot::set_current_range(float x1, float x2, float y1, float y2)
{
	current_min_x_1 = x1;
	current_max_x_1 = x2;
	current_min_y_1 = y1;
	current_max_y_1 = y2;
	
	
}

void Scatterplot::setBrushEventInfo(BrushEventInfo e)
{
	be = e;
	if (be.sp_index != index && brush_status == BRUSH_ENABLED) {
		brush_status = BRUSH_DISABLED;
		brush_start.x = 0;
		brush_start.y = 0;
		brush_end.x = 0;
		brush_end.y = 0;


	}
}

void Scatterplot::set_reference_pos(int x, int y)
{
	x_pos = x;
	y_pos = y;
}

void Scatterplot::set_axis_name(std::string x_name, std::string y_name)
{ 
	x_axis_name = x_name;
	y_axis_name = y_name;
}

void Scatterplot::set_column_val(std::vector<float> x_val, std::vector<float> y_val)
{
	x_data = x_val;
	y_data = y_val;
	min_x = x_data[0];
	min_y = y_data[0];
	max_x = x_data[0];
	max_y = y_data[0];
	for (int j = 1; j < x_data.size(); j++)
	{
		if (min_x > x_data[j])
			min_x = x_data[j];

		if (min_y > y_data[j])
			min_y = y_data[j];

		if (max_y < y_data[j])
			max_y = y_data[j];

		if (max_x < x_data[j])
			max_x = x_data[j];
	}
	set_current_range(min_x, max_x, min_y, max_y);
}

void Scatterplot::set_index(int i)
{
	index = i;
}


void Scatterplot::set_other_sp_brush_status(int status)
{
	other_sp_brush_status = status;
}

void Scatterplot::brush()
{
	ofPoint brush_start_offset_rm;
	ofPoint brush_end_offset_rm;
	
	brush_start_offset_rm.x = MIN(brush_start.x, brush_end.x) - x_label_offset - x_pos;
	brush_start_offset_rm.y = height - MAX(brush_start.y, brush_end.y) - y_label_offset + y_pos;

	brush_end_offset_rm.x = MAX(brush_start.x, brush_end.x) - x_label_offset - x_pos;
	brush_end_offset_rm.y = height - MIN(brush_start.y, brush_end.y) - y_label_offset + y_pos;
	
	float x1 = ofMap(brush_start_offset_rm.x, 0, width - x_label_offset - 50, min_x , max_x );
	float y1 = ofMap(brush_start_offset_rm.y, 0, height - y_label_offset - 50, min_y, max_y);
	float x2 = ofMap(brush_end_offset_rm.x, 0, width - x_label_offset - 50, min_x, max_x);
	float y2 = ofMap(brush_end_offset_rm.y, 0, height - y_label_offset - 50, min_y, max_y);

	BrushEventInfo event_info = BrushEventInfo();
	event_info.sp_index = index;
	event_info.brush_status = BRUSH_ENABLED;
	for (int i = 0; i < x_data.size(); i++) {
		if (x_data[i] >= current_min_x_1 && x_data[i] <= current_max_x_1 && y_data[i] >= current_min_y_1 && y_data[i] <= current_max_y_1) {
			event_info.brushed_indexes.push_back(i);
		}
		else {
			event_info.unbrushed_indexes.push_back(i);
		}
	}

	ofNotifyEvent(brush_event, event_info, this);
	set_current_range(x1, x2, y1, y2);
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
		}
		else
		{
			brush_status = BRUSH_DISABLED;
			brush_start.x = 0;
			brush_start.y = 0;
			brush_end.x = 0;
			brush_end.y = 0;

			BrushEventInfo event_info = BrushEventInfo();
			event_info.sp_index = index;
			event_info.brush_status = BRUSH_DISABLED;
			ofNotifyEvent(brush_event, event_info, this);
			//set_current_range(min_x, max_x, min_y, max_y);
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




