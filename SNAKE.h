#pragma once
#define FIELD_BEGIN_X 1
#define FIELD_BEGIN_Y 1
#define LOSE 0
#define WIN 1
#define APPLE 79
#define KEY_ARROW_UP 72
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#include <deque>
#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <conio.h>

class Snake;

struct Field
{
	Field(SHORT, SHORT, const char);
	void draw();
	inline const SHORT get_height() const { return height; }
	inline const SHORT get_width() const { return width; }
	inline const char get_agg() const { return aggregate; }
private:
	const SHORT height, width;
	char aggregate;
};

struct Apple
{
	Apple(SHORT, SHORT, Snake*);
	void draw();
	void redraw();
	const COORD get_coord() { return coord; }
private:
	static std::default_random_engine e;
	std::uniform_int_distribution<SHORT> dx;
	std::uniform_int_distribution<SHORT> dy;
	Snake* snake;
	COORD coord;
};

enum Course { RIGHT, UP, LEFT, DOWN };

class Snake
{
	friend struct Apple;

	Apple apple;
	const Field* field;
	std::deque<COORD> coord;
	double speed;
	unsigned snake_course;
public:
	Snake(const COORD&, const Field&, double = 1);
	void draw();
	void draw_in_motion();
	void move();
	void eating();
	void go_left();
	void go_right();
	void go_up();
	void go_down();
};

bool operator==(const COORD&, const COORD&);
bool operator!=(const COORD&, const COORD&);
void game_over(const bool);

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);