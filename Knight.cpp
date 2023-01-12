//Arthur Wang: awang91
//Kaden Rosenblatt: krosen23
//Taylor Nguyen: tnguy228
#include <stdlib.h>
#include "Knight.h"

bool Chess::Knight::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end)const {
  return legal_move_shape(start, end);
}

bool Chess::Knight::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
  if( (abs(start.first-end.first)==2 && abs(start.second-end.second)==1) ||
      (abs(start.first-end.first)==1 && abs(start.second-end.second)==2) ) {
    return true;
  }
  return false;
}
