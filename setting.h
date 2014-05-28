#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED
#include <windows.h>
class setting{
  public:
    setting();
    void setWindowInfo();
    void setCursorInfo();
  private:
    HWND hwnd;
    HANDLE hOut;
};


#endif // SETTING_H_INCLUDED
