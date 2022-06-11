#include "game.hpp"

/* game playing */

/*  */

/* game ending detection */
void endGame(Game &game);
/* end game ending detection */

int main()
{
	system("mode con cols=32 lines=40"); 
	system("color 7C"); 
	system("title FLAPPY BIRD");
	srand(time(NULL));
	console.showBorder();
	getch();
	Game game;
	Sleep(200);
	game.deadBird();
	Sleep(1000);
	endGame(game);
	getch();
}

/* game ending detection */
void endGame(Game &game)
{
	game.setScore(game.getBird().getScore());
	console.clearScreen(" ", " ");
	game.showScore(game.getScore());
}
/* end game ending detection */