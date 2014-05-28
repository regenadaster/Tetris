#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "point.h"
/**
 block type tips:
   type one is:
             ****
   type two is:
             **
             **
   type three
             **
              **
   type four:
              *
             ***
   type five:
            ***
              *
   type six:
            ***
            *
   type seven:
             **
            **
**/

class block{
  public:
    block();
    ~block();
    block(const block&);
    void reflesh();
    void setTypeAndState();
    void setType(int);
    int getNextType()const;
    int getType()const;
    void randSet();
    void setState(int);
    int getState()const;
    int getNextState()const;
    void initPos();
    void setBpos(int, int);
    void rotote();
    int getData(int x,int y);
    void allocData();
    void setCur(int,int);
    point getPos()const;
    void init();
    void initTypeAndState();
    block& operator=(const block &right);
  private:
    const point startP;
    int typeArr[7][4][4];
    int b_type;
    int next_type;
    int next_state;
    int b_state;
    int **data;
    point b_pos;
};


#endif // BLOCK_H_INCLUDED
