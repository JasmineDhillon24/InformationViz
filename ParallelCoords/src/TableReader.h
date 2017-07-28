#pragma once
#include "iostream"
#include "vector"
#include "string"
#include "cstring"

using namespace std;
typedef struct {
	string col_name;
	float min;
	float max;
}Column;

class TableReader
{
public:
	TableReader();
	~TableReader();
	void read_data(const char* filename);
	std::vector<Column*> column_name;
	std::vector<std::vector<float*>> column_val;
	std::vector<vector<float*>> get_column_values();
	std::vector<Column*> get_column_name();
	void clear();
};




