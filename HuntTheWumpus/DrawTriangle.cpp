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

void DrawTriangle(Vector2 Position, float Height, float Width)
{
	drawLine(Position.x - Width / 2, Position.y + Height / 2, Position.x + Width / 2, Position.y + Height / 2);
	drawLine(Position.x + Width / 2, Position.y + Height / 2, Position.x, Position.y - Height / 2);
	drawLine(Position.x, Position.y - Height / 2, Position.x - Width / 2, Position.y + Height / 2);
}