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

float splashTimer = 0;
bool SplashSreenRunOnce = true;

void SplashScreenState()
{
	if (SplashSreenRunOnce == true)
	{
		string welcomeString = "Welcome to Hunt The Wumpus!";
		cout << welcomeString << endl;
		SplashSreenRunOnce = false;
	}

	splashTimer += getDeltaTime();

	//Change to main menu after 4 seconds
	if (splashTimer > 4)
	{
		CurrentGameLevel = MainMenu;
		splashTimer = 0;
	}
	DrawText(title.position, title.text, title.height, title.width);
}