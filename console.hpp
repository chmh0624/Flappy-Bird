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
public:

/* members for score controller */
	short startScorePositionX, curScorePositionX;
	int printedNumber;
/* end members for score controller */

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

	// clear screen with given string
	void clearScreen(std::string outer, std::string inner)
	{
		if ((width - 1) % 2 == 1)
			width ++;
		for (int i=0; i<width; i++)
		{
			for (int j=0; j<height; j++)
			{
				if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
				{
					if (i%2 == 0)
					{
						setCursorPosition(i, j);
						std::cout << outer ;
					}
				}
				else
				{
					setCursorPosition(i, j);
					std::cout << inner;
				}
			}
		}
	}

	// print game information on the screen
	void showInfo()
	{
		clearScreen("=", " ");
		int start = 2;
		std::ifstream input("rule.txt");  
	    std::vector <std::string> sv;  
	    std::string s;
	    while( getline(input,s) )
	    	sv.push_back(s);
	    int starth = height / 2 - sv.size() / 2;
	    int startw;
	    for (int i=0; i<sv.size(); i++)
	    {
	    	startw = width / 2 - sv[i].length() / 2;
	    	for (char c: sv[i])
	    	{
	    		setCursorPosition(startw++, starth);
	    		std::cout << c;
	    		Sleep(50);
	    	}
	    	starth ++;
	    	// setCursorPosition(4, 4);
	    	// Sleep(1000);
	    	// std::cout << i; 
		}	
    }	

    // print border on the screen
    void showBorder()
    {
    	if ((width - 1) % 2 == 1)
			width ++;
		for (int i=0; i<width; i++)
		{
			for (int j=0; j<height; j++)
			{
				if (j == 0 || j == height - 1)
				{
					if (i%2 == 0)
					{
						setCursorPosition(i, j);
						std::cout << "■" ;
					}
				}
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
			setCursorPosition(curScorePositionX, 31 + i);
			std::cout << numbers[5 * n + i] << " ";
		}
		curScorePositionX += 6;
	}

	// activate show FINAL score process on the screen
    void showFinalScore(int _score)
    {
    	printedNumber = 0;
    	curScorePositionX = getWidth() / 2 - 9;
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
			setCursorPosition(curScorePositionX, 30 + i);
			for (char c: numbers[5 * n + i])
				std::cout << c;
			std::cout << std::endl;
		}
		curScorePositionX += 6;
	}
/* end score function */

};

Console gamePreSetting(int w, int h)
{
	Console console(w, h);
	console.clearScreen("=", " ");
	console.showInfo();
	getch();
	console.clearScreen("#", " ");
	return console;
}

Console console(30, 30);
