#include <iostream>
#include <stdio.h>
#include "table.h"
#include <memory.h>
#include <time.h>
table::table():THeight(20),TWidth(150){
  nextb.setBpos(32,10);
  tableInit();
  colorChange();
  InitializeCriticalSection(&mycs);
  drawGameFrame();
  drawAuthor();
  drawScore();
  setGameVerge();
}
void table::drawGameFrame(){
  t_drawer.drawRect(1,0,26,20);
  t_drawer.drawRect(30,0,40,20);
}
void table::setGameVerge(){
  int i;
  for(i=0;i<getWidth();i++){
    bmap[i][20]=1;
    bmap[i][0]=1;
  }
  for(i=0;i<getHeight();i++){
    bmap[0][i]=1;
    bmap[1][i]=1;
    bmap[2][i]=1;
    bmap[26][i]=1;
  }
}
void table::tableInit(){
  isPaint=0;
  b_h=0;
  b_w=0;
  score=0;
  gameOver=0;
  memset(bmap,0,sizeof(bmap));
  setHeight(THeight);
  setWidth(TWidth);
}
void table::colorChange(){
  srand((int)time(0));
  colorRand=rand()%6;
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
void table::deleteLevel(){
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
      t_drawer.erase_HorizontalLine(4,25,i);
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
        t_drawer.drawBlockUnit(i,j);
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
/**
  the parameter of crash are x and y
    x refer the block forward x
    y fefer the block forward y
**/
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
      t_drawer.drawBlockUnit(_j,_i);
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
  if(isFirstStep()){
    if(crash(0,1)==1){
      GameOver();
    }
    drawNextBlockBySide();
  }
  lastTime=GetTickCount();
  while(GetTickCount()-lastTime<=500){
    if(assistant.isKeyUp()){
      if(isRotote()){
        erase_block(current);
        current.rotote();
        t_drawer.drawBlock(current,colorRand);
        setIspaint(1);
        Sleep(100);
      }
    }
    if(assistant.isKeyLeft()){
      if(crash(-2,0)==0) {
        moveStep(-2,0);
        Sleep(90);
      }
    }
    if(assistant.isKeyRight()){
      if(crash(2,0)==0) {
        moveStep(2,0);
        Sleep(90);
     }
    }
    if(assistant.isKeyDown()){
      if(crash(0,1)==0) {
        moveStep(0,1);
        Sleep(15);
      }
    }
  }
  autoMoveDown();
}
void table::autoMoveDown(){
  if(crash(0,1)==0){
    moveStep(0,1);
  }
  else{
    colorChange();
    addToBmap();
    deleteLevel();
    current.reflesh();
    t_drawer.era_block(32,10);
  }
}
void table::erase_block(block &bl){
  if(getIspaint()){
    table_era(bl);
    setIspaint(0);
  }
}
void table::moveStep(int x,int y){
  erase_block(current);
  setBw(current.getPos().getX()+x);
  setBh(current.getPos().getY()+y);
  current.setBpos(getBw(),getBh());
  t_drawer.drawBlock(current,colorRand);
  setIspaint(1);
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
/**
    this function is to draw the next block
  by the side;
**/
void table::drawNextBlockBySide(){
  if(current.getNextType()==current.getType()){
    current.randSet();
  }
  int typeN=current.getNextType();
  int stateN=current.getNextState();
  nextb.setType(typeN);
  nextb.setState(stateN);
  t_drawer.drawBlock(nextb,colorRand);
}
int table::isFirstStep(){
 if(getBh()==1){
  return 1;
 }
 return 0;
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
