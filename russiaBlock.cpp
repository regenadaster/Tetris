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
  //SetConsoleTextAttribute(hOut,0x01|0x05);
  //printf("HelloWorld!\n");
  //Sleep(3000);
  //RECT r={0,0,10,10};
  //COORD cur = {15, 5};
  //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
  //printf("                     ");
  //InvalidateRect(hwnd,&r,TRUE);
  //UpdateWindow (hwnd);
  //system("cls");
  table gameTable;
  COORD coordSize={150,80};
  SMALL_RECT rect={0,0,120,50};
  SetConsoleWindowInfo(hOut,TRUE,&rect);
  lastTime=GetTickCount();
  CONSOLE_CURSOR_INFO cursor_info;
  cursor_info.bVisible = FALSE;
  cursor_info.dwSize   = 100;
  SetConsoleCursorInfo(hOut, &cursor_info);
  while(1){
    gameTable.run();
  //printf("%d %d",fir.getPos().getX(),fir.getPos().getY());
  //printf("%d  ",p.getX());
  //printf("%d",gameTable.getWidth());
    if(gameTable.getGameOver()){
      break;
    }
  }
  return 0;
}
