#include "ThePacmanGame.h"

void ConvertToInt(string stringToConvert,int& Xtemp,int& Ytemp,char& fig)
{
	int number = 0;
	int index = 0;
	while (stringToConvert[index] != ':')
	{
		index++;
	}
	//if (index >= stringToConvert.size() || !isdigit(stringToConvert[index]))
	//{
	//	cout << "wrong input";
	//	exit(0);
	//}
	index++;
	while (isdigit(stringToConvert[index]))
	{
		number = number * 10 + (stringToConvert[index++] - '0');
	}
	Xtemp = number;
	index++;
	number = 0;
	while (isdigit(stringToConvert[index]))
	{
		number = number * 10 + (stringToConvert[index++] - '0');
	}
	Ytemp = number;
	index++;
	while (stringToConvert[index] != ':')
	{
		index++;
	}
	index++;
	fig = stringToConvert[index];

	

}
void ConvertToObjAndDir(string stringToConvert, string& objInput, string& dirObj)
{
	int index = 0;
	string sub_str = "";
	if (stringToConvert[index] == '-')
		return;
	while (stringToConvert[index] != ' ')
	{
		sub_str += stringToConvert[index++];
	}
	objInput= sub_str;
	sub_str = "";
	index++;
	if (objInput == "Ghost")
	{
		index += 2;;
	}
	while (stringToConvert[index] !=0)
	{
		sub_str += stringToConvert[index++];
	}
	dirObj = sub_str;
}
void ThePacmanGame::printboard()
{
	for (int i = 0; i < rowBoard; i++) {
		for (int j = 0; j < colBoard; j++)
		{
				cout << initbrd[i][j];
		}
		cout << endl;
	}
}
char ThePacmanGame::Selectlevel()
{
	char level;
	std::cout << "Please choose level:" << endl << "a =BEST , b =GOOD , c =NOVICE" << endl;
	std::cin >> level;
	while (level != 'a' && level != 'b' && level != 'c')
	{
		std::cout << "Invalid char,please try again:" << endl;
		std::cout << "Please choose level:" << endl << "'a' =BEST , 'b' =GOOD , 'c' =NOVICE" << endl;
		std::cin >> level;
	}
	clear_screen();
	return level;
}
int ThePacmanGame::run(fstream& stepfile,fstream& resfile,int score, int totalPoints, char level,int caseOpt,int& totalPacmanMoves)
{
	//Declaration:
	int PACdir = 8, randomfruitx, randomfruity, gdir = 0, pacmanprevdir = 8, countBcase = 0, countBcase2 = 0, fruitCounterRun = 0;
	char key = 0, key2 = 0, CurrentFruitChar, NextFruitChar, NextPacmanChar, CurrentPacmanChar;;
	char* CurrentGhostsCharArr = new char[ghostCounter], * NextGhostsCharArr = new char[ghostCounter];;
	bool delaymonsters = false, visibleFruit = true, ifWin = false, randomMade, escIsPushed = false, withFiles = false;
	Point CurrentPacmanStep,NextFruitStep = Point(0, 0),NextPacmanStep = Point(0, 0),CurrentFruitStep; 
	Point* CurrentGhostsStepArr = new Point[ghostCounter],*NextGhostsStepArr = new Point[ghostCounter]; 
	if (caseOpt == 2)
		withFiles = true;

	//Implemention:
	if (IfMenuIsFirst()==true)
		gotoxy(rowBoard, colBoard + 2);
		p.setpoint(Pacmanstart.getx(), Pacmanstart.gety());
		MakeRandomFruitPoint(&randomfruitx, &randomfruity, rowBoard, colBoard);
		while (initbrd[randomfruity][randomfruitx] == '#')
		MakeRandomFruitPoint(&randomfruitx, &randomfruity, rowBoard, colBoard);
		fruit.Point::setpoint(randomfruitx, randomfruity);
	for (int i = 0; i < ghostCounter; i++)
		gstarr[i].setghostDirection(0);
	if (withFiles == true)
		stepfile << "Fruit random point is :" << randomfruitx <<" "<< randomfruity <<", the value is:"<<fruit.getfruitval()<<endl;
	
	do {
		if (_kbhit())
		{
			key = _getch();
			if (key == 'w' || key == 'W' || key == 'a' || key == 'A' || key == 'd' || key == 'D' || key == 'x' || key == 'X' || key == 's' || key == 'S')
			{
				if ((PACdir = p.getDirection(key)) != -1)
				{
					p.setDirection(PACdir);
					pacmanprevdir = PACdir;
				}
			}
			if (caseOpt != 3 && caseOpt!=2)
			{
				EscFunc(&key, gstarr, ghostCounter, &p, pacmanprevdir, menurowstart, menucolstart, IfMenuIsFirst());
			}
		}
		if (IfMenuIsFirst() == true)
		{
			gotoxy(0, rowBoard + 2);
			cout << "                                                 ";
		}

		gotoxy(menucolstart, menurowstart);
		cout << "Live remainig:" << lives << "                                       ";
		gotoxy(menucolstart, menurowstart + 1);
		cout << "Score:" << score << "                                       ";
		cout << endl;
		UpdateSteps(CurrentPacmanStep, CurrentFruitStep, NextPacmanStep, NextFruitStep, CurrentPacmanChar, NextPacmanChar, CurrentFruitChar, NextFruitChar, CurrentGhostsCharArr, NextGhostsCharArr,p, fruit, ghostCounter, CurrentGhostsStepArr, NextGhostsStepArr, gstarr, PACdir);
		CountsScore(CurrentPacmanChar, CurrentPacmanStep, score, initbrd);
		if (checkWin(key2, score, totalPoints,caseOpt) == true)
			return WON;
		p.move(NextPacmanChar, NextPacmanStep, IfMenuIsFirst(), rowBoard, colBoard, stepfile,"Pacman ",withFiles,totalPacmanMoves);
		UpdateSteps(CurrentPacmanStep, CurrentFruitStep, NextPacmanStep, NextFruitStep, CurrentPacmanChar, NextPacmanChar, CurrentFruitChar, NextFruitChar, CurrentGhostsCharArr, NextGhostsCharArr,p, fruit, ghostCounter, CurrentGhostsStepArr, NextGhostsStepArr, gstarr, PACdir);

		//Check if pacman hitted ghosts:
		for (int i = 0; i < ghostCounter; i++)
		{
			if (CurrentGhostsStepArr[i].getx() == CurrentPacmanStep.getx() && CurrentGhostsStepArr[i].gety() == CurrentPacmanStep.gety())
			{
				for (int i = 0; i < ghostCounter; i++)
					gstarr[i].setghostDirection(8);
					p.setDirection(8);
				for (int i = 0; i < ghostCounter; i++)
					gstarr[i].deleteghost(CurrentGhostsCharArr[i],IfMenuIsFirst());
					p.deletepac(IfMenuIsFirst());
					p.Point::setpoint(Pacmanstart.getx(), Pacmanstart.gety());
				for (int i = 0; i < ghostCounter; i++)
					gstarr[i].Point::setpoint(Ghostsstart[i].getx(), Ghostsstart[i].gety());
				for (int i = 0; i < ghostCounter; i++)
				{
					gstarr[i].setghostDirection(0);
					CalcCurrentGhostsSteps(ghostCounter, CurrentGhostsStepArr, gstarr);
					CalcNextGhostsStep(ghostCounter, NextGhostsStepArr, gstarr);
					CurrentGhostsCharArr[i] = initbrd[CurrentGhostsStepArr[i].gety()][CurrentGhostsStepArr[i].getx()];
					NextGhostsCharArr[i] = initbrd[NextGhostsStepArr[i].gety()][NextGhostsStepArr[i].getx()];
					string obj = "Ghost " + std::to_string(i)+" ";
					gstarr[i].move(NextGhostsCharArr[i], CurrentGhostsCharArr[i],IfMenuIsFirst(), level, rowBoard, colBoard,stepfile,obj,withFiles);
				}
				gotoxy(menucolstart, menurowstart + 1);
				cout << "You hitted a ghost!" << "                           " << endl;
				lives -= 1;
			}
		}
		//Check if Ghost hitted Fruit:
		for (int i = 0; i < ghostCounter; i++)
		{
			if (visibleFruit == true)
			{
				if (CurrentFruitStep.getx() == CurrentGhostsStepArr[i].getx() && CurrentFruitStep.gety() == CurrentGhostsStepArr[i].gety())
				{
					CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
					visibleFruit = false;
					//fruit.setfruitDirection(8);
					//stepfile << endl << "Fruit ";
					//randomMade=fruit.move(NextFruitChar, ' ', IfMenuIsFirst(), rowBoard, colBoard,stepfile,"Fruit ",withFiles);
					//while(randomMade==true)
					//randomMade = fruit.move(NextFruitChar, ' ', IfMenuIsFirst(), rowBoard, colBoard, stepfile, "Fruit ", withFiles);
					fruit.deletefruit(CurrentFruitChar, IfMenuIsFirst());
				}
			}
		}
		if (delaymonsters == false)//Delay the monster and move the ghosts:
		{
			fruitCounterRun++;
			if (visibleFruit == true)
			randomMade = fruit.move(NextFruitChar,CurrentFruitChar, IfMenuIsFirst(), rowBoard, colBoard, stepfile, "Fruit ", withFiles);
			while (randomMade == true)
			{
				UpdateSteps(CurrentPacmanStep, CurrentFruitStep, NextPacmanStep, NextFruitStep, CurrentPacmanChar, NextPacmanChar, CurrentFruitChar, NextFruitChar, CurrentGhostsCharArr, NextGhostsCharArr, p, fruit, ghostCounter, CurrentGhostsStepArr, NextGhostsStepArr, gstarr, PACdir);
				randomMade = fruit.move(NextFruitChar, CurrentFruitChar, IfMenuIsFirst(), rowBoard, colBoard, stepfile, "Fruit ", withFiles);
			}
			if (visibleFruit == false)
			{
				//fruit.move(NextFruitChar, CurrentFruitChar, IfMenuIsFirst(), rowBoard, colBoard, stepfile, "Fruit ", false);
				if (withFiles == true)
					stepfile << "fruit is invisible"<<endl;
			}
			CurrentPacmanStep = Point(p.getx(), p.gety());
			CurrentFruitStep = Point(fruit.Point::getx(), fruit.Point::gety());
			CalcCurrentGhostsSteps(ghostCounter, CurrentGhostsStepArr, gstarr);
			CalcNextGhostsStep(ghostCounter, NextGhostsStepArr, gstarr);
			NextPacmanStep = GetNextStep(PACdir, CurrentPacmanStep.getx(), CurrentPacmanStep.gety());
			NextFruitStep = GetNextStep(fruit.getfruitDirection(), fruit.Point::getx(), fruit.Point::gety());
			CurrentPacmanChar = initbrd[CurrentPacmanStep.gety()][CurrentPacmanStep.getx()];
			NextPacmanChar = initbrd[NextPacmanStep.gety()][NextPacmanStep.getx()];
			CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
			NextFruitChar = initbrd[NextFruitStep.gety()][NextFruitStep.getx()];
			for (int i = 0; i < ghostCounter; i++)
			{
				CurrentGhostsCharArr[i] = initbrd[CurrentGhostsStepArr[i].gety()][CurrentGhostsStepArr[i].getx()];
				NextGhostsCharArr[i] = initbrd[NextGhostsStepArr[i].gety()][NextGhostsStepArr[i].getx()];
			}
			//if ghost hitted fruit
			for (int i = 0; i < ghostCounter; i++)
			{
				if (visibleFruit == true)
				{
					if (CurrentFruitStep.getx() == CurrentGhostsStepArr[i].getx() && CurrentFruitStep.gety() == CurrentGhostsStepArr[i].gety())
					{
						CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
						visibleFruit = false;
						//fruit.setfruitDirection(8);
						fruit.deletefruit(CurrentFruitChar, IfMenuIsFirst());
						//if (visibleFruit == true)
							//stepfile << "Ghost hitted fruit";
					}
				}
			}
			//move ghosts
			for (int i = 0; i < ghostCounter; i++)
			{
				string obj = "Ghost " + std::to_string(i)+" ";
				randomMade = gstarr[i].move(NextGhostsCharArr[i], CurrentGhostsCharArr[i], IfMenuIsFirst(), level, rowBoard, colBoard, stepfile,obj,withFiles);
				while (randomMade == true)
				{
					UpdateSteps(CurrentPacmanStep, CurrentFruitStep, NextPacmanStep, NextFruitStep, CurrentPacmanChar, NextPacmanChar, CurrentFruitChar, NextFruitChar, CurrentGhostsCharArr, NextGhostsCharArr, p, fruit, ghostCounter, CurrentGhostsStepArr, NextGhostsStepArr, gstarr, PACdir);
					randomMade = gstarr[i].move(NextGhostsCharArr[i], CurrentGhostsCharArr[i], IfMenuIsFirst(), level, rowBoard, colBoard, stepfile, obj, withFiles);
				}
			}
			delaymonsters = true;
			CurrentPacmanStep = Point(p.getx(), p.gety());
			CurrentFruitStep = Point(fruit.Point::getx(), fruit.Point::gety());
			CalcCurrentGhostsSteps(ghostCounter, CurrentGhostsStepArr, gstarr);
			CalcNextGhostsStep(ghostCounter, NextGhostsStepArr, gstarr);
			NextPacmanStep = GetNextStep(PACdir, CurrentPacmanStep.getx(), CurrentPacmanStep.gety());
			NextFruitStep = GetNextStep(fruit.getfruitDirection(), fruit.Point::getx(), fruit.Point::gety());
			CurrentPacmanChar = initbrd[CurrentPacmanStep.gety()][CurrentPacmanStep.getx()];
			NextPacmanChar = initbrd[NextPacmanStep.gety()][NextPacmanStep.getx()];
			CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
			NextFruitChar = initbrd[NextFruitStep.gety()][NextFruitStep.getx()];
			for (int i = 0; i < ghostCounter; i++)
			{
				CurrentGhostsCharArr[i] = initbrd[CurrentGhostsStepArr[i].gety()][CurrentGhostsStepArr[i].getx()];
				NextGhostsCharArr[i] = initbrd[NextGhostsStepArr[i].gety()][NextGhostsStepArr[i].getx()];
			}
		}
		else if (delaymonsters == true)
			delaymonsters = false;
		UpdateSteps(CurrentPacmanStep, CurrentFruitStep, NextPacmanStep, NextFruitStep, CurrentPacmanChar, NextPacmanChar, CurrentFruitChar, NextFruitChar, CurrentGhostsCharArr, NextGhostsCharArr,p, fruit, ghostCounter, CurrentGhostsStepArr, NextGhostsStepArr, gstarr, PACdir);
		//Check if pacman hitted ghosts:
		for (int i = 0; i < ghostCounter; i++)
		{
			if (CurrentGhostsStepArr[i].getx() == CurrentPacmanStep.getx() && CurrentGhostsStepArr[i].gety() == CurrentPacmanStep.gety())
			{

				for (int i = 0; i < ghostCounter; i++)
					gstarr[i].setghostDirection(8);
				p.setDirection(8);

				for (int i = 0; i < ghostCounter; i++)
					gstarr[i].deleteghost(CurrentGhostsCharArr[i], IfMenuIsFirst());
				p.deletepac(IfMenuIsFirst());

				p.Point::setpoint(Pacmanstart.getx(), Pacmanstart.gety());
				for (int i = 0; i < ghostCounter; i++)
					gstarr[i].Point::setpoint(Ghostsstart[i].getx(), Ghostsstart[i].gety());

				for (int i = 0; i < ghostCounter; i++)
				{
					gstarr[i].setghostDirection(0);
					CalcCurrentGhostsSteps(ghostCounter, CurrentGhostsStepArr, gstarr);
					CalcNextGhostsStep(ghostCounter, NextGhostsStepArr, gstarr);
					CurrentGhostsCharArr[i] = initbrd[CurrentGhostsStepArr[i].gety()][CurrentGhostsStepArr[i].getx()];
					NextGhostsCharArr[i] = initbrd[NextGhostsStepArr[i].gety()][NextGhostsStepArr[i].getx()];
					string obj= "Ghost "+std::to_string(i)+" ";
					gstarr[i].move(NextGhostsCharArr[i], CurrentGhostsCharArr[i], IfMenuIsFirst(), level, rowBoard, colBoard,stepfile,obj,withFiles);
				}
				gotoxy(menucolstart, menurowstart + 1);
				cout << "You hitted a ghost!" << "                           " << endl;
				lives -= 1;
			}

		}
		//Check if pacman hitted Fruit:
		if (CurrentFruitStep.getx() == CurrentPacmanStep.getx() && CurrentFruitStep.gety() == CurrentPacmanStep.gety())
		{
			if (visibleFruit == true)
			{
				score += fruit.getfruitval();
			}
		}
		//Check if Ghost hitted Fruit:
		for (int i = 0; i < ghostCounter; i++)
		{
			if (visibleFruit == true)
			{
				if (CurrentFruitStep.getx() == CurrentGhostsStepArr[i].getx() && CurrentFruitStep.gety() == CurrentGhostsStepArr[i].gety())
				{
					CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
					visibleFruit = false;
					//fruit.setfruitDirection(8);
					fruit.deletefruit(CurrentFruitChar, IfMenuIsFirst());
					//if (withFiles == true)
					//stepfile << "Ghost hitted fruit"<<endl;
				}

			}
					
		}
		//Switch for the level options(move of ghosts)
		switch (level) {
		case 'a':
		{//Best
			for (int i = 0; i < ghostCounter; i++)
			{
				SmartDirection(&gdir, CurrentGhostsStepArr[i], CurrentPacmanStep, gstarr, initbrd);
				gstarr[i].setghostDirection(gdir);
			}
			break;
		}
		case 'b':
		{
			if (countBcase < 40 )
			{
				countBcase++;
				for (int i = 0; i < ghostCounter; i++)
				{
					SmartDirection(&gdir, CurrentGhostsStepArr[i], CurrentPacmanStep, gstarr, initbrd);
					gstarr[i].setghostDirection(gdir);
				}
			}
			 if (countBcase >= 40 )
			{
				if (countBcase == 40)
				{

					int randomIndex1;
					int DirectionArr[4] = { 1,3,5,7 };
					srand(time(NULL));
					randomIndex1 = rand() % 4;
					for (int i = 0; i < ghostCounter; i++)
					{
						while (DirectionArr[randomIndex1] == gstarr[i].getghostDirection() || DirectionArr[randomIndex1] - 1 == gstarr[i].getghostDirection())
						{
							randomIndex1 = rand() % 4;
						}
						gstarr[i].setghostDirection(DirectionArr[randomIndex1]);
					}
				}
				countBcase++;
				 if (countBcase == 50)
				{
					countBcase = 0;
				
				}
			}
			break;
		}
		case 'c'://Novice
		{
			break;
		}
		}
		if (fruitCounterRun > 30)
		{
			CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
			visibleFruit = false;
			//fruit.setfruitDirection(8);
			fruit.deletefruit(CurrentFruitChar, IfMenuIsFirst());
		}
		if (fruitCounterRun == 80)
		{
			visibleFruit = true;
			MakeRandomFruitPoint(&randomfruitx, &randomfruity, rowBoard, colBoard);
			while (initbrd[randomfruity][randomfruitx] == '#')
				MakeRandomFruitPoint(&randomfruitx, &randomfruity, rowBoard, colBoard);
			if (withFiles == true)
			{
				stepfile << "Fruit random point is :" << randomfruitx << " " << randomfruity << ", the value is:" << fruit.getfruitval() << endl;
			}
			fruit.Point::setpoint(randomfruitx, randomfruity);
			//fruit.setfruitDirection(2);
			fruitCounterRun = 0;

		}
		stepfile << "------------"<<endl;
		Sleep(300);
	} while (lives > 0);
	if (lives == 0)
	{
		GameOverFunc(&key2);
		return LOSE;
	}
		

}
bool ThePacmanGame::GetMovesFromFiles(fstream& stepfile,string& line,string& objInput,string& dirObj,int& ghostCounter,Pacman& p,bool& delaymonsters,bool& withFruit,Fruit& fruit,Ghost* gstarr,char* CurrentGhostsCharArr,bool& IfMenuIsFirst,Point& Pacmanstart,Point* Ghostsstart,int& menucolstart,int& menurowstart,int& lives)
{
	std::getline(stepfile, line);
	char fig;
	int Xtemp, Ytemp;
	if (line == "")
		return true;
	if (line=="------------")
		return false;
	ConvertToObjAndDir(line, objInput, dirObj);
	if (objInput == "Fruit" && dirObj == "random")
	{
		ConvertToInt(line, Xtemp, Ytemp, fig);
		fruit.setpoint(Xtemp, Ytemp);
		fruit.setFigure(fig);
		withFruit = true;
		return false;

	}
	//get pacman direction
	if (objInput == "Pacman")
	{
		if (dirObj == "stay")
		{
			//key = 's';
			p.setDirection(8);
		}
		else if (dirObj == "up")
		{
			//key = 'w';
			p.setDirection(0);
		}
		else if (dirObj == "down")
		{
			//key = 'x';
			p.setDirection(3);
		}
		else if (dirObj == "left")
		{
			//key = 'a';
			p.setDirection(5);
		}
		else if (dirObj == "right")
		{
			//key = 'd';
			p.setDirection(7);
		}
	}

	if (delaymonsters == false) {
		//Get fruit
		std::getline(stepfile, line);
		ConvertToObjAndDir(line, objInput, dirObj);
		if (objInput == "Fruit" && dirObj != "is" && dirObj!="random")
		{
			if (dirObj == "stay")
				fruit.setfruitDirection(8);
			else if (dirObj == "up")
				fruit.setfruitDirection(0);
			else if (dirObj == "down")
				fruit.setfruitDirection(3);
			else if (dirObj == "left")
				fruit.setfruitDirection(5);
			else if (dirObj == "right")
				fruit.setfruitDirection(7);
			withFruit = true;
		}
		//Get ghosts
		for (int i = 0; i < ghostCounter; i++)
		{
			std::getline(stepfile, line);
			ConvertToObjAndDir(line, objInput, dirObj);
			if (objInput == "Ghost")
			{
				if (dirObj == "stay")
					gstarr[i].setghostDirection(8);
				else if (dirObj == "up")
					gstarr[i].setghostDirection(0);
				else if (dirObj == "down")
					gstarr[i].setghostDirection(3);
				else if (dirObj == "left")
					gstarr[i].setghostDirection(5);
				else if (dirObj == "right")
					gstarr[i].setghostDirection(7);


			}
		}
	}


	return true;
}
int ThePacmanGame::runFromFile(fstream& stepfile, fstream& resfile, int score, int totalPoints, char level, int caseOpt, int& totalPacmanMoves)
{
	//Declaration:
	string line, objInput, dirObj;
	int i = 0, Xtemp, Ytemp,PACdir = 8, randomfruitx, randomfruity, gdir = 0, pacmanprevdir = 8, countBcase = 0, countBcase2 = 0, fruitCounterRun = 0;
	char key = 0, key2 = 0,randomfig;
	bool  silentMood=false,ifmenuisfirst = IfMenuIsFirst(),ifContinue = true,delaymonsters = false, visibleFruit = true, ifWin = false, escIsPushed = false;
	const bool withFiles = false;
	Point CurrentPacmanStep, NextFruitStep = Point(0, 0), CurrentFruitStep;
	Point NextPacmanStep = Point(0, 0);
	Point* CurrentGhostsStepArr = new Point[ghostCounter];
	Point* NextGhostsStepArr = new Point[ghostCounter];
	char CurrentPacmanChar, NextPacmanChar, CurrentFruitChar, NextFruitChar;
	char* CurrentGhostsCharArr = new char[ghostCounter];
	char* NextGhostsCharArr = new char[ghostCounter];
	if (caseOpt == 4)
		silentMood = true;

	//Implemeition:
	if (IfMenuIsFirst() == true)
		gotoxy(rowBoard, colBoard + 2);
	getline(stepfile, line);
	ConvertToInt(line, Xtemp, Ytemp,randomfig);
	p.setpoint(Pacmanstart.getx(), Pacmanstart.gety());
	fruit.Point::setpoint(Xtemp, Ytemp);
	fruit.setFigure(randomfig);
	do {
		
		ifContinue= GetMovesFromFiles(stepfile, line, objInput, dirObj, ghostCounter, p, delaymonsters, visibleFruit, fruit,gstarr, CurrentGhostsCharArr, ifmenuisfirst, Pacmanstart, Ghostsstart, menucolstart, menurowstart,lives);
		if (ifContinue == true)
		{
			if (!silentMood)
			{
				if (IfMenuIsFirst() == true)
				{
					gotoxy(0, rowBoard + 2);
					cout << "                                                 ";
				}
				gotoxy(menucolstart, menurowstart);
				cout << "Live remainig:" << lives << "                                       ";
				gotoxy(menucolstart, menurowstart + 1);
				cout << "Score:" << score << "                                       ";
				cout << endl;
			}
			UpdateSteps(CurrentPacmanStep, CurrentFruitStep, NextPacmanStep, NextFruitStep, CurrentPacmanChar, NextPacmanChar, CurrentFruitChar, NextFruitChar, CurrentGhostsCharArr, NextGhostsCharArr,p, fruit, ghostCounter, CurrentGhostsStepArr, NextGhostsStepArr, gstarr, PACdir);
			CountsScore(CurrentPacmanChar, CurrentPacmanStep, score, initbrd);
			if (checkWin(key2, score, totalPoints,caseOpt) == true)
			{
				return WON;
				break;
			}
			p.move(NextPacmanChar, NextPacmanStep, IfMenuIsFirst(), rowBoard, colBoard, stepfile, "Pacman ", withFiles, totalPacmanMoves);
			UpdateSteps(CurrentPacmanStep, CurrentFruitStep, NextPacmanStep, NextFruitStep, CurrentPacmanChar, NextPacmanChar, CurrentFruitChar, NextFruitChar, CurrentGhostsCharArr, NextGhostsCharArr,p, fruit, ghostCounter, CurrentGhostsStepArr, NextGhostsStepArr, gstarr, PACdir);
			//Check if pacman hitted ghosts:
			for (int i = 0; i < ghostCounter; i++)
			{
				if (CurrentGhostsStepArr[i].getx() == CurrentPacmanStep.getx() && CurrentGhostsStepArr[i].gety() == CurrentPacmanStep.gety())
				{
					for (int i = 0; i < ghostCounter; i++)
						gstarr[i].setghostDirection(8);
						p.setDirection(8);
					for (int i = 0; i < ghostCounter; i++)
						gstarr[i].deleteghost(CurrentGhostsCharArr[i], IfMenuIsFirst());
						p.deletepac(IfMenuIsFirst());
					for (int i = 0; i < ghostCounter; i++)
						gstarr[i].Point::setpoint(Ghostsstart[i].getx(), Ghostsstart[i].gety());
						p.Point::setpoint(Pacmanstart.getx(), Pacmanstart.gety());
						if (!silentMood)
						{
							gotoxy(menucolstart, menurowstart + 1);
							cout << "You hitted a ghost!" << "                           " << endl;
						}
						lives -= 1;
				}
			}
			//Check if Ghost hitted Fruit:
			for (int i = 0; i < ghostCounter; i++)
			{
				if (visibleFruit == true)
				{	//if ghost hitted fruit
					if (CurrentFruitStep.getx() == CurrentGhostsStepArr[i].getx() && CurrentFruitStep.gety() == CurrentGhostsStepArr[i].gety())
					{
						CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
						visibleFruit = false;
						//fruit.setfruitDirection(8);
						//stepfile << endl << "Fruit ";
						//fruit.move(NextFruitChar, ' ', IfMenuIsFirst(), rowBoard, colBoard, stepfile, "Fruit ", withFiles);
						fruit.deletefruit(CurrentFruitChar, IfMenuIsFirst());
						visibleFruit = false;
						//if (withFiles == true)
							//stepfile << "Ghost hitted fruit" << endl;
					}
				}
			}
			if (delaymonsters == false)//Delay the monster and move the ghosts:
			{
				fruitCounterRun++;
				if (visibleFruit == true)
					fruit.move(NextFruitChar, CurrentFruitChar, IfMenuIsFirst(), rowBoard, colBoard, stepfile, "Fruit ", withFiles);
				CurrentPacmanStep = Point(p.getx(), p.gety());
				CurrentFruitStep = Point(fruit.Point::getx(), fruit.Point::gety());
				CalcCurrentGhostsSteps(ghostCounter, CurrentGhostsStepArr, gstarr);
				CalcNextGhostsStep(ghostCounter, NextGhostsStepArr, gstarr);
				NextPacmanStep = GetNextStep(PACdir, CurrentPacmanStep.getx(), CurrentPacmanStep.gety());
				NextFruitStep = GetNextStep(fruit.getfruitDirection(), fruit.Point::getx(), fruit.Point::gety());
				CurrentPacmanChar = initbrd[CurrentPacmanStep.gety()][CurrentPacmanStep.getx()];
				NextPacmanChar = initbrd[NextPacmanStep.gety()][NextPacmanStep.getx()];
				CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
				NextFruitChar = initbrd[NextFruitStep.gety()][NextFruitStep.getx()];
				for (int i = 0; i < ghostCounter; i++)
				{
					CurrentGhostsCharArr[i] = initbrd[CurrentGhostsStepArr[i].gety()][CurrentGhostsStepArr[i].getx()];
					NextGhostsCharArr[i] = initbrd[NextGhostsStepArr[i].gety()][NextGhostsStepArr[i].getx()];
				}
				for (int i = 0; i < ghostCounter; i++)
				{
					if (visibleFruit == true)
					{
						if (CurrentFruitStep.getx() == CurrentGhostsStepArr[i].getx() && CurrentFruitStep.gety() == CurrentGhostsStepArr[i].gety())
						{
							CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
							visibleFruit = false;
							//fruit.setfruitDirection(8);
							fruit.deletefruit(CurrentFruitChar, IfMenuIsFirst());
							visibleFruit = false;
						}

					}

				}
				for (int i = 0; i < ghostCounter; i++)
				{
					string obj = "Ghost " + std::to_string(i) + " ";
					gstarr[i].move(NextGhostsCharArr[i], CurrentGhostsCharArr[i], IfMenuIsFirst(), level, rowBoard, colBoard, stepfile, obj, withFiles);
				}
				delaymonsters = true;
				CurrentPacmanStep = Point(p.getx(), p.gety());
				CurrentFruitStep = Point(fruit.Point::getx(), fruit.Point::gety());
				CalcCurrentGhostsSteps(ghostCounter, CurrentGhostsStepArr, gstarr);
				CalcNextGhostsStep(ghostCounter, NextGhostsStepArr, gstarr);
				NextPacmanStep = GetNextStep(PACdir, CurrentPacmanStep.getx(), CurrentPacmanStep.gety());
				NextFruitStep = GetNextStep(fruit.getfruitDirection(), fruit.Point::getx(), fruit.Point::gety());
				CurrentPacmanChar = initbrd[CurrentPacmanStep.gety()][CurrentPacmanStep.getx()];
				NextPacmanChar = initbrd[NextPacmanStep.gety()][NextPacmanStep.getx()];
				CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
				NextFruitChar = initbrd[NextFruitStep.gety()][NextFruitStep.getx()];
				for (int i = 0; i < ghostCounter; i++)
				{
					CurrentGhostsCharArr[i] = initbrd[CurrentGhostsStepArr[i].gety()][CurrentGhostsStepArr[i].getx()];
					NextGhostsCharArr[i] = initbrd[NextGhostsStepArr[i].gety()][NextGhostsStepArr[i].getx()];
				}
			}
			else
				delaymonsters = false;
			UpdateSteps(CurrentPacmanStep, CurrentFruitStep, NextPacmanStep, NextFruitStep, CurrentPacmanChar, NextPacmanChar, CurrentFruitChar, NextFruitChar, CurrentGhostsCharArr, NextGhostsCharArr,p, fruit, ghostCounter, CurrentGhostsStepArr, NextGhostsStepArr, gstarr, PACdir);
			//Check if pacman hitted ghosts:
			for (int i = 0; i < ghostCounter; i++)
			{
				if (CurrentGhostsStepArr[i].getx() == CurrentPacmanStep.getx() && CurrentGhostsStepArr[i].gety() == CurrentPacmanStep.gety())
				{
					for (int i = 0; i < ghostCounter; i++)
						gstarr[i].setghostDirection(8);
						p.setDirection(8);
					for (int i = 0; i < ghostCounter; i++)
						gstarr[i].deleteghost(CurrentGhostsCharArr[i], IfMenuIsFirst());
						//p.deletepac(IfMenuIsFirst());
					for (int i = 0; i < ghostCounter; i++)
						gstarr[i].Point::setpoint(Ghostsstart[i].getx(), Ghostsstart[i].gety());
						p.Point::setpoint(Pacmanstart.getx(), Pacmanstart.gety());
						if (!silentMood)
						{
							gotoxy(menucolstart, menurowstart + 1);
							cout << "You hitted a ghost!" << "                           " << endl;
						}
						lives -= 1;
				}
			}
			//Check if pacman hitted Fruit:
			if (CurrentFruitStep.getx() == CurrentPacmanStep.getx() && CurrentFruitStep.gety() == CurrentPacmanStep.gety())
			{
				if (visibleFruit == true)
				{
					score += fruit.getfruitval();
					if (visibleFruit == true)
					{
						CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
						//fruit.setfruitDirection(8);
						fruit.deletefruit(CurrentFruitChar, IfMenuIsFirst());
						
					}
				}
			}
			//Check if Ghost hitted Fruit:
			for (int i = 0; i < ghostCounter; i++)
			{
				if (visibleFruit == true)
				{
					if (CurrentFruitStep.getx() == CurrentGhostsStepArr[i].getx() && CurrentFruitStep.gety() == CurrentGhostsStepArr[i].gety())
					{
						CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
						visibleFruit = false;
						//fruit.setfruitDirection(8);
						fruit.deletefruit(CurrentFruitChar, IfMenuIsFirst());
						visibleFruit = false;
					}
				}
			}
			Sleep(300);
		}
	} while (lives > 0);
	if (lives == 0)
	{
		GameOverFunc(&key2);
		return LOSE;
	}
}
vector<string> ThePacmanGame::getScreenFiles() const {
	vector<string> files;
	string extension = ".screen";
	fs::path path = fs::current_path();
	for (auto& p : fs::recursive_directory_iterator(path)) {
		if (p.path().extension() == extension)
		{
			files.push_back(p.path().stem().string() + extension);
		}		
	}
	std::sort(files.begin(), files.end());
	return files;
}
void FindStepsFiles(int i) {
	int counter1 = 0, counter2 = 0;
	string exceptionmsg="Steps file is missing for run a game from files.";
	string extension1 = ".steps", extension2 = ".result";
	fs::path path = fs::current_path();
	for (auto& p : fs::recursive_directory_iterator(path)) {
		if (p.path().extension() == extension1)
			counter1++;
		//if (p.path().extension() == extension2)
			//counter2++;
	}
	if (counter1 ==0)
		throw exceptionmsg;
}
int ThePacmanGame::StartGame(fstream& inputfile,fstream& stepfile,fstream& resfile, ThePacmanGame& p, char level,int caseOpt, int& totalPacmanMoves)
{
	string tmparr;
	string excpmsg1 = "The board should include exactly 1 pacman character(@)";
	string excpmsg2 = "Menu Start Char was not found(&).";
	rowBoard = 0;
	totalPoints = 0;
	ghostCounter = 0;
	int res;
	int pacmanCounter = 0, writegst = 0;
	bool menuStartFound = false, menuisfirst = false;;
	std::getline(inputfile, tmparr);
	colBoard = tmparr.length();
	if (tmparr[0] == '&')
	{
		menuisfirst = true;
		menurowstart = 0; menucolstart = 0;
		menuStartFound = true;
		std::getline(inputfile, tmparr);
		colBoard = tmparr.length();
		startRowBoard = STARTBOARD;
	}
	rowBoard++;
	while (std::getline(inputfile, tmparr))
	{
		if (tmparr[0] != '&')
		{
			rowBoard++;
			for (int i = 0; i < colBoard; i++)
			{
				if (tmparr[i] == '$')
					ghostCounter++;
				if (tmparr[i] == '@')
					pacmanCounter++;
				if (tmparr[i] == ' ')
					totalPoints++;
				if (tmparr[i] == '\0')
					break;

			}
		}
	}
	if (pacmanCounter != 1)
	{
		throw excpmsg1;
	}
	if (menuStartFound == false && tmparr != "&")
	{
		throw excpmsg2;
	}
	if(IfMenuIsFirst()==true)
		endRowBoard = rowBoard+STARTBOARD;
	if (menuStartFound == false)
	{
		menurowstart = rowBoard; menucolstart = 0;
		menuStartFound = true;
	}
	gstarr = new Ghost[ghostCounter];
	Ghostsstart = new Point[ghostCounter];
	inputfile.clear();
	inputfile.seekg(0);
	if (menurowstart == 0)
	{
		getline(inputfile, tmparr);
		
	}//"eat the &
	for (int i = 0; i < rowBoard; i++)
	{
		getline(inputfile, tmparr);
		for (int j = 0; j < tmparr.length(); j++)
		{
			if (tmparr[j] == ' ')
			{
				tmparr[j] = '.';
			}
			if (tmparr[j] == '%')
			{
				tmparr[j] = ' ';
			}
			if (tmparr[j] == '#')
			{
				tmparr[j] = '#';
			}
			if (tmparr[j] == '@')
			{
				Pacmanstart.setx(j);
				Pacmanstart.sety(i);
				tmparr[j] = '.';
			}
			if (tmparr[j] == '$')
			{
				tmparr[j] = '.';
				gstarr[writegst].setx(j);
				gstarr[writegst].sety(i);
				Ghostsstart[writegst].setx(j);
				Ghostsstart[writegst].sety(i);
				writegst++;

			}
			if (tmparr[j] == '\0')
			{
				tmparr[j] = '\0';
			}
		}
		for (int x = 0; x < colBoard; x++)
			initbrd[i][x] = tmparr[x];
	}
	if (menurowstart == 0)
	{
		cout << endl;
		cout << endl;
	}
		
	if (caseOpt!=4)
		p.printboard();
		if (caseOpt == 1)
			res = p.run(stepfile,resfile,0, totalPoints, level,caseOpt,totalPacmanMoves);
		else if (caseOpt == 2)
		{
			res = p.run(stepfile, resfile, 0, totalPoints, level, caseOpt, totalPacmanMoves);
			if (res == LOSE)
			{
				resfile << "Loose after " << totalPacmanMoves << " moves." << endl;
				return LOSE;
			}
				
		}
		else if (caseOpt==3||caseOpt==4)
		{
			res = p.runFromFile(stepfile, resfile, 0, 30, level, caseOpt, totalPacmanMoves); 
			if (res == LOSE)
			{
			resfile << "Loose after " << totalPacmanMoves << " moves." << endl;
			return LOSE;
			}
			
		}
		delete[] gstarr;
		delete[] Ghostsstart;
		inputfile.close();
		stepfile.close();
		resfile.close();
		return true;
}
void ThePacmanGame::MakeRandomFruitPoint(int* randomfruitx, int* randomfruity,int rowBoard, int colBoard)
{
		srand(time(NULL));
		(*randomfruitx) = rand() % colBoard;
		(*randomfruity) = rand() % rowBoard;
		//int randomfruitnumber = 5 + (rand() % 5);
		//fruit.setFigure(randomfruitnumber);
		
	
	
}
Point GetNextStep(int Direction, int Currentx, int Currenty)
{
	Point NextStep(0, 0);
	switch (Direction) {//cases of Direction 
	case 0:
	case 1:// UP
		NextStep.setx(Currentx);
		NextStep.sety(Currenty - 1);

		break;

	case 2:
	case 3: // DOWN
		NextStep.setx(Currentx);
		NextStep.sety(Currenty + 1);

		break;

	case 4:
	case 5:// LEFT
		NextStep.setx(Currentx - 1);
		NextStep.sety(Currenty);

		break;
	case 6:
	case 7:// RIGHT
		NextStep.setx(Currentx + 1);
		NextStep.sety(Currenty);

		break;
	case 8:
	case 9://STAY
		NextStep.setx(Currentx);
		NextStep.sety(Currenty);
		break;
	default:
		NextStep.setx(Currentx);
		NextStep.sety(Currenty);
		break;
	}//cases of directions and calc the next step
	return NextStep;

}
void GameOverFunc(char* key2)
{
	clear_screen();
		cout << "Game Over, You lose! " << endl<<"Press any key to go to the menu." << endl;
		(*key2) = _getch();
		clear_screen();
}
void ThePacmanGame::EscFunc(char* key, Ghost* gstarr, int gstsize,Pacman* p,int pacmanprevdir,int menurowstart, int menucolstart,bool IfMenuIsFirst)
{
	if ((*key) == 27)
	{
		(*p).setDirection(8);
		for(int i=0;i<gstsize;i++)
		gstarr[i].setghostDirection(8);
		if (!IfMenuIsFirst)
			gotoxy(menucolstart, menurowstart + 3);
		else
			gotoxy(0,rowBoard+2);
		cout << "Game paused, press ESC again to continue";

		(*key) = _getch();
		while ((*key) != 27)
		{
			(*p).setDirection(8);
			for (int i = 0; i < gstsize; i++)
			gstarr[i].setghostDirection(8);
			if (!IfMenuIsFirst)
			gotoxy(menucolstart, menurowstart + 3);
			else
			gotoxy(0, rowBoard+2);
			cout << "Game paused, press ESC again to continue";
			(*key) = _getch();
		}
		(*p).setDirection(pacmanprevdir);
	}
}
void SmartDirection(int* newdirection,Point CurrentGhostStep,Point CurrentPacmanStep,Ghost* gstarr,char initbrd[][80])
{
	int distanceX, distanceY;
	distanceX = abs(CurrentGhostStep.getx() - CurrentPacmanStep.getx());
	distanceY = abs(CurrentGhostStep.gety() - CurrentPacmanStep.gety());
	Point NextGhostStepSmart(0, 0);
	char NextGhostCharSmart;
	if (distanceX > distanceY)
	{
			if (CurrentGhostStep.getx() > CurrentPacmanStep.getx())
				*newdirection = 5;	//ghost move left
			else if (CurrentGhostStep.getx() < CurrentPacmanStep.getx())
				*newdirection = 6;//ghost move right
				NextGhostStepSmart = GetNextStep(*newdirection, (*gstarr).Point::getx(), (*gstarr).Point::gety());
				NextGhostCharSmart = initbrd[NextGhostStepSmart.gety()][NextGhostStepSmart.getx()];
			if (NextGhostCharSmart == '#')
			{
					if (CurrentGhostStep.gety() > CurrentPacmanStep.gety())
						*newdirection = 0;//ghost move up
					else if (CurrentGhostStep.gety() < CurrentPacmanStep.gety())
						*newdirection = 2;//ghost move down
					NextGhostStepSmart = GetNextStep(*newdirection, (*gstarr).Point::getx(), (*gstarr).Point::gety());
					NextGhostCharSmart = initbrd[NextGhostStepSmart.gety()][NextGhostStepSmart.getx()];
					while (NextGhostCharSmart == '#')
					{
						//Makerandom
						int randomIndex;
						int DirectionArr[4] = { 1,3,5,7 };
						srand(time(NULL));
						randomIndex = rand() % 4;
						while ((*newdirection == DirectionArr[randomIndex]) || (*newdirection == (DirectionArr[randomIndex] - 1)))
							randomIndex = rand() % 4;
						*newdirection = DirectionArr[randomIndex];
						NextGhostStepSmart = GetNextStep(*newdirection, (*gstarr).Point::getx(), (*gstarr).Point::gety());
						NextGhostCharSmart = initbrd[NextGhostStepSmart.gety()][NextGhostStepSmart.getx()];
					}

			}

	}
	else
	{
				if (CurrentGhostStep.gety() >CurrentPacmanStep.gety())
					*newdirection = 0;//ghost move up
				
				else if (CurrentGhostStep.gety() < CurrentPacmanStep.gety())
					*newdirection = 2;//ghost move down
		
		NextGhostStepSmart = GetNextStep(*newdirection, (*gstarr).Point::getx(), (*gstarr).Point::gety());
		NextGhostCharSmart = initbrd[NextGhostStepSmart.gety()][NextGhostStepSmart.getx()];
		if (NextGhostCharSmart == '#')
		{
			if (CurrentGhostStep.getx() > CurrentPacmanStep.getx())
				*newdirection = 5;//ghost move left
				
			else  if (CurrentGhostStep.getx() < CurrentPacmanStep.getx())
				*newdirection = 6;//ghost move right
		}

	}
}
bool checkWin(char& key,int score,int totalPoints,int caseOpt)
{
	if (caseOpt==4)
		return true;

	if (score >= totalPoints&&caseOpt!=3) {
		clear_screen();
		cout << "Congratulation!-YOU WON" << endl << "Press any key to continue to the next board." << endl;
		key = _getch();
		clear_screen();
		return true;
		//ThePacmanGame()
	}//if won the game
	if (score >= totalPoints && caseOpt == 3) {
		clear_screen();
		return true;
		//ThePacmanGame()
	}//if won the game


	return false;
}
void CalcCurrentGhostsSteps(int ghostCounter, Point* CurrentGhostsStepArr,Ghost* gstarr)
{
	for (int i = 0; i < ghostCounter; i++)
		CurrentGhostsStepArr[i] = Point(gstarr[i].Point::getx(), gstarr[i].Point::gety());
}
void CalcNextGhostsStep(int ghostCounter,Point* NextGhostsStepArr,Ghost* gstarr)
{
	for (int i = 0; i < ghostCounter; i++)
		NextGhostsStepArr[i] = GetNextStep(gstarr[i].getghostDirection(), gstarr[i].Point::getx(), gstarr[i].Point::gety());

}
void CountsScore(char CurrentPacmanChar,Point CurrentPacmanStep,int& score, char initbrd[][80])
{
	if (CurrentPacmanChar == '.')//count the points of pacman
	{
		score++;
		initbrd[CurrentPacmanStep.gety()][CurrentPacmanStep.getx()] = ' ';//init the board
	}
}
void printmenu() {
	cout << "MENU" << endl;
	cout << "1.Simple Option." << endl;
	cout << "2.Save Option" << endl;
	cout << "3.Load Option" << endl;
	cout << "4.Silence Option" << endl;
	cout << "8.Present instructions and keys." << endl;
	cout << "9.Exit." << endl;
}
void printinstructions() {
	cout << "Welcome to Pacman!" << endl;
	cout << "Game Instructions : The Pacman is the main player marked with @.It can move anywhere on the board except the walls and cave of the winds.You can move right, left upand down respectively with the DAWX keysand you can also stop the Pacman with the S key." << endl;
	cout << "Throughout the board there are dots representing food that the Pacman should eat.The object of the game is to finish all the food on the board without being disqualified.In addition there are 2 ghosts roaming the board and if the Pacman collides with them it is disqualification.Each player has 3 lives.When it reaches zero the game is over." << endl;
	cout << "G o o d l u c k!" << endl;
}
void ThePacmanGame::UpdateSteps(Point& CurrentPacmanStep,Point& CurrentFruitStep,Point& NextPacmanStep,Point& NextFruitStep,char& CurrentPacmanChar,char& NextPacmanChar,char& CurrentFruitChar,char& NextFruitChar,char* CurrentGhostsCharArr,char* NextGhostsCharArr,
	Pacman& p,Fruit& fruit,int ghostCounter,Point* CurrentGhostsStepArr,Point* NextGhostsStepArr,Ghost* gstarr,int PACdir)
{
	CurrentPacmanStep = Point(p.getx(), p.gety());
	CurrentFruitStep = Point(fruit.Point::getx(), fruit.Point::gety());
	CalcCurrentGhostsSteps(ghostCounter,CurrentGhostsStepArr, gstarr);
	CalcNextGhostsStep(ghostCounter, NextGhostsStepArr, gstarr);
	NextPacmanStep = GetNextStep(PACdir, CurrentPacmanStep.getx(),CurrentPacmanStep.gety());
	NextFruitStep = GetNextStep(fruit.getfruitDirection(), fruit.Point::getx(), fruit.Point::gety());
	CurrentPacmanChar = initbrd[CurrentPacmanStep.gety()][CurrentPacmanStep.getx()];
	NextPacmanChar = initbrd[NextPacmanStep.gety()][NextPacmanStep.getx()];
	CurrentFruitChar = initbrd[CurrentFruitStep.gety()][CurrentFruitStep.getx()];
	NextFruitChar = initbrd[NextFruitStep.gety()][NextFruitStep.getx()];
	for (int i = 0; i < ghostCounter; i++)
	{
		CurrentGhostsCharArr[i] = initbrd[CurrentGhostsStepArr[i].gety()][CurrentGhostsStepArr[i].getx()];
		NextGhostsCharArr[i] = initbrd[NextGhostsStepArr[i].gety()][NextGhostsStepArr[i].getx()];
	}
}
