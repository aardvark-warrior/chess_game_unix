//Arthur Wang: awang91
//Kaden Rosenblatt: krosen23
//Taylor Nguyen: tnguy228
#include <stdlib.h>
#include "Piece.h"
#include "Pawn.h"

bool Chess::Pawn::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  //if pawn doesn't move left or right by exactly 1
  if (abs(end.first-start.first)!=1) return false;

  //if pawn is white
  if(Chess::Piece::is_white()) {
    //if doesn't move forward by exactly 1
    if (end.second-start.second != 1) return false;
  }
  //if pawn is black
  else {
    //if pawn doesn't move foward by exactly 1
    if (start.second-end.second != 1) return false;
  }
  return true;
}

bool Chess::Pawn::legal_move_shape(std::pair<char, char> start,std::pair<char, char> end) const {
  //if pawn has moved horizantally
  if (end.first != start.first) {
    return false;
  }

  //if pawn is white
  if (Chess::Piece::is_white()){
    //if pawn doesn't move forward
    if (end.second-start.second <= 0) return false;
    //if pawn moves forward more than one and
    //pawn is not moving up by two when it's on the starting rank
    if ( end.second-start.second!=1 &&  
	 !(end.second-start.second==2 && start.second=='2') ) {
      return false;
    }
  }
  //if pawn is black
  else{
    if(start.second-end.second<=0) return false;
    if ( start.second-end.second!=1 &&
	 !(start.second-end.second==2 && start.second=='7') ) {
      return false;
    }
  }	
  return true;
}
