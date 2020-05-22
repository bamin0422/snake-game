#include "CharPosition.h"
#include "Snake.h"

Snake::Snake(){
    direction = 'l';
    initBody();
}

Snake::~Snake(){
}


void Snake::initBody(){
    for (int32 i = 0; i < 5; i++) {
		entire.push_back(CharPosition(30+i, 10));
	}
	for (int32 i = 0; i < entire.size(); i++){
		move(entire[i].y, entire[i].x);
		addch(partchar);
	}
}

void Snake::Update(){
	int32 KeyPressed = getch();
	switch(KeyPressed)
	{
		case KEY_LEFT:
			if (direction != 'r') 
			{ direction = 'l'; }  
			break;
		case KEY_RIGHT:
			if (direction != 'l')
			{ direction = 'r'; }
			break;
		case KEY_UP:
			if (direction != 'd')
			{ direction = 'u'; }
			break;
		case KEY_DOWN:
			if (direction != 'u')
			{ direction = 'd'; }
			break;
		case KEY_BACKSPACE:
			direction = 'q'; // key to quit the game
			break;
	}

	// the snake moves and we add an extra character at the beginning of the vector
	// add a head and initialise new coordinates for CharPosition according to the direction input
	if (direction == 'l')
	{ entire.insert(entire.begin(), CharPosition(entire[0].x-1, entire[0].y)); } 
	else if (direction == 'r')
	{ entire.insert(entire.begin(), CharPosition(entire[0].x+1, entire[0].y)); }
	else if (direction == 'u')
	{ entire.insert(entire.begin(), CharPosition(entire[0].x, entire[0].y-1)); }
	else if (direction == 'd')
	{ entire.insert(entire.begin(), CharPosition(entire[0].x, entire[0].y+1)); }
}


void Snake::Render(){
	// the snake doesn't eat fruit, remains same size
	if (true) // 작아지는 아이템을 안 먹었을 경우
	{
		move(entire[entire.size()-1].y, entire[entire.size()-1].x); // moves at the end of the tail
		printw(" "); // add empty ch to remove last character
		refresh();
		entire.pop_back(); // removes the last element in the vector, reducing the container size by one
	}
	// move to the new CharPosition coordinates
	move(entire[0].y, entire[0].x);
	addch(partchar); // add a new head
	refresh();
}