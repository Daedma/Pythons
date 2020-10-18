#include "SNAKE.h"

Field::Field(SHORT w = 50, SHORT h = 50, const char ag = ' '):
	height(h), width(w), aggregate(ag){}

void Field::draw()
{
	edit_console();
	SetConsoleCursorPosition(hConsole, { FIELD_BEGIN_X - 1, FIELD_BEGIN_Y - 1 });
	SetConsoleTextAttribute(hConsole, FRAME_COLOR);
	std::cout << char(FIELD_FRAME);
	for (size_t i = FIELD_BEGIN_X + 1; i != FIELD_BEGIN_X + width; ++i)
		std::cout << char(FIELD_FRAME);
	std::cout << char(FIELD_FRAME) << '\n' << char(FIELD_FRAME);
	for (SHORT y = FIELD_BEGIN_Y; y != height; ++y) 
	{
		SetConsoleTextAttribute(hConsole, FIELD_COLOR);
		for (SHORT x = FIELD_BEGIN_X; x != width; ++x)
		{
			SetConsoleCursorPosition(hConsole, { x,y });
			std::cout << aggregate;
		}
		SetConsoleTextAttribute(hConsole, FRAME_COLOR);
		std::cout << char(FIELD_FRAME) << '\n';
		std::cout << char(FIELD_FRAME);
	}
	for (size_t i = FIELD_BEGIN_X + 1; i != FIELD_BEGIN_X + width; ++i)
		std::cout << char(FIELD_FRAME);
	std::cout << char(FIELD_FRAME);
}

void Field::edit_console()
{
	//устанавливаем название окна консоли...
	SetConsoleTitle("Pythons!\0");
	//делаем курсос невидимым...
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hConsole, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);
	//устанавливаем размер буффера консоли...
	SetConsoleScreenBufferSize(hConsole, { width, height });
	//устанавливаем размер окна консоли...
	SMALL_RECT windowSize = { 0, 0, width, height };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void Field::rainbow(WORD& palette)
{
	SetConsoleTextAttribute(hConsole, ++palette);
	if (palette == FULL_PALETTE)
		palette = CLEAR_PALETTE;
}

void Field::clear(size_t speed)
{
	SHORT x = width / 2;
	SHORT y = height / 2;
	SHORT delta_x = 0;
	SHORT delta_y = 0;
	WORD palette = CLEAR_PALETTE;
	while ((x >= FIELD_BEGIN_X && x <= width) || (y <= height && y >= FIELD_BEGIN_Y))
	{
		++delta_x;
		for (SHORT i = 0; i != delta_x; ++i)
		{
			if (x+i <= width && x+i>=FIELD_BEGIN_X && y<=height)
			{
				rainbow(palette);
				SetConsoleCursorPosition(hConsole, { (x + i), y });
				std::cout << ' ';
				Sleep(speed);
			}
		}
		x += delta_x;
		++delta_y;
		for(SHORT i=0;i!=delta_y;++i)
		{
			if (y-i <= height && y-i>=FIELD_BEGIN_Y-1 && x<=width) 
			{
				rainbow(palette);
				SetConsoleCursorPosition(hConsole, { x,(y - i) });
				std::cout << ' ';
				Sleep(speed);
			}
		}
		y -= delta_y;
		++delta_x;
		for (SHORT i = 0; i != delta_x; ++i)
		{
			if (x-i <= width && x-i >= FIELD_BEGIN_X && y >= FIELD_BEGIN_Y-1)
			{
				rainbow(palette);
				SetConsoleCursorPosition(hConsole, { (x - i), y });
				std::cout << ' ';
				Sleep(speed);
			}
		}
		x -= delta_x;
		++delta_y;
		for (SHORT i = 0; i != delta_y; ++i)
		{
			if (y+i <= height && y+i >= FIELD_BEGIN_Y-1 && x >= FIELD_BEGIN_X-1)
			{
				rainbow(palette);
				SetConsoleCursorPosition(hConsole, { x,(y + i) });
				std::cout << ' ';
				Sleep(speed);
			}
		}
		y += delta_y;
	}
}

