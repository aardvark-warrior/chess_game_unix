///////////////////////////////////
// IT IS OK TO MODIFY THIS FILE, //
// YOU WON'T HAND IT IN!!!!!     //
///////////////////////////////////
#ifndef MYSTERY_H
#define MYSTERY_H

#include "Piece.h"
#include <stdlib.h>
namespace Chess
{
  class Mystery : public Piece {

  public:
    bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
      if( (abs(start.first-end.first)==4 && abs(start.second-end.second)==2) ||
      (abs(start.first-end.first)==2 && abs(start.second-end.second)==4) ) {
      return true;
  }
      return false;
    }

    char to_ascii() const {
      return is_white() ? 'M' : 'm';
    }

  private:
    Mystery(bool is_white) : Piece(is_white) {}

    friend Piece* create_piece(char piece_designator);
  };
}
#endif // MYSTERY_H
