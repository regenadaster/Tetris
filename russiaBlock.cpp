#define _WIN32_WINNT 0x0500
#include <iostream>
#include <stdio.h>
#include "table.h"
#include "point.h"
#include "drawer.h"
#include "block.h"
#include "eraser.h"
#include "setting.h"

int main(){
  setting gameSetting;
  table gameTable;
  while(1){
    gameTable.run();
    if(gameTable.getGameOver()){
      break;
    }
  }
  return 0;
}
