//Arthur Wang: awang91
//Kaden Rosenblatt: krosen23
//Taylor Nguyen: tnguy228

#include <iostream>
#include <utility>
#include <map>
#include "Terminal.h"
#include "Board.h"
#include "CreatePiece.h"

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  Board::Board(const Board& other) {
    *this = other;
  }

  Board::~Board() {
    this->clear();
  }

Board& Board::operator=(const Board& other) {
    if (this != &other) {
      //clear board
      this->clear();
    }
    //add all pieces from other board to this
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = other.occ.cbegin(); it != other.occ.cend(); it++) {
      this->add_piece(it->first,it->second->to_ascii());
    }
    return *this;
  }
  
  const Piece* Board::operator()(std::pair<char, char> position) const {
    if (occ.find(position) == occ.end()) {
      return NULL;
    }
    else {
      return occ.find(position)->second;
    }
  }

  bool Board::rm_piece(std::pair<char, char> position) {
    //if position out of range
    if ( position.first < 65 || position.first > 72 ||
	 position.second < 49 || position.second > 56) {
      return false;
    }
    if (occ.find(position) != occ.end()) {
      Piece* piece = occ.at(position);
      delete piece;
      occ.erase(position);
    }
    return true;
  }
  
  bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
    //if position out of range
    if ( position.first < 65 || position.first > 72 ||
	 position.second < 49 || position.second > 56) {
      return false;
    }
    //if piece already exists at position
    if ( occ[position] != NULL ) {
      return false;
    }
    //if designator is invalid (create_piece returns nullptr is invalid)
    /*
    if (! (piece_designator == 'K' || piece_designator == 'k' ||
	   piece_designator == 'Q' || piece_designator == 'q' ||
	   piece_designator == 'B' || piece_designator == 'b' ||
	   piece_designator == 'N' || piece_designator == 'n' ||
	   piece_designator == 'R' || piece_designator == 'r' ||
	   piece_designator == 'P' || piece_designator == 'p' ||
	   piece_designator == 'M' || piece_designator == 'm' ) ) {
      return false;
    */
    if ( (occ[position] = create_piece(piece_designator)) == nullptr ) {
      return false;
    }
    //occ[position] = create_piece(piece_designator);
    return true;
  }

  bool Board::has_valid_kings() const {
    int count_white  = 0;
    int count_black = 0;
    for ( std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.cbegin();
	  it != occ.cend();
	  it++ ) {
      if ( it->second->to_ascii() == 75 )
	count_white++;
      else if ( it->second->to_ascii() == 107 )
	count_black++;
    }
    return count_white==1 && count_black==1;
  }

  void Board::display() const {
    int count = 8;
    for(char i = 65; i <= 72; i++) {
      std::cout<<"  " << i << "  ";
    }
    std::cout<<std::endl;
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	if((r % 2 == 0 && c % 2 == 0) || (r % 2 == 1 && c % 2 == 1) ){
	  Terminal::color_bg(Terminal::BLACK);
	}
	else {
	  Terminal::color_bg(Terminal::WHITE);
	}
	const Piece* piece = (*this)(std::pair<char, char>(c, r));
	if (piece) {
	  if (piece->is_white()) Terminal::color_fg(0,Terminal::RED);
	  else Terminal::color_fg(0,Terminal::CYAN);
	  std::cout << "  " << piece->to_ascii() << "  ";
	} else {
	  Terminal::color_fg(0, Terminal::DEFAULT_COLOR);
	  std::cout <<"  "<< '-' <<"  ";
	}
      }
      Terminal::set_default();
      std::cout << "  " << count-- << std::endl;
    }
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        const Piece* piece = board(std::pair<char, char>(c, r));
        if (piece) {
          os << piece->to_ascii();
        } else {
          os << '-';
        }
      }
      os << std::endl;
    }
    return os;
  }

    void Board::clear() {
    if (!this->occ.empty()) {
    //add all pieces from other board to this
    for (std::map<std::pair<char, char>, Piece*>::iterator it = this->occ.begin();
	 it != this->occ.end(); it++) {
      delete(it->second); 
    }
    occ.clear();
   }
  }
  
std::istream& operator>>(std::istream& is, Board& board) {
  char data; 
  Board board1;
  for (char c = '8'; c >= '1'; c--) {
    for (char r = 'A'; r <= 'H'; r++) {
      is>>data;
      if (data == '-') {
      }
      else {
	board1.add_piece(std::pair<char, char> (r, c), data);
      }
      
    }
  }
  board = board1;
  return is;
}
  
}
