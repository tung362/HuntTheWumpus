#include "GameFunction.h"
#include "sfwdraw.h"
#include "string.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>

using namespace sfw;
using namespace sfw_string;
using std::cin;
using std::cout;
using std::endl;

int Randint(int Min, int Max)
{
	return Min + (rand() % (Max - Min + 1)); //Got From http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
}