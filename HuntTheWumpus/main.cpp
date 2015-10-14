#include <iostream>
#include <cstring>
#include "sfwdraw.h"
#include "string.h"
#include "GameObject.h"
#include "GameFunction.h"
#include <ctime>
#include <fstream>

using namespace sfw;
using namespace sfw_string;
using std::cin;
using std::cout;
using std::endl;

Level CurrentGameLevel = SplashScreen;
Level TempLevel;
bool CreateNewMap = true;
bool IsPlayerTurn = true;
bool FirstTimeRunning = true;
bool LoseGame = false;
bool WinGame = false;
bool UseConsoleForMenu = false;
int PlayerTurnNum = 0;
char PlayerName[128];
int RoomsAlreadyUsed[20]; //Prevents a room from having more than one kind of encounter


//Objects
//Splashscreen
Text title = { { 200, 400 }, "Hunt The Wumpus", 50, 40 };

//Main Menu
Text mainTitle = { { 200, 100 }, "Hunt THe Wumpus", 50, 40 };
Text playButton = { { 100, 200 }, "Play", 30, 20 };
Text instructionButton = { { 100, 300 }, "Instructions", 30, 20 };
Text aboutButton = { { 100, 400 }, "About", 30, 20 };
Text HighScoreViewButton = { { 100, 500 }, "View High Scores", 30, 20 };
Text HighScoreCleaButton = { { 100, 600 }, "Clear High Scores", 30, 20 };
Text exitButton = { { 100, 700 }, "Exit", 30, 20 };
Box selectBox = { { 100, 200 }, 30, 250 };

//Insturction
Text instructTitle = { { 300, 100 }, "Instructions", 50, 40 };
Text ReadConsoleText = { { 500, 400 }, "Read The Console", 20, 10 };
Text instrucBackButton = { { 1040, 740 }, "Back", 30, 20 };

//About
Text tungText = { { 400, 400 }, "Tung Nguyen", 40, 30 };
Text aboutBackButton = { { 1040, 740 }, "Back", 30, 20 };

//Levels (Every level)
Room room[20];
Krampus krampus;
Player player;
Arrow arrow[5];
Text WinText = { { 530, 400 }, "You Win", 25, 15 };
Text LoseText = { { 500, 400 }, "You Lose", 25, 15 };

int main()
{
	//Screen Size
	initContext(1200, 800, "Hunt the wumpus");
	srand(time(NULL));

	//OnLogicUpdate
	while (stepContext())
	{
		switch (CurrentGameLevel)
		{
		case Exit:
			break;
		case SplashScreen:
			SplashScreenState();
			break;
		case MainMenu:
			MainMenuState();
			break;
		case Instruction:
			InstructionState();
			break;
		case About:
			AboutState();
			break;
		case StartGame:
			CreateMap();
		case Pause:
			player.OnLogicUpdate();
		case Level1:
			PlayerTurnNum += 1;
			if (LoseGame == false && WinGame == false)
			{
				for (int i = 0; i < 5; ++i) arrow[i].OnLogicUpdate();
				krampus.OnLogicUpdate();
				for (int i = 0; i < 20; ++i) room[i].OnLogicUpdate();
				FirstTimeRunning = false;
			}
			else CurrentGameLevel = EndGame;
			break;
		case EndGame:
			WinLose();
			break;
		default:
			break;
		}

		//Exits Console And Client
		if (CurrentGameLevel == Exit) break;
	}

	termContext();
	return 0;
}