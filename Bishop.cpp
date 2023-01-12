//Arthur Wang: awang91
//Kaden Rosenblatt: krosen23
//Taylor Nguyen: tnguy228
#include <stdlib.h>
#include "Bishop.h"

bool Chess::Bishop::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  return Piece::legal_capture_shape(start, end);
}

bool Chess::Bishop::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const{
  if (start.first-end.first != 0 && abs(start.first-end.first)==abs(start.second-end.second)) {
    return true;
  }
  return false;
}
