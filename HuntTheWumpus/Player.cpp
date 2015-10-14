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



Player::Player()
{
	CurrentRoom = 0;
	arrowNum = 5;
}


Player::~Player()
{
}

void Player::OnLogicUpdate()
{
	//Prints to console and input commands
	ConsoleCommand();

	//Update Position on map
	position = room[CurrentRoom].GetPosition();
	DrawPlayer();
}

void Player::ConsoleCommand()
{
	//Dangers, also determines if the player can move
	if (room[CurrentRoom].HasBat() == true)
	{
		system("cls");
		cout << "Oh no! you ran into a room of giant bats! They carried you to a random room" << endl;

		for (int i = 0; i < 50; ++i) //Assign random, non dangerous room
		{
			bool matchesRoomsAlreadyUsed = false;
			int randomRoom = Randint(0, 19);

			for each (int number in RoomsAlreadyUsed)
			{
				if (randomRoom == number) matchesRoomsAlreadyUsed = true;
			}

			if (matchesRoomsAlreadyUsed == true) i -= 1;
			else
			{
				CurrentRoom = room[randomRoom].GetID() - 1;
				break;
			}
		}
		IsPlayerTurn = false;
	}
	else if (room[CurrentRoom].HasPit() == true)
	{
		system("cls");
		cout << "Oh no! You fell into an endless pit!" << endl << "Game Over" << endl;
		LoseGame = true;
		IsPlayerTurn = false;
	}
	else if (room[CurrentRoom].HasWumpus() == true)
	{
		if (krampus.HasAwaken() == true)
		{
			system("cls");
			cout << "Oh no! The Wumpus Ate You!" << endl << "Game Over" << endl;
			LoseGame = true;
			IsPlayerTurn = false;
		}
		else //Wumpus becomes active
		{
			cout << "You woke up the Wumpus! " << endl << "The Wumpus charges out of the room" << endl;
			krampus.Awake();

			int choice = Randint(1, 3);

			//Moves wumpus to one of the random connected rooms
			switch (choice)
			{
			case 1:
				room[room[CurrentRoom].GetRoom1().GetID() - 1].SetWumpusStatus(true);
				krampus.SetCurrentRoom(room[room[CurrentRoom].GetRoom1().GetID() - 1].GetID() - 1);
				break;
			case 2:
				room[room[CurrentRoom].GetRoom2().GetID() - 1].SetWumpusStatus(true);
				krampus.SetCurrentRoom(room[room[CurrentRoom].GetRoom2().GetID() - 1].GetID() - 1);
				break;
			case 3:
				room[room[CurrentRoom].GetRoom3().GetID() - 1].SetWumpusStatus(true);
				krampus.SetCurrentRoom(room[room[CurrentRoom].GetRoom3().GetID() - 1].GetID() - 1);
				break;
			default:
				break;
			}

			room[CurrentRoom].SetWumpusStatus(false);
			IsPlayerTurn = false;
		}
	}
	else if (room[CurrentRoom].HasArrow() == true)
	{
		system("cls");
		cout << "Oh no! You got shot by your own arrow!" << endl << "Game Over" << endl;
		LoseGame = true;
		IsPlayerTurn = false;
	}
	//Checks arrows to see if player has any left or else player dies
	else if (arrowNum <= 0)
	{
		int arrowsStillAlive = 0;
		for each (Arrow singleArrow in arrow)
		{
			if (singleArrow.GetisDead() == false) arrowsStillAlive += 1;
		}

		if (arrowsStillAlive == 0)
		{
			cout << "You ran out of arrows! You lose!";
			LoseGame = true;
			IsPlayerTurn = false;
		}
		else IsPlayerTurn = true;
	}

	else
	{
		IsPlayerTurn = true;
	}

	//Is it the player's turn?
	if (IsPlayerTurn == true)
	{
		cout << "You are in room: " << room[CurrentRoom].GetID() << endl;
		cout << "You Have " << arrowNum << " arrow Left " << endl;
		cout << "You see a tunnel leading to room: " << room[CurrentRoom].GetRoom1().GetID() << endl;
		cout << "You see a tunnel leading to room: " << room[CurrentRoom].GetRoom2().GetID() << endl;
		cout << "You see a tunnel leading to room: " << room[CurrentRoom].GetRoom3().GetID() << endl;

		//Warns of nearby danger
		if (room[CurrentRoom].GetRoom1().HasBat() || room[CurrentRoom].GetRoom2().HasBat() || room[CurrentRoom].GetRoom3().HasBat())
		{
			cout << "You heard a wooshing noise in the distance " << endl;
		}
		if (room[CurrentRoom].GetRoom1().HasPit() || room[CurrentRoom].GetRoom2().HasPit() || room[CurrentRoom].GetRoom3().HasPit())
		{
			cout << "A cold breeze fills the air " << endl;
		}
		if (room[CurrentRoom].GetRoom1().HasWumpus() || room[CurrentRoom].GetRoom2().HasWumpus() || room[CurrentRoom].GetRoom3().HasWumpus())
		{
			cout << "You feel chills down your spine as if something horrible is close " << endl;
		}
		cout << "Type 1 to shoot arrow" << endl;
		cout << "Type 2 to move" << endl;
		cout << "Type 3 to quit" << endl;

		int choice;

		if (FirstTimeRunning == true)
		{
			choice = 0;
			position = room[CurrentRoom].GetPosition();
			DrawPlayer();
		}
		else cin >> choice;

		switch (choice)
		{
		case 1:
			if (arrowNum > 0) ShootArrow();
			else cout << "Oh no! You ran out of arrows, hopefully your last arrow hits the wumpus" << endl;
			break;
		case 2:
			Movement();
			IsPlayerTurn = false;
			break;
		case 3:
			LoseGame = true;
			IsPlayerTurn = false;
			break;
		default:
			system("cls");
		}
	}
}

