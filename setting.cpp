#define _WIN32_WINNT 0x0500
#include <iostream>
#include "setting.h"
#include <conio.h>
#include<winuser.h>

using namespace std;

setting::setting(){
  hwnd=GetConsoleWindow();
  hOut=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hOut, FOREGROUND_BLUE|FOREGROUND_INTENSITY|FOREGROUND_RED);
  setWindowInfo();
  setCursorInfo();
}
void setting::setWindowInfo(){
  COORD coordSize={150,80};
  SMALL_RECT rect={0,0,120,50};
  SetConsoleWindowInfo(hOut,TRUE,&rect);
}
void setting::setCursorInfo(){
  CONSOLE_CURSOR_INFO cursor_info;
  cursor_info.bVisible = FALSE;
  cursor_info.dwSize   = 100;
  SetConsoleCursorInfo(hOut, &cursor_info);
}
