#include "character.hpp"

class Game
{
private:
	Bird bird;
	bool isEndGame;
/* members for array pillars */
	Pillar pillars[10];
	int pillarsIdx = 0, startPillarsIdx = 0, endPillarsIdx = 0;
	int len = 0;
	bool influencedPillar;
/* end members for array pillars */	
	
public:
/* constructor */
	Game()
	{
		bird = Bird();
		bird.setScore(0);
		console.showScore(bird.getScore());
		pillarsIdx = -1;
		startPillarsIdx = 0;
		endPillarsIdx = 0;
		len = 0;
		// if any pillar approaching to bird
		influencedPillar = false;
		isEndGame = false;
		playGame();
	}
/* end constructor */

/* member controllers */
	Bird getBird() { return bird; }
/* end member controllers */

/* render pillars */
	void setPillar()
	{
		pillarsIdx ++;
		len ++;
		if (pillarsIdx >= 10)
		{
			pillarsIdx %= 10;
			endPillarsIdx = pillarsIdx;
		}
		pillars[pillarsIdx] = Pillar();
	}
/* end render pillars */

/* keyboard detection */
	void playGame()
	{
		int x = 1;
		setPillar();
		while (bird.getState()) 
		{
			if (!influencedPillar) 
			{
				setPillar();
				console.setCursorPosition(4, 4);
				std::cout << x ++ ;
			}
			influencedPillar = false;
		/* pillar movement */
			// data xx data
			if (startPillarsIdx > endPillarsIdx)
			{
				for (int i=startPillarsIdx; i<10 && bird.getState(); i++)
				{
					bird.setState(!pillars[i].movingForward(bird));
					if (pillars[i].getX() > bird.getX())
						influencedPillar = true;
				}
				for (int i=0; i<=endPillarsIdx && bird.getState(); i++)
				{
					bird.setState(!pillars[i].movingForward(bird));
					if (pillars[i].getX() > bird.getX())
						influencedPillar = true;
				}
				Sleep(100);
				if (!bird.getState())
					break;
			}
			// xx data
			else
			{
				for (int i=startPillarsIdx; i<=endPillarsIdx && bird.getState(); i++)
				{
					bird.setState(!pillars[i].movingForward(bird));
					if (pillars[i].getX() > bird.getX())
						influencedPillar = true;
				}
				Sleep(100);
				if (!bird.getState())
					break;
				console.setCursorPosition(4, 6);
				std::cout << x << " " << influencedPillar << " " << pillarsIdx;
			}
		/* end pillar movement */

		/* handle bird movement */

			/* keyboard detection */
				clock_t timeRecord = clock();
				while (clock() - timeRecord < 200)
				{
					if (kbhit() && getch() == ' ' && (bird.getY() - 2 > 0))
					{
						bird.clearBird();
						bird.setY(bird.getY() - 1);
						bird.showBird();
					}
					if (bird.getY() <= 2)
					{
						bird.setState(false);
						break;
					}
				}
			/* end keyboard detection */

			/* bird drop */ 
				bird.clearBird();
				bird.setY(bird.getY() + 1);
				bird.showBird();
				if (bird.getY() >= console.getHeight() - 3)
				{
					bird.setState(false);
					break;
				}
			/* end bird drop */
			
			/* bump ceiling, floor */
				if (bird.getY() >= console.getHeight() - 2 || bird.getY() <= 2)
				{
					bird.setState(false);
					break;
				}
			/* end bumped ceiling, floor */

		/* end handle bird movement */
		}
	}
/* end keyboard detection */

/* game ending detection */
	void deadBird()
	{
		for (short i = bird.getY(); i < console.getHeight() - 2; i++)
		{
			bird.clearBird();
			bird.setY(bird.getY() + 1);
			bird.showBird();
			Sleep(100);
		}
	}
/* end game ending detection */



};