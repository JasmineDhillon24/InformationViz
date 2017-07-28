#include "TableReader.h"
#include "fstream"
#include "sstream"

TableReader::TableReader()
{
	
}


TableReader::~TableReader()
{
}

void TableReader::read_data(const char * filename)
{
	std::ifstream myfile;
	myfile.open(filename);
	std::string line;
	int line_count = 0;
	vector<string> temp_cols;

	while (std::getline(myfile, line)) {
		if (line_count == 0)
		{
			char * pch;
			char * writable = new char[line.size() + 1];
			std::copy(line.begin(), line.end(), writable);
			writable[line.size()] = '\0';

			pch = strtok(writable, "\t");
			while (pch != NULL)
			{
				temp_cols.push_back(pch);
				pch = strtok(NULL, "\t");
			}
		}
		else if (line_count == 1) {
			char * pch;
			char * writable = new char[line.size() + 1];
			std::copy(line.begin(), line.end(), writable);
			writable[line.size()] = '\0';

			pch = strtok(writable, "\t");
			int index = 0;
			int temp_index = 0;
			while (pch != NULL)
			{
				int k = 0;
				bool is_num = true;
				string str = pch;
				while (k < str.length()) {
					if (isdigit(pch[k]) || pch[k] == '.')
					{

					}
					else {
						is_num = false;
						break;
					}
					k++;
				}
				if (is_num) {
					Column *c = new Column();
					c->col_name = temp_cols[temp_index];
					column_name.push_back(c);
					column_val.push_back(std::vector<float*>());
					index++;
				}
				pch = strtok(NULL, "\t");
				temp_index++;
			}

			break;
		}
		line_count++;
	}
	myfile.close();

	myfile.open(filename);
	line_count = 0;
	while (std::getline(myfile, line))
	{
		
		if(line_count > 0){
			char * pch;
			char * writable = new char[line.size() + 1];
			std::copy(line.begin(), line.end(), writable);
			writable[line.size()] = '\0';

			pch = strtok(writable, "\t");
			int index = 0;
			while (pch != NULL)
			{
				int k = 0;
				bool is_num = true;
				string str = pch;
				while (k < str.length()) {
					if (isdigit(pch[k]) || pch[k] == '.')
					{

					}
					else {
						is_num = false;
						break;
					}
					k++;
				}
				if (is_num) {
					float* val = new float();
					*val = std::stof(pch);
					column_val[index].push_back(val);
					index++;
				}
				pch = strtok(NULL, "\t");
			}
		}
		line_count++;
	}
	myfile.close();

	// calculate min-max
	for (int i = 0; i < column_name.size(); i++) {
		float min= *column_val[i][0] , max= *column_val[i][0] ;

		for (int j = 0; j < column_val[i].size(); j++) {
			if (min > *column_val[i][j])
				 min = *column_val[i][j];
			
				if (max < *column_val[i][j])
				 max = *column_val[i][j];

		}

		column_name[i]->min = min;
		column_name[i]->max = max;
	}
}

std::vector<vector<float*>> TableReader::get_column_values()
{
	return column_val;
}

std::vector<Column*> TableReader::get_column_name()
{
	return column_name;
}

void TableReader::clear()
{
	for (int i = 0; i < column_name.size(); i++) {
		column_val[i].clear();
	}
	column_name.clear();
	column_val.clear();
}





