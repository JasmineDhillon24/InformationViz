#pragma once
#include <vector>

class BrushEventInfo
{
public:
	BrushEventInfo();
	~BrushEventInfo();

	std::vector<int> brushed_indexes;
	std::vector<int> unbrushed_indexes;
	int sp_index;
	int brush_status;
};

