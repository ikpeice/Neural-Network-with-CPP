#pragma once

#include <iostream>
#include<conio.h>
#include<dos.h>
#include <windows.h>
#include <time.h>
#include <vector>
#include <cstdint>

#include "font.h"



using namespace std;

class DotDisplay
{

public:
	DotDisplay(uint8_t width, uint8_t hieght);
	void begin();
	void print(const char* s);

private:
	void gotoxy(int x, int y);
	void setcursor(bool visible, DWORD size);
	void drawBorder();
	void show();
	void scroll(char a, char b, char c, char d, char e);
	void shiftIn(char c);
	vector<char> binaryToChar(unsigned char b);

private:
	const uint8_t SCREEN_HEIGHT;
	const uint8_t SCREEN_WIDTH;
	vector<vector<char>> buffer;
};

