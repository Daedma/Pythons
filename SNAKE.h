#pragma once
//начальные значения
#define FIELD_BEGIN_X 1
#define FIELD_BEGIN_Y 1
#define LOSE 0
#define WIN 1
#define INITIAL_SPEED 100
//коды клавиш
#define KEY_ARROW_UP 72
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
//чары
#define APPLE 79
#define SNAKE 219
#define FIELD_FRAME 178
#define INITIAL_SNAKE_SIZE 6
//цвета
#define FULL_PALETTE 0b0111'1111
#define CLEAR_PALETTE 0b0000'1111
#define FIELD_COLOR 0b0110'1110
#define FRAME_COLOR 0b1000'0001
#define SNAKE_COLOR (0b0000'1010 | (FIELD_COLOR & 0b1111'0000))
#define APPLE_COLOR (0b0000'1100 | (FIELD_COLOR & 0b1111'0000))

#include <utility>
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
	const SHORT get_height() const { return height; }
	const SHORT get_width() const { return width; }
	const char get_agg() const { return aggregate; }
	void clear(size_t speed);
private:
	const SHORT height, width;
	const char aggregate;
	void edit_console();
	void rainbow(WORD&);
};

struct Apple
{
	Apple(SHORT, SHORT, Snake*);
	void draw() const;
	void redraw();
	const COORD& get_coord() const { return coord; }
	COORD& get_coord() { return coord; }
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
	void build(const COORD&, const Field&);

	void game_over(const bool);
	Apple apple;
	Field* field;
	std::deque<COORD> coord;
	double speed;
	unsigned snake_course;
public:
	Snake(const COORD&, Field&, double = 1);
	void draw() const;
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

const COORD get_mouse_clk();

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const HANDLE in_hConsole = GetStdHandle(STD_INPUT_HANDLE);