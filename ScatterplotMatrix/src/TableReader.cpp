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

	while (std::getline(myfile, line))
	{
		if (line_count == 0)
		{
			char * pch;
			char * writable = new char[line.size() + 1];
			std::copy(line.begin(), line.end(), writable);
			writable[line.size()] = '\0';

			pch = strtok(writable, "\t");
			while (pch != NULL)
			{
				column_name.push_back(pch);
				column_val.push_back(std::vector<float>());
				pch = strtok(NULL, "\t");
			}
		}
		else

		{
			char * pch;
			char * writable = new char[line.size() + 1];
			std::copy(line.begin(), line.end(), writable);
			writable[line.size()] = '\0';

			pch = strtok(writable, "\t");
			int index = 0;
			while (pch != NULL)
			{
				column_val[index].push_back(std::stof(pch));
				pch = strtok(NULL, "\t");
				index++;
			}
		}
		line_count++;
	}
	myfile.close();

}

std::vector<float> TableReader::get_column(int which_column)
{
	return column_val[which_column];
}

std::string TableReader::get_column_name(int which_column)
{
	return column_name[which_column];
}





