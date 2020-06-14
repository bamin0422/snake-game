#include "CharPosition.h"
#include "myFunction.h"
#include "GameOverScene.h"
#include "IScene.h"
#include "Snake.h"
#include "MapManager.h"

extern MapManager * mapManager;

Snake::Snake()
{
	direction = 'l';
	partchar = '*';
	getmaxyx(stdscr, maxheight, maxwidth);
	initBody();
}

Snake::~Snake()
{
}

void Snake::PushData(){
    for (int32 i = 0; i < entire.size(); i++){
        if(i==0){
            mapManager->PatchData(entire[i].y, entire[i].x, '3');
        }
        else{
            mapManager->PatchData(entire[i].y, entire[i].x, '4');
        }
	}
}

void Snake::initBody()
{
	for (int32 i = 0; i < 5; i++)
	{
		entire.push_back(CharPosition(30 + i, 10));
	}
}


void Snake::SetDirection(char ch){
	direction=ch;
}

void Snake::Update(float eTime){
	//  ths snake's size below 3. Chanege GameScene to GameOverScene
	int32 KeyPressed;
	if (entire.size() < 3 || (entire[0].x <= 0 || entire[0].x >= maxwidth / 4 * 3 - 1) || (entire[0].y >= maxheight - 1 || entire[0].y <= 0))
	{
		ChangeScene(new GameOverScene());
	}
	if (KeyPressed >= 3)
		KeyPressed = getch();
	switch (KeyPressed)
	{
	case KEY_LEFT:
		if (direction != 'r')
		{
			direction = 'l';
		}
		else
			ChangeScene(new GameOverScene());
		break;
	case KEY_RIGHT:
		if (direction != 'l')
		{
			direction = 'r';
		}
		else
			ChangeScene(new GameOverScene());
		break;
	case KEY_UP:
		if (direction != 'd')
		{
			direction = 'u';
		}
		else
			ChangeScene(new GameOverScene());
		break;
	case KEY_DOWN:
		if (direction != 'u')
		{
			direction = 'd';
		}
		else
			ChangeScene(new GameOverScene());
		break;
	case KEY_BACKSPACE:
		direction = 'q'; // key to quit the game
		break;
	}

	// the snake moves and we add an extra character at the beginning of the vector
	// add a head and initialise new coordinates for CharPosition according to the direction input
	if (direction == 'l')
	{
		entire.insert(entire.begin(), CharPosition(entire[0].x - 1, entire[0].y));
	}
	else if (direction == 'r')
	{
		entire.insert(entire.begin(), CharPosition(entire[0].x + 1, entire[0].y));
	}
	else if (direction == 'u')
	{
		entire.insert(entire.begin(), CharPosition(entire[0].x, entire[0].y - 1));
	}
	else if (direction == 'd')
	{
		entire.insert(entire.begin(), CharPosition(entire[0].x, entire[0].y + 1));
	}
    
    //isGrow는 false일 때 entire 벡터에 갱신된 head가 추가되면 맨 뒤에 있는 entire 원소 제거
    if(isGrow==false){
        CutTail();
    }

	
    PushData();
}

void Snake::CutTail(){
    mapManager->PatchData(entire[entire.size() - 1].y, entire[entire.size() - 1].x,'0');
    entire.pop_back();
}

void Snake::Grow(){
    isGrow=true;
}

void Snake::Shrink(){
    isShrink=true;
    CutTail();
}


void Snake::Render()
{
	// // the snake doesn't eat fruit, remains same size
	// if (!(eatFruit || eatPoison)) // 작아지는 아이템을 안 먹었을 경우
	// {
        
	// }
	// else if (eatFruit)
	// {
	// 	refresh();
	// }
	// else if (eatPoison){
	// 	entire.pop_back();
	// 	mapManager->PatchData(entire[entire.size() - 1].y, entire[entire.size() - 1].x,'0');
	// 	printw(" ");
	// 	entire.pop_back(); // add empty ch to remove last character
	// 	refresh();
	// }

	// // move to the new CharPosition coordinates
	// move(entire[0].y, entire[0].x);
	// addch(partchar); // add a new head

	// refresh();
}

// void Snake::EatItem(bool fruit, bool poison)
// {
// 	eatFruit = fruit;
// 	eatPoison = poison;
// }