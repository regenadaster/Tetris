#include <iostream>
#include <stdio.h>
#include "table.h"
#include <memory.h>
table::table(){
  int i,j;
  b_h=0;
  b_w=0;
  score=0;
  gameOver=0;
  lastTime=GetTickCount();
  isPaint=0;
  InitializeCriticalSection(&mycs);
  t_drawer.drawRect(1,0,26,20);
  t_drawer.drawRect(30,0,40,20);
  drawAuthor();
  drawScore();
  setHeight(THeight);
  setWidth(TWidth);
  memset(bmap,0,sizeof(bmap));
  for(i=0;i<150;i++){
    bmap[i][20]=1;
    bmap[i][0]=1;
  }
  for(i=0;i<20;i++){
    bmap[0][i]=1;
    bmap[1][i]=1;
    bmap[2][i]=1;
    bmap[26][i]=1;
  }
}
void table::drawAuthor(){
  t_drawer.drawTXT("Next:",33,9);
  t_drawer.drawTXT("do by:",33,17);
  t_drawer.drawTXT("LGT",35,18);
}
void table::drawScore(){
  t_drawer.drawTXT("SCORE:",33,3);
  t_drawer.drawINT(score,35,4);
}
void table::setHeight(int h){
  t_height=h;
}
void table::setWidth(int w){
  t_width=w;
}
int table::getHeight(){
  return t_height;
}
int table::getWidth(){
  return t_width;
}
void table::addToBmap(){
  int _i,_j,xx,yy;
  yy=current.getPos().getY();
  xx=current.getPos().getX();
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      if(!bmap[xx+_i*2][yy+_j]&&current.getData(_i,_j)){
        bmap[xx+_i*2][yy+_j]=1;
      }
    }
  }
}
void table::deleteGood(){
  int i,j,flag,cn;
  cn=0;
  for(i=1;i<20;i++){
    flag=1;
    for(j=4;j<25;j+=2){
      if(bmap[j][i]!=1){
        flag=0;
      }
    }
    if(flag==1){
      score++;
      moveDown(i);
      t_drawer.era_line(i);
      era_table();
      drawScore();
      drawBmap();
    }
  }
}
void table::era_table(){
  int i,j;
  for(i=4;i<25;i++){
    for(j=1;j<20;j++){
      t_drawer.era_Dot(i,j);
    }
  }
}
void table::drawBmap(){
  int i,j;
  for(i=4;i<25;i++){
    for(j=1;j<20;j++){
      if(bmap[i][j]){
        t_drawer.drawDot(i,j);
      }
    }
  }
}
void table::eraLineBmap(int y){
  int i;
  for(i=4;i<25;i++){
    bmap[i][y]=0;
  }
}
bool table::crash(int x,int y){
  int xx,yy,_i,_j;
  yy=current.getPos().getY();
  xx=current.getPos().getX();
  if(xx+x<=0||xx+x>=26){
    return 1;
  }
  else{
    for(_i=0;_i<4;_i++){
      for(_j=0;_j<4;_j++){
        if(current.getData(_i,_j)){
          if(bmap[xx+x+_i*2][yy+y+_j]){
            return 1;
          }
        }
      }
    }
  }
  return 0;
}
void table::GameOver(){
  int _i,_j;
  gameOver=1;
  for(_i=1;_i<20;_i++){
    for(_j=2;_j<25;_j+=2){
      Sleep(5);
      t_drawer.drawDot(_j,_i);
    }
  }
  t_drawer.drawTXT("Game Over!",10,10);
  t_drawer.setCur(0,21);
}
void table::run(){
  int h,w;
  h=current.getPos().getY();
  w=current.getPos().getX();
  setBh(h);
  setBw(w);
  if(getBh()==1&&crash(0,1)==1){
    GameOver();
  }
  if(getBh()==1){
    nextb.setType(current.getNextType());
    nextb.setState(current.getNextState());
    nextb.setBpos(32,10);
    t_drawer.drawBlock(nextb);
  }
  lastTime=GetTickCount();
  while(GetTickCount()-lastTime<=500){
    if(GetAsyncKeyState(VK_UP)){
      if(isRotote()){
      if(getIspaint()){
        table_era(current);
        setIspaint(0);
      }
      current.rotote();
      t_drawer.drawBlock(current);
      setIspaint(1);
      Sleep(100);
      }
    }
    if(GetAsyncKeyState(VK_LEFT)){
      if(crash(-2,0)==0) {
        if(getIspaint()){
          table_era(current);
          setIspaint(0);
        }
        w=current.getPos().getX();
        setBw(w-2);
        current.setBpos(getBw(),getBh());
        t_drawer.drawBlock(current);
        setIspaint(1);
        Sleep(90);
      }
    }
    if(GetAsyncKeyState(VK_RIGHT)){
      if(crash(2,0)==0) {
        if(getIspaint()){
          table_era(current);
          setIspaint(0);
        }
        w=current.getPos().getX();
        setBw(w+2);
        current.setBpos(getBw(),getBh());
        t_drawer.drawBlock(current);
        setIspaint(1);
        Sleep(90);
     }
    }
    if(GetAsyncKeyState(VK_DOWN)){
      if(crash(0,1)==0) {
        BhIncrement();
        if(getIspaint()){
          table_era(current);
          setIspaint(0);
        }
        current.setBpos(getBw(),getBh());
        t_drawer.drawBlock(current);
        setIspaint(1);
        Sleep(20);
      }
    }
  }
  if(getBh()!=1) if(crash(0,1)==0) {
    if(getIspaint()){
      table_era(current);
      setIspaint(0);
    }
  }
  if(crash(0,1)==0){
    BhIncrement();
    if(getIspaint()){
      table_era(current);
      setIspaint(0);
    }
    current.setBpos(getBw(),getBh());
    t_drawer.drawBlock(current);
    setIspaint(1);
  }
  else{
    addToBmap();
    deleteGood();
    current.reflesh();
    t_drawer.era_block(32,10);
  }
}
int table::isRotote(){
  int tmp_one[4][4];
  int tmp_two[4][4];
  int _i,_j,xx,yy;
  xx=current.getPos().getX();
  yy=current.getPos().getY();
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      tmp_one[_i][_j]=current.getData(_i,_j);
    }
  }
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      tmp_two[_i][_j]=tmp_one[3-_j][_i];
    }
  }
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      if(tmp_two[_i][_j]){
        if(bmap[xx+_i*2][yy+_j]){
          return 0;
        }
      }
    }
  }
  return 1;
}
int table::getGameOver(){
  return gameOver;
}
void table::moveDown(int y){
  int i,j;
  for(i=4;i<25;i++){
    for(j=y;j>1;j--){
       bmap[i][j]=bmap[i][j-1];
    }
  }
}
void table::setBw(int ww){
  EnterCriticalSection(&mycs);
  this->b_w=ww;
  LeaveCriticalSection(&mycs);
}
void table::setBh(int hh){
  this->b_h=hh;
}
int table::getBh(){
  return b_h;
}
int table::getBw(){
  return b_w;
}
void table::BhIncrement(){
  EnterCriticalSection(&mycs);
  b_h++;
  LeaveCriticalSection(&mycs);
}
void table::setIspaint(int x){
  isPaint=x;
}
int table::getIspaint(){
  return isPaint;
}
void table::table_era(block& bl){
  int (*bmapptr)[25];
  bmapptr=bmap;
  t_drawer.e_act(bl,bmapptr);
}
