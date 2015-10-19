#include "GameObject.h"
#include "sfwdraw.h"
#include "string.h"
#include "GameFunction.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace sfw;
using namespace sfw_string;
using std::cin;
using std::cout;
using std::endl;



Arrow::Arrow()
{
	position = Vector2(9000, 9000);
	TurnsLeft = 4;
	isAwake = false;
	isDead = false;
	std::fill_n(RestrictedRooms, 20, 50);
	FirstTime = true;
}


Arrow::~Arrow()
{
}

void Arrow::OnLogicUpdate()
{
	if (isAwake == true && isDead == false)
	{
		Movement();

		position = room[CurrentRoom].GetPosition();
		DrawArrow();
	}
}

void Arrow::Movement()
{
	if (FirstTime == true)
	{
		SetRestrictedRoom(room[CurrentRoom].GetID() - 1);
		position = room[CurrentRoom].GetPosition();
		DrawArrow();
		FirstTime = false;
	}
	else
	{
		TurnsLeft -= 1;

		//if it's still alive
		if (TurnsLeft > 0)
		{
			SetRestrictedRoom(room[CurrentRoom].GetID() - 1);

			//Finds a random unvisited room connected to the current room and move to it
			for (int i = 0; i < 1; ++i)
			{
				int choice = Randint(1, 3); //3 but really only 2 choices becuase the arrow can't move backwards

				if (choice == 1 && room[CurrentRoom].GetRoom1().GetID() != RestrictedRooms[room[CurrentRoom].GetRoom1().GetID() - 1])
				{
					room[CurrentRoom].SetArrowStatus(false);
					room[room[CurrentRoom].GetRoom1().GetID() - 1].SetArrowStatus(true);
					CurrentRoom = room[CurrentRoom].GetRoom1().GetID() - 1;
				}
				else if (choice == 2 && room[CurrentRoom].GetRoom2().GetID() != RestrictedRooms[room[CurrentRoom].GetRoom2().GetID() - 1])
				{
					room[CurrentRoom].SetArrowStatus(false);
					room[room[CurrentRoom].GetRoom2().GetID() - 1].SetArrowStatus(true);
					CurrentRoom = room[CurrentRoom].GetRoom2().GetID() - 1;
				}
				else if (choice == 3 && room[CurrentRoom].GetRoom3().GetID() != RestrictedRooms[room[CurrentRoom].GetRoom3().GetID() - 1])
				{
					room[CurrentRoom].SetArrowStatus(false);
					room[room[CurrentRoom].GetRoom3().GetID() - 1].SetArrowStatus(true);
					CurrentRoom = room[CurrentRoom].GetRoom3().GetID() - 1;
				}
				else i -= 1; //keep looping until a valid match
			}
		}
		else
		{
			//Kill the arrow
			room[CurrentRoom].SetArrowStatus(false);
			position = Vector2(9000, 9000);
			isDead = true;
		}
	}
}

void Arrow::DrawArrow()
{
	//Display after player wins/loses or Debug Mode is true
	if (DebugMode == true || LoseGame == true || WinGame == true) DrawBox(position, 5, 30);
}

void Arrow::Awake()
{
	isAwake = true;
}

void Arrow::SetRestrictedRoom(int RoomNumber)
{
	RestrictedRooms[RoomNumber] = RoomNumber + 1;
}

void Arrow::SetCurrentRoom(int RoomNumber)
{
	CurrentRoom = RoomNumber;
}

Vector2 Arrow::GetPosition()
{
	return position;
}

bool Arrow::GetIsAwake()
{
	return isAwake;
}

bool Arrow::GetisDead()
{
	return isDead;
}

int Arrow::GetCurrentRoom()
{
	return CurrentRoom;
}

void Arrow::ResetAll()
{
	position = Vector2(9000, 9000);
	TurnsLeft = 4;
	CurrentRoom = 0;
	isAwake = false;
	isDead = false;
	std::fill_n(RestrictedRooms, 20, 50);
	FirstTime = true;
}
