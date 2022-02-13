#ifndef _PACMAN_H
#define _PACMAN_H

#include <cstring>
#include "Point.h"
#include<exception>

class Pacman:public Point {
	int direction;
	char arrowKeys[10];
	char figure;
	int scorecounter;
public:
	Pacman(int _direction = 8, char _fig = '@', int _scorecounter = 0) {
		arrowKeys[0] = 'w';
		arrowKeys[1] = 'W';
		arrowKeys[2] = 'x';
		arrowKeys[3] = 'X';
		arrowKeys[4] = 'a';
		arrowKeys[5] = 'A';
		arrowKeys[6] = 'd';
		arrowKeys[7] = 'D';
		arrowKeys[8] = 's';
		arrowKeys[9] = 'S';
		direction = _direction;
		figure = _fig;
		scorecounter = _scorecounter;
	}
	void setFigure(const char c) {
		figure = c;
	}
	void move(char nextch, Point nextstep,bool IfMenuIsFirst, int rowBoard, int colBoard, fstream& outputfile,string obj,bool withFiles,int& totalPacmanMoves);
	void deletepac(bool IfMenuIsFirst,char ch = ' ')
	{
		Point::draw(ch,IfMenuIsFirst);
	}
	int getDirection(char key);
	void setDirection(int dir) {
		direction = dir;
	}

};

#endif