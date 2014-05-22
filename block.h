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
    void setBpos(int, int);
    void rotote();
    int getData(int x,int y);
    void allocData();
    void setCur(int,int);
    point getPos()const;
    block& operator=(const block &right);
    class Proxy{
      public:
        Proxy(int *arr);
        int operator[](int index);
      private:
        int *_arr;
    };
    Proxy operator[](int index){
      //printf("data[%d]:%d ",index,data[index]);
      return Proxy(data[index]);
    }
  private:
    int b_type;
    int next_type;
    int next_state;
    int b_state;
    int **data;
    point b_pos;
};


#endif // BLOCK_H_INCLUDED
