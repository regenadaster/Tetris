#define _WIN32_WINNT 0x0500
#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<winuser.h>
#include<conio.h>
#include "table.h"
#include "point.h"
#include "drawer.h"
#include "block.h"
#include "eraser.h"

int main()
{
  int lastTime,ntime;
  HANDLE hOut;
  HWND hwnd=GetConsoleWindow();
  COORD pos={15,5};
  hOut=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hOut,pos);
  SetConsoleTextAttribute(hOut, FOREGROUND_BLUE|FOREGROUND_INTENSITY|FOREGROUND_RED);
  table gameTable;
  COORD coordSize={150,80};
  SMALL_RECT rect={0,0,120,50};
  SetConsoleWindowInfo(hOut,TRUE,&rect);
  CONSOLE_CURSOR_INFO cursor_info;
  cursor_info.bVisible = FALSE;
  cursor_info.dwSize   = 100;
  SetConsoleCursorInfo(hOut, &cursor_info);
  while(1){
    gameTable.run();
    if(gameTable.getGameOver()){
      break;
    }
  }
  return 0;
}
