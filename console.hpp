#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

std::string numbers[50] = 
{
	" ooo ",
	"o   o",
	"o   o",
	"o   o",
	" ooo ",

	" oo  ",
	"ooo  ",
	"  o  ",
	"  o  ",
	"ooooo",

	" ooo ",
	"o   o",
	"   o ",
	"  o  ",
	"ooooo",

	" ooo ",
	"o   o",
	"  ooo",
	"o   o",
	" ooo ",

	"   o ",
	" o o ",
	"o  o ",
	"ooooo",
	"   o ",

	"ooooo",
	"o    ",
	"ooooo",
	"    o",
	"ooooo",

	"ooooo",
	"o    ",
	"ooooo",
	"o   o",
	"ooooo",

	"ooooo",
	"    o",
	"   o ",
	"  o  ",
	"  o  ",

	" ooo ",
	"o   o",
	" ooo ",
	"o   o",
	" ooo ",

	" ooo ",
	"o   o",
	" ooo ",
	"    o",
	" ooo "
};

std::string countdown[147] = 
{
	" ooooo ",
	"o     o",
	"     o ",
	"   oo  ",
	"     o ",
	"o     o",
	" ooooo ",

	" ooooo ",
	"o     o",
	"     o ",
	"    o  ",
	"   o   ",
	"  o    ",
	"ooooooo",

	"   o   ",
	"  oo   ",
	" ooo   ",
	"   o   ",
	"   o   ",
	"   o   ",
	"ooooooo"
};

/*
	----------> x (width)
	|
	|
	|
	v
	y (height)
*/

class Console
{
private:
	int height, width;
	short lastPillarX;
/* members for score controller */
	short startScorePositionX, curScorePositionX;
	int printedNumber;
/* end members for score controller */
public:

/* constructor */
	Console (){}
	Console (int w, int h) 
	{
		height = h; 
		width = w;
		lastPillarX = width / 2 + 1;
	} 
	Console (const Console &console)
	{
		height = console.height;
		width = console.width;
		lastPillarX = width / 2 + 1;
	}
/* end constructor */

/* members controller */
	int getHeight() { return height; }
	int getWidth() { return width; }
	short getLastPillarX() { return lastPillarX; }
	void setHeight(int h) { height = h; }
	void setWidth(int w) { width = w; }
	void setLastPillarX(short x) { lastPillarX = x; }
/* end members controller */

/* function */

	// set cursor to a specific position
	void setCursorPosition(short x, short y)
	{
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos = {x, y};
		SetConsoleCursorPosition(output, pos);
	}

	void hideCursor()
	{
		CONSOLE_CURSOR_INFO Cursor;
		Cursor.bVisible = false;
		Cursor.dwSize = sizeof(Cursor);
		HANDLE Hand = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorInfo(Hand, &Cursor);
	}

	// clear screen with given string
	void clearScreen()
	{
		if ((width - 1) % 2 == 1)
			width ++;
		for (int i=0; i<width; i++)
		{
			for (int j=0; j<height; j++)
			{
				if (!(j == 0 || j == height - 1))
				{
					setCursorPosition(i, j);
					std::cout << " ";
				}
			}
		}
	}

	// print game information on the screen
	void showInfo()
	{
		showBorder();
		clickSpaceToStart("Rules: (click space to confirm)");
		clearScreen();
		clickSpaceToStart("Click \"Space\" to Fly");
		clearScreen();
		clickSpaceToStart("No touching CEILING!");
		clearScreen();
		clickSpaceToStart("No touching FLOOR!");
		clearScreen();
		clickSpaceToStart("No touching PILLARS!");
		clearScreen();
		clickSpaceToStart("Ready? Click \"Space\" to Start");
		clearScreen();
    }	

    void clickSpaceToStart(std::string str)
    {
    	int starth = height / 2;
	    int startw = width / 2 - str.length() / 2;
    	for (char c: str)
    	{
    		setCursorPosition(startw++, starth);
    		std::cout << c;
    		Sleep(50);
    	}
		while (!kbhit())
			if (getch() == ' ')
			{
				setCursorPosition(width / 2 - str.length() / 2, starth);
				for (int i=0; i<str.length(); i++)
					std::cout << " ";
				break;
			}
    }
	
    // print border on the screen
    void showBorder()
    {
    	if ((width - 1) % 2 == 1)
			width ++;
		setCursorPosition(0, 0);
		std::cout << "▁ ▃ ▄ ▅ ▆ Flappy Bird ▆ ▅ ▄ ▃ ▁";
		for (int i=0; i<width; i++)
		{
			if (i%2 == 0)
			{
				setCursorPosition(i, height - 1);
				std::cout << "■" ;
			}
		}
    }
/* end function */

/* score function */

	// activate show score process on the screen
    void showScore(int _score)
    {
    	printedNumber = 0;
    	curScorePositionX = getWidth() / 2 - 9;
    	printNumber(_score / 100);
    	printNumber(_score / 10 % 10);
    	printNumber(_score % 10);
    }

    // print characters with number-like words
	void printNumber(int n)
	{
		for (int i=0; i<5; i++)
		{
			setCursorPosition(curScorePositionX, 31 + i);
			std::cout << numbers[5 * n + i] << " ";
		}
		curScorePositionX += 6;
	}

	// activate show FINAL score process on the screen
    void showFinalScore(int _score)
    {
    	curScorePositionX = getWidth() / 2 - 9;
    	for (int i=0; i<3; i++)
    	{
    		for (int j=0; j<5; j++)
			{
				setCursorPosition(curScorePositionX, 31 + j);
				std::cout << "     " << " ";
			}
			curScorePositionX += 6;
    	}
    	for (int i=0; i<=_score; i++)
    	{
    		printedNumber = 0;
	    	curScorePositionX = getWidth() / 2 - 9;
	    	printFinalNumber(i / 100);
	    	printFinalNumber(i / 10 % 10);
	    	printFinalNumber(i % 10);
	    	Sleep(100);
    	}
    }

    // print characters FINAL with number-like words
	void printFinalNumber(int n)
	{
		short y = getHeight() / 2;
		for (int i=0; i<5; i++)
		{
			setCursorPosition(curScorePositionX, y + i);
			for (char c: numbers[5 * n + i])
				std::cout << c;
			std::cout << std::endl;
		}
		curScorePositionX += 6;
	}
/* end score function */

};

Console console(30, 30);
