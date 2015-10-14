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

extern bool useLevelDelay;

bool keyIsPressedAbout = true;
float keyPressDelayTimerAbout = 0;
bool aboutRunOnce = true;

void AboutState()
{
	if (aboutRunOnce == true)
	{
		system("cls");
		string tungString = "Made By: Tung Nguyen";
		cout << tungString << endl;
		aboutRunOnce = false;
	}

	if (keyIsPressedAbout == true)
	{
		keyPressDelayTimerAbout += getDeltaTime();

		if (keyPressDelayTimerAbout > 0.5f)
		{
			keyIsPressedAbout = false;
		}
	}

	//Back to main menu
	if (getKey(32) && keyIsPressedAbout == false) //pressed space key
	{
		aboutRunOnce = true;
		keyPressDelayTimerAbout = 0;
		useLevelDelay = true;
		keyIsPressedAbout = true;
		CurrentGameLevel = MainMenu;
	}
	selectBox = { { aboutBackButton.position.x + 40, aboutBackButton.position.y }, 60, 150 };

	DrawText(aboutBackButton.position, aboutBackButton.text, aboutBackButton.height, aboutBackButton.width);
	DrawText(tungText.position, tungText.text, tungText.height, tungText.width);
	DrawBox(selectBox.position, selectBox.height, selectBox.width);
}