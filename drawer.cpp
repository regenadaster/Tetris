#include <iostream>
#include <stdio.h>
#include "windows.h"
#include "drawer.h"

drawer::drawer(){
  dHandle=GetStdHandle(STD_OUTPUT_HANDLE);
}
void drawer::drawLine(int sx,int sy,int ex,int ey){
  int i;
  if(sx==ex){
    for(i=sy+1;i<ey;i+=1){
      setCur(sx,i);
      printf("%s","©ª");
    }
  }
  if(sy==ey){
    for(i=sx+1;i<ex;i+=2){
      setCur(i,sy);
      printf("%s","©¨");
    }
  }
}
void drawer::drawRect(int sx,int sy,int ex,int ey){
  drawLine(sx,sy,sx,ey);
  drawLine(sx,sy,ex,sy);
  drawLine(ex,sy,ex,ey);
  drawLine(sx,ey,ex,ey);
  if(sx<ex&&sy<ey){
    setCur(sx,sy);
    printf("%s","©°");
    setCur(sx,ey);
    printf("%s","©¸");
    setCur(ex,sy);
    printf("%s","©´");
    setCur(ex,ey);
    printf("%s","©¼");
  }
}
void drawer::setCur(int xx,int yy){
  COORD pos={xx,yy};
  SetConsoleCursorPosition(this->dHandle,pos);
}
void drawer::setCur(point &po){
  setCur(po.getX(),po.getY());
}
void drawer::drawBlock(block& bl){
  int bx,by,_i,_j;
  bx=bl.getPos().getX();
  by=bl.getPos().getY();
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      setCur(bx+_i*2,by+_j);
      if(bl.getData(_i,_j)==1){
        printf("%s","¡ö");
      }
    }
  }
}
void drawer::e_act(block& bl,int (*bm)[25]){
  point s=bl.getPos();
  int sx,sy,_i,_j;
  sx=s.getX();
  sy=s.getY();
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      setCur(sx+_i*2,_j+sy);
      if(bl.getData(_i,_j)&&!bm[sx+_i*2][_j+sy]) {
        printf("%s","  ");//maybe some bugs;
      }
    }
  }
}
void drawer::era_line(int yy){
  int i;
  for(i=4;i<25;i+=2){
    setCur(i,yy);
    printf("%s"," ");
  }
}
void drawer::drawDot(int xx,int yy){
  setCur(xx,yy);
  printf("%s","¡ö");
}
void drawer::era_Dot(int xx,int yy){
  setCur(xx,yy);
  printf("%s"," ");
}
void drawer::drawTXT(char *str,int x,int y){
  setCur(x,y);
  printf("%s",str);
}
void drawer::drawINT(int val,int x,int y){
  setCur(x,y);
  printf("%d",val);
}
void drawer::era_block(int x,int y){
  int sx,sy,_i,_j;
  sx=x;
  sy=y;
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      setCur(sx+_i*2,_j+sy);
      printf("%s","¡¡");//maybe some bugs;
    }
  }
}

