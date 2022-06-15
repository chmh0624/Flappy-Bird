# Flappy-Bird

## Compile the code into .exe
- g++ -fexec-charset=BIG5 -static main.cpp -o main
- Using g++
- Big5 format 
- Static Compile

## How to play?
- Press "space" to make bird fly
- Unable to touch the pillars, floor, ceiling
- One point for going through the hole of pillar

## Game Part
1. Rules Announcement: Click space the whole sentence printed
2. Characters:
  - Bird: appears as '@' 
  - Pillar: appears as '####   ###' (in vertical)
3. Score: 
  - Show below the screen
  - Update instantly after score changes
  - When end game, show at the center of the screen

## Code
1. main.cpp
2. game.hpp (class Game) : control the game
3. character.hpp (class Bird, class Pillar) : define the bird and the pillars
4. console.hpp (class console) : control the cursor
