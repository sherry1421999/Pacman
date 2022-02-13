#ifndef _GHOST_H
#define _GHOST_H
#include <time.h> 
#include <cstring>
#include "Point.h"
#include<exception>


class Ghost :public Point{
	int ghostdirection;
	char figure;

public:
	Ghost(int gstdir=1,char fig='$')
	{
		ghostdirection = gstdir;
		figure = fig;
	};
	void setFigure(const char c) {
		figure = c;
	}
	void deleteghost(char ch,bool IfMenuIsFirst)
	{
		
		Point::draw(ch,IfMenuIsFirst);
		
	}
	bool move(char ghost1nextchar,char ghost1curchar,bool IfMenuIsFirst,char level,int rowBoard,int colBoard,fstream& outputfile,string obj,bool withFiles);
	int getghostDirection();
	void setghostDirection(int dir) {

		ghostdirection = dir;
	}

};

#endif