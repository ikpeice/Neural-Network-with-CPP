#include "dotDisplay.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;



DotDisplay::DotDisplay(uint8_t width, uint8_t hieght):
	SCREEN_WIDTH(width+1),SCREEN_HEIGHT(hieght+1)
{
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		vector<char> col;
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			col.push_back('-');
		}
		buffer.push_back(col);
	}
}

void DotDisplay::begin()
{
	drawBorder();
	Sleep(1000);
	show();
	//(void)binaryToChar(20);
}

void DotDisplay::gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void DotDisplay::setcursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

void DotDisplay::drawBorder()
{
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		gotoxy(0, i); cout << "+";
		gotoxy(SCREEN_WIDTH, i); cout << "+";
	}
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		gotoxy(i, 0); cout << "+";
		gotoxy(i, SCREEN_HEIGHT); cout << "+";
	}
}

void DotDisplay::show()
{
	for (int i = 1; i < SCREEN_WIDTH; i++)
	{
		for (int j = 1; j < SCREEN_HEIGHT; j++)
		{
			gotoxy(i,j); cout << buffer[i][j-1];
			//Sleep(1);
		}

	}
}

void DotDisplay::print(const char* s)
{
	if (s != NULL)
	{
		while (*s != '\0')
		{
			//cout << "printing\n" << *s << endl;
			scroll(font[*s - ' '][0], font[*s - ' '][1], font[*s - ' '][2], font[*s - ' '][3], font[*s - ' '][4]);
			s++;
		}
	}
}

void DotDisplay::scroll(char a, char b, char c, char d, char e)
{
	for (int i = 0; i < 5; i++)
	{
		char s = a;
		a = b; b = c; c = d; d = e;
		shiftIn(s);
		show();
		
		Sleep(50);
		/*
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{

		}
		*/

	}
	shiftIn(0x00);
}

void DotDisplay::shiftIn(char c)
{
	for (unsigned char i = 0; i < SCREEN_WIDTH-1; i++)
	{
		buffer[i] = buffer[i + 1];
	}
	//cout <<"Frome shift:"<< binaryToChar(c)[2];
	buffer[SCREEN_WIDTH - 1] = binaryToChar(c);
}

vector<char> DotDisplay::binaryToChar(unsigned char b)
{
	byte x = 0x01;
	vector<char> y;
	for (int i = 0; i < 8; i++)
	{
		y.push_back((b & x)>0? '0' : '-');
		//cout << y.at(i) << endl;
		x = x << 1;
	}
	return y;
}

