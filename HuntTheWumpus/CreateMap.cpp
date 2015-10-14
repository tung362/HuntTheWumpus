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

void CreateMap()
{
	std::fstream HighScoreFile;

	if (CreateNewMap == true)
	{
		//Create a name to put into the high score
		cout << "What is your name? (Up to 128 characters)" << endl;

		HighScoreFile.open("HighScores.txt", std::fstream::app);
		if (HighScoreFile.is_open())
		{
			cin.ignore();
			cin.getline(PlayerName, 128);
			HighScoreFile << endl << PlayerName << ": ";
			HighScoreFile.close();
		}

		//Setting Room settings
		AssignMapValues(Vector2(600, 300), room, 100, 100);

		CreateNewMap = false;
	}
}