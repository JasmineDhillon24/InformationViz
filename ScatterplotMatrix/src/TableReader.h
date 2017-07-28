#pragma once
#include "iostream"
#include "vector"
#include "string"
#include<string.h>

class TableReader
{
public:
	TableReader();
	~TableReader();
	void read_data(const char* filename);
	std::vector<std::string> column_name;
	std::vector<std::vector<float>> column_val;
	std::vector<float> get_column(int which_column);
	std::string get_column_name(int which_column);
};




