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

extern bool useLevelDelay;

bool keyIsPressedInstruct = true;
float keyPressDelayTimerInstruct = 0;
bool instructionRunOnce = true;

void InstructionState()
{
	if (instructionRunOnce == true)
	{
		std::fstream InstructionFile;

		system("cls");
		InstructionFile.open("Instruction.txt", std::ios_base::in);

		if (InstructionFile.is_open())
		{
			std::string s;
			while (std::getline(InstructionFile, s)) cout << s << endl;
			InstructionFile.close();
		}
		instructionRunOnce = false;
	}

	if (keyIsPressedInstruct == true)
	{
		keyPressDelayTimerInstruct += getDeltaTime();

		if (keyPressDelayTimerInstruct > 0.5f)
		{
			keyIsPressedInstruct = false;
		}
	}

	if (getKey(32) && keyIsPressedInstruct == false) //pressed space key
	{
		instructionRunOnce = true;
		keyPressDelayTimerInstruct = 0;
		useLevelDelay = true;
		keyIsPressedInstruct = true;
		CurrentGameLevel = MainMenu;
	}
	selectBox = { { instrucBackButton.position.x + 40, instrucBackButton.position.y }, 60, 150 };

	DrawText(instructTitle.position, instructTitle.text, instructTitle.height, instructTitle.width);
	DrawText(instrucBackButton.position, instrucBackButton.text, instrucBackButton.height, instrucBackButton.width);
	DrawText(ReadConsoleText.position, ReadConsoleText.text, ReadConsoleText.height, ReadConsoleText.width);
	DrawBox(selectBox.position, selectBox.height, selectBox.width);
}