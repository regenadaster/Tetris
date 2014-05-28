#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "interaction.h"

using namespace std;

interaction::interaction(){
}
int interaction::isKeyDown(){
  return GetAsyncKeyState(VK_DOWN);
}
int interaction::isKeyLeft(){
  return GetAsyncKeyState(VK_LEFT);
}
int interaction::isKeyRight(){
  return GetAsyncKeyState(VK_RIGHT);
}
int interaction::isKeyUp(){
  return GetAsyncKeyState(VK_UP);
}

