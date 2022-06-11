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

/* members for score controller */
	int score;
	short startScorePositionX, curScorePositionX;
	int printedNumber;
/* end members for score controller */	
	
public:
/* constructor */
	Game()
	{
		bird = Bird();
		score = 0;
		pillarsIdx = -1;
		startPillarsIdx = 0;
		endPillarsIdx = 0;
		len = 0;
		influencedPillar = false;
		isEndGame = false;
		playGame();
	}
/* end constructor */

/* member controllers */
	int getScore() { return score; }
	void setScore(int _score) { score = _score; }
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
		int i=1;
		while (bird.getState()) 
		{
			if (!influencedPillar) 
			{
				influencedPillar = false;
				//setPillar();
			}
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

/* score function */

	// activate show score process on the screen
    void showScore(int _score)
    {
    	printedNumber = 0;
    	curScorePositionX = console.getWidth() / 2 - 9;
    	std::deque <int> tmp;
    	while (_score / 10 != 0)
    	{
    		tmp.push_front(_score % 10);
    		_score /= 10;
    	}
    	tmp.push_front(_score % 10);
    	for (int i=0; i<3-tmp.size(); i++)
    		printNumber(0);
    	for (int i=0; i<tmp.size(); i++)
    		printNumber(tmp[i]);
    }

    // print characters with number-like words
	void printNumber(int n)
	{
		for (int i=0; i<5; i++)
		{
			console.setCursorPosition(curScorePositionX, 30 + i);
			std::cout << numbers[5 * n + i] << " ";
		}
		curScorePositionX += 6;
	}

	// activate show FINAL score process on the screen
    void showFinalScore(int _score)
    {
    	printedNumber = 0;
    	curScorePositionX = console.getWidth() / 2 - 9;
    	std::deque <int> tmp;
    	while (_score / 10 != 0)
    	{
    		tmp.push_front(_score % 10);
    		_score /= 10;
    	}
    	tmp.push_front(_score % 10);
    	for (int i=0; i<3-tmp.size(); i++)
    		printNumber(0);
    	for (int i=0; i<tmp.size(); i++)
    		printNumber(tmp[i]);
    }

    // print characters FINAL with number-like words
	void printFinalNumber(int n)
	{
		for (int i=0; i<5; i++)
		{
			console.setCursorPosition(curScorePositionX, 30 + i);
			for (char c: numbers[5 * n + i])
				std::cout << c;
			std::cout << std::endl;
		}
		curScorePositionX += 6;
	}
/* end score function */

};