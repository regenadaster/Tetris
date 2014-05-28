#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
class point{
  public:
    point();
    point(const point &);
    point(int ,int );
    void setX(const int);
    void setY(const int);
    int getX()const;
    int getY()const;
    point &operator=(const point &right);
  private:
    int x;
    int y;
};


#endif // POINT_H_INCLUDED
