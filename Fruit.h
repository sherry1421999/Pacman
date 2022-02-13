#ifndef _FRUIT_H
#define _FRUIT_H
#include <time.h> 
#include <cstring>
#include "Point.h"
#include <sstream>
#include<exception>


class Fruit :public Point {
	int fruitdirection;
	char figure;
	int figureval;

public:
	Fruit()
	{
		srand(time(NULL));
		int randomfruitnumber = 5 + (rand() % 5);
		std::string s = std::to_string(randomfruitnumber);
		char const* pchar = s.c_str();
		figure = *pchar;
		fruitdirection = 2;
		figureval = randomfruitnumber;
		
		
	};
	Point GetStartBoardPoint()
	{
		return GetStartBoardPoint();
	}
	void setFigure(const char c) {

		/*srand(time(NULL));
		int randomfruitnumber = 5 + (rand() % 9);
		std::string s = std::to_string(randomfruitnumber);
		char const* pchar = s.c_str();
		figure = *pchar;*/
		figure = c;
		figureval = c - 48;
		//figureval = c;
	}
	char getFigure() {
		return figure;
	}
	int getfruitval() {

		return figureval;
	}
	void deletefruit(char ch, bool IfMenuIsFirst)
	{	
		Point::draw(ch, IfMenuIsFirst);	
	}
	bool move(char fruitnextchar, char fruitcurchar, bool withcolors, int rowBoard, int colBoard,fstream& outputfile,string obj,bool withFiles);
	int getfruitDirection();
	void setfruitDirection(int dir) {
		fruitdirection = dir;
	}

};

#endif