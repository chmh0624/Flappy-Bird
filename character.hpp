#include "console.hpp"

class Bird
{
private:
	short x, y;
	char body;
	bool state;
	int score;
public:
/* constructor */
	Bird ()
	{
		x = console.getWidth() / 3;
		y = console.getWidth() / 2;
		body = '@';
		score = 0;
		showBird();
		state = true;
	}
	Bird (const Bird &bird)
	{
		x = bird.x;
		y = bird.y;
		body = '@';
		score = bird.score;
		state = bird.state;
	}
/* end constructor */

/* members controller */
	short getX() { return x; }
	void setX(short _x) { x = _x; }
	short getY() { return y; }
	short setY(short _y) { y = _y; }
	int getScore() { return score; }
	void setScore(int _score) { score = _score; }
	void setState(bool _state) { state = _state; }
	bool getState() { return state; }
/* end members controller */

/* functions */
	void showBird()
	{
		console.setCursorPosition(x, y);
		std::cout << body;
	}
	void clearBird()
	{
		console.setCursorPosition(x, y);
		std::cout << " ";	
	}
/* end functions */
};

class Pillar
{
private:
	short x, y1, y2;
	bool state;
public:

/* constructor */
	Pillar()
	{
		x = randomPosX();
		y1 = randomPosY() - 1;
		y2 = y1 + 2;
		showPillar(x);
		state = true;
	}
/* end constructor */

/* position function */
	short getX() { return x; }
	// short getY() { return y; }

	short randomPosX()
	{
		srand((unsigned int)time(NULL));
		short toBeReturn = 0;
		while (toBeReturn <= console.getWidth() / 5 * 3 && toBeReturn <= console.getLastPillarX())
			toBeReturn = console.getWidth() / 2 + rand() % (console.getWidth() / 2 - 1);
		return toBeReturn;
	}

	short randomPosY()
	{
		srand((unsigned int)time(NULL));
		short toBeReturn = 0;
		while (toBeReturn < (console.getHeight() / 4) || toBeReturn > (console.getHeight() / 4 * 3))
			toBeReturn = 2  + rand() % (console.getHeight());
		return toBeReturn;
	} 
/* end position function */

/* pillar movement */
	void showPillar(short _x)
	{
		for (int i=2; i<console.getHeight()-1; i++)
		{
			console.setCursorPosition(_x, i);
			if (i < y1 || i > y2)
				std::cout << "#";
		}
	}

	void clearPillar(short _x)
	{
		for (int i=2; i<console.getHeight()-1; i++)
		{
			console.setCursorPosition(_x, i);
			if (i < y1 || i > y2)
				std::cout << " ";
		}
	}

	bool movingForward(Bird &bird)
	{

		/* declare needed variables */ 
			bool bumpedBird = false;
		/* end declare needed variables */ 

		/* bumped into bird */
			if (x - 1 == bird.getX() && (bird.getY() < y1 || bird.getY() > y2))
			{
				state = false;
				bird.setState(false);
				bumpedBird = true;
				return true;
			}
		/* end bumped into bird */

		/* safe flight */
			if (x - 1 == bird.getX() &&  (bird.getY() >= y1 || bird.getY() <= y2))
			{
				bird.setScore(bird.getScore() + 1);
				console.showScore(bird.getScore());
			}
		/* end safe flight */

		/* pillar movement */
			if (x - 1 > 1)
			{
				showPillar(x-1);
				clearPillar(x);
				Sleep(200);
				x --;
				if (x > bird.getX())
					console.setLastPillarX(x);
			}
			else
			{
				state = false;
				clearPillar(x);
			}
		/* end pillar movement */
		
		/* return does pillar bumped into bird */
			return bumpedBird;
		/* end return */
	}
/* end pillar movement */

};