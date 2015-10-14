#include "GameFunction.h"
#include "sfwdraw.h"
#include "string.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace sfw;
using namespace sfw_string;
using std::cin;
using std::cout;
using std::endl;

float WinLoseTimer = 0;

void WinLose()
{

	WinLoseTimer += getDeltaTime();
	if(LoseGame == true) DrawText(LoseText.position, LoseText.text, LoseText.height, LoseText.width);
	else if (WinGame == true) DrawText(WinText.position, WinText.text, WinText.height, WinText.width);

	if (WinLoseTimer >= 5) //After a few seconds reset all and go back to main menu
	{
		std::fstream HighScoreFile;
		HighScoreFile.open("HighScores.txt", std::fstream::app);
		if (HighScoreFile.is_open())
		{
			if (LoseGame == true) HighScoreFile << "Died on turn: " << PlayerTurnNum << endl;
			else if (WinGame == true) HighScoreFile << "Killed the wumpus on turn: " << PlayerTurnNum << endl << endl;
			HighScoreFile.close();
		}

		ResetMap();
		CurrentGameLevel = MainMenu;
		WinLoseTimer = 0;
	}
}