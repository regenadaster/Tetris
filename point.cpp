#include <iostream>
#include "point.h"

point::point():x(0),y(0){
}
point::point(const point &po){
  this->x=po.x;
  this->y=po.y;
}
point& point::operator=(const point &right){
  if(&right==this){
    return *this;
  }
  else{
    this->x=right.x;
    this->y=right.y;
  }

}
point::point(int xx,int yy){
  setX(xx);
  setY(yy);
}
void point::setX(const int xx){
  x=xx;
}
void point::setY(const int yy){
  y=yy;
}
int point::getX()const{
  return x;
}
int point::getY()const{
  return y;
}
