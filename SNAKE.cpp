#include "SNAKE.h"
#include  <stdexcept>

Snake::Snake(const COORD& beg_coord, Field& _field, double beg_speed) :
	speed(beg_speed), field(&_field), snake_course(RIGHT), apple(_field.get_width(), _field.get_height(), this)
{
	build(beg_coord, _field);
}

void Snake::build(const COORD& beg_coord, const Field& _field)
{
	if ((beg_coord.X <= (_field.get_width() - (INITIAL_SNAKE_SIZE + 1))) && (beg_coord.X >= FIELD_BEGIN_X) && (beg_coord.Y <= _field.get_height()) && (beg_coord.Y >= FIELD_BEGIN_Y))
	{
		COORD crd = beg_coord;
		for (unsigned i = 0; i != INITIAL_SNAKE_SIZE + 1; ++i, ++crd.X)
		{
			coord.push_back(crd);
		}
	}
	else if ((beg_coord.X == (_field.get_width() - 1)) && (beg_coord.Y <= (_field.get_height() - (INITIAL_SNAKE_SIZE + 1))))
	{
		COORD crd = beg_coord;
		for (unsigned i = 0; i != INITIAL_SNAKE_SIZE + 1; ++i, ++crd.Y)
		{
			coord.push_back(crd);
		}
	}
	else
		throw std::invalid_argument("Invalid coordinates");
}

void Snake::draw() const
{
	SetConsoleTextAttribute(hConsole, SNAKE_COLOR);
	auto it = coord.begin()+1;
	while (it != coord.end())
	{
		SetConsoleCursorPosition(hConsole, *it);
		std::cout << char(SNAKE);
		++it;
	}
	apple.draw();
}

void Snake::draw_in_motion()
{
	SetConsoleCursorPosition(hConsole, coord.back());
	SetConsoleTextAttribute(hConsole, SNAKE_COLOR);
	std::cout << char(SNAKE);
	SetConsoleCursorPosition(hConsole, coord.front());
	SetConsoleTextAttribute(hConsole, FIELD_COLOR);
	std::cout << field->get_agg();
	Sleep(INITIAL_SPEED / speed);
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