#ifndef DRAWER_H_INCLUDED
#define DRAWER_H_INCLUDED
#include "windows.h"
#include "block.h"
#include "point.h"
class drawer{
  public:
    drawer();
    void setCur(int,int);
    void setCur(point &);
    void drawDot(int ,int);
    void drawLine(int ,int ,int ,int );
    void drawRect(int ,int ,int ,int );
    void drawBlock(block&,int);
    void drawTXT(char *str,int x,int y);
    void drawINT(int val,int x,int y);
    void e_act(block&,int(*)[25]);
    void era_block(int x,int y);
    void era_Dot(int,int);
    void era_line(int);
  private:
    HANDLE dHandle;
    DWORD colors[6];
};


#endif // DRAWER_H_INCLUDED
