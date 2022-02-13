#ifndef _THEPACMANGAME_H_
#define _THEPACMANGAME_H_
#define _CRT_SECURE_NO_WARNINGS
#include "io_utils.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Point.h"
#include "Fruit.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include<exception>

using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;

class ThePacmanGame
{
	enum { ROWS = 24, COLS = 80, ESC = 27, WON = 1, LOSE = 0 ,STARTBOARD=2};
	int filesSize;
	vector<string>	files = getScreenFiles();
	Pacman p;
	Ghost* gstarr;
	Fruit fruit;
	char initbrd[25][80];
	int menurowstart,menucolstart,ghostCounter;
	Point Pacmanstart;
	Point* Ghostsstart=nullptr;
	int rowBoard,colBoard,totalPoints;
	int startRowBoard,endRowBoard;
	int lives;

public:
	ThePacmanGame()
	{
		filesSize = files.size();
		menurowstart = 0, menucolstart = 0, ghostCounter = 0;
		totalPoints = 0;
		lives = 3;
	}
	vector<string> getScreenFiles() const;
	void printboard();
	bool IfMenuIsFirst()
	{
		if (startRowBoard == STARTBOARD)
			return true;
		return false;
	}
	int StartGame(fstream& inputfile,fstream& outputfile,fstream& resfile, ThePacmanGame& p, char level,int caseOpt, int& totalPacmanMoves);
	int run(fstream& outputfile,fstream& resfile, int score, int totalPoints, char level,int caseOpt, int& totalPacmanMoves);
	int runFromFile(fstream& outputfile, fstream& resfile, int score, int totalPoints, char level, int caseOpt, int& totalPacmanMoves);
	char Selectlevel();
	bool GetMovesFromFiles(fstream& stepfile, string& line, string& objInput, string& dirObj, int& ghostCounter, Pacman& p, bool& delaymonsters,bool& withFruit, Fruit& fruit, Ghost* gstarr, char* CurrentGhostsCharArr, bool& IfMenuIsFirst,Point& Pacmanstart, Point* Ghostsstart, int& menucolstart, int& menurowstart, int& lives);
	char GetCharFromBoard(int x, int y)
	{
		char ch;
		ch = initbrd[y][x];
		return ch;
	}
	int GetMenuRowStart() { return menurowstart; }
	int GetMenuColStart() { return menucolstart; }
	int GetrowBoard() { return rowBoard; }
	int GetColBoard() { return colBoard; }
	int GetNumOfBoard() { return filesSize; }
	void EscFunc(char* key, Ghost* gstarr, int gstsize, Pacman* p, int pacmanprevdir, int menurowstart, int menucolstart, bool IfMenuIsFirst);
	void MakeRandomFruitPoint(int* randomfruitx, int* randomfruity, int rowBoard, int colBoard);
	void UpdateSteps(Point& CurrentPacmanStep, Point& CurrentFruitStep, Point& NextPacmanStep, Point& NextFruitStep, char& CurrentPacmanChar, char& NextPacmanChar, char& CurrentFruitChar, char& NextFruitChar, char* CurrentGhostsCharArr, char* NextGhostsCharArr,
		Pacman& p, Fruit& fruit, int ghostCounter, Point* CurrentGhostsStepArr, Point* NextGhostsStepArr, Ghost* gstarr, int PACdir);
};
void ConvertToObjAndDir(string stringToConvert, string& objInput, string& dirObj);
void ConvertToInt(string stringToConvert, int& Xtemp, int& Ytemp,char& fig);
Point GetNextStep(int Direction, int Currentx, int Currenty);
void GameOverFunc(char* key2);
void SmartDirection(int* newdirection, Point CurrentGhostStep, Point CurrentPacmanStep, Ghost* gstarr, char initbrd[][80]);
bool checkWin(char& key, int score,int totalPoints, int caseOpt);
void CalcCurrentGhostsSteps(int ghostCounter, Point* CurrentGhostsStepArr, Ghost* gstarr);
void CalcNextGhostsStep(int ghostCounter, Point* NextGhostsStepArr, Ghost* gstarr);
void CountsScore(char CurrentPacmanChar, Point CurrentPacmanStep, int& score, char initbrd[][80]);
void printmenu();
void FindStepsFiles(int filescounter);
void printinstructions();


#endif