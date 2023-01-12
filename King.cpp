//Arthur Wang: awang91
//Kaden Rosenblatt: krosen23
//Taylor Nguyen: tnguy228
#include <stdlib.h>
#include "King.h"

bool Chess::King::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end)const {
  return legal_move_shape(start, end);
}

bool Chess::King::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end)const {
  //if King doesn't move horizontally
  if (start.first-end.first == 0 && abs(start.second-end.second) == 1)
    return true;
  //if King doesn't move vertically
  else if (start.second-end.second == 0 && abs(start.first-end.first) == 1)
    return true;
  //if King moves diagonally
  else if (abs(start.first-end.first) == 1 && abs(start.second-end.second) == 1) 
    return true;
  
  return false;
  
}
