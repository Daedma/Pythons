#include "SNAKE.h"

bool operator==(const COORD& lhs, const COORD& rhs)
{
	return (lhs.X == rhs.X) && (lhs.Y == rhs.Y);
}

bool operator!=(const COORD& lhs, const COORD& rhs)
{
	return !(lhs == rhs);
}

void game_over(const bool exodus)
{
	system("cls");
	if (exodus == WIN)
	{
		std::cout << "YOU WIN!" << std::endl;
	}
	else
		std::cout << "YOU LOSE!" << std::endl;
	Sleep(5000);
	exit(0);
}