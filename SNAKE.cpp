#include "SNAKE.h"
#include  <stdexcept>

Snake::Snake(const COORD& beg_coord, const Field& _field, double beg_speed) :
	speed(beg_speed), field(&_field), snake_course(RIGHT), apple(_field.get_width(), _field.get_height(), this)
{
	if ((beg_coord.X <= (_field.get_width() - 3)) && (beg_coord.X >= FIELD_BEGIN_X) && (beg_coord.Y <= _field.get_height()) && (beg_coord.Y >= FIELD_BEGIN_Y))
	{
		COORD crd = beg_coord;
		for (unsigned i = 0; i != 7; ++i, ++crd.X)
		{
			coord.push_back(crd);
		}
	}
	else if ((beg_coord.X == (_field.get_width())) && (beg_coord.Y <= (_field.get_width() - 3)))
	{
		COORD crd = beg_coord;
		for (unsigned i = 0; i != 7; ++i, ++crd.Y)
		{
			coord.push_back(crd);
		}
	}
	else
		throw std::invalid_argument("Invalid coordinates");
}

void Snake::draw()
{
	auto it = coord.begin()+1;
	while (it != coord.end())
	{
		SetConsoleCursorPosition(hConsole, *it);
		std::cout << char(254);
		++it;
	}
	apple.draw();
}

void Snake::draw_in_motion()
{
	SetConsoleCursorPosition(hConsole, coord.back());
	std::cout << char(254);
	SetConsoleCursorPosition(hConsole, coord.front());
	std::cout << field->get_agg();
	Sleep(100 / speed);
}

void Snake::move()
{
	coord.pop_front();
	switch (snake_course)
	{
	case(RIGHT):
		if (coord.back().X == field->get_width()-1)
			coord.push_back({ FIELD_BEGIN_X, coord.back().Y });
		else
			coord.push_back({ coord.back().X + 1, coord.back().Y });
		break;
	case(LEFT):
		if (coord.back().X == FIELD_BEGIN_X)
			coord.push_back({ field->get_width()-1, coord.back().Y });
		else
			coord.push_back({ coord.back().X - 1, coord.back().Y });
		break;
	case(DOWN):
		if (coord.back().Y == field->get_height()-1)
			coord.push_back({ coord.back().X, FIELD_BEGIN_Y });
		else
			coord.push_back({ coord.back().X, coord.back().Y + 1 });
		break;
	case(UP):
		if (coord.back().Y == FIELD_BEGIN_Y)
			coord.push_back({ coord.back().X, field->get_height()-1 });
		else
			coord.push_back({ coord.back().X, coord.back().Y - 1 });
		break;
	}
	auto f = std::find(coord.begin(), coord.end(), coord.back());
	if ((f!= coord.end()-1) && (f!=coord.end()) && (f!=coord.end()-2))
		game_over(LOSE);
	if (coord.back() == apple.get_coord())
	{
		eating();
		apple.redraw();
	}
}

void Snake::eating()
{
	switch (snake_course)
	{
	case(RIGHT):
		if (coord.back().X == field->get_width() - 1)
			coord.push_back({ FIELD_BEGIN_X, coord.back().Y });
		else
			coord.push_back({ coord.back().X + 1, coord.back().Y });
		break;
	case(LEFT):
		if (coord.back().X == FIELD_BEGIN_X)
			coord.push_back({ field->get_width() - 1, coord.back().Y });
		else
			coord.push_back({ coord.back().X - 1, coord.back().Y });
		break;
	case(DOWN):
		if (coord.back().Y == field->get_height() - 1)
			coord.push_back({ coord.back().X, FIELD_BEGIN_Y });
		else
			coord.push_back({ coord.back().X, coord.back().Y + 1 });
		break;
	case(UP):
		if (coord.back().Y == FIELD_BEGIN_Y)
			coord.push_back({ coord.back().X, field->get_height() - 1 });
		else
			coord.push_back({ coord.back().X, coord.back().Y - 1 });
		break;
	}
	if (coord.size() == ((FIELD_BEGIN_X - 2) * (FIELD_BEGIN_Y - 2)))
		game_over(WIN);
	speed += 0.1;
}

void Snake::go_left()
{
	if(snake_course!=RIGHT)
		snake_course = LEFT;
}

void Snake::go_right()
{
	if (snake_course != LEFT)
		snake_course = RIGHT;
}

void Snake::go_up()
{
	if (snake_course != DOWN)
		snake_course = UP;
}

void Snake::go_down()
{
	if (snake_course != UP)
		snake_course = DOWN;
}