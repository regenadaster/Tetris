#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include "drawer.h"
#include "block.h"
#include "point.h"
#include "interaction.h"
class table{
  public:
   table();
   int isFirstStep();
   void drawNextBlockBySide();
   void tableInit();
   void setHeight(int );
   void setGameVerge();
   void drawGameFrame();
   int getHeight();
   void autoMoveDown();
   void setWidth(int );
   int getWidth();
   void addToBmap();
   void run();
   bool crash(int ,int );
   void eraLineBmap(int );
   void deleteLevel();
   void drawBmap();
   void moveStep(int ,int );
   void setBh(int );
   int getBh();
   void BhIncrement();
   void setBw(int );
   int getBw();
   void era_table();
   void drawScore();
   void moveDown(int );
   void GameOver();
   void drawAuthor();
   int getGameOver();
   void setIspaint(int );
   int getIspaint();
   int isRotote();
   void colorChange();
   void erase_block(block&);
   void table_era(block&);
  private:
    interaction assistant;
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
