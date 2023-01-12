  //Arthur Wang: awang91                                 //Kaden Rosenblatt: krosen23                            //Taylor Nguyen: tnguy228  
  #include <cassert>
  #include "Game.h"
  #include <stdlib.h>

  namespace Chess
  {
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    Game::Game() : is_white_turn(true) {
      // Add the pawns
      for (int i = 0; i < 8; i++) {
        board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
        board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
      }

      // Add the rooks
      board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
      board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
      board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
      board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

      // Add the knights
      board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
      board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
      board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
      board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

      // Add the bishops
      board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
      board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
      board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
      board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

      // Add the kings and queens
      board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
      board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
      board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
      board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
    }

    void Game::make_move(std::pair<char, char> start, std::pair<char, char> end) {
      const Piece * moving_piece = this->board(start);
      const Piece * captured_piece = this->board(end);
      //check all exceptions
      if (invalid_position(start)) throw Exception("start position is not on board");
      else if (invalid_position(end)) throw Exception("end position is not on board");
      else if (null_start_piece(moving_piece)) throw Exception("no piece at start position");
      else if (invalid_color_move(moving_piece,this->is_white_turn)) throw Exception("piece color and turn do not match");
      else if (illegal_move_shape(moving_piece, captured_piece,start, end)) throw Exception("illegal move shape");
      else if (capture_own_piece(moving_piece, captured_piece)) throw Exception ("cannot capture own piece");
      else if (illegal_capture_shape(moving_piece, captured_piece,start, end)) throw Exception("illegal capture shape");
      else if (invalid_path(start,end, this->board)) throw Exception("path is not clear");
      else if (exposes_check(moving_piece, start, end, this->board,this->is_white_turn)) throw Exception("move exposes check");
      
      else {//move is valid
      //capture piece / move piece to square
      char piece_name = moving_piece->to_ascii();
      this->board.rm_piece(start);
      this->board.rm_piece(end);
      //if promoting, auto queen the pawn
      if (piece_name == 'P' && end.second == '8') piece_name = 'Q';
      else if (piece_name == 'p' && end.second == '1') piece_name = 'q';
      this->board.add_piece(end,piece_name);
      //switch turn
      this->is_white_turn = !this->is_white_turn;
      }
    }

    bool Game::in_check(bool white) const {
      //make copy of board to avoid modifying actual board
      Board board(this->board);
      //search board for king position
      std::pair<char, char> king_pos = find_king(board);
      //check every valid piece for valid king capture
      for (char r = '8'; r >= '1'; r--) {
          for (char c = 'A'; c <= 'H'; c++) {
            const Piece * piece = board(std::make_pair(c,r));
            //if piece is opposite color, try capturing king
            if (piece != NULL && piece->is_white() != white) {
                std::pair<char, char> start = std::make_pair(c, r);
                if (!illegal_capture_shape(piece,board(king_pos),start,king_pos) && !invalid_path(start,king_pos,board)) return true;
            }
          }
      }
      //otherwise no legal capture of king possible 
      return false;
    }

    bool Game::in_mate(bool white) const {
      //if in check and in stale mate -> all possible moves are invalid (they dont block the check or move the king out of check) -> mate
      if (in_check(white) && in_stalemate(white)) return true;
      //else there are valid moves to get king out of check
      return false;
    }

    bool Game::in_stalemate(bool white) const {
      Board board(this->board);
      //for every piece on board
      for (char r = '8'; r >= '1'; r--) {
          for (char c = 'A'; c <= 'H'; c++) {
            std::pair<char, char> start = std::make_pair(c, r);
            const Piece * piece = board(start);
            //if piece is this player's
            if (piece != NULL && piece->is_white() == white) {
            //check if it can move to any position on board
            for (char r2 = '8'; r2 >= '1'; r2--) {
              for (char c2 = 'A'; c2 <= 'H'; c2++) {
                std::pair<char, char> end = std::make_pair(c2, r2);
                const Piece * captured_piece = board(end);
                //if valid move, not stale mate
                if (!illegal_move_shape(piece, captured_piece,start, end) && !capture_own_piece(piece,captured_piece) &&
                !illegal_capture_shape(piece, captured_piece,start, end) && !invalid_path(start, end, board) && !exposes_check(piece,start,end,board,white))
                return false;
              }
            }
            }   
          }
      }
      //every piece of player's can't move, stalemate
      return true;
    }

    std::istream& operator>> (std::istream& is, Game& game) {
      std::cout<<"entered"<<std::endl;
      char data;
      is >> game.board;
      
      is >> data;
      switch(data){
      case 'w':
        game.is_white_turn = true;
        break;
      case 'b':
        game.is_white_turn = false;
        break;
      default:
        std::cout<<"Error: Unreadable file format"<<std::endl;
        break;
      }
      return is;
    }  

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    std::ostream& operator<< (std::ostream& os, const Game& game) {
      // Write the board out and then either the character 'w' or the character 'b',
      // depending on whose turn it is
      return os << game.get_board() << (game.turn_white() ? 'w' : 'b');
    }
    bool Game::invalid_position(std::pair<char, char> pos) const{
      return (pos.first < 65 || pos.first > 72 || pos.second < 49 || pos.second > 56);
    }

    bool Game::null_start_piece(const Piece * moving_piece) const{
      return moving_piece == NULL;
    }

    bool Game::invalid_color_move(const Piece * moving_piece, const bool white) const{
      return (moving_piece->is_white() != white);
    }

    bool Game::illegal_move_shape(const Piece * moving_piece, const Piece* captured_piece,std::pair<char, char> start, std::pair<char, char> end) const{
      //if piece didn't move, invalid move shape
      if (start.first-end.first == 0 && start.second-end.second == 0) return true;
      //if we are capturing a piece, ignore/return
      if (captured_piece != NULL) return false;
      //else call as normal
      return !moving_piece->legal_move_shape(start,end);
    }

    bool Game::capture_own_piece(const Piece * moving_piece, const Piece * captured_piece) const{
      //empty square not capturing anything -> false;
      if (captured_piece == NULL) return false;
      return captured_piece->is_white() == moving_piece->is_white();
    }

    bool Game::illegal_capture_shape(const Piece * moving_piece, const Piece * captured_piece,std::pair<char, char> start, std::pair<char, char> end) const{
      //if there is no piece, ignore, return false
      if (captured_piece == NULL) return false;
      return !moving_piece->legal_capture_shape(start, end);
    }

    bool Game::invalid_path(std::pair<char, char> start, std::pair<char, char> end, const Board& board) const{

    int horizontal_distance = start.first - end.first;
    int vertical_distance = start.second - end.second;
    //if path is non linear, assume path is unaffected by intermediary pieces
    if (horizontal_distance != 0 && vertical_distance != 0 && abs(horizontal_distance) != abs(vertical_distance)) return false;
    //ignoring first and last square, iterate over all squares traveled over to see if any piece obstructs
    for (int i = 1, j = 1; i < abs(horizontal_distance) || j < abs(vertical_distance); i++, j++) {
      char new_horizontal = start.first;
      //ensure horizontal_distance to travel still
      if (i <= abs(horizontal_distance)) {
        //if dist negative, need to increase the character A->H
        if (horizontal_distance < 0) new_horizontal += i;
        //else dist positive, decrease character A<-H
        else new_horizontal -= i;
      }
      char new_vertical = start.second; 
      if (j <= abs(vertical_distance)) {
        if (vertical_distance < 0) new_vertical += j;
        else new_vertical -= j;
      }
      if (board(std::make_pair(new_horizontal,new_vertical)) != NULL) return true;
    }
    return false;
    }

  //returns whether a move would expose check for a player
  bool Game::exposes_check(const Piece * moving_piece, std::pair<char, char> start, std::pair<char, char> end, const Board& board, bool white) const{
    //create a copy of curr game state 
    Game game_copy;
    game_copy.is_white_turn = white;
    game_copy.board = board;

    //capture piece on board copy
    char piece_name = moving_piece->to_ascii();
    game_copy.board.rm_piece(start);
    game_copy.board.rm_piece(end);
    game_copy.board.add_piece(end,piece_name);
    //return whether move exposed check
    return game_copy.in_check(white);
  }

  std::pair<char, char> Game::find_king(const Board& board) const {
    for (char r = '8'; r >= '1'; r--) {
            for (char c = 'A'; c <= 'H'; c++) {
          const Piece* piece = board(std::make_pair(c,r));
          //check if king of correct color then set as pos
          if (piece != NULL) {
          if ((piece->to_ascii() == 'K' && this->is_white_turn) || (piece->to_ascii() == 'k' && !this->is_white_turn)) return std::make_pair(c,r);
          }
          }  
    }
    //always guaranteed to find king, never will reach this line
    return std::make_pair('A','1');;
  }
}
