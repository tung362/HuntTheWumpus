#pragma once

class Player;
class Arrow;
class Room;
class Krampus;

class Vector2
{
public:
	float x;
	float y;
	Vector2();
	~Vector2();
	Vector2(float x1, float y1);
	Vector2 operator+(Vector2 otherVec);
	Vector2 operator-(Vector2 otherVec);
	Vector2 operator*(Vector2 otherVec);
	Vector2 operator/(Vector2 otherVec);
	void operator+=(Vector2 otherVec);
	void operator-=(Vector2 otherVec);
	void operator*=(Vector2 otherVec);
	void operator/=(Vector2 otherVec);
	bool operator==(Vector2 otherVec);
	bool operator!=(Vector2 otherVec);
};

struct Text
{
	Vector2 position;
	char text[128];
	float height;
	float width;
};

struct Box
{
	Vector2 position;
	float height;
	float width;
};

class Player
{
private:
	Vector2 position;
	int CurrentRoom;
	int arrowNum;
public:
	Player();
	~Player();
	void OnLogicUpdate(); //Run every frame
	void ConsoleCommand();
	void Movement();
	void ShootArrow();
	void DrawPlayer();
	Vector2 GetPosition();
	int GetCurrentRoom();
	void ResetAll();
};

class Arrow
{
private:
	Vector2 position;
	int CurrentRoom;
	int TurnsLeft;
	int RestrictedRooms[20];
	bool isAwake;
	bool isDead;
	bool FirstTime;
public:
	Arrow();
	~Arrow();
	void OnLogicUpdate(); //Run every frame
	void Movement();
	void DrawArrow();
	void Awake();
	void SetRestrictedRoom(int RoomNumber);
	void SetCurrentRoom(int RoomNumber);
	Vector2 GetPosition();
	bool GetIsAwake();
	bool GetisDead();
	int GetCurrentRoom();
	void ResetAll();
};

class Room
{
private:
	Vector2 position;
	Room *OtherRoom[3];
	int roomID;
	bool hasABat;
	bool hasPitFall;
	bool hasAWumpus;
	bool hasAArrow;
public:
	Room();
	~Room();
	void OnLogicUpdate(); //Run every frame
	void DrawRoom();
	void SetRoomStats(Vector2 NewPosition, int NewRoomID, bool NewHasBat, bool NewHasPitFall, bool NewHasWumpus, bool NewHasArrow);
	void SetOtherRooms(int Room1, int Room2, int Room3); //sets the 3 rooms the player can go to in this room
	void SetPitStatus(bool has);
	void SetBatStatus(bool has);
	void SetWumpusStatus(bool has);
	void SetArrowStatus(bool has);
	Room GetRoom1(); //Get the first room this room is connected to
	Room GetRoom2(); //Get the second room this room is connected to
	Room GetRoom3(); //Get the third room this room is connected to
	int GetID();
	Vector2 GetPosition();
	bool HasBat();
	bool HasPit();
	bool HasWumpus();
	bool HasArrow();
	void ResetAll();
};

class Krampus
{
private:
	bool hasWoken;
	int CurrentRoom;
	bool FirstTime;
public:
	Krampus();
	~Krampus();
	void OnLogicUpdate(); //Run every frame
	void Movement();
	void SetCurrentRoom(int RoomNumber);
	bool HasAwaken();
	void Awake();
	void ResetAll();
};

//Splashscreen
extern Text title;

//Main Menu
extern Text mainTitle;
extern Text playButton;
extern Text instructionButton;
extern Text aboutButton;
extern Text HighScoreViewButton;
extern Text HighScoreCleaButton;
extern Text exitButton;
extern Box selectBox;

//Insturction
extern Text instructTitle;
extern Text ReadConsoleText;
extern Text instrucBackButton;

//About
extern Text tungText;
extern Text aboutBackButton;

//Levels (Every level)
extern Room room[20];
extern Krampus krampus;
extern Player player;
extern Arrow arrow[5];
extern Text WinText;
extern Text LoseText;