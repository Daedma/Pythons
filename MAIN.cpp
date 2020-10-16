#include "SNAKE.h"

int main()
{
	Field field(50, 20, 176);
	COORD beg_crd = { 25, 10 };
	Snake sn(beg_crd, field);
	field.draw();
	sn.draw();
	while (true)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case(KEY_ARROW_DOWN):
				sn.go_down();
				break;
			case('s'):
				sn.go_down();
				break;
			case(KEY_ARROW_UP):
				sn.go_up();
				break;
			case('w'):
				sn.go_up();
				break;
			case(KEY_ARROW_RIGHT):
				sn.go_right();
				break;
			case('d'):
				sn.go_right();
				break;
			case(KEY_ARROW_LEFT):
				sn.go_left();
				break;
			case('a'):
				sn.go_left();
				break;
			default:
				break;
			}	
		}
		sn.move();
		sn.draw_in_motion();
	}
}