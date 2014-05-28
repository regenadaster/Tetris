#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include "drawer.h"
#include "block.h"
#include "point.h"
class table{
  public:
   table();
   void setHeight(int );
   int getHeight();
   void setWidth(int );
   int getWidth();
   void addToBmap();
   void run();
   bool crash(int x,int y);
   void eraLineBmap(int y);
   void deleteGood();
   void drawBmap();
   void setBh(int hh);
   int getBh();
   void BhIncrement();
   void setBw(int ww);
   int getBw();
   void era_table();
   void drawScore();
   void moveDown(int y);
   void GameOver();
   void drawAuthor();
   int getGameOver();
   void setIspaint(int x);
   int getIspaint();
   int isRotote();
   void colorChange();
   void table_era(block&);
  private:
    int lastTime;
    int isPaint;
    CRITICAL_SECTION mycs;
    int b_h;
    int b_w;
    drawer t_drawer;
    block nextb;
    block current;
    int score;
    int gameOver;
    const int THeight;
    const int TWidth;
    int bmap[150][25];
    int t_height;
    int t_width;
    int colorRand;
};


#endif // TABLE_H_INCLUDED
