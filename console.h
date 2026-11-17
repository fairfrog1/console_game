#ifndef CONSOLE_H
#define CONSOLE_H

#ifdef __WIN32__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>

// foreground color macros
#define FG_BLACK   0
#define FG_WHITE   15
#define FG_DBLUE   1
#define FG_DGREEN  2
#define FG_LBLUE   3
#define FG_RED     4
#define FG_MAG     5
#define FG_YELLOW  6
#define FG_LGREY   7
#define FG_GREY    8
#define FG_BLUE    9
#define FG_GREEN   10
#define FG_CYAN    11
#define FG_PINK    12
#define FG_LMAG    13
#define FG_LYELLOW 14

// backround color macros
#define BG_BLACK   0
#define BG_WHITE   240
#define BG_DBLUE   16
#define BG_DGREEN  32
#define BG_LBLUE   48
#define BG_RED     64
#define BG_MAG     80
#define BG_YELLOW  96
#define BG_LGREY   112
#define BG_GREY    128
#define BG_BLUE    144
#define BG_GREEN   160
#define BG_CYAN    176
#define BG_PINK    192
#define BG_LMAG    208
#define BG_LYELLOW 224



int get_buffer_width() {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info = {0};
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);    
    if (consoleHandle == INVALID_HANDLE_VALUE || consoleHandle == NULL) {
        printf("%lu", GetLastError());
        return 1;
    }
    if(GetConsoleScreenBufferInfo(consoleHandle, &buffer_info)) {
	return buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
    }
}

int get_buffer_height() {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info = {0};
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (consoleHandle == INVALID_HANDLE_VALUE || consoleHandle == NULL) {
        printf("%lu", GetLastError());
        return 1;
    }
    if(GetConsoleScreenBufferInfo(consoleHandle, &buffer_info)) {
	return buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;
    }
}

void hide_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void set_cursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_color(int color) {  // you put in arguments like that: set_color( FG_COLOR | BG_COLOR );
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#endif


#endif
