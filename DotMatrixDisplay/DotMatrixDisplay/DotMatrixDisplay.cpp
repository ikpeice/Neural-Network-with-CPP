// DotMatrixDisplay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<conio.h>
#include<dos.h>
#include <windows.h>
#include <time.h>

#include "dotDisplay.h"


DotDisplay display(80, 8);


int main()
{
	display.begin();
	display.print("SPACE IN AFRICA -- WEATHER STATION        ");

	while (1);
}

