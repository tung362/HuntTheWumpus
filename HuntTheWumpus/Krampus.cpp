#include "GameObject.h"
#include "sfwdraw.h"
#include "string.h"
#include "GameFunction.h"
#include <iostream>
#include <cstring>
#include <windows.h>

using namespace sfw;
using namespace sfw_string;
using std::cin;
using std::cout;
using std::endl;



Krampus::Krampus()
{
	hasWoken = false;
	FirstTime = true;
}


Krampus::~Krampus()
{
}

void Krampus::OnLogicUpdate()
{
	if (hasWoken == false)
	{
		//Wake up when an arrow is fired
		for each (Arrow singleArrow in arrow)
		{
			if (singleArrow.GetIsAwake() == true) hasWoken = true;
		}
	}
	else Movement();

	//Win if arrow hits the wumpus
	for each (Arrow singleArrow in arrow)
	{
		//Win if arrow hits the wumpus
		if (CurrentRoom == singleArrow.GetCurrentRoom())
		{
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			cout << "You shot the wumpus!" << endl << "You Win" << endl;
			WinGame = true;
			IsPlayerTurn = false;
		}
	}
}

void Krampus::Movement()
{
	if (FirstTime == true)
	{
		FirstTime = false;
	}
	else
	{
		int chance = Randint(1, 4); //25% chance to move and 75% chance to stay idle

		if (chance == 1 || chance == 2 || chance == 3)
		{
			int choice = Randint(1, 3); //Moves to one of the random connected rooms

			switch (choice)
			{
			case 1:
				room[CurrentRoom].SetWumpusStatus(false);
				room[room[CurrentRoom].GetRoom1().GetID() - 1].SetWumpusStatus(true);
				CurrentRoom = room[CurrentRoom].GetRoom1().GetID() - 1;
				break;
			case 2:
				room[CurrentRoom].SetWumpusStatus(false);
				room[room[CurrentRoom].GetRoom2().GetID() - 1].SetWumpusStatus(true);
				CurrentRoom = room[CurrentRoom].GetRoom2().GetID() - 1;
				break;
			case 3:
				room[CurrentRoom].SetWumpusStatus(false);
				room[room[CurrentRoom].GetRoom3().GetID() - 1].SetWumpusStatus(true);
				CurrentRoom = room[CurrentRoom].GetRoom3().GetID() - 1;
				break;
			default:
				break;
			}
		}

		//Lose if player runs into him a second time
		if (CurrentRoom == player.GetCurrentRoom())
		{
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			cout << "Oh no! The Wumpus Ate You!" << endl << "Game Over" << endl;
			LoseGame = true;
			IsPlayerTurn = false;
		}
	}
}

void Krampus::SetCurrentRoom(int RoomNumber)
{
	CurrentRoom = RoomNumber;
}

bool Krampus::HasAwaken()
{
	return hasWoken;
}

void Krampus::Awake()
{
	hasWoken = true;
}

void Krampus::ResetAll()
{
	hasWoken = false;
	FirstTime = true;
}