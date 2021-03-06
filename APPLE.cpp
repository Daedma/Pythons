#include "SNAKE.h"
#include <ctime>

std::default_random_engine Apple::e(time(0));

Apple::Apple(SHORT x, SHORT y, Snake* _snake):
	dx(FIELD_BEGIN_X + 1, x - 1), dy(FIELD_BEGIN_Y + 1, y - 1), snake(_snake)
{
	do {
		coord = { dx(e), dy(e) };
	} while (std::find(snake->coord.begin(), snake->coord.end(), coord) != snake->coord.end());
}

void Apple::draw() const
{
	SetConsoleTextAttribute(hConsole, APPLE_COLOR);
	SetConsoleCursorPosition(hConsole, coord);
	std::cout << char(APPLE);
}

void Apple::redraw()
{
	SetConsoleCursorPosition(hConsole, coord);
	SetConsoleTextAttribute(hConsole, SNAKE_COLOR);
	std::cout << char(SNAKE);
	do {
		coord = { dx(e), dy(e) };
	} while (std::find(snake->coord.begin(), snake->coord.end(), coord) != snake->coord.end());
	draw();
}