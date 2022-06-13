#include "game.hpp"

/* game detection */
void gamePreSetting();
void endGame(Game &game);
/* end game detection */

int main()
{
	system("mode con cols=32 lines=40"); 
	system("color 0B"); 
	system("title FLAPPY BIRD");
	srand(time(NULL));
	console.hideCursor();
	gamePreSetting();
	console.showBorder();
	Game game;
	Sleep(200);
	game.deadBird();
	Sleep(1000);
	endGame(game);
	getch();
}

/* game detection */
void gamePreSetting()
{
	console.showBorder();
	console.showInfo();
	int startw, starth;
	for (int i = 0; i<3; i++)
	{
		starth = console.getHeight() / 2 - 3;
		for (int j=0; j<7; j++)
		{
			startw = console.getWidth() / 2 - 3;
			console.setCursorPosition(startw, starth++);
			std::cout << countdown[7 * i + j];
		}
		Sleep(1000);
	}
	console.clearScreen();
}

void endGame(Game &game)
{
	game.getBird().setScore(game.getBird().getScore());
	console.clearScreen();
	console.showFinalScore(game.getBird().getScore());
}
/* end game detection */
