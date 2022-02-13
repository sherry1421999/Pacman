#include "Point.h"

void Point::draw(char ch,bool IfMenuIsFirst) {
	if(!IfMenuIsFirst)
	gotoxy(x, y);
	else 
	gotoxy(x, y+2);
	cout << ch << endl;
}



void Point::move(int dir,int rowBoard,int colBoard,fstream& outputfile,string obj,bool withFiles) {
	
	if (withFiles == true)
	outputfile <<obj;
	switch (dir) {
	case 0 :
	case 1:
	// UP
		--y;
		if(withFiles==true)
		outputfile<<"up";
		if (y < 1) {
			y = rowBoard-1;
		}
		break;
	case 2:
	case 3:// DOWN
		++y;
		if (withFiles == true)
		outputfile << "down";
		if (y > rowBoard-1) {
			y = 0;
		}
		break;
	case 4:
	case 5:// LEFT
		--x;
		if (withFiles == true)
		outputfile << "left";
		if (x < 1) {
			x = colBoard-1;
		}
		break;
	case 6:
	case 7:// RIGHT
		++x;
		if (withFiles == true)
		outputfile << "right";
		if (x > colBoard-1) {
			x = 0;
		}
		break;

	default://STAY
		if (withFiles == true)
		outputfile << "stay";
		break;

	}
	if(withFiles==true)
	outputfile << endl;
	
}
void Point::setx(int _x)
{
	this->x = _x;
}
void Point::sety(int _y)
{
	this->y = _y;
}
void Point::setpoint(int _x,int _y)
{
	this->y = _y;
	this->x = _x;
}
int Point::getx()
{
	return this->x;
}
int Point::gety() {
	return this->y;
}