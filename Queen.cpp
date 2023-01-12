//Arthur Wang: awang91
//Kaden Rosenblatt: krosen23
//Taylor Nguyen: tnguy228
#include <stdlib.h>
#include "Queen.h"

bool Chess::Queen::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end)const{
  return legal_move_shape(start, end);
}

bool Chess::Queen:: legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  //vertical movement
  if (end.first-start.first == 0 && end.second-start.second != 0) {
    return true;
  }
  //horizontal movement
  else if (end.first-start.first != 0 && end.second-start.second == 0) {
    return true;
  }
  //diagonal movement
  else if (abs(start.first-end.first) == abs(start.second-end.second)) {
    return true;
  }
  return false;
}
