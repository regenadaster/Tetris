#include <iostream>
#include <stdio.h>
#include "windows.h"
#include "drawer.h"
#include "time.h"

drawer::drawer(){
  dHandle=GetStdHandle(STD_OUTPUT_HANDLE);
  colors[0]=FOREGROUND_GREEN;
  colors[1]=FOREGROUND_BLUE;
  colors[2]=FOREGROUND_RED;
  colors[3]=FOREGROUND_GREEN|FOREGROUND_BLUE;
  colors[4]=FOREGROUND_BLUE|FOREGROUND_RED;
  colors[5]=FOREGROUND_GREEN|FOREGROUND_RED;
}
void drawer::draw(int xx,int yy,char *cha){
  setCur(xx,yy);
  printf("%s",cha);
}
void drawer::drawLine(int sx,int sy,int ex,int ey){
  int i;
  if(sx==ex){
    for(i=sy+1;i<ey;i+=1){
      draw(sx,i,"©ª");
    }
  }
  if(sy==ey){
    for(i=sx+1;i<ex;i+=2){
      draw(i,sy,"©¨");
    }
  }
}
void drawer::drawRect(int sx,int sy,int ex,int ey){
  drawLine(sx,sy,sx,ey);
  drawLine(sx,sy,ex,sy);
  drawLine(ex,sy,ex,ey);
  drawLine(sx,ey,ex,ey);
  if(sx<ex&&sy<ey){
    draw(sx,sy,"©°");
    draw(sx,ey,"©¸");
    draw(ex,sy,"©´");
    draw(ex,ey,"©¼");
  }
}
void drawer::setCur(int xx,int yy){
  COORD pos={xx,yy};
  SetConsoleCursorPosition(this->dHandle,pos);
}
void drawer::setCur(point &po){
  setCur(po.getX(),po.getY());
}
void drawer::drawBlock(block& bl,int cRand){
  int bx,by,_i,_j;
  SetConsoleTextAttribute(dHandle,colors[cRand]|FOREGROUND_INTENSITY);
  bx=bl.getPos().getX();
  by=bl.getPos().getY();
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      if(bl.getData(_i,_j)==1){
        draw(bx+_i*2,by+_j,"¡ö");
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
      if(bl.getData(_i,_j)&&!bm[sx+_i*2][_j+sy]) {
        draw(sx+_i*2,_j+sy,"  ");//maybe some bugs;
      }
    }
  }
}
void drawer::erase_line(int sx,int sy,int ex,int ey){
  int i;
  if(sx==ex){
    for(i=sy;i<ey;i++){
      draw(sx,i," ");
    }
  }
  if(sy==ey){
    for(i=sx;i<ex;i++){
      draw(sy,i," ");
    }
  }
}
void drawer::erase_HorizontalLine(int sx,int ex,int y){
  erase_line(sx,y,ex,y);
}
void drawer::drawBlockUnit(int xx,int yy){
  draw(xx,yy,"¡ö");
}
void drawer::era_Dot(int xx,int yy){
  draw(xx,yy," ");
}
void drawer::drawTXT(char *str,int x,int y){
  draw(x,y,str);
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
      draw(sx+_i*2,_j+sy,"¡¡");//maybe some bugs;
    }
  }
}