void Player::Movement()
{
	cout << "Which room would you like to go into? " << endl;
	cout << "Type 1 to goto room: " << room[CurrentRoom].GetRoom1().GetID() << endl;
	cout << "Type 2 to goto room: " << room[CurrentRoom].GetRoom2().GetID() << endl;
	cout << "Type 3 to goto room: " << room[CurrentRoom].GetRoom3().GetID() << endl;

	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:
		CurrentRoom = room[CurrentRoom].GetRoom1().GetID() - 1;
		break;
	case 2:
		CurrentRoom = room[CurrentRoom].GetRoom2().GetID() - 1;
		break;
	case 3:
		CurrentRoom = room[CurrentRoom].GetRoom3().GetID() - 1;
		break;
	default:
		system("cls");
	}

	system("cls");
}

void Player::ShootArrow()
{
	cout << "Which room would you like to shoot through?" << endl;
	cout << "Type 1 to shoot into room: " << room[CurrentRoom].GetRoom1().GetID() << endl;
	cout << "Type 2 to shoot into room: " << room[CurrentRoom].GetRoom2().GetID() << endl;
	cout << "Type 3 to shoot into room: " << room[CurrentRoom].GetRoom3().GetID() << endl;
	cout << "Type 4 change mind" << endl;

	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:
		room[room[CurrentRoom].GetRoom1().GetID() - 1].SetArrowStatus(true);
		arrow[arrowNum - 1].SetRestrictedRoom(room[CurrentRoom].GetID() - 1); //Restrict Arrows from shooting back at the player
		arrow[arrowNum - 1].SetCurrentRoom(room[CurrentRoom].GetRoom1().GetID() - 1); //Set arrow's starting position in chosen room
		arrow[arrowNum - 1].Awake();
		arrowNum -= 1; //used up 1 arrow
		break;
	case 2:
		room[room[CurrentRoom].GetRoom2().GetID() - 1].SetArrowStatus(true);
		arrow[arrowNum - 1].SetRestrictedRoom(room[CurrentRoom].GetID() - 1);
		arrow[arrowNum - 1].SetCurrentRoom(room[CurrentRoom].GetRoom2().GetID() - 1);
		arrow[arrowNum - 1].Awake();
		arrowNum -= 1;
		break;
	case 3:
		room[room[CurrentRoom].GetRoom3().GetID() - 1].SetArrowStatus(true);
		arrow[arrowNum - 1].SetRestrictedRoom(room[CurrentRoom].GetID() - 1);
		arrow[arrowNum - 1].SetCurrentRoom(room[CurrentRoom].GetRoom3().GetID() - 1);
		arrow[arrowNum - 1].Awake();
		arrowNum -= 1;
		break;
	case 4:
		system("cls");
		ConsoleCommand();
		break;
	default:
		system("cls");
	}

	system("cls");
}

void Player::DrawPlayer()
{
	DrawTriangle(position, 20, 20);
}

Vector2 Player::GetPosition()
{
	return position;
}

int Player::GetCurrentRoom()
{
	return CurrentRoom;
}

void Player::ResetAll()
{
	CurrentRoom = 0;
	arrowNum = 5;
}
