#include "GameFunction.h"
#include "sfwdraw.h"
#include "string.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace sfw;
using namespace sfw_string;
using std::cin;
using std::cout;
using std::endl;

int selectID = 1; //1 = Play, 2 = Instructions, 3 = About, 4 = Exit
bool keyIsPressed = false;
float keyPressDelayTimer = 0;

bool useLevelDelay = false;
float useLevelDelayTimer = 0;
bool mainMenuRunOnce = true;

void DisplayConsole()
{
	std::fstream InstructionFile;
	std::fstream HighScoreFile;

	if (mainMenuRunOnce == true)
	{
		string commandText[2];
		commandText[0] = "Type 1 to use Console Main Menu";
		commandText[1] = "Type 2 to use Button Main Menu";
		cout << commandText[0] << endl;
		cout << commandText[1] << endl;

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
			UseConsoleForMenu = true;
			mainMenuRunOnce = false;
			break;
		case 2:
			system("cls");
			cout << "Press 'w' or 's' key to select a button and use 'Space' to press button" << endl;
			UseConsoleForMenu = false;
			mainMenuRunOnce = false;
			break;
		default:
			break;
		}
	}

	if (UseConsoleForMenu == true)
	{
		system("cls");
		cout << "Hunt the Wumpus" << endl;
		cout << "---------------" << endl;
		cout << "Type 1 to play" << endl;
		cout << "Type 2 for instructions" << endl;
		cout << "Type 3 for about" << endl;
		cout << "Type 4 to view High Scores" << endl;
		cout << "Type 5 to clear High Scores" << endl;
		cout << "Type 6 to exit" << endl;

		int choice2;
		cin >> choice2;

		switch (choice2)
		{
		case 1:
			useLevelDelayTimer = 0;
			CurrentGameLevel = StartGame;
			break;
		case 2:
			useLevelDelayTimer = 0;

			InstructionFile.open("Instruction.txt", std::ios_base::in);

			if (InstructionFile.is_open())
			{
				std::string s;
				while (std::getline(InstructionFile, s)) cout << s << endl;
				InstructionFile.close();
			}
			system("pause");
			break;
		case 3:
			useLevelDelayTimer = 0;
			cout << "Made By: Tung Nguyen" << endl;
			system("pause");
			break;
		case 4:
			useLevelDelayTimer = 0;
			HighScoreFile.open("HighScores.txt", std::ios_base::in);

			if (HighScoreFile.is_open())
			{
				std::string s;
				while (std::getline(HighScoreFile, s)) cout << s << endl;
				HighScoreFile.close();
			}
			system("pause");
			break;
		case 5:
			useLevelDelayTimer = 0;
			cout << "File Cleared" << endl;
			HighScoreFile.open("HighScores.txt", std::fstream::out | std::fstream::trunc);
			HighScoreFile.close();
			system("pause");
			break;
		case 6:
			useLevelDelayTimer = 0;
			CurrentGameLevel = Exit;
			break;
		default:
			break;
		}
	}
}

void MainMenuState()
{
	DisplayConsole();
	std::fstream HighScoreFile;

	//How long until they can press the key again (Prevents Super fast button select)
	if (keyIsPressed == true)
	{
		keyPressDelayTimer += getDeltaTime();

		if (keyPressDelayTimer > 0.2f) keyIsPressed = false;
	}

	//How long until they can Transition levels agein (Prevents instant transition back)
	if (useLevelDelay == true)
	{
		useLevelDelayTimer += getDeltaTime();

		if (useLevelDelayTimer > 1.5f) useLevelDelay = false;
	}

	//Move select bar up
	if (getKey('w') && keyIsPressed == false)
	{
		selectID -= 1;
		keyPressDelayTimer = 0;
		keyIsPressed = true;
	}
	//Move select bar down
	else if (getKey('s') && keyIsPressed == false)
	{
		selectID += 1;
		keyPressDelayTimer = 0;
		keyIsPressed = true;
	}

	//Loops Select box to the bottom
	if (selectID <= 0) selectID = 6;
	//Loops Select box to the top
	else if (selectID > 6) selectID = 1;

	if (selectID == 1) //Play
	{
		selectBox = { { playButton.position.x + 40, playButton.position.y }, 60, 150 };
		if (getKey(32) && useLevelDelay == false)
		{
			useLevelDelayTimer = 0;
			useLevelDelay = true;
			CurrentGameLevel = StartGame; //pressed space key
		}
	}
	else if (selectID == 2) //Instruction
	{
		selectBox = { { instructionButton.position.x + 160, instructionButton.position.y }, 60, 390 };
		if (getKey(32) && useLevelDelay == false)
		{
			useLevelDelayTimer = 0;
			useLevelDelay = true;
			CurrentGameLevel = Instruction;
		}
	}
	else if (selectID == 3) //About
	{
		selectBox = { { aboutButton.position.x + 55, aboutButton.position.y }, 60, 175 };
		if (getKey(32) && useLevelDelay == false)
		{
			useLevelDelayTimer = 0;
			useLevelDelay = true;
			CurrentGameLevel = About;
		}
	}
	else if (selectID == 4) //View High Score
	{
		selectBox = { { HighScoreViewButton.position.x + 225, HighScoreViewButton.position.y }, 60, 525 };
		if (getKey(32) && useLevelDelay == false)
		{
			useLevelDelayTimer = 0;
			HighScoreFile.open("HighScores.txt", std::ios_base::in);

			if (HighScoreFile.is_open())
			{
				system("cls");
				std::string s;
				while (std::getline(HighScoreFile, s)) cout << s << endl;
				HighScoreFile.close();
				useLevelDelay = true;
			}
		}
	}
	else if (selectID == 5) //Clear High Score
	{
		selectBox = { { HighScoreCleaButton.position.x + 235, HighScoreCleaButton.position.y }, 60, 545 };
		if (getKey(32) && useLevelDelay == false)
		{
			system("cls");
			useLevelDelayTimer = 0;
			cout << "File Cleared" << endl;
			HighScoreFile.open("HighScores.txt", std::fstream::out | std::fstream::trunc);
			HighScoreFile.close();
			useLevelDelay = true;
		}
	}
	else if (selectID == 6) //Exit
	{
		selectBox = { { exitButton.position.x + 40, exitButton.position.y }, 60, 150 };
		if (getKey(32) && useLevelDelay == false)
		{
			useLevelDelayTimer = 0;
			useLevelDelay = true;
			CurrentGameLevel = Exit;
		}
	}

	DrawText(mainTitle.position, mainTitle.text, mainTitle.height, mainTitle.width);
	DrawText(playButton.position, playButton.text, playButton.height, playButton.width);
	DrawText(instructionButton.position, instructionButton.text, instructionButton.height, instructionButton.width);
	DrawText(aboutButton.position, aboutButton.text, aboutButton.height, aboutButton.width);
	DrawText(HighScoreViewButton.position, HighScoreViewButton.text, HighScoreViewButton.height, HighScoreViewButton.width);
	DrawText(HighScoreCleaButton.position, HighScoreCleaButton.text, HighScoreCleaButton.height, HighScoreCleaButton.width);
	DrawText(exitButton.position, exitButton.text, exitButton.height, exitButton.width);
	DrawBox(selectBox.position, selectBox.height, selectBox.width);
}