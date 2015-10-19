#include "GameFunction.h"
#include "sfwdraw.h"
#include "string.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>
#include <windows.h>

using namespace sfw;
using namespace sfw_string;
using std::cin;
using std::cout;
using std::endl;

void ResetMap()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	//Reset game object back to default values
	player.ResetAll();
	for (int i = 0; i < 5; ++i) arrow[i].ResetAll();
	for (int i = 0; i < 20; ++i) room[i].ResetAll();
	krampus.ResetAll();
	IsPlayerTurn = true;
	FirstTimeRunning = true;
	CreateNewMap = true;
	LoseGame = false;
	WinGame = false;
}