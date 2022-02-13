#ifndef _POINT_H_
#define _POINT_H_


#include <iostream>
#include <fstream>
#include "io_utils.h"
#include<exception>

using namespace std;

class Point {
	int x;
	int y;

public:
	void draw(char ch,bool IfMenuIsFirst);
	Point(int _x, int _y) :x(_x), y(_y) {}
	Point()
	{
		x = 38;
		y = 16;
	}
	void setx(int _x);
	void sety(int _y);
	void setpoint(int _x, int _y);
	virtual void move(int direction,int rowBoard,int colBoarad, fstream& outputfile,string obj,bool withFiles);
	int getx();
	int gety();
};

#endif