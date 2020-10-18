#include "SNAKE.h"

bool operator==(const COORD& lhs, const COORD& rhs)
{
	return (lhs.X == rhs.X) && (lhs.Y == rhs.Y);
}

bool operator!=(const COORD& lhs, const COORD& rhs)
{
	return !(lhs == rhs);
}

const COORD get_mouse_clk()
{
	DWORD numEvents = 0; //кол-во непрочитанных сообщений
	bool isRunning = true; //флаг продолжения работы
	DWORD numEventsRead = 0; //кол-во прочитанных сообщений
	COORD mouse_coord;
	while (isRunning)
	{
		GetNumberOfConsoleInputEvents(in_hConsole, &numEvents);
		if (numEvents != 0)
		{
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(in_hConsole, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i)
			{
				if (eventBuffer[i].EventType == MOUSE_EVENT)
				{
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						mouse_coord = eventBuffer[i].Event.MouseEvent.dwMousePosition;
						isRunning = false;
						break;
					}
				}
			}
			delete[] eventBuffer;
		}
	}
	return mouse_coord;
}

void Snake::game_over(const bool exodus)
{
	//system("cls");
	SetConsoleCursorPosition(hConsole, { field->get_width() / 2 - 10, field->get_height() / 2 - 3 });
	for (size_t i = 0; i != 20; ++i)
		std::cout << char(FIELD_FRAME);
	for (SHORT a = 2; a != -2; --a)
	{
		SetConsoleCursorPosition(hConsole, { field->get_width() / 2 - 10, field->get_height() / 2 - a });
		std::cout << char(FIELD_FRAME);
		for (size_t i = 0; i != 18; ++i)
		{
			std::cout << field->get_agg();
		}
		std::cout << char(FIELD_FRAME);
	}
	SetConsoleCursorPosition(hConsole, { field->get_width() / 2 - 10, field->get_height() / 2 + 2 });
	for (size_t i = 0; i != 20; ++i)
		std::cout << char(FIELD_FRAME);
	SetConsoleCursorPosition(hConsole, { field->get_width() / 2 - 5, field->get_height() / 2 - 2 });
	if (exodus == WIN)
	{
		SetConsoleTextAttribute(hConsole, 0b0010'1111);
		std::cout << "YOU WIN!";
		SetConsoleTextAttribute(hConsole, 0b0000'0111);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 0b0100'1111);
		std::cout << "YOU LOSE!";
		SetConsoleTextAttribute(hConsole, 0b0000'0111);
		SetConsoleCursorPosition(hConsole, { field->get_width() / 2 - 6, field->get_height() / 2 - 1 });
		std::cout << "your score: " << (coord.size()- INITIAL_SNAKE_SIZE);
	}
	SetConsoleCursorPosition(hConsole, { field->get_width() / 2 - 5, field->get_height() / 2 });
	std::cout << "Restart?";
	SetConsoleCursorPosition(hConsole, { field->get_width() / 2 - 8, field->get_height() / 2 + 1 });
	SetConsoleTextAttribute(hConsole, 0b0010'1111);
	std::cout << "YES";
	SetConsoleCursorPosition(hConsole, { field->get_width() / 2 + 5, field->get_height() / 2 + 1 });
	SetConsoleTextAttribute(hConsole, 0b0100'1111);
	std::cout << "NO";
	//const std::pair<const COORD, const COORD> _yes = { { field->get_width() / 2 - 8, field->get_height() / 2 + 1 } , { field->get_width() / 2 - 5, field->get_height() / 2 + 1 } };
	//const std::pair<const COORD, const COORD> _no = { { field->get_width() / 2 + 5, field->get_height() / 2 + 1 }, { field->get_width() / 2 + 7, field->get_height() / 2 + 1 } };
	//COORD clk = get_mouse_clk();
	//!((a)&&(b))||((a)&&(c))
	bool Waiting = true;
	while (Waiting)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case(KEY_ARROW_LEFT):
				SetConsoleTextAttribute(hConsole, 0b0000'0111);
				Waiting = false;
				field->draw();
				coord.clear();
				build({ field->get_width() / 2, field->get_height() / 2 }, *field);
				snake_course = RIGHT;
				speed = 1;
				apple.redraw();
				draw();
				break;
			case(KEY_ARROW_RIGHT):
				field->clear(1);
				SetConsoleCursorPosition(hConsole, { field->get_width() / 2 - 1, field->get_height() / 2 });
				SetConsoleTextAttribute(hConsole, 0b1111'1000);
				std::cout << "Bye!";
				Sleep(2500);
				exit(0);
			}
		}
	}
	//while (!((clk.Y == _yes.first.Y) && (((clk.X >= _yes.first.X) && (clk.X <= _yes.second.X)) || ((clk.X >= _no.first.X) && (clk.X <= _no.second.X)))))
	//{
	//	if (clk.Y == _yes.first.Y)
	//	{
	//		if ((clk.X >= _yes.first.X) && (clk.X <= _yes.second.X))
	//		{
	//			//продолжить игру
	//			SetConsoleTextAttribute(hConsole, 0b0000'0111);
	//			field->draw();
	//			coord.clear();
	//			build({ field->get_width()/2, field->get_height()/2 }, *field);
	//			snake_course = RIGHT;
	//			speed = 1;
	//			apple.redraw();
	//			draw();
	//		}
	//		else if ((clk.X >= _no.first.X) && (clk.X <= _no.second.X))
	//		{
	//			//закончить игру
	//			Sleep(5000);
	//			exit(EXIT_SUCCESS);
	//		}
	//	}
	//	else
	//		clk = get_mouse_clk();
	//}
}