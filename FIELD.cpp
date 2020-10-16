#include "SNAKE.h"

Field::Field(SHORT w = 50, SHORT h = 50, const char ag = ' '):
	height(h), width(w), aggregate(ag){}

void Field::draw()
{
	SetConsoleTitle("Pythons!\0");
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hConsole, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);

	SetConsoleCursorPosition(hConsole, { FIELD_BEGIN_X - 1, FIELD_BEGIN_Y - 1 });
	std::cout << char(178);
	for (size_t i = FIELD_BEGIN_X + 1; i != FIELD_BEGIN_X + width; ++i)
		std::cout << char(178);
	std::cout << char(178) << '\n' << char(178);
	for (SHORT y = FIELD_BEGIN_Y; y != height; ++y) 
	{
		for (SHORT x = FIELD_BEGIN_X; x != width; ++x)
		{
			SetConsoleCursorPosition(hConsole, { x,y });
			std::cout << aggregate;
		}
		std::cout << char(178) << '\n';
		std::cout << char(178);
	}
	for (size_t i = FIELD_BEGIN_X + 1; i != FIELD_BEGIN_X + width; ++i)
		std::cout << char(178);
	std::cout << char(178);
}