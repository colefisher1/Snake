#pragma once
class Tile
{
public:
	int getStatus()
	{
		return status;
	}
	void setStatus(int num)
	{
		status = num;
	}
private:
		int status; // 0-Empty, 1- Snake, 2- Apple, 3 - Boundary 4 - Loss

};

