#include "GameObject.h"
#include "sfwdraw.h"
#include "string.h"
#include "GameFunction.h"
#include <iostream>
#include <cstring>
#include <sstream>

using namespace sfw;
using namespace sfw_string;
using std::cin;
using std::cout;
using std::endl;
using std::stringstream;

Room::Room()
{
	position = Vector2(0, 0);
	roomID = 0;
	hasABat = false;
	hasPitFall = false;
	hasAWumpus = false;
	hasAArrow = false;
}


Room::~Room()
{
}

void Room::OnLogicUpdate()
{
	DrawRoom();
}

void Room::DrawRoom()
{
	drawLine(position.x, position.y, OtherRoom[0]->position.x, OtherRoom[0]->position.y);
	drawLine(position.x, position.y, OtherRoom[1]->position.x, OtherRoom[1]->position.y);
	drawLine(position.x, position.y, OtherRoom[2]->position.x, OtherRoom[2]->position.y);

	stringstream roomIDToString;
	roomIDToString << roomID;
	std::string P1str = roomIDToString.str();

	DrawText(Vector2(position.x, position.y + 10), P1str.c_str(), 10, 10);

	//Display after player wins/loses or Debug Mode is true
	if (DebugMode == true || LoseGame == true || WinGame == true)
	{
		if (hasPitFall == true) drawCircle(position.x, position.y, 30);
		if (hasABat == true) drawCircle(position.x, position.y, 15);
		if (hasAWumpus == true) DrawBox(Vector2(position.x, position.y), 35, 35);
		if (hasAArrow == true) DrawBox(position, 30, 5);
	}
}

void Room::SetRoomStats(Vector2 NewPosition, int NewRoomID, bool NewHasBat, bool NewHasPitFall, bool NewHasWumpus, bool NewHasArrow)
{
	position = NewPosition;
	roomID = NewRoomID;
	hasABat = NewHasBat;
	hasPitFall = NewHasPitFall;
	hasAWumpus = NewHasWumpus;
}

void Room::SetOtherRooms(int Room1, int Room2, int Room3)
{
	OtherRoom[0] = &room[Room1 - 1];
	OtherRoom[1] = &room[Room2 - 1];
	OtherRoom[2] = &room[Room3 - 1];
}

void Room::SetPitStatus(bool has)
{
	if (has == true) hasPitFall = true;
	else hasPitFall = false;
}

void Room::SetBatStatus(bool has)
{
	if (has == true) hasABat = true;
	else hasABat = false;
}

void Room::SetWumpusStatus(bool has)
{
	if (has == true) hasAWumpus = true;
	else hasAWumpus = false;
}

void Room::SetArrowStatus(bool has)
{
	if (has == true) hasAArrow = true;
	else hasAArrow = false;
}

Room Room::GetRoom1()
{
	return room[OtherRoom[0]->GetID() - 1];
}

Room Room::GetRoom2()
{
	return room[OtherRoom[1]->GetID() - 1];
}

Room Room::GetRoom3()
{
	return room[OtherRoom[2]->GetID() - 1];
}

int Room::GetID()
{
	return roomID;
}

Vector2 Room::GetPosition()
{
	return position;
}

bool Room::HasBat()
{
	return hasABat;
}

bool Room::HasPit()
{
	return hasPitFall;
}

bool Room::HasWumpus()
{
	return hasAWumpus;
}

bool Room::HasArrow()
{
	return hasAArrow;
}

void Room::ResetAll()
{
	position = Vector2(0, 0);
	roomID = 0;
	hasABat = false;
	hasPitFall = false;
	hasAWumpus = false;
	hasAArrow = false;
}
