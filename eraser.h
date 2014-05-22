#ifndef ERASER_H_INCLUDED
#define ERASER_H_INCLUDED
#include "point.h"
#include "drawer.h"
#include "block.h"

class eraser{
  public:
    eraser();
    void setCur(int,int);
    void e_act(block);
  private:
    HANDLE eHandle;
};

#endif // ERASER_H_INCLUDED
