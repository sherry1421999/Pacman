#include "Pacman.h"
#include "ThePacmanGame.h"
#include "Ghost.h"


void Pacman::move(char nextch, Point nextstep,bool IfMenuIsFirst,int rowBoard,int colBoard,fstream& outputfile,string obj,bool withfiles,int& totalPacmanMoves)
{
	Point currentPacmanStep=Point(this->getx(),this->gety());
	Point::draw(figure,IfMenuIsFirst);
	if (nextch != '#') {
		Point::draw(' ',IfMenuIsFirst);
		Point::move(direction,rowBoard,colBoard,outputfile,obj,withfiles);
		Point::draw(figure, IfMenuIsFirst);
	}
	else
	{
		if (withfiles == true)
			outputfile << obj<<"stay"<<endl;
	}
	Point currentNewPacmanStep = Point(this->getx(), this->gety());
	if(currentNewPacmanStep.getx()!= currentPacmanStep.getx()|| currentNewPacmanStep.gety() != currentPacmanStep.gety())
		totalPacmanMoves++;

}

int Pacman::getDirection(char key)
{
	for (int i = 0; i < 10; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}