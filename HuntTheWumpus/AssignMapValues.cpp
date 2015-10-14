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

void AssignMapValues(Vector2 Position, Room *Rooms, float Height, float Width)
{
	//Sets the default values of the room
	Rooms[0].SetRoomStats(Vector2(Position.x, Position.y - (1 * Height)), 1, false, false, false, false);
	Rooms[1].SetRoomStats(Vector2(Position.x + (1.25 * Width), Position.y), 2, false, false, false, false);
	Rooms[2].SetRoomStats(Vector2(Position.x + (1 * Width), Position.y + (1 * Height)), 3, false, false, false, false);
	Rooms[3].SetRoomStats(Vector2(Position.x - (1 * Width), Position.y + (1 * Height)), 4, false, false, false, false);
	Rooms[4].SetRoomStats(Vector2(Position.x - (1.25 * Width), Position.y), 5, false, false, false, false);
	Rooms[5].SetRoomStats(Vector2(Position.x, Position.y - (1.5 * Height)), 6, false, false, false, false);
	Rooms[6].SetRoomStats(Vector2(Position.x + (2 * Width), Position.y - (0.25 * Height)), 7, false, false, false, false);
	Rooms[7].SetRoomStats(Vector2(Position.x + (1.5 * Width), Position.y + (1.75 * Height)), 8, false, false, false, false);
	Rooms[8].SetRoomStats(Vector2(Position.x - (1.5 * Width), Position.y + (1.75 * Height)), 9, false, false, false, false);
	Rooms[9].SetRoomStats(Vector2(Position.x - (2 * Width), Position.y - (0.25 * Height)), 10, false, false, false, false);
	Rooms[10].SetRoomStats(Vector2(Position.x + (1.5 * Width), Position.y - (1.5 * Height)), 11, false, false, false, false);
	Rooms[11].SetRoomStats(Vector2(Position.x + (2.5 * Width), Position.y + (1 * Height)), 12, false, false, false, false);
	Rooms[12].SetRoomStats(Vector2(Position.x, Position.y + (2.75 * Height)), 13, false, false, false, false);
	Rooms[13].SetRoomStats(Vector2(Position.x - (2.5 * Width), Position.y + (1 * Height)), 14, false, false, false, false);
	Rooms[14].SetRoomStats(Vector2(Position.x - (1.5 * Width), Position.y - (1.5 * Height)), 15, false, false, false, false);
	Rooms[15].SetRoomStats(Vector2(Position.x + (2.25 * Width), Position.y - (2.25 * Height)), 16, false, false, false, false);
	Rooms[16].SetRoomStats(Vector2(Position.x + (3.5 * Width), Position.y + (1.25 * Height)), 17, false, false, false, false);
	Rooms[17].SetRoomStats(Vector2(Position.x, Position.y + (3.75 * Height)), 18, false, false, false, false);
	Rooms[18].SetRoomStats(Vector2(Position.x - (3.5 * Width), Position.y + (1.25 * Height)), 19, false, false, false, false);
	Rooms[19].SetRoomStats(Vector2(Position.x - (2.25 * Width), Position.y - (2.25 * Height)), 20, false, false, false, false);

	//Connects the rooms together
	Rooms[0].SetOtherRooms(6, 2, 5);
	Rooms[1].SetOtherRooms(7, 1, 3);
	Rooms[2].SetOtherRooms(8, 2, 4);
	Rooms[3].SetOtherRooms(9, 3, 5);
	Rooms[4].SetOtherRooms(10, 4, 1);
	Rooms[5].SetOtherRooms(11, 1, 15);
	Rooms[6].SetOtherRooms(12, 2, 11);
	Rooms[7].SetOtherRooms(13, 3, 12);
	Rooms[8].SetOtherRooms(14, 4, 13);
	Rooms[9].SetOtherRooms(15, 5, 14);
	Rooms[10].SetOtherRooms(16, 6, 7);
	Rooms[11].SetOtherRooms(17, 7, 8);
	Rooms[12].SetOtherRooms(18, 8, 9);
	Rooms[13].SetOtherRooms(19, 9, 10);
	Rooms[14].SetOtherRooms(20, 10, 6);
	Rooms[15].SetOtherRooms(20, 11, 17);
	Rooms[16].SetOtherRooms(18, 12, 16);
	Rooms[17].SetOtherRooms(19, 13, 17);
	Rooms[18].SetOtherRooms(20, 14, 18);
	Rooms[19].SetOtherRooms(16, 15, 19);

	//Randomly add pits, bats, and the wumpus
	int pitLeft = 2;
	int Bat = 2;
	int wumpusLeft = 1;
	std::fill_n(RoomsAlreadyUsed, 20, 50);

	for (int i = 0; i < 50; ++i) //Assign pits
	{
		bool matchesRoomsAlreadyUsed = false;
		int randRoomNum = Randint(0, 19);

		for each (int number in RoomsAlreadyUsed)
		{
			if (randRoomNum == number || randRoomNum == 0) matchesRoomsAlreadyUsed = true;
		}

		if (matchesRoomsAlreadyUsed == true) i -= 1;
		else
		{
			bool canAssign = true;

			if (canAssign == true)
			{
				if (pitLeft > 0)
				{
					RoomsAlreadyUsed[i] = randRoomNum;
					Rooms[randRoomNum].SetPitStatus(true);
					pitLeft -= 1;
					canAssign = false;
				}
				else
				{
					if (Bat > 0)
					{
						RoomsAlreadyUsed[i] = randRoomNum;
						Rooms[randRoomNum].SetBatStatus(true);
						Bat -= 1;
						canAssign = false;
					}
					else
					{
						if (wumpusLeft > 0)
						{
							RoomsAlreadyUsed[i] = randRoomNum;
							Rooms[randRoomNum].SetWumpusStatus(true);
							krampus.SetCurrentRoom(randRoomNum);
							wumpusLeft -= 1;
							canAssign = false;
						}
						else break;
					}
				}
			}
		}
	}
}