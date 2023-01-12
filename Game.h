//Arthur Wang: awang91
//Kaden Rosenblatt: krosen23
//Taylor Nguyen: tnguy228
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{

  class Game {

  public:
    // This default constructor initializes a board with the standard
    // piece positions, and sets the state to white's turn
    Game();

    // Returns a constant reference to the board
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    const Board& get_board() const { return board; }

    // Returns true if it is white's turn
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    bool turn_white() const { return is_white_turn; }

    // Attemps to make a move. If successful, the move is made and
    // the turn is switched white <-> black. Otherwise, an exception is thrown
    void make_move(std::pair<char, char> start, std::pair<char, char> end);

    // Returns true if the designated player is in check
    bool in_check(bool white) const;

    // Returns true if the designated player is in mate
    bool in_mate(bool white) const;

    // Returns true if the designated player is in mate
    bool in_stalemate(bool white) const;
    
    // Reads the board in from a stream
    friend std::istream& operator>> (std::istream& is, Game& game);
    
  private:
    // The board
    Board board;

    // Is it white's turn?
    bool is_white_turn;

    //helper methods for exceptions:

    //returns true if position is not on board
    bool invalid_position(std::pair<char, char> start) const;
    //return true if no piece to move
    bool null_start_piece(const Piece * moving_piece) const;
    //returns true if not moving right color piece
    bool invalid_color_move(const Piece * moving_piece, const bool white) const;
    //returns true if piece isn't capturing another and its move shape isn't correct based on its type
    bool illegal_move_shape(const Piece * moving_piece, const Piece* captured_piece,std::pair<char, char> start, std::pair<char, char> end) const;
    //returns if move would capture own players piece
    bool capture_own_piece(const Piece * moving_piece, const Piece * captured_piece) const;
    //returns true if piece is capturing another and its capture shape is invalid based on type
    bool illegal_capture_shape(const Piece * moving_piece, const Piece * captured_piece,std::pair<char, char> start, std::pair<char, char> end) const;
    //returns true if a piece with linear capture movement has its path obstructed during capture
    bool invalid_path( std::pair<char, char> start, std::pair<char, char> end, const Board& board) const;
    //returns true if move would expose player's king to a check
    bool exposes_check(const Piece * moving_piece, std::pair<char, char> start, std::pair<char, char> end, const Board& board, bool white) const;
    //returns the position of a king on a board without modifying the board
    std::pair<char, char> find_king(const Board& board) const;
  };
  std::ostream& operator<< (std::ostream& os, const Game& game);

}
#endif // GAME_H
