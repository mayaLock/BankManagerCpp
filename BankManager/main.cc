/*
    A simple bank management system	in C++ std-17.

    Author:		Dipayan Sarker
    Date:		December 09, 2020
    file:		main.cc

    Version:	2.0.0.1
*/

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include "bankmanagerapp.h"

static void clear() // os dependent 
{
    COORD topLeft{ 0, 0 };
    HANDLE console = ::GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;
    ::GetConsoleScreenBufferInfo(console, &screen);
    ::FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    ::FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    ::SetConsoleCursorPosition(console, topLeft);
}

int main(int argc, const char* argv[])
{
    BankManagerApp app(clear);
    app.run();
	return 0;
}