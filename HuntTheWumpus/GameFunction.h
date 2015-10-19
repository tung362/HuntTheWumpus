#pragma once
#include "GameObject.h"

//Global Data
enum Level
{
	Exit, SplashScreen, MainMenu, Instruction, About, StartGame, Pause, Level1, EndGame
};
extern Level CurrentGameLevel;
extern Level TempLevel;
extern bool CreateNewMap;
extern bool IsPlayerTurn;
extern bool FirstTimeRunning;
extern bool LoseGame;
extern bool WinGame;
extern bool UseConsoleForMenu;
extern int PlayerTurnNum;
extern bool DebugMode;
extern char PlayerName[128];
extern int RoomsAlreadyUsed[20];
//End Of Global Data

void CreateMap();
void ResetMap();
void AssignMapValues(Vector2 Position, Room *Rooms, float Height, float Width);
void DrawBox(Vector2 Position, float Height, float Width);
void DrawTriangle(Vector2 Position, float Height, float Width);
int Randint(int Min, int Max);
void WinLose();
void DrawText(Vector2 Position, const char Text[], float Height, float Width);
void DrawA(Vector2 Position, float Height, float Width);
void DrawB(Vector2 Position, float Height, float Width);
void DrawC(Vector2 Position, float Height, float Width);
void DrawD(Vector2 Position, float Height, float Width);
void DrawE(Vector2 Position, float Height, float Width);
void DrawF(Vector2 Position, float Height, float Width);
void DrawG(Vector2 Position, float Height, float Width);
void DrawH(Vector2 Position, float Height, float Width);
void DrawI(Vector2 Position, float Height, float Width);
void DrawJ(Vector2 Position, float Height, float Width);
void DrawK(Vector2 Position, float Height, float Width);
void DrawL(Vector2 Position, float Height, float Width);
void DrawM(Vector2 Position, float Height, float Width);
void DrawN(Vector2 Position, float Height, float Width);
void DrawO(Vector2 Position, float Height, float Width);
void DrawP(Vector2 Position, float Height, float Width);
void DrawQ(Vector2 Position, float Height, float Width);
void DrawR(Vector2 Position, float Height, float Width);
void DrawS(Vector2 Position, float Height, float Width);
void DrawT(Vector2 Position, float Height, float Width);
void DrawU(Vector2 Position, float Height, float Width);
void DrawV(Vector2 Position, float Height, float Width);
void DrawW(Vector2 Position, float Height, float Width);
void DrawX(Vector2 Position, float Height, float Width);
void DrawY(Vector2 Position, float Height, float Width);
void DrawZ(Vector2 Position, float Height, float Width);
void Draw1(Vector2 Position, float Height, float Width);
void Draw1(Vector2 Position, float Height, float Width);
void Draw2(Vector2 Position, float Height, float Width);
void Draw3(Vector2 Position, float Height, float Width);
void Draw4(Vector2 Position, float Height, float Width);
void Draw5(Vector2 Position, float Height, float Width);
void Draw6(Vector2 Position, float Height, float Width);
void Draw7(Vector2 Position, float Height, float Width);
void Draw8(Vector2 Position, float Height, float Width);
void Draw9(Vector2 Position, float Height, float Width);
void Draw0(Vector2 Position, float Height, float Width);
void SplashScreenState();
void MainMenuState();
void InstructionState();
void AboutState();
