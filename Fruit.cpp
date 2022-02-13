#include "Fruit.h"
#include "ThePacmanGame.h"

bool Fruit::move(char fruitnextchar, char fruitcurchar, bool IfMenuIsFirst,int rowBoard,int colBoard,fstream& outputfile,string obj,bool withFiles)
{

	if (fruitnextchar == '#' || this->getx() > colBoard || this->gety() > rowBoard||this->getx()<0||this->gety()<0)
	{
		if (this->getfruitDirection() == 8)
		{
			Point::draw(' ', IfMenuIsFirst);
		}
		else
		Point::draw(figure, IfMenuIsFirst);
		int randomIndex;
		int DirectionArr[4] = { 1,3,5,7 };
		srand(time(NULL));
		randomIndex = rand() % 4;
		while (DirectionArr[randomIndex] == fruitdirection || DirectionArr[randomIndex] - 1 == fruitdirection)
		{
			randomIndex = rand() % 4;
		}
		fruitdirection = DirectionArr[randomIndex];

		return true;
	}
	else if (fruitcurchar == ' ' && this->getx() < colBoard && this->gety() < rowBoard && this->getx() > 0 && this->gety() > 0)
	{
		Point::draw(figure, IfMenuIsFirst);
		Point::draw(' ', IfMenuIsFirst);
		Point::move(fruitdirection, rowBoard, colBoard,outputfile,obj,withFiles);
		Point::draw(figure, IfMenuIsFirst);
		return false;
	}
	else if (fruitcurchar == '.' && this->getx() < colBoard && this->gety() < rowBoard && this->getx() > 0 && this->gety() > 0)
	{
		Point::draw(figure, IfMenuIsFirst);
		Point::draw('.', IfMenuIsFirst);
		Point::move(fruitdirection,rowBoard,colBoard,outputfile,obj,withFiles);
		Point::draw(figure, IfMenuIsFirst);
		return false;
	}
}
int Fruit::getfruitDirection()
{
	return fruitdirection;
}


