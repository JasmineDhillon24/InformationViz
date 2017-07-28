#include "ParallelCoordinates.h"



ParallelCoordinates::ParallelCoordinates()
{
}


ParallelCoordinates::~ParallelCoordinates()
{
}

void ParallelCoordinates::set_column_name(std::vector<Column*> col_name)
{
	column_name = col_name;
	axis_offset = (width1 - 2 * x_offset) / (column_name.size()-1);
	axis_height = height1 - 2 * y_offset;
	for (int i = 0; i < column_name.size(); i++) {
		min_max_invert.push_back(true);
		brushed_start_val.push_back(-1);
		brushed_end_val.push_back(-1);

	}
}

void ParallelCoordinates::set_column_val(std::vector<std::vector<float*>> col_val)
{
	column_val = col_val;
	int r = 66, g = 244, b_min = 0, b_max = 255;
	float b_offset = (b_max - b_min) / (float)column_val[0].size();
	for (int i = 0; i < column_val[0].size(); i++) {
		ofColor color;
		color.set(r, g, b_min + (int)(i*b_offset));
		line_colors.push_back(color);

		vector<bool> b;
		for (int j = 0; j < column_name.size(); j++)
		{
			b.push_back(true);
		}
		brushed.push_back(b);
	}
}

void ParallelCoordinates::draw()
{
	ofPushMatrix();
	ofTranslate(x_pos1, y_pos1);
	ofSetColor(255, 255, 255);
	ofDrawRectangle(0, 0, width1, height1);




	
	int tick_count = 4;
	float tick_offset = axis_height / (tick_count+1);
	for (int i = 0; i < column_name.size(); i++)
	{
		
		float axis_x = x_offset + i*axis_offset;
		float axis_y = y_offset;
		
		if (i<column_name.size()-1) {
			float axis2_x = x_offset + (i + 1)*axis_offset;
			for (int k = 0; k < column_val[i].size(); k++)
			{
				ofSetColor(line_colors[k]);
				float column1_val = *column_val[i][k];
				float column2_val = *column_val[i+1][k];
				float mapped_val1;
				float mapped_val2;
				if (min_max_invert[i]) {
					mapped_val1 = ofMap(column1_val, column_name[i]->min, column_name[i]->max, axis_y + axis_height, axis_y);
				}
				else {
					mapped_val1 = ofMap(column1_val, column_name[i]->min, column_name[i]->max, axis_y, axis_y + axis_height);
				}
				if (min_max_invert[i + 1]) {
					mapped_val2 = ofMap(column2_val, column_name[i + 1]->min, column_name[i + 1]->max, axis_y + axis_height, axis_y);
				}
				else {
					mapped_val2 = ofMap(column2_val, column_name[i + 1]->min, column_name[i + 1]->max, axis_y, axis_y + axis_height);
				}
				
				bool draw = true;

				for (int j = 0; j < column_name.size() && draw; j++) {
					draw = draw && brushed[k][j];
				}
				if (draw) {
					ofDrawLine(axis_x, mapped_val1, axis2_x, mapped_val2);
				}
				
			}
		}


		ofSetColor(0, 0, 0);
		ofDrawLine(axis_x, axis_y, axis_x, axis_height+ axis_y);

		if (brushed_start_val[i] != -1 && brushed_end_val[i] != -1) {

			ofSetColor(171, 181, 179, 160);
			float start_y = ofMap(brushed_start_val[i], column_name[i]->min, column_name[i]->max, axis_y, axis_y+axis_height );
			float end_y = ofMap(brushed_end_val[i], column_name[i]->min, column_name[i]->max, axis_y, axis_y+axis_height );
			ofDrawRectangle(axis_x - 10, start_y, 20, end_y-start_y);

		}

		ofSetColor(0, 0, 0);
	    string_width= verdana.stringWidth(column_name[i]->col_name);
		verdana1.drawString(column_name[i]->col_name, axis_x- string_width/2, axis_y - 15 );
		string str = to_string(min_max_invert[i] ? column_name[i]->min : column_name[i]->max);
		string sub = str.substr(0, 5);
		string sub4 = min_max_invert[i] ? "MIN = " : "MAX = ";
		string sub5 = sub4.append(sub);
		verdana.drawString(sub5, axis_x - (verdana.stringWidth(sub5)) / 2, axis_height + axis_y + 10);
		string str1 = to_string(min_max_invert[i] ? column_name[i]->max : column_name[i]->min);
		string sub1 = str1.substr(0, 5);
		string sub3 = min_max_invert[i] ? "MAX = " : "MIN = ";
		string sub2 = sub3.append(sub1);
		verdana.drawString(sub2, axis_x - (verdana.stringWidth(sub2)) / 2, axis_y);

		float val_offset = (column_name[i]->max - column_name[i]->min) / tick_count;
		for (int j = 1; j <= tick_count; j++) {
			ofDrawLine(axis_x - 5, axis_y + (tick_count - j + 1)*tick_offset, axis_x + 5, axis_y + (tick_count - j + 1)*tick_offset);
			string str2 = to_string(min_max_invert[i] ? val_offset*j : val_offset*(tick_count - j + 1));
			string sub2 = str2.substr(0, 5);
			verdana.drawString(sub2, axis_x + 10, axis_y + (tick_count - j + 1)*tick_offset + 5);
		}
	}





	ofPopMatrix();
	if (label_clicked != -1) {
		ofSetColor(0, 0, 0);
		verdana.drawString(column_name[label_clicked]->col_name, label_dragged_x + 5, label_dragged_y + 5);

	}
}

void ParallelCoordinates::update()
{

}

void ParallelCoordinates::setup(float x_pos, float y_pos, float width, float height)
{
	ofRegisterMouseEvents(this);
	height1 = height;
	width1 = width;
	x_pos1 = x_pos;
	y_pos1 = y_pos;

	x_offset = 0.025f*width1;
	y_offset = 0.050f*height1;

	verdana.load("verdana.ttf", font_size, true, true);
	verdana.setLineHeight(38.0f);
	verdana.setLetterSpacing(1.037);
	verdana1.load("verdana.ttf", font_size1, true, true);
	verdana1.setLineHeight(38.0f);
	verdana1.setLetterSpacing(1.037);

}

void ParallelCoordinates::clear()
{
	line_colors.clear();
	axis_offset = axis_height = 0;
	min_max_invert.clear();
	label_clicked = -1;
	
	axis_brushed = -1;
	brushed_start_val.clear();
	brushed_end_val.clear();

	for (int i = 0; i < brushed.size(); i++) {
		brushed[i].clear();
	}
	brushed.clear();
	axis_brushed = -1;
}

void ParallelCoordinates::mouseMoved(ofMouseEventArgs & args)
{
	

}

void ParallelCoordinates::mouseDragged(ofMouseEventArgs & args)
{
	if (label_clicked != -1) {
		label_dragged_x = args.x;
		label_dragged_y = args.y;
		return;
	}

	ofPushMatrix();
	ofTranslate(x_pos1, y_pos1);

	if (axis_brushed != -1) {
		float axis_x = x_offset + axis_brushed*axis_offset;
		float axis_y = y_offset;
		float y_coord = args.y - y_pos1;
		if (y_coord < axis_y) {
			y_coord = axis_y;
		}
		else if (y_coord > axis_y + axis_height) {
			y_coord = axis_y + axis_height;
		}
		brushed_end_val[axis_brushed] = ofMap(y_coord, axis_y, axis_y+axis_height, column_name[axis_brushed]->min, column_name[axis_brushed]->max);

		float min, max;
		min = MIN(brushed_start_val[axis_brushed], brushed_end_val[axis_brushed]);
		max = MAX(brushed_start_val[axis_brushed], brushed_end_val[axis_brushed]);
		for (int i = 0; i < column_val[axis_brushed].size(); i++) {
			if (*column_val[axis_brushed][i] < min || *column_val[axis_brushed][i] > max) {
				brushed[i][axis_brushed] = false;
			}
			else {
				brushed[i][axis_brushed] = true;
			}

		}
	
	}

	ofPopMatrix();
	
}

void ParallelCoordinates::mousePressed(ofMouseEventArgs & args)
{
	ofPushMatrix();
	ofTranslate(x_pos1, y_pos1);

	for (int i = 0; i < column_name.size(); i++)
	{
		float axis_x = x_offset + i*axis_offset;
		float axis_y = y_offset;
		if (args.y-y_pos1 >= axis_y- verdana.stringHeight((to_string(column_name[i]->min))) &&  args.y-y_pos1 <= axis_y) {
			if (args.x-x_pos1 >= axis_x - verdana.stringWidth(to_string(column_name[i]->min)) / 2 && args.x-x_pos1<= axis_x + verdana.stringWidth(to_string(column_name[i]->min)) / 2) {				
				min_max_invert[i] = !min_max_invert[i];
				break;
			}
		}
	}

	for (int i = 0; i < column_name.size(); i++)
	{
		float axis_x = x_offset + i*axis_offset;
		float axis_y = y_offset;
		if (args.y - y_pos1 >= axis_y -15 - verdana.stringHeight(column_name[i]->col_name) && args.y - y_pos1 <= axis_y-15) {
			if (args.x - x_pos1 >= axis_x - axis_x - (verdana.stringWidth(column_name[i]->col_name)) / 2 && args.x - x_pos1 <= axis_x + (verdana.stringWidth(column_name[i]->col_name))/2) {
				label_clicked = i;
				break;
			}
		}
	}

	for (int i = 0; i < column_name.size(); i++) {
		float axis_x = x_offset + i*axis_offset;
		float axis_y = y_offset;
		if (args.y - y_pos1 >= axis_y && args.y - y_pos1 <= axis_y + axis_height) {
			if (args.x - x_pos1 >= axis_x - 15 && args.x - x_pos1 <= axis_x + 15) {
				axis_brushed = i;
		
				brushed_start_val[i] = ofMap(args.y - y_pos1, axis_y, axis_y+axis_height, column_name[i]->min, column_name[i]->max);
				brushed_end_val[i] = ofMap(args.y - y_pos1, axis_y, axis_y+axis_height, column_name[i]->min, column_name[i]->max);

				break;

			}
		}
	}

	ofPopMatrix();
}

void ParallelCoordinates::mouseReleased(ofMouseEventArgs & args)
{
	ofPushMatrix();
	ofTranslate(x_pos1, y_pos1);
		
	if (label_clicked != -1) {
		int label_released = -1;

		for (int i = 0; i < column_name.size(); i++)
		{
			float axis_x = x_offset + i*axis_offset;
			float axis_y = y_offset;
			if (args.y - y_pos1 >= axis_y - 15 - verdana.stringHeight(column_name[i]->col_name) && args.y - y_pos1 <= axis_y - 15) {
				if (args.x - x_pos1 >= axis_x - axis_x - (verdana.stringWidth(column_name[i]->col_name)) / 2 && args.x - x_pos1 <= axis_x + (verdana.stringWidth(column_name[i]->col_name)) / 2) {
					label_released = i;
					break;
				}
			}
		}

		if (label_released != -1) {
			if (label_released != label_clicked) {
				Column* temp = column_name[label_clicked];
				vector<float*> temp_val = column_val[label_clicked];
				if (label_clicked < label_released) {
					for (int i = label_clicked; i < label_released; i++) {
						column_name[i] = column_name[i + 1];
						column_val[i] = column_val[i + 1];
					}
				}
				else {
					for (int i = label_clicked; i > label_released; i--) {
						column_name[i] = column_name[i - 1];
						column_val[i] = column_val[i - 1];
					}
				}

				column_name[label_released] = temp;
				column_val[label_released] = temp_val;
			}
			else {
				// clear brush
				brushed_start_val[label_clicked] = brushed_end_val[label_clicked] = -1;
				for (int i = 0; i < column_val[label_clicked].size(); i++) {
					brushed[i][label_clicked] = true;
				}
			}
		}

		label_clicked = -1;
		label_released = -1;
	}
	
	if (axis_brushed != -1) {
		float axis_x = x_offset + axis_brushed*axis_offset;
		float axis_y = y_offset;
		float y_coord = args.y - y_pos1;
		if (y_coord < axis_y) {
			y_coord = axis_y;
		}
		else if (y_coord > axis_y + axis_height) {
			y_coord = axis_y + axis_height;
		}
		brushed_end_val[axis_brushed] = ofMap(y_coord, axis_y, axis_y+axis_height, column_name[axis_brushed]->min, column_name[axis_brushed]->max);

		float min, max;
		min = MIN(brushed_start_val[axis_brushed], brushed_end_val[axis_brushed]);
		max = MAX(brushed_start_val[axis_brushed], brushed_end_val[axis_brushed]);
		for (int i = 0; i < column_val[axis_brushed].size(); i++) {

			if (*column_val[axis_brushed][i] < min || *column_val[axis_brushed][i] > max) {
				brushed[i][axis_brushed] = false;
			}
			else {
				brushed[i][axis_brushed] = true;
			}
		}

		axis_brushed = -1;
				
	}
	ofPopMatrix();
}

void ParallelCoordinates::mouseScrolled(ofMouseEventArgs & args)
{
}

void ParallelCoordinates::mouseEntered(ofMouseEventArgs & args)
{
}

void ParallelCoordinates::mouseExited(ofMouseEventArgs & args)
{
}
