#include <stdio.h>
#include "block.h"
#include "stdlib.h"
#include "time.h"

block::block():startP(point(6,1)){
  init();
  setTypeArr();
  allocData();
  randSet();
  setTypeAndState();
  randSet();
}
void block::setTypeArr(){
  int i,j,k;
  int tmpArr[7][4][4]={
    {
      {0,1,0,0},
      {0,1,0,0},
      {0,1,0,0},
      {0,1,0,0}
    },
    {
      {0,0,0,0},
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0}
    },
    {
      {0,1,0,0},
      {0,1,1,0},
      {0,0,1,0},
      {0,0,0,0}
    },
    {
      {0,1,0,0},
      {0,1,1,0},
      {0,1,0,0},
      {0,0,0,0}
    },
    {
      {0,1,0,0},
      {0,1,0,0},
      {0,1,1,0},
      {0,0,0,0}
    },
    {
      {0,0,1,0},
      {0,0,1,0},
      {0,1,1,0},
      {0,0,0,0}
    },
    {
      {0,0,1,0},
      {0,1,1,0},
      {0,1,0,0},
      {0,0,0,0}
    }
  };
  for(i=0;i<7;i++){
    for(j=0;j<4;j++){
      for(k=0;k<4;k++){
        typeArr[i][j][k]=tmpArr[i][j][k];
      }
    }
  }
}
void block::allocData(){
  int k,i,j;
  this->data=new int*[4];
  for(k=0;k<4;k++){
    this->data[k]=new int[4];
  }
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      this->data[i][j]=0;
    }
  }
}
int block::getType()const{
  return b_type;
}
int block::getState()const{
  return b_state;
}
int block::getNextType()const{
  return next_type;
}
int block::getNextState()const{
  return next_state;
}
block& block::operator=(const block&right){
  this->b_type=right.getType();
  this->b_pos=right.getPos();
  this->setType(this->b_type);
  this->setState(right.getState());
  return *this;
}
block::block(const block&right){
  //delete []this->data;
  allocData();
  this->b_type=right.getType();
  this->b_pos=right.getPos();
  this->setType(this->b_type);
  this->setState(right.getState());
}
void block::reflesh(){
  init();
  setTypeAndState();
  randSet();
}
point block::getPos()const{
  return b_pos;
}
void block::setBpos(int xx,int yy){
  b_pos.setX(xx);
  b_pos.setY(yy);
}
void block::setType(int t){
  if(t>0&&t<8){
    b_type=t;
    int (*ptr)[4][4];
    int i,j;
    ptr=typeArr;
    for(i=0;i<4;i++){
      for(j=0;j<4;j++){
        data[i][j]=ptr[t-1][i][j];
     // printf("data[%d][%d]:%d ",i,j,data[i][j]);
      }
    }
  }
}
void block::setState(int s){
  if(s>0&&s<5){
    while(this->b_state!=s){
      rotote();
    }
  }
}
void block::rotote(){
  int _i,_j;
  int temp[4][4];
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      temp[_i][_j]=data[_i][_j];
    }
  }
  for(_i=0;_i<4;_i++){
    for(_j=0;_j<4;_j++){
      data[_i][_j]=temp[3-_j][_i];
    }
  }
  b_state=(b_state+1)%5;
  if(b_state==0) b_state++;
}
block::~block(){
  delete[]data;
}
void block::randSet(){
  srand((int)time(0));
  int ran=rand()%8;
  int tran=rand()%5;
  if(ran==0) ran++;
  if(tran==0) tran++;
  next_type=ran;
  next_state=tran;
}
void block::setTypeAndState(){
  setType(next_type);
  setState(next_state);
}
int block::getData(int x,int y){
  return this->data[x][y];
}
void block::initTypeAndState(){
  b_type=0;
  b_state=0;
}
void block::init(){
  initTypeAndState();
  initPos();
}
void block::initPos(){
  this->b_pos.setX(startP.getX());
  this->b_pos.setY(startP.getY());
}
