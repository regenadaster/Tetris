#include <stdio.h>
#include "eraser.h"

eraser::eraser(){
  eHandle=GetStdHandle(STD_OUTPUT_HANDLE);
}
void eraser::setCur(int xx,int yy){
  COORD pos={xx,yy};
  SetConsoleCursorPosition(this->eHandle,pos);
}
void eraser::e_act(block bl){
  point s=bl.getPos();
  int cn=0;
  int sx,sy,_i,_j;
  sx=s.getX();
  sy=s.getY();
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      setCur(sx+_j*2,_i+sy);
      if(bl[_j][_i]) {
        printf("%s","¡¡");//maybe some bugs;
        cn++;
      }
    }
  }
}

