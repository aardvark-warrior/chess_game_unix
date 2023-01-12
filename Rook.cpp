//Arthur Wang: awang91
//Kaden Rosenblatt: krosen23
//Taylor Nguyen: tnguy228
#include "Rook.h"

//legal capture legal_capture_shop
bool Chess::Rook::legal_capture_shape(std::pair<char, char> start,std::pair<char, char> end) {
  return legal_move_shape(start, end);
}

bool Chess::Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  if (end.first - start.first != 0 && end.second - start.second != 0) {
    return false;
  }
  return true;
}
