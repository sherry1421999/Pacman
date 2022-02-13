#include "ThePacmanGame.h"

using  std::cin;
using  std::cout;
using std::getline;


int main()
{
	fstream boardfile;
	fstream stepfile;
	fstream resfile;
	int userchoice = 0;
	while (userchoice != 9)
	{
		ThePacmanGame p;
		if (p.GetNumOfBoard() <= 0)
		{
			cout << "No files was found.";
			userchoice = 9;
		}
		else
		{
			vector<string>	files = p.getScreenFiles();
			enum { WON = 1, LOSE = 0 };
			printmenu();
			cin >> userchoice;
			clear_screen();
			bool withcolors = false;
			int level;
			bool breakplay = false;
			switch (userchoice)
			{
					//Simple Option
				case 1:
				{
				int totalPacmanMoves = 1;
				level = p.Selectlevel();
				for (int i = 0; i < p.GetNumOfBoard(); i++)
				{
					boardfile.open(files[i], ios_base::in);
					int res;
					if (breakplay != true)
					{
						try
						{
							res = p.StartGame(boardfile, stepfile, resfile, p, level, 1, totalPacmanMoves);
						}
						catch (const string& msg) { clear_screen(); cout << msg << endl; return 1; }
						if (res == WON)
						{
							totalPacmanMoves = 0;
							continue;
						}
						else if (res == LOSE)
						{
							clear_screen();
							breakplay = true;
							break;
						}
					}

				}
				//if won after all boards:
				resfile << "Won after:" << totalPacmanMoves << endl;
				boardfile.close();
				stepfile.close();
				resfile.close();
				break;
			}
				  //Save Option
				case 2:
				{
				level = p.Selectlevel();
				int totalPacmanMoves = 1;
				for (int i = 0; i < p.GetNumOfBoard(); i++)
				{
					int res;
					boardfile.open(files[i], ios_base::in);
					string stepfilename = "pacman_" + std::to_string(i) + ".steps";
					stepfile.open(stepfilename, ios_base::out);
					string resname = "pacman_" + std::to_string(i) + ".result";
					resfile.open(resname, ios_base::out);
					if (breakplay != true)
					{
						try
						{
							res = p.StartGame(boardfile, stepfile, resfile, p, level, 2, totalPacmanMoves);
						}
						catch (string& msg)
						{
							clear_screen();
							cout << msg << endl;
							return 1;
						}
						if (res == LOSE)
						{
							//resfile << "Loose after:" << totalPacmanMoves << endl;
							breakplay = true;
							break;
						}
						else if (res == WON)
						{
							totalPacmanMoves = 0;
							continue;
						}
					}
					//if won after all boards:
					//resfile << "Won after:" << totalPacmanMoves << endl;
					break;
				}
				//Load Option
			}
				//load option
				case 3:
				{
				//catch (...) { return 1; }
				int totalPacmanMoves = 1;
				for (int i = 0; i < p.GetNumOfBoard(); i++)
				{
					/*try
					{
						FindStepsFiles(p.GetNumOfBoard());
					}
					catch (string& msg) {
						cout << msg << endl;
						return 1;
					}*/
					int res;
					totalPacmanMoves = 0;
					boardfile.open(files[i], ios_base::in);
					string stepfilename = "pacman_" + std::to_string(i) + ".steps";
					stepfile.open(stepfilename, ios_base::in);
					string resname = "pacman_" + std::to_string(i) + ".result";
					resfile.open(resname, ios_base::in);
					if (breakplay != true)
					{
						try {
						res = p.StartGame(boardfile, stepfile, resfile, p, 1, 3, totalPacmanMoves);
						}
						catch (string& msg)
						{
							clear_screen();
							cout << msg << endl;
							return 1;
						}
						if (res == WON)
						{
							clear_screen();
							continue;
						}
						else if (res == LOSE)
						{
							resfile << "Loose after:" << totalPacmanMoves << endl;
							clear_screen();
							breakplay = true;
							break;
						}
					}
				}
				//if won after all boards:
				//resfile << "Won after:" << totalPacmanMoves << endl;
				break;
			}
				//Silence Option
				case 4:
					try
					{
						FindStepsFiles(p.GetNumOfBoard());
					}
					catch (const string& msg) { clear_screen(); cout << msg << endl; return 1; }
					int totalPacmanMoves = 1;
					for (int i = 0; i < p.GetNumOfBoard(); i++)
					{
						totalPacmanMoves = 0;
						boardfile.open(files[i], ios_base::in);
						string stepfilename = "pacman_" + std::to_string(i) + ".steps";
						stepfile.open(stepfilename, ios_base::in);
						string resname = "pacman_" + std::to_string(i) + ".result";
						resfile.open(resname, ios_base::in);
						if (breakplay != true)
						{

							int res = p.StartGame(boardfile, stepfile, resfile, p, 1, 4, totalPacmanMoves);
							if (res == WON)
							{
								clear_screen();
								continue;
							}
							else if (res == LOSE)
							{
								resfile << "Loose after:" << totalPacmanMoves << endl;
								clear_screen();
								breakplay = true;
								break;
							}
						}
					}
			
			}

		}
	}
}
