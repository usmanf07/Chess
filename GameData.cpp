#include "GameData.h"

#include<fstream>

#include<iostream>

using namespace std;

void PromotePawn(GameData & Game, chessMove Move) {
  // A special move that is allowed under special conditions
  int FR, FC, TR, TC;
  FR = Move.FromRow;
  FC = Move.FromColumn;
  TR = Move.ToRow;
  TC = Move.ToColumn;

  //BLACK PAWN
  if (Game.Board[FR][FC].Code == PAWN && Game.Board[FR][FC].PieceColor == BLACK) {

    if (TR == 7) {

      if (Game.Board[FR][FC].Code == PAWN) {
        cout << endl;
        cout << "**********************" << endl;
        cout << "To Promote Pawn, enter the respective number, press enter. Then Press the same number again to resume" << endl;
        cout << "You can promote Pawn, Enter number according to the piece:        " << endl;
        cout << "1 = QUEEN  |  2 = KNIGHT  |  3 = BISHOP  |  4 = ROOK              " << endl;
        cout << "**********************" << endl;
        cin >> pawnpromote;

        if (pawnpromote == 1) {
          Game.Board[FR][FC].Code = Game.Board[TR][TC].Code = QUEEN;
        }

        if (pawnpromote == 2)
          Game.Board[FR][FC].Code = Game.Board[TR][TC].Code = KNIGHT;

        if (pawnpromote == 3)
          Game.Board[FR][FC].Code = Game.Board[TR][TC].Code = BISHOP;

        if (pawnpromote == 4)
          Game.Board[FR][FC].Code = Game.Board[TR][TC].Code = ROOK;
      }
    }
  }
  //WHITE PAWN
  if (Game.Board[FR][FC].Code == PAWN && Game.Board[FR][FC].PieceColor == WHITE) {

    if (TR == 0) {

      if (Game.Board[FR][FC].Code == PAWN) {
        cout << endl;
        cout << "**********************" << endl;
        cout << "To Promote Pawn, enter the respective number, press enter. Then Press the same number again to resume" << endl;
        cout << "You can promote Pawn, Enter number according to the piece:        " << endl;
        cout << "1 = QUEEN  |  2 = KNIGHT  |  3 = BISHOP  |  4 = ROOK              " << endl;
        cout << "**********************" << endl;
        cin >> pawnpromote;
        if (pawnpromote == 1) {
          Game.Board[FR][FC].Code = Game.Board[TR][TC].Code = QUEEN;
        }

        if (pawnpromote == 2)
          Game.Board[FR][FC].Code = Game.Board[TR][TC].Code = KNIGHT;

        if (pawnpromote == 3)
          Game.Board[FR][FC].Code = Game.Board[TR][TC].Code = BISHOP;

        if (pawnpromote == 4)
          Game.Board[FR][FC].Code = Game.Board[TR][TC].Code = ROOK;
      }
    }

    return;
  }
}

bool isValidMove(GameData & Game, chessMove Move) {

  int FR, FC, TR, TC, nu, pu, lu, ku;
  FR = Move.FromRow;
  FC = Move.FromColumn;
  TR = Move.ToRow;
  TC = Move.ToColumn;
  nu = TR - FR;
  pu = FR - TR;
  if (TC > FC)
    lu = TC - FC;
  else
    lu = FC - TC;

  isfacingCheck(Game, Move, Game.Board[TR][TC].PieceColor);
  if (Game.Board[FR][FC].PieceColor == BLACK && Game.TurningPlayer == WHITE) {
    //White's Move Error
    error = "MW";
    return false;
  }
  if (Game.Board[FR][FC].PieceColor == WHITE && Game.TurningPlayer == BLACK) {
    //Black's Move Error
    error = "MB";
    return false;
  }

  if (Game.Board[FR][FC].Code == NONE) {

    //Empty Piece
    error = "EP";
    return false;
  }

  //Black Pawns

  if (Game.Board[FR][FC].Code == PAWN && Game.Board[FR][FC].PieceColor == BLACK) {
    ////////////////////////////////////is facing check//////////////////////////////////////////////////////////////

    if (Game.TurningPlayer == BLACK) {

      if (vow(Game, FR, FC, TR, TC) == false)
        return false;
    }
    //Enpassant Move from left (\)
    if (enpassant_white == 2) {
      if (TR == FR + 1 && TC == FC + 1 && Game.Board[TR][TC].Code == NONE) {
        capturedpieces_white[enpassant_capture_white] = Game.Board[TR - 1][TC].Code;
        Game.Board[TR - 1][TC].Code = NONE;
        enpassant_white = 0;
        enpassant_capture_white--;
        return true;
      }
    }
    //Enpassant Move from left(/)
    if (enpassant_white == 1) {
      if (TR == FR + 1 && TC == FC - 1 && Game.Board[TR][TC].Code == NONE) {
        capturedpieces_white[enpassant_capture_white] = Game.Board[TR - 1][TC].Code;
        Game.Board[TR - 1][TC].Code = NONE;
        enpassant_white = 0;
        enpassant_capture_white--;
        return true;
      }
    }

    if (TR <= FR) {
      error = "BPR";
      return false;
    }

    if (FC != TC) {

      if (lu > 1) {
        error = "BPC";
        return false;
      }

      if (Game.Board[TR][TC].Code == NONE) {
        error = "BPSP";
        return false;
      }

      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor == BLACK) {

        error = "BPR";
        return false;
      }
    }
    if (FR == 1) {
      if (nu > 2) {
        error = "BP2S";
        return false;
      }
    } else {

      if (nu > 1) {
        error = "BP1S";
        return false;
      }
    }
    if (FC == TC && Game.Board[TR][TC].Code != NONE) {
      error = "BPCS";
      return false;
    }

  }
  //White Pawns
  if (Game.Board[FR][FC].Code == PAWN && Game.Board[FR][FC].PieceColor == WHITE) {
    if (Game.TurningPlayer == WHITE) {

      if (vowe(Game, FR, FC, TR, TC) == false)

        return false;
    }

    //Enpassant Move from right (\)
    if (enpassant_black == 2) {
      if (TR == FR - 1 && TC == FC - 1 && Game.Board[TR][TC].Code == NONE) {
        capturedpieces_black[enpassant_capture_black] = Game.Board[TR + 1][TC].Code;
        Game.Board[TR + 1][TC].Code = NONE;
        enpassant_black = 0;
        enpassant_capture_black--;
        fiftymove_draw = 0;
        return true;
      }
    }
    //Enpassant Move from left(/)
    if (enpassant_black == 1 && Game.Board[TR][TC].Code == NONE) {
      if (TR == FR - 1 && TC == FC + 1) {
        capturedpieces_black[15] = Game.Board[TR + 1][TC].Code;
        Game.Board[TR + 1][TC].Code = NONE;
        enpassant_black = 0;
        fiftymove_draw = 0;
        return true;
      }
    }

    if (TR >= FR) {
      error = "WPR";
      return false;
    }
    if (lu > 1) {
      error = "WPD";
      return false;
    }
    if (FC != TC) {

      if (Game.Board[TR][TC].Code == NONE) {
        error = "WPC";
        return false;
      }

      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor == WHITE) {

        error = "WPROP";
        return false;
      }

    }
    if (FR == 6) {
      if (pu > 2) {
        error = "WP2S";
        return false;
      }
    } else {

      if (pu > 1) {
        error = "WP1S";
        return false;
      }

    }
    if (FC == TC && Game.Board[TR][TC].Code != NONE) {
      error = "WPCS";
      return false;
    }
  }

  //Black Rook
  if (Game.Board[FR][FC].Code == ROOK && Game.Board[FR][FC].PieceColor == BLACK) {

    /////////////////////////////CONDITION FOR IS FACING CHECK//////////////////////////////

    if (Game.TurningPlayer == BLACK) {

      if (vow(Game, FR, FC, TR, TC) == false)
        return false;
    }

    //For same column and rows
    if (TR == FR && TC == FC) {
      error = "BRSRC";
      return false;
    }

    //Horizontal Move

    if (TR == FR && TC != FC) {

      //Path is clear to right?
      if (FC < TC) {
        for (int i = FC + 1; i < TC; i++) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "BRPR";
            return false;
          }
        }
      }
      //Path is clear to left?

      if (FC > TC) {
        for (int i = FC - 1; i > TC; i--) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "BRPL";
            return false;
          }
        }
      }
      //Rook on Black piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
        error = "BRCOP";
        return false;
      }

      return true;

    }

    //Vertical Move
    if (TR != FR && TC == FC) {
      //Path is clear upwards?
      if (FR < TR) {
        for (int i = FR + 1; i < TR; i++) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "BRU";
            return false;
          }
        }
      }
      //Path is clear to down?

      if (FR > TR) {
        for (int i = FR - 1; i > TR; i--) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "BRD";
            return false;
          }
        }
      }
      //Rook On black piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
        error = "BRCOP2";
        return false;
      }

      return true;
    }

    //Rook Diagonal Move error
    else {
      error = "BRVH";
      return false;
    }

  }

  ////////////////////////////////////WHITE ROOK/////////////////////////////////////////////////////	 
  if (Game.Board[FR][FC].Code == ROOK && Game.Board[FR][FC].PieceColor == WHITE) {

    /////////////////////////////////////check condition//////////////////////////////////////////

    if (Game.TurningPlayer == WHITE) {

      if (vowe(Game, FR, FC, TR, TC) == false)
        return false;
    }
    //For same column and rows
    if (TR == FR && TC == FC) {
      error = "WRSRC";
      return false;
    }

    //Horizontal Move
    if (TR == FR && TC != FC) {

      //Path is clear to right?
      if (FC < TC) {
        for (int i = FC + 1; i < TC; i++) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "WRPR";
            return false;
          }
        }
      }
      //Path is clear to left?

      if (FC > TC) {
        for (int i = FC - 1; i > TC; i--) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "WRPL";
            return false;
          }
        }
      }

      //Rook on White piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
        error = "WRCOP";
        return false;
      }

      return true;

    }

    //Vertical Move
    if (TR != FR && TC == FC) {
      //Path is clear downwards?
      if (FR < TR) {
        for (int i = FR + 1; i < TR; i++) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "WRD";
            return false;
          }
        }
      }
      //Path is clear upwards?

      if (FR > TR) {
        for (int i = FR - 1; i > TR; i--) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "WRU";
            return false;
          }
        }
      }
      //Rook On white piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
        error = "WRCOP2";
        return false;
      }

      return true;
    }

    //Rook Diagonal Move error
    else {
      error = "WRVH";
      return false;
    }

  }

  ////////////////////////////////////BLACK KNIGHT/////////////////////////////////////////////////////	 
  if (Game.Board[FR][FC].Code == KNIGHT && Game.Board[FR][FC].PieceColor == BLACK) {
    ////////////////////CHECK CONDITION ///////////////////////
    if (Game.TurningPlayer == BLACK) {

      if (vow(Game, FR, FC, TR, TC) == false)
        return false;
    }

    if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
      error = "BKNCROP";
      return false;
    }

    if (TR == FR && TC == FC) {
      error = "BKNSRC";
      return false;
    }

    if (((TR - FR == 1) || (FR - TR == 1)) && ((FC - TC != 2) && (TC - FC != 2))) {
      error = "BKNCMS1";
      return false;
    } else {
      if (((TC - FC == 1) || (FC - TC == 1)) && ((FR - TR != 2) && (TR - FR != 2))) {
        error = "BKNCMS2";
        return false;
      } else {
        if (((FR - TR != 1) && (TR - FR != 1)) && ((FC - TC != 1) && (TC - FC != 1))) {
          error = "BKNCMS3";
          return false;
        } else {
          if ((FR == TR) || (FC == TC)) {
            error = "BKNCMS4";
            return false;
          } else {
            return true;
          }
        }
      }
    }
    return true;
  }
  ////////////////////////////////////WHITE KNIGHT/////////////////////////////////////////////////////	 
  if (Game.Board[FR][FC].Code == KNIGHT && Game.Board[FR][FC].PieceColor == WHITE) {

    if (Game.TurningPlayer == WHITE) {

      if (vowe(Game, FR, FC, TR, TC) == false)
        return false;
    }
    if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
      error = "WKNCROP";
      return false;
    }

    if (TR == FR && TC == FC) {
      error = "WKNSRC";
      return false;
    }

    if (((TR - FR == 1) || (FR - TR == 1)) && ((FC - TC != 2) && (TC - FC != 2))) {
      error = "WKNCMS1";
      return false;
    } else {
      if (((TC - FC == 1) || (FC - TC == 1)) && ((FR - TR != 2) && (TR - FR != 2))) {
        error = "WKNCMS2";
        return false;
      } else {
        if (((FR - TR != 1) && (TR - FR != 1)) && ((FC - TC != 1) && (TC - FC != 1))) {
          error = "WKNCMS3";
          return false;
        } else {
          if ((FR == TR) || (FC == TC)) {
            error = "WKNCMS4";
            return false;
          } else {
            return true;
          }
        }
      }
    }
    return true;
  }
  ///////////////////////////////////WHITE BISHOP/////////////////////////////////////////////////////	 
  if (Game.Board[FR][FC].Code == BISHOP && Game.Board[FR][FC].PieceColor == WHITE) {
    if (Game.TurningPlayer == WHITE) {

      if (vowe(Game, FR, FC, TR, TC) == false)
        return false;
    }
    //upward right
    if (FR - TR == TC - FC && FR > TR && TC > FC) {
      if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
        error = "WBCML1";
        return false;
      }
      for (int i = FR - 1, j = FC + 1; i > TR; i--, j++) {

        if (Game.Board[i][j].Code != NONE) {
          error = "WBCML2";
          return false;
        }
      }
      if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
        return true;
    } else {
      if (TR - FR == FC - TC && TR > FR && FC > TC) {
        if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
          error = "WBCML3";
          return false;
        }
        for (int i = FR + 1, j = FC - 1; i < TR; i++, j--) {

          if (Game.Board[i][j].Code != NONE) {
            error = "WBCML4";
            return false;
          }
        }
        if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
          return true;

      } else {
        if (FR - TR == FC - TC && FR > TR && FC > TC) {
          if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
            error = "WBCML5";
            return false;
          }
          for (int i = FR - 1, j = FC - 1; i > TR; i--, j--) {

            if (Game.Board[i][j].Code != NONE) {
              error = "WBCML6";
              return false;
            }
          }
          if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
            return true;
        } else {
          if (TR - FR == TC - FC && TR > FR && TC > FC) {
            if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
              error = "WBCML7";
              return false;
            }
            for (int i = FR + 1, j = FC + 1; i < TR; i++, j++) {

              if (Game.Board[i][j].Code != NONE) {
                error = "WBCML8";
                return false;
              }
            }
            if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
              return true;
          } else {
            error = "WBCML9";
            return false;
          }
        }
      }

    }

  }

  ////////////////////////////////////BLACK BISHOP/////////////////////////////////////////////////////	  
  if (Game.Board[FR][FC].Code == BISHOP && Game.Board[FR][FC].PieceColor == BLACK) {
    ////////////////////face chrck
    if (Game.TurningPlayer == BLACK) {

      if (vow(Game, FR, FC, TR, TC) == false)
        return false;
    }
    if (TR - FR == TC - FC && TR > FR && TC > FC) {
      if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
        error = "BBNES1";
        return false;

      }
      for (int i = FR + 1, j = FC + 1; i < TR; i++, j++) {

        if (Game.Board[i][j].Code != NONE) {
          error = "BBNES2";
          return false;
        }
      }
      if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
        return true;
    } else {
      if (FR - TR == FC - TC && FR > TR && FC > TC) {

        if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
          error = "BBNES3";
          return false;

        }

        for (int i = FR - 1, j = FC - 1; i > TR; i--, j--) {

          if (Game.Board[i][j].Code != NONE) {
            error = "BBNMP1";
            return false;
          }
        }
        if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
          return true;
      } else {
        if (TR - FR == FC - TC && TR > FR && FC > TC) {
          if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
            error = "BBNMP2";
            return false;
          }
          for (int i = FR + 1, j = FC - 1; i < TR; i++, j--) {

            if (Game.Board[i][j].Code != NONE) {
              error = "BBNMP3";
              return false;
            }
          }
          if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
            return true;

        } else {
          if (FR - TR == TC - FC && FR > TR && TC > FC) {

            if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
              error = "BBNMP4";
              return false;
            }
            for (int i = FR - 1, j = FC + 1; i > TR; i--, j++) {

              if (Game.Board[i][j].Code != NONE) {
                error = "BBNMP5";
                return false;
              }
            }
            if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
              return true;
          } else {
            error = "BBNMP6";
            return false;

          }

        }
      }

    }

  }

  ////////////////////////////////////WHITE KING/////////////////////////////////////////////////////
  if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == WHITE) {

    if (facechecke == 1) {
      if (Game.Board[TR][TC].Code == NONE) {

        Game.Board[TR][TC].Code = KING;
        Game.Board[TR][TC].PieceColor = WHITE;
        Game.Board[FR][FC].Code = NONE;

        isfacingCheck(Game, Move, Game.Board[TR][TC].PieceColor);

        if (facechecke == 1) {
          Game.Board[TR][TC].Code = NONE;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

          return false;
        }
        if (facechecke == 0) {
          Game.Board[TR][TC].Code = NONE;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
        }

      }

      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {

        return false;
      }

    }
    if (facechecke == 1) {

      if (Game.Board[TR][TC].Code != NONE) {

        int h;
        if (Game.Board[TR][TC].Code == PAWN) {

          h = 1;

        }
        if (Game.Board[TR][TC].Code == ROOK) {

          h = 2;

        }
        if (Game.Board[TR][TC].Code == BISHOP) {

          h = 3;

        }

        if (Game.Board[TR][TC].Code == KNIGHT) {

          h = 4;

        }
        if (Game.Board[TR][TC].Code == QUEEN) {

          h = 5;

        }

        if (Game.Board[TR][TC].Code == KING) {

          h = 6;
        }

        v = h;
      }

      Game.Board[TR][TC].Code = KING;
      Game.Board[TR][TC].PieceColor = WHITE;
      Game.Board[FR][FC].Code = NONE;

      isfacingCheck(Game, Move, Game.Board[TR][TC].PieceColor);

      if (facechecke == 0) {
        if (v == 1)

        {

          Game.Board[TR][TC].Code = PAWN;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }

        if (v == 2) {

          Game.Board[TR][TC].Code = ROOK;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }
        if (v == 3) {

          Game.Board[TR][TC].Code = BISHOP;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }
        if (v == 4) {

          Game.Board[TR][TC].Code = KNIGHT;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }
        if (v == 5) {

          Game.Board[TR][TC].Code = QUEEN;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }
        if (v == 6) {

          Game.Board[TR][TC].Code = KING;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }
      }
      if (facechecke == 1) {

        if (v == 1)

        {

          Game.Board[TR][TC].Code = PAWN;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }

        if (v == 2) {

          Game.Board[TR][TC].Code = ROOK;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }
        if (v == 3) {

          Game.Board[TR][TC].Code = BISHOP;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }
        if (v == 4) {

          Game.Board[TR][TC].Code = KNIGHT;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }
        if (v == 5) {

          Game.Board[TR][TC].Code = QUEEN;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }
        if (v == 6) {

          Game.Board[TR][TC].Code = KING;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }

      }

    }

    if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
      error = "WKCROP";
      return false;
    }
    ////////////////////Castling with Right Rook
    if (FR == 7 && FC == 4 && TR == 7 && TC == 6) {
      if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == WHITE && Game.Board[7][5].Code == NONE && Game.Board[7][6].Code == NONE && Game.Board[7][7].Code == ROOK && Game.Board[7][7].PieceColor == WHITE) {
        Game.Board[7][5].Code = ROOK;
        Game.Board[7][7].Code = NONE;
        return true;
      }
    }
    /////////////////////Castling with Left Rook
    if (FR == 7 && FC == 4 && TR == 7 && TC == 2) {
      if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == WHITE && Game.Board[7][3].Code == NONE && Game.Board[7][2].Code == NONE && Game.Board[7][1].Code == NONE && Game.Board[7][0].Code == ROOK && Game.Board[7][0].PieceColor == WHITE) {
        Game.Board[7][3].Code = ROOK;
        Game.Board[7][0].Code = NONE;
        return true;
      }
    }

    int rowscheck, colscheck;

    if (FC == TC && FR < TR) {
      rowscheck = TR - FR;
      if (rowscheck == 1) {
        return true;
      } else {
        error = "WKM1SD1";
        return false;
      }
    } else if (FC == TC && FR > TR) {
      rowscheck = FR - TR;
      if (rowscheck == 1) {
        return true;
      } else {
        error = "WKM1SD2";
        return false;
      }
    }

    if (FR == TR && FC < TC) {
      colscheck = TC - FC;
      if (colscheck == 1) {
        return true;
      } else {
        error = "WKM1SD3";
        return false;
      }
    } else if (FR == TR && FC > TC) {
      colscheck = FC - TC;
      if (colscheck == 1) {
        return true;
      } else {
        cout << "WKM1SD4";
        return false;
      }
    }

    if (FR > TR) {
      rowscheck = FR - TR;
    } else if (FR < TR) {
      rowscheck = TR - FR;

    }

    if (FC > TC) {
      colscheck = FC - TC;
    } else if (FC < TC) {
      colscheck = TC - FC;
    }

    if (colscheck == 1 && rowscheck == 1) {
      return true;
    } else {
      error = "WKM1SD5";
      return false;
    }

  }

  ////////////////////////////////////BLACK KING/////////////////////////////////////////////////////
  if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == BLACK) {

    if (facecheck == 2) {
      if (Game.Board[TR][TC].Code == NONE) {

        Game.Board[TR][TC].Code = KING;
        Game.Board[TR][TC].PieceColor = BLACK;
        Game.Board[FR][FC].Code = NONE;

        isfacingCheck(Game, Move, Game.Board[TR][TC].PieceColor);

        if (facecheck == 2) {
          Game.Board[TR][TC].Code = NONE;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          return false;
        }
        if (facecheck == 0) {
          Game.Board[TR][TC].Code = NONE;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
        }

      }

      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {

        return false;
      }

    }
    if (facecheck == 2) {

      if (Game.Board[TR][TC].Code != NONE) {

        int h;
        if (Game.Board[TR][TC].Code == PAWN) {

          h = 1;

        }
        if (Game.Board[TR][TC].Code == ROOK) {

          h = 2;

        }
        if (Game.Board[TR][TC].Code == BISHOP) {

          h = 3;

        }

        if (Game.Board[TR][TC].Code == KNIGHT) {

          h = 4;

        }
        if (Game.Board[TR][TC].Code == QUEEN) {

          h = 5;

        }

        if (Game.Board[TR][TC].Code == KING) {

          h = 6;
        }

        v = h;
      }

      Game.Board[TR][TC].Code = KING;
      Game.Board[TR][TC].PieceColor = BLACK;
      Game.Board[FR][FC].Code = NONE;

      isfacingCheck(Game, Move, Game.Board[TR][TC].PieceColor);

      if (facecheck == 0) {
        if (v == 1)

        {

          Game.Board[TR][TC].Code = PAWN;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }

        if (v == 2) {

          Game.Board[TR][TC].Code = ROOK;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }
        if (v == 3) {

          Game.Board[TR][TC].Code = BISHOP;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }
        if (v == 4) {

          Game.Board[TR][TC].Code = KNIGHT;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }
        if (v == 5) {

          Game.Board[TR][TC].Code = QUEEN;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }
        if (v == 6) {

          Game.Board[TR][TC].Code = KING;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }
      }
      if (facecheck == 2) {

        if (v == 1)

        {

          Game.Board[TR][TC].Code = PAWN;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }

        if (v == 2) {

          Game.Board[TR][TC].Code = ROOK;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }
        if (v == 3) {

          Game.Board[TR][TC].Code = BISHOP;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }
        if (v == 4) {

          Game.Board[TR][TC].Code = KNIGHT;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }
        if (v == 5) {

          Game.Board[TR][TC].Code = QUEEN;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }
        if (v == 6) {

          Game.Board[TR][TC].Code = KING;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }

      }

    }

    ////////////////////Castling with Right Rook
    if (FR == 0 && FC == 4 && TR == 0 && TC == 6) {
      if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == BLACK && Game.Board[0][5].Code == NONE && Game.Board[0][6].Code == NONE && Game.Board[0][7].Code == ROOK && Game.Board[0][7].PieceColor == BLACK) {
        Game.Board[0][5].Code = ROOK;
        Game.Board[0][7].Code = NONE;
        return true;
      }
    }
    /////////////////////Castling with Left Rook
    if (FR == 0 && FC == 4 && TR == 0 && TC == 2) {
      if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == BLACK && Game.Board[0][3].Code == NONE && Game.Board[0][2].Code == NONE && Game.Board[0][1].Code == NONE && Game.Board[0][0].Code == ROOK && Game.Board[0][0].PieceColor == BLACK) {
        Game.Board[0][3].Code = ROOK;
        Game.Board[0][0].Code = NONE;
        return true;
      }
    }
    if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
      error = "BKCROP";
      return false;
    }

    int rowscheck, colscheck;

    if (FC == TC && FR < TR) {
      rowscheck = TR - FR;
      if (rowscheck == 1) {
        return true;
      } else {
        error = "BKM1SD1";
        return false;
      }
    } else if (FC == TC && FR > TR) {
      rowscheck = FR - TR;
      if (rowscheck == 1) {
        return true;
      } else {
        error = "BKM1SD2";
        return false;
      }
    }

    if (FR == TR && FC < TC) {
      colscheck = TC - FC;
      if (colscheck == 1) {
        return true;
      } else {
        error = "BKM1SD3";
        return false;
      }
    } else if (FR == TR && FC > TC) {
      colscheck = FC - TC;
      if (colscheck == 1) {
        return true;
      } else {
        error = "BKM1SD4";
        return false;
      }
    }

    if (FR > TR) {
      rowscheck = FR - TR;
    } else if (FR < TR) {
      rowscheck = TR - FR;

    }

    if (FC > TC) {
      colscheck = FC - TC;
    } else if (FC < TC) {
      colscheck = TC - FC;
    }

    if (colscheck == 1 && rowscheck == 1) {
      return true;
    } else {
      error = "BKM1SD5";
      return false;
    }

  }

  ////////////////////////////////////WHITE QUEEN/////////////////////////////////////////////////////

  if (Game.Board[FR][FC].Code == QUEEN && Game.Board[FR][FC].PieceColor == WHITE) {
    if (Game.TurningPlayer == WHITE) {

      if (vowe(Game, FR, FC, TR, TC) == false)
        return false;
    }
    //Rook Moves

    //For same column and rows
    if (TR == FR && TC == FC) {
      error = "WQCMSRC";
      return false;
    }

    //Horizontal Move
    if (TR == FR && TC != FC) {

      //Path is clear to right?
      if (FC < TC) {
        for (int i = FC + 1; i < TC; i++) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "WQR";
            return false;
          }
        }
      }
      //Path is clear to left?

      if (FC > TC) {
        for (int i = FC - 1; i > TC; i--) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "WQL";
            return false;
          }
        }
      }

      //Rook on White piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {

        error = "WQCROP";
        return false;
      }

      return true;

    }

    //Vertical Move
    if (TR != FR && TC == FC) {
      //Path is clear downwards?
      if (FR < TR) {
        for (int i = FR + 1; i < TR; i++) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "WQD";
            return false;
          }
        }
      }
      //Path is clear upwards?

      if (FR > TR) {
        for (int i = FR - 1; i > TR; i--) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "WQU";
            return false;
          }
        }
      }
      //Rook On white piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
        error = "WQCROP2";
        return false;
      }

    }

    //Bishop Moves

    if (FR - TR == TC - FC && FR > TR && TC > FC) {
      if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
        error = "WQNML1";
        return false;
      }
      for (int i = FR - 1, j = FC + 1; i > TR; i--, j++) {

        if (Game.Board[i][j].Code != NONE) {
          error = "WQNML2";
          return false;
        }
      }
      if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
        return true;
    } else {
      if (TR - FR == FC - TC && TR > FR && FC > TC) {
        if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
          error = "WQNML3";
          return false;
        }
        for (int i = FR + 1, j = FC - 1; i < TR; i++, j--) {

          if (Game.Board[i][j].Code != NONE) {
            error = "WQNML4";
            return false;
          }
        }
        if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
          return true;

      } else {
        if (FR - TR == FC - TC && FR > TR && FC > TC) {
          if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
            error = "WQNML5";
            return false;
          }
          for (int i = FR - 1, j = FC - 1; i > TR; i--, j--) {

            if (Game.Board[i][j].Code != NONE) {
              error = "WQNML6";
              return false;
            }
          }
          if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
            return true;
        } else {
          if (TR - FR == TC - FC && TR > FR && TC > FC) {
            if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
              error = "WQNML7";
              return false;
            }
            for (int i = FR + 1, j = FC + 1; i < TR; i++, j++) {

              if (Game.Board[i][j].Code != NONE) {
                error = "WQNML8";
                return false;
              }
            }
            if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
              return true;
          } else {
            if (TR != FR && TC == FC) {
              //Path is clear downwards?
              if (FR < TR) {
                for (int i = FR + 1; i < TR; i++) {
                  if (Game.Board[i][TC].Code != NONE) {
                    error = "WQD2";
                    return false;
                  }
                }
              }
              //Path is clear upwards?

              if (FR > TR) {
                for (int i = FR - 1; i > TR; i--) {
                  if (Game.Board[i][TC].Code != NONE) {
                    error = "WQU2";
                    return false;
                  }
                }
              }
              //Rook On white piece
              if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
                error = "WQCROP3";
                return false;
              }

            } else {
              error = "WQNMVHD";
              return false;
            }
          }
        }
      }

    }

  }

  ////////////////////////////////////BLACK QUEEN/////////////////////////////////////////////////////
  if (Game.Board[FR][FC].Code == QUEEN && Game.Board[FR][FC].PieceColor == BLACK) {

    if (Game.TurningPlayer == BLACK) {

      if (vow(Game, FR, FC, TR, TC) == false)
        return false;
    }

    //Rook Moves

    //For same column and rows
    if (TR == FR && TC == FC) {
      error = "BQNMSRC";
      return false;
    }

    //Horizontal Move

    if (TR == FR && TC != FC) {

      //Path is clear to right?
      if (FC < TC) {
        for (int i = FC + 1; i < TC; i++) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "BQR";
            return false;
          }
        }
      }
      //Path is clear to left?

      if (FC > TC) {
        for (int i = FC - 1; i > TC; i--) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "BQL";
            return false;
          }
        }
      }
      //Rook on Black piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
        error = "BQNROP";
        return false;
      }

      return true;

    }

    //Vertical Move
    if (TR != FR && TC == FC) {
      //Path is clear upwards?
      if (FR < TR) {
        for (int i = FR + 1; i < TR; i++) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "BQU";
            return false;
          }
        }
      }
      //Path is clear to down?

      if (FR > TR) {
        for (int i = FR - 1; i > TR; i--) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "BQD";
            return false;
          }
        }
      }
      //Rook On black piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
        error = "BQNROP2";
        return false;
      }

    }

    //Bishop Moves

    if (TR - FR == TC - FC && TR > FR && TC > FC) {
      if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
        error = "BQNES1";
        return false;

      }
      for (int i = FR + 1, j = FC + 1; i < TR; i++, j++) {

        if (Game.Board[i][j].Code != NONE) {
          error = "BQNES2";
          return false;
        }
      }
      if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
        return true;
    } else {
      if (FR - TR == FC - TC && FR > TR && FC > TC) {

        if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
          error = "BQNES3";
          return false;

        }

        for (int i = FR - 1, j = FC - 1; i > TR; i--, j--) {

          if (Game.Board[i][j].Code != NONE) {
            error = "BQNML1";
            return false;
          }
        }
        if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
          return true;
      } else {
        if (TR - FR == FC - TC && TR > FR && FC > TC) {
          if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
            error = "BQNML2";
            return false;
          }
          for (int i = FR + 1, j = FC - 1; i < TR; i++, j--) {

            if (Game.Board[i][j].Code != NONE) {
              error = "BQNML3";
              return false;
            }
          }
          if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
            return true;

        } else {
          if (FR - TR == TC - FC && FR > TR && TC > FC) {

            if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
              error = "BQNML4";
              return false;
            }
            for (int i = FR - 1, j = FC + 1; i > TR; i--, j++) {

              if (Game.Board[i][j].Code != NONE) {
                error = "BQDNC";
                return false;
              }
            }
            if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
              return true;
          } else {
            if (TR != FR && TC == FC) {
              //Path is clear upwards?
              if (FR < TR) {
                for (int i = FR + 1; i < TR; i++) {
                  if (Game.Board[i][TC].Code != NONE) {
                    error = "BQU2";
                    return false;
                  }
                }
              }
              //Path is clear to down?

              if (FR > TR) {
                for (int i = FR - 1; i > TR; i--) {
                  if (Game.Board[i][TC].Code != NONE) {
                    error = "BQD2";
                    return false;
                  }
                }
              }
              //Rook On black piece
              if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
                error = "BQNROP3";
                return false;
              }

            } else {
              error = "BQNMVHD";
              return false;
            }

          }

        }
      }

    }

  }

  //Add new conditions here
  return true;
}

int MakeMove(GameData & Game, chessMove Move) {
  //Function to make a move on the board
  // It will return 0 if the move is valid and a code of error to specify why the move is not valid otherwise
  if (!isValidMove(Game, Move)) {
    return 1;
  }

  int FR, FC, TR, TC, k, s;
  FR = Move.FromRow;
  FC = Move.FromColumn;
  TR = Move.ToRow;
  TC = Move.ToColumn;
  k = FC;
  s = FR;
  ////////////////PIECE CAPTURE////////////
  if (Game.Board[FR][FC].PieceColor == WHITE && Game.Board[TR][TC].PieceColor == BLACK) {
    capturedpieces_black[p1] = Game.Board[TR][TC].Code;
    fiftymove_draw = 0;
    p1++;
  }
  if (Game.Board[FR][FC].PieceColor == BLACK && Game.Board[TR][TC].PieceColor == WHITE) {
    capturedpieces_white[p2] = Game.Board[TR][TC].Code;
    fiftymove_draw = 0;
    p2++;
  }
  /////////////ENPASSANT ON WHITE PAWN/////////////////
  if (Game.Board[FR][FC].Code == PAWN && Game.Board[FR][FC].PieceColor == WHITE) {
    fiftymove_draw = 0;
    if (FR == 6 && TR == 4 && FC == TC) {
      //LEFT ENPASSANT
      if (Game.Board[TR][TC - 1].Code == PAWN && Game.Board[TR][TC - 1].PieceColor == BLACK) {
        enpassant_white = 2;
      }

      //RIGHT ENPASSANT
      if (Game.Board[TR][TC + 1].Code == PAWN && Game.Board[TR][TC + 1].PieceColor == BLACK) {
        enpassant_white = 1;
      }
    }
  }
  ////////////ENPASSANT ON BLACK PAWN/////////////////
  if (Game.Board[FR][FC].Code == PAWN && Game.Board[FR][FC].PieceColor == BLACK) {
    fiftymove_draw = 0;
    if (FR == 1 && TR == 3 && FC == TC) {
      //LEFT ENPASSANT
      if (Game.Board[TR][TC - 1].Code == PAWN && Game.Board[TR][TC - 1].PieceColor == WHITE) {
        enpassant_black = 1;
      }

      //RIGHT ENPASSANT
      if (Game.Board[TR][TC + 1].Code == PAWN && Game.Board[TR][TC + 1].PieceColor == WHITE) {
        enpassant_black = 2;
      }
    }
  }
  //////////////////PAWN PROMOTE////////////////////
  if (TR == 7 && Game.Board[FR][FC].Code == PAWN) {
    if (Game.Board[FR][FC].PieceColor == BLACK)
      PromotePawn(Game, Move);
  }

  if (TR == 0 && Game.Board[FR][FC].Code == PAWN) {
    if (Game.Board[FR][FC].PieceColor == WHITE) {
      PromotePawn(Game, Move);
    }
  }

  Game.Board[TR][TC].Code =
    Game.Board[FR][FC].Code;
  Game.Board[TR][TC].PieceColor =
    Game.Board[FR][FC].PieceColor;

  Game.Board[FR][FC].Code = NONE;
  fiftymove_draw++;
  isfacingCheck(Game, Move, Game.Board[TR][TC].PieceColor);

  if (Game.TurningPlayer == BLACK) {
    system("Color 70");
    Game.TurningPlayer = WHITE;
  } else {
    system("Color 07");
    Game.TurningPlayer = BLACK;
  }
  string X = to_string(i);
  saveGame(Game, "hassan" + X + ".txt");

  y = i - 1;
  i++;

  return 0;
}

void initGame(GameData & Game) {

  for (int i = 0; i < 16; i++) {
    capturedpieces_black[i] = 0;
  }
  for (int i = 0; i < 16; i++) {
    capturedpieces_white[i] = 0;
  }
  for (int r = 0; r < 2; r++)
    for (int c = 0; c < 8; c++)
      Game.Board[r][c].PieceColor = BLACK;

  for (int r = 2; r < 6; r++)
    for (int c = 0; c < 8; c++)
      Game.Board[r][c].Code = NONE;

  for (int r = 6; r < 8; r++)
    for (int c = 0; c < 8; c++)
      Game.Board[r][c].PieceColor = WHITE;

  Game.Board[0][0].Code = Game.Board[0][7].Code = ROOK;
  Game.Board[7][0].Code = Game.Board[7][7].Code = ROOK;

  Game.Board[0][1].Code = Game.Board[0][6].Code = KNIGHT;
  Game.Board[7][1].Code = Game.Board[7][6].Code = KNIGHT;

  Game.Board[0][2].Code = Game.Board[0][5].Code = BISHOP;
  Game.Board[7][2].Code = Game.Board[7][5].Code = BISHOP;

  Game.Board[0][3].Code = Game.Board[7][3].Code = QUEEN;
  Game.Board[0][4].Code = Game.Board[7][4].Code = KING;

  for (int c = 0; c < 8; c++)
    Game.Board[1][c].Code = Game.Board[6][c].Code = PAWN;

  Game.TurningPlayer = WHITE;

  return;
}

void isfacingCheck(GameData & Game, chessMove Move, Color Player) {

  facecheck = 0;
  facechecke = 0;
  int k = 0, l = 0, q = 0, r = 0;
  int FR, FC, TR, TC;
  FR = Move.FromRow;
  FC = Move.FromColumn;
  TR = Move.ToRow;
  TC = Move.ToColumn;

  //New Conditions Here
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (Game.Board[i][j].Code == KING && Game.Board[i][j].PieceColor == BLACK) {
        k = i;
        l = j;
      }

    }
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (Game.Board[i][j].Code == KING && Game.Board[i][j].PieceColor == WHITE) {
        q = i;
        r = j;
      }

    }
  }

  /////////////////////////////////////BLACK KING THROUGH QUEEN AND ROOK//////////////////////////////////
  for (int m = k + 1, n = l; m < 8; m++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facecheck = 2;
        break;
      }

    }

  }
  for (int m = k - 1, n = l; m >= 0; m--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facecheck = 2;
        break;
      }

    }

  }
  for (int m = k, n = l + 1; n < 8; n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facecheck = 2;
        break;
      }

    }

  }
  for (int m = k, n = l - 1; n >= 0; n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facecheck = 2;
        break;
      }

    }

  }

  for (int m = k, n = l - 1; n >= 0; n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN && Game.Board[m][n].PieceColor == WHITE || Game.Board[m][n].Code == ROOK) {
        facecheck = 2;
        break;
      }

    }

  }

  ////////////////////////////////////////////white king through rook and queen////////////////////////////////////////////////////

  for (int m = q + 1, n = r; m < 8; m++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facechecke = 1;
        break;
      }

    }

  }
  for (int m = q - 1, n = r; m >= 0; m--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facechecke = 1;
        break;
      }

    }

  }
  for (int m = q, n = r + 1; n < 8; n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facechecke = 1;
        break;
      }

    }

  }
  for (int m = q, n = r - 1; n >= 0; n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facechecke = 1;
        break;
      }

    }

  }

  for (int m = q, n = r - 1; n >= 0; n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN && Game.Board[m][n].PieceColor == WHITE || Game.Board[m][n].Code == ROOK) {
        facechecke = 1;
        break;
      }

    }

  }

  /////////////////////////////////////////BLACK KING THROUGH BISHOP AND QUEEN//////////////////////////////
  /////down  (/)

  for (int m = k + 1, n = l - 1; n >= 0, m < 8; m++, n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facecheck = 2;
        break;
      }

    }

  }

  /////down  (\)
  for (int m = k + 1, n = l + 1; n < 8, m < 8; m++, n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facecheck = 2;
        break;
      }

    }

  }

  /////up (/)///////

  for (int m = k - 1, n = l + 1; n < 8, m >= 0; m--, n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facecheck = 2;
        break;
      }

    }

  }

  /////up (\)///////

  for (int m = k - 1, n = l - 1; n >= 0, m >= 0; m--, n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facecheck = 2;
        break;
      }

    }

  }

  ////////////////////////////////////(white king through queen and bishop)//////////////////////////

  for (int m = q + 1, n = r - 1; n >= 0, m < 8; m++, n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facechecke = 1;
        break;
      }

    }

  }

  /////down  (\)
  for (int m = q + 1, n = r + 1; n < 8, m < 8; m++, n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facechecke = 1;
        break;
      }

    }

  }

  /////up (/)///////

  for (int m = q - 1, n = r + 1; n < 8, m >= 0; m--, n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facechecke = 1;
        break;
      }

    }

  }

  /////up (\)///////

  for (int m = q - 1, n = r - 1; n >= 0, m >= 0; m--, n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facechecke = 1;
        break;
      }

    }

  }

  ////////////////////black king through pawn////////////////////////////

  for (int m = k + 1, n = l + 1; m <= k + 1; m++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != PAWN && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == PAWN) {
        facecheck = 2;
        break;
      }

    }

  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////

  for (int m = k + 1, n = l - 1; m >= k - 1; m--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != PAWN && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == PAWN) {
        facecheck = 2;
        break;
      }

    }

  }

  ////////////////////WHITE king through pawn////////////////////////////

  for (int m = q - 1, n = r + 1; n <= r + 1; n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != PAWN && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == PAWN) {
        facechecke = 1;
        break;
      }

    }

  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////

  for (int m = q - 1, n = r - 1; m <= q - 1; m++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != PAWN && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == PAWN) {
        facechecke = 1;
        break;
      }

    }

  }

  //////////////////////////////WHITE KING THROUGH KNIGHT///////////////////////////////////////////////////

  if (q + 2 < 8 && r + 1 < 8) {

    if (Game.Board[q + 2][r + 1].Code == KNIGHT && Game.Board[q + 2][r + 1].PieceColor == BLACK) {
      facechecke = 1;

    }

  }

  if (q - 2 >= 0 && r + 1 < 8) {

    if (Game.Board[q - 2][r + 1].Code == KNIGHT && Game.Board[q - 2][r + 1].PieceColor == BLACK) {
      facechecke = 1;

    }

  }
  if (q - 2 >= 0 && r - 1 >= 0) {

    if (Game.Board[q - 2][r - 1].Code == KNIGHT && Game.Board[q - 2][r - 1].PieceColor == BLACK) {
      facechecke = 1;

    }

  }
  if (q + 2 < 8 && r - 1 >= 0) {

    if (Game.Board[q + 2][r - 1].Code == KNIGHT && Game.Board[q + 2][r - 1].PieceColor == BLACK) {
      facechecke = 1;

    }

  }
  if (q + 1 < 8 && r + 2 < 8) {

    if (Game.Board[q + 1][r + 2].Code == KNIGHT && Game.Board[q + 1][r + 2].PieceColor == BLACK) {
      facechecke = 1;

    }

  }
  if (q + 1 < 8 && r - 2 >= 0) {

    if (Game.Board[q + 1][r - 2].Code == KNIGHT && Game.Board[q + 1][r - 2].PieceColor == BLACK) {
      facecheck = 2;

    }

  }
  if (q - 1 >= 0 && r + 2 < 8) {

    if (Game.Board[q - 1][r + 2].Code == KNIGHT && Game.Board[q - 1][r + 2].PieceColor == BLACK) {
      facechecke = 1;

    }

  }

  if (q - 1 >= 0 && r - 2 >= 0) {

    if (Game.Board[q - 1][r - 2].Code == KNIGHT && Game.Board[q - 1][r - 2].PieceColor == BLACK) {
      facechecke = 1;

    }

  }

  if (q - 1 >= 0 && r + 2 < 8) {

    if (Game.Board[q - 1][r + 2].Code == KNIGHT && Game.Board[q - 1][r + 2].PieceColor == BLACK) {
      facechecke = 1;

    }

  }

  //////////////////////////////BLACK KING THROUGH KNIGHT///////////////////////////////////////////////////
  //1 column left and 2 rows upward from king

  if (k + 2 < 8 && l + 1 < 8) {

    if (Game.Board[k + 2][l + 1].Code == KNIGHT && Game.Board[k + 2][l + 1].PieceColor == WHITE) {
      facecheck = 2;

    }

  }

  if (k - 2 >= 0 && l + 1 < 8) {

    if (Game.Board[k - 2][l + 1].Code == KNIGHT && Game.Board[k - 2][l + 1].PieceColor == WHITE) {
      facecheck = 2;

    }

  }
  if (k - 2 >= 0 && l - 1 >= 0) {

    if (Game.Board[k - 2][l - 1].Code == KNIGHT && Game.Board[k - 2][l - 1].PieceColor == WHITE) {
      facecheck = 2;

    }

  }
  if (k + 2 < 8 && l - 1 >= 0) {

    if (Game.Board[k + 2][l - 1].Code == KNIGHT && Game.Board[k + 2][l - 1].PieceColor == WHITE) {
      facecheck = 2;

    }

  }
  if (k + 1 < 8 && l + 2 < 8) {

    if (Game.Board[k + 1][l + 2].Code == KNIGHT && Game.Board[k + 1][l + 2].PieceColor == WHITE) {
      facecheck = 2;

    }

  }

  if (k + 1 < 8 && l - 2 >= 0) {

    if (Game.Board[k + 1][l - 2].Code == KNIGHT && Game.Board[k + 1][l - 2].PieceColor == WHITE) {
      facecheck = 2;

    }

  }
  if (k - 1 >= 0 && l + 2 < 8) {

    if (Game.Board[k - 1][l + 2].Code == KNIGHT && Game.Board[k - 1][l + 2].PieceColor == WHITE) {
      facecheck = 2;
    }

  }

  if (k - 1 >= 0 && l - 2 >= 0) {

    if (Game.Board[k - 1][l - 2].Code == KNIGHT && Game.Board[k - 1][l - 2].PieceColor == WHITE) {
      facecheck = 2;

    }

  }

  if (k - 1 >= 0 && l + 2 < 8) {

    if (Game.Board[k - 1][l + 2].Code == KNIGHT && Game.Board[k - 1][l + 2].PieceColor == WHITE) {
      facecheck = 2;

    }

  }

  return;
}
int saveGame(GameData & Game, string File_Name) {
  string extension;
  //Extracting File extension
  extension = File_Name.substr(File_Name.find('.') + 1);

  ofstream save(File_Name.c_str());

  //Error in file
  if (save.fail()) {
    error = "EOP";
    return 2;
  }

  if (extension == "txt") {

    for (int i = 0; i < 8; i++) {

      for (int j = 0; j < 8; j++) {

        save << Game.Board[i][j].Code << " ";

      }
      save << endl;
    }
    cout << endl;
    for (int i = 9, k = 0; i <= 16; i++, k++) {

      for (int j = 0, l = 0; j < 8; j++, l++) {

        save << Game.Board[k][l].PieceColor << " ";

      }
      save << endl;

    }
    save << Game.TurningPlayer;
    save << endl;
    save << player1;
    save << endl;
    save << player2;
    save << endl;
    for (int i = 0; i < 16; i++)
      save << capturedpieces_black[i];
    save << endl;
    for (int i = 0; i < 16; i++)
      save << capturedpieces_white[i];
    save.close();
    return 0;
  }

  //Error in extension
  else {
    error = "IFE";
    return 1;
  }
}

int loadGame(GameData & Game, string File_Name) {
  string hassan[8][8];
  string extension;
  //Extracting File extension
  extension = File_Name.substr(File_Name.find('.') + 1);

  ifstream read(File_Name.c_str());

  //Error in file
  if (read.fail()) {
    error = "CRF";
    return 2;
  }

  if (extension == "txt") {
    for (int i = 0; i < 8; i++) {

      for (int j = 0; j < 8; j++) {

        read >> File_Name;
        hassan[i][j] = File_Name;
        if (File_Name == "1")
          Game.Board[i][j].Code = PAWN;

        if (File_Name == "0")
          Game.Board[i][j].Code = NONE;

        if (File_Name == "2")
          Game.Board[i][j].Code = ROOK;

        if (File_Name == "3")
          Game.Board[i][j].Code = BISHOP;

        if (File_Name == "4")
          Game.Board[i][j].Code = KNIGHT;

        if (File_Name == "5")
          Game.Board[i][j].Code = QUEEN;

        if (File_Name == "6")
          Game.Board[i][j].Code = KING;

      }
      cout << endl;
    }
    for (int i = 9, k = 0; i <= 16; i++, k++) {

      for (int j = 0, l = 0; j < 8; j++, l++) {

        read >> File_Name;
        if (File_Name == "0")
          Game.Board[k][l].PieceColor = BLACK;

        if (File_Name == "1")
          Game.Board[k][l].PieceColor = WHITE;
      }
    }
    read >> File_Name;
    if (File_Name == "0")
      Game.TurningPlayer = BLACK;

    if (File_Name == "1")
      Game.TurningPlayer = WHITE;

    read >> player1;
    read >> player2;

    read.close();
    return 0;

  }
  //Error in extension
  else {
    error = "IFE2";
    return 1;
  }
}

bool isCheckmate(GameData & Game, Color Player) {

  int i, p, l, r, s;
  if (facecheck == 2) {

    for (int k = 0; k < 8; k++) {
      for (int j = 0; j < 8; j++) {
        if (Game.Board[k][j].Code == KING && Game.Board[k][j].PieceColor == BLACK) {
          r = k;
          s = j;
          break;
        }
      }

    }

    ///////////////////////////////////king check//////////////////////////////
    if (r + 1 < 8) {
      if (isValideeMove(Game, r, s, r + 1, s) == true) {

        pp++;

      }
    }
    if (r - 1 >= 0) {
      if (isValideeMove(Game, r, s, r - 1, s) == true) {

        pp++;

      }
    }
    if (s + 1 < 8) {
      if (isValideeMove(Game, r, s, r, s + 1) == true) {

        pp++;

      }
    }
    if (s - 1 >= 0) {
      if (isValideeMove(Game, r, s, r, s - 1) == true) {

        pp++;

      }
    }
    if (r + 1 < 8 && s + 1 < 8) {
      if (isValideeMove(Game, r, s, r + 1, s + 1) == true) {

        pp++;

      }
    }
    if (r - 1 >= 0 && s + 1 < 8) {
      if (isValideeMove(Game, r, s, r - 1, s + 1) == true) {

        pp++;

      }
    }
    if (r - 1 >= 0 && s - 1 >= 0) {
      if (isValideeMove(Game, r, s, r - 1, s - 1) == true) {

        pp++;

      }
    }
    if (r + 1 < 8 && s - 1 >= 0) {

      if (isValideeMove(Game, r, s, r + 1, s - 1) == true) {

        pp++;

      }
    }
    if (pp >= 1) {
      pp = 0;
      return false;
    }

    //////////////////////////////////roook///////////position and check/////////////////////////
    for (int k = 0; k < 8; k++) {
      for (int j = 0; j < 8; j++) {
        if (Game.Board[k][j].Code == ROOK && Game.Board[k][j].PieceColor == BLACK) {
          p = k;
          l = j;

        }
        /////////Diagonal//////Up//////Right
        for (int k = r, oi = s; k < 8, oi < 8; k++, oi++) {
          if (isValideeMove(Game, p, l, k, oi) == true) {

            pp++;

          }
        }

        /////////Diagonal
        for (int k = r, oi = s; k < 8, oi >= 0; k++, oi--) {
          if (isValideeMove(Game, p, l, k, oi) == true) {

            pp++;

          }
        }

        for (int k = r, oi = s; k >= 0, oi >= 0; k--, oi--) {

          if (isValideeMove(Game, p, l, k, oi) == true) {

            pp++;

          }

        }

        for (int k = r, oi = s; k >= 0, oi < 8; k--, oi++) {

          if (isValideeMove(Game, p, l, k, oi) == true) {

            pp++;

          }

        }

        /////vertical//////QUEEN////////check//////////
        for (int k = r; k < 8; k++) {
          if (isValideeMove(Game, p, l, k, s) == true) {
            pp++;

          }
        }

        /////vertical//////up////////check//////////
        for (int k = r; k >= 0; k--) {
          if (isValideeMove(Game, p, l, k, s) == true) {
            pp++;
          }
        }
        ///////Horizontal Left////////////
        for (int k = s; k >= 0; k--) {
          if (isValideeMove(Game, p, l, r, k) == true) {
            pp++;
          }
        }
        ///////Horizontal Right////////////
        for (int k = s; k < 8; k++) {
          if (isValideeMove(Game, p, l, r, k) == true) {
            pp++;
          }
        }

        if (pp >= 1) {
          pp = 0;
          return false;
        }

      }

    }

    ///////////////////////////////////////bishop/////////////////////////////////////////
    for (int k = 0; k < 8; k++) {
      for (int j = 0; j < 8; j++) {
        if (Game.Board[k][j].Code == BISHOP && Game.Board[k][j].PieceColor == BLACK) {
          p = k;
          l = j;
        }

        /////////Diagonal//////Up//////Right
        for (int k = r, oi = s; k < 8, oi < 8; k++, oi++) {
          if (isValideeMove(Game, p, l, k, oi) == true) {

            pp++;

          }
        }

        /////////Diagonal
        for (int k = r, oi = s; k < 8, oi >= 0; k++, oi--) {
          if (isValideeMove(Game, p, l, k, oi) == true) {

            pp++;

          }
        }

        for (int k = r, oi = s; k >= 0, oi >= 0; k--, oi--) {

          if (isValideeMove(Game, p, l, k, oi) == true) {

            pp++;

          }

        }

        for (int k = r, oi = s; k >= 0, oi < 8; k--, oi++) {

          if (isValideeMove(Game, p, l, k, oi) == true) {

            pp++;

          }

        }

        /////vertical//////QUEEN////////check//////////
        for (int k = r; k < 8; k++) {
          if (isValideeMove(Game, p, l, k, s) == true) {
            pp++;

          }
        }

        /////vertical//////up////////check//////////
        for (int k = r; k >= 0; k--) {
          if (isValideeMove(Game, p, l, k, s) == true) {
            pp++;
          }
        }
        ///////Horizontal Left////////////
        for (int k = s; k >= 0; k--) {
          if (isValideeMove(Game, p, l, r, k) == true) {
            pp++;
          }
        }
        ///////Horizontal Right////////////
        for (int k = s; k < 8; k++) {
          if (isValideeMove(Game, p, l, r, k) == true) {
            pp++;
          }
        }

        if (pp >= 1) {
          pp = 0;
          return false;
        }

      }

      ///////////////////////////////////////QUEEN/////////////////////////////////////////
      for (int k = 0; k < 8; k++) {
        for (int j = 0; j < 8; j++) {
          if (Game.Board[k][j].Code == QUEEN && Game.Board[k][j].PieceColor == BLACK) {
            p = k;
            l = j;
          }

          /////////Diagonal//////Up//////Right
          for (int k = r, oi = s; k < 8, oi < 8; k++, oi++) {
            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }
          }

          /////////Diagonal
          for (int k = r, oi = s; k < 8, oi >= 0; k++, oi--) {
            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }
          }

          for (int k = r, oi = s; k >= 0, oi >= 0; k--, oi--) {

            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }

          }

          for (int k = r, oi = s; k >= 0, oi < 8; k--, oi++) {

            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }

          }

          /////vertical//////QUEEN////////check//////////
          for (int k = r; k < 8; k++) {
            if (isValideeMove(Game, p, l, k, s) == true) {
              pp++;

            }
          }

          /////vertical//////up////////check//////////
          for (int k = r; k >= 0; k--) {
            if (isValideeMove(Game, p, l, k, s) == true) {
              pp++;
            }
          }
          ///////Horizontal Left////////////
          for (int k = s; k >= 0; k--) {
            if (isValideeMove(Game, p, l, r, k) == true) {
              pp++;
            }
          }
          ///////Horizontal Right////////////
          for (int k = s; k < 8; k++) {
            if (isValideeMove(Game, p, l, r, k) == true) {
              pp++;
            }
          }

          if (pp >= 1) {
            pp = 0;
            return false;
          }

        }

      }

      ////////////////////////////////pawn/////////////////////////////////////////////
      for (int k = 0; k < 8; k++) {
        for (int j = 0; j < 8; j++) {
          if (Game.Board[k][j].Code == PAWN && Game.Board[k][j].PieceColor == BLACK) {
            p = k;
            l = j;
          }

          /////////Diagonal//////Up//////Right
          for (int k = r, oi = s; k < 8, oi < 8; k++, oi++) {
            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }
          }

          /////////Diagonal
          for (int k = r, oi = s; k < 8, oi >= 0; k++, oi--) {
            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }
          }

          for (int k = r, oi = s; k >= 0, oi >= 0; k--, oi--) {

            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }

          }

          for (int k = r, oi = s; k >= 0, oi < 8; k--, oi++) {

            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }

          }

          /////vertical//////QUEEN////////check//////////
          for (int k = r; k < 8; k++) {
            if (isValideeMove(Game, p, l, k, s) == true) {
              pp++;

            }
          }

          /////vertical//////up////////check//////////
          for (int k = r; k >= 0; k--) {
            if (isValideeMove(Game, p, l, k, s) == true) {
              pp++;
            }
          }
          ///////Horizontal Left////////////
          for (int k = s; k >= 0; k--) {
            if (isValideeMove(Game, p, l, r, k) == true) {
              pp++;
            }
          }
          ///////Horizontal Right////////////
          for (int k = s; k < 8; k++) {
            if (isValideeMove(Game, p, l, r, k) == true) {
              pp++;
            }
          }

          if (pp >= 1) {
            pp = 0;
            return false;
          }

        }

      }
      /////////////////////////////////////////knight //////////////////////////////////
      for (int k = 0; k < 8; k++) {
        for (int j = 0; j < 8; j++) {
          if (Game.Board[k][j].Code == KNIGHT && Game.Board[k][j].PieceColor == BLACK) {
            p = k;
            l = j;
          }

          /////////Diagonal//////Up//////Right
          for (int k = r, oi = s; k < 8, oi < 8; k++, oi++) {
            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }
          }

          /////////Diagonal
          for (int k = r, oi = s; k < 8, oi >= 0; k++, oi--) {
            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }
          }

          for (int k = r, oi = s; k >= 0, oi >= 0; k--, oi--) {

            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }

          }

          for (int k = r, oi = s; k >= 0, oi < 8; k--, oi++) {

            if (isValideeMove(Game, p, l, k, oi) == true) {

              pp++;

            }

          }

          /////vertical//////QUEEN////////check//////////
          for (int k = r; k < 8; k++) {
            if (isValideeMove(Game, p, l, k, s) == true) {
              pp++;

            }
          }

          /////vertical//////up////////check//////////
          for (int k = r; k >= 0; k--) {
            if (isValideeMove(Game, p, l, k, s) == true) {
              pp++;
            }
          }
          ///////Horizontal Left////////////
          for (int k = s; k >= 0; k--) {
            if (isValideeMove(Game, p, l, r, k) == true) {
              pp++;
            }
          }
          ///////Horizontal Right////////////
          for (int k = s; k < 8; k++) {
            if (isValideeMove(Game, p, l, r, k) == true) {
              pp++;
            }
          }

          if (pp >= 1) {
            pp = 0;
            return false;
          }

        }

      }

    }
    return true;
  }
  int t, y, u, o, v;

  if (facechecke == 1) {

    for (int k = 0; k < 8; k++) {
      for (int j = 0; j < 8; j++) {
        if (Game.Board[k][j].Code == KING && Game.Board[k][j].PieceColor == WHITE) {
          o = k;
          v = j;
          break;
        }
      }
    }

    ///////////////////////////////////king check//////////////////////////////
    if (o + 1 < 8) {
      if (isValideeMove(Game, o, v, o + 1, v) == true) {

        pp_wh++;

      }
    }
    if (o - 1 >= 0) {
      if (isValideeMove(Game, o, v, o - 1, v) == true) {

        pp_wh++;

      }
    }
    if (v + 1 < 8) {
      if (isValideeMove(Game, o, v, o, v + 1) == true) {

        pp_wh++;

      }
    }
    if (v - 1 >= 0) {
      if (isValideeMove(Game, o, v, o, v - 1) == true) {

        pp_wh++;

      }
    }
    if (o + 1 < 8 && v + 1 < 8) {
      if (isValideeMove(Game, o, v, o + 1, v + 1) == true) {

        pp_wh++;

      }
    }
    if (o - 1 >= 0 && v + 1 < 8) {
      if (isValideeMove(Game, o, v, o - 1, v + 1) == true) {

        pp_wh++;

      }
    }
    if (o - 1 >= 0 && v - 1 >= 0) {
      if (isValideeMove(Game, o, v, o - 1, v - 1) == true) {

        pp_wh++;

      }
    }
    if (o + 1 < 8 && v - 1 >= 0) {

      if (isValideeMove(Game, o, v, o + 1, v - 1) == true) {

        pp_wh++;

      }
    }
    if (pp_wh >= 1) {
      pp_wh = 0;
      return false;
    }

    //////////////////////////////////roook///////////position and check/////////////////////////
    for (int k = 0; k < 8; k++) {
      for (int j = 0; j < 8; j++) {
        if (Game.Board[k][j].Code == ROOK && Game.Board[k][j].PieceColor == WHITE) {
          y = k;
          u = j;

        }
        /////////Diagonal//////Up//////Right
        for (int k = o, oi = v; k < 8, oi < 8; k++, oi++) {
          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }
        }

        /////////Diagonal
        for (int k = o, oi = v; k < 8, oi >= 0; k++, oi--) {
          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }
        }

        for (int k = o, oi = v; k >= 0, oi >= 0; k--, oi--) {

          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }

        }

        for (int k = o, oi = v; k >= 0, oi < 8; k--, oi++) {

          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }

        }

        /////vertical//////QUEEN////////check//////////
        for (int k = o; k < 8; k++) {
          if (isValideeMove(Game, y, u, k, v) == true) {
            pp_wh++;

          }
        }

        /////vertical//////up////////check//////////
        for (int k = o; k >= 0; k--) {
          if (isValideeMove(Game, y, u, k, v) == true) {
            pp_wh++;
          }
        }
        ///////Horizontal Left////////////
        for (int k = v; k >= 0; k--) {
          if (isValideeMove(Game, y, u, o, k) == true) {
            pp_wh++;
          }
        }
        ///////Horizontal Right////////////
        for (int k = v; k < 8; k++) {
          if (isValideeMove(Game, y, u, o, k) == true) {
            pp_wh++;
          }
        }

        if (pp_wh >= 1) {
          pp_wh = 0;
          return false;
        }

      }

    }

    ///////////////////////////////////////bishop/////////////////////////////////////////
    for (int k = 0; k < 8; k++) {
      for (int j = 0; j < 8; j++) {
        if (Game.Board[k][j].Code == BISHOP && Game.Board[k][j].PieceColor == WHITE) {
          y = k;
          u = j;
        }

        /////////Diagonal//////Up//////Right
        for (int k = o, oi = v; k < 8, oi < 8; k++, oi++) {
          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }
        }

        /////////Diagonal
        for (int k = o, oi = v; k < 8, oi >= 0; k++, oi--) {
          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }
        }

        for (int k = o, oi = v; k >= 0, oi >= 0; k--, oi--) {

          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }

        }

        for (int k = o, oi = v; k >= 0, oi < 8; k--, oi++) {

          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }

        }

        /////vertical//////QUEEN////////check//////////
        for (int k = o; k < 8; k++) {
          if (isValideeMove(Game, y, u, k, v) == true) {
            pp_wh++;

          }
        }

        /////vertical//////up////////check//////////
        for (int k = o; k >= 0; k--) {
          if (isValideeMove(Game, y, u, k, v) == true) {
            pp_wh++;
          }
        }
        ///////Horizontal Left////////////
        for (int k = v; k >= 0; k--) {
          if (isValideeMove(Game, y, u, o, k) == true) {
            pp_wh++;
          }
        }
        ///////Horizontal Right////////////
        for (int k = v; k < 8; k++) {
          if (isValideeMove(Game, y, u, o, k) == true) {
            pp_wh++;
          }
        }

        if (pp_wh >= 1) {
          pp_wh = 0;
          return false;
        }

      }
    }

    ///////////////////////////////////////QUEEN/////////////////////////////////////////
    for (int k = 0; k < 8; k++) {
      for (int j = 0; j < 8; j++) {
        if (Game.Board[k][j].Code == QUEEN && Game.Board[k][j].PieceColor == WHITE) {
          y = k;
          u = j;
        }

        /////////Diagonal//////Up//////Right
        for (int k = o, oi = v; k < 8, oi < 8; k++, oi++) {
          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }
        }

        /////////Diagonal
        for (int k = o, oi = v; k < 8, oi >= 0; k++, oi--) {
          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }
        }

        for (int k = o, oi = v; k >= 0, oi >= 0; k--, oi--) {

          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }

        }

        for (int k = o, oi = v; k >= 0, oi < 8; k--, oi++) {

          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }

        }

        /////vertical//////QUEEN////////check//////////
        for (int k = o; k < 8; k++) {
          if (isValideeMove(Game, y, u, k, v) == true) {
            pp_wh++;

          }
        }

        /////vertical//////up////////check//////////
        for (int k = o; k >= 0; k--) {
          if (isValideeMove(Game, y, u, k, v) == true) {
            pp_wh++;
          }
        }
        ///////Horizontal Left////////////
        for (int k = v; k >= 0; k--) {
          if (isValideeMove(Game, y, u, o, k) == true) {
            pp_wh++;
          }
        }
        ///////Horizontal Right////////////
        for (int k = v; k < 8; k++) {
          if (isValideeMove(Game, y, u, o, k) == true) {
            pp_wh++;
          }
        }

        if (pp_wh >= 1) {
          pp_wh = 0;
          return false;
        }

      }

    }

    ////////////////////////////////pawn/////////////////////////////////////////////
    for (int k = 0; k < 8; k++) {
      for (int j = 0; j < 8; j++) {
        if (Game.Board[k][j].Code == PAWN && Game.Board[k][j].PieceColor == WHITE) {
          y = k;
          u = j;
        }

        /////////Diagonal//////Up//////Right
        for (int k = o, oi = v; k < 8, oi < 8; k++, oi++) {
          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }
        }

        /////////Diagonal
        for (int k = o, oi = v; k < 8, oi >= 0; k++, oi--) {
          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }
        }

        for (int k = o, oi = v; k >= 0, oi >= 0; k--, oi--) {

          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }

        }

        for (int k = o, oi = v; k >= 0, oi < 8; k--, oi++) {

          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }

        }

        /////vertical//////QUEEN////////check//////////
        for (int k = o; k < 8; k++) {
          if (isValideeMove(Game, y, u, k, v) == true) {
            pp_wh++;

          }
        }

        /////vertical//////up////////check//////////
        for (int k = o; k >= 0; k--) {
          if (isValideeMove(Game, y, u, k, v) == true) {
            pp_wh++;
          }
        }
        ///////Horizontal Left////////////
        for (int k = v; k >= 0; k--) {
          if (isValideeMove(Game, y, u, o, k) == true) {
            pp_wh++;
          }
        }
        ///////Horizontal Right////////////
        for (int k = v; k < 8; k++) {
          if (isValideeMove(Game, y, u, o, k) == true) {
            pp_wh++;
          }
        }

        if (pp_wh >= 1) {
          pp_wh = 0;
          return false;
        }

      }

    }
    /////////////////////////////////////////knight //////////////////////////////////
    for (int k = 0; k < 8; k++) {
      for (int j = 0; j < 8; j++) {
        if (Game.Board[k][j].Code == KNIGHT && Game.Board[k][j].PieceColor == WHITE) {
          y = k;
          u = j;
        }

        /////////Diagonal//////Up//////Right
        for (int k = o, oi = v; k < 8, oi < 8; k++, oi++) {
          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }
        }

        /////////Diagonal
        for (int k = o, oi = v; k < 8, oi >= 0; k++, oi--) {
          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }
        }

        for (int k = o, oi = v; k >= 0, oi >= 0; k--, oi--) {

          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }

        }

        for (int k = o, oi = v; k >= 0, oi < 8; k--, oi++) {

          if (isValideeMove(Game, y, u, k, oi) == true) {

            pp_wh++;

          }

        }

        /////vertical//////QUEEN////////check//////////
        for (int k = o; k < 8; k++) {
          if (isValideeMove(Game, y, u, k, v) == true) {
            pp_wh++;

          }
        }

        /////vertical//////up////////check//////////
        for (int k = o; k >= 0; k--) {
          if (isValideeMove(Game, y, u, k, v) == true) {
            pp_wh++;
          }
        }
        ///////Horizontal Left////////////
        for (int k = v; k >= 0; k--) {
          if (isValideeMove(Game, y, u, o, k) == true) {
            pp_wh++;
          }
        }
        ///////Horizontal Right////////////
        for (int k = v; k < 8; k++) {
          if (isValideeMove(Game, y, u, o, k) == true) {
            pp_wh++;
          }
        }

        if (pp_wh >= 1) {
          pp_wh = 0;
          return false;
        }

      }

    }

    return true;
  }

  return false;
}

int saveeGame(GameData & Game, string File_Name) {

  ofstream save(File_Name);

  //Error in file

  for (int i = 0; i < 8; i++) {

    for (int j = 0; j < 8; j++) {

      save << Game.Board[i][j].Code << " ";

    }
    save << endl;
  }
  cout << endl;
  for (int i = 9, k = 0; i <= 16; i++, k++) {

    for (int j = 0, l = 0; j < 8; j++, l++) {

      save << Game.Board[k][l].PieceColor << " ";

    }
    save << endl;

  }
  save << Game.TurningPlayer;
  save << endl;
  save << player1;
  save << endl;
  save << player2;
  save.close();
  return 0;
}

int saveMoves(GameData & Game, chessMove Move, string MovesHistory) {

  ofstream save(MovesHistory, ofstream::out | ofstream::app);

  if (Game.TurningPlayer == 1) {
    playerMoves = "White";
  }
  if (Game.TurningPlayer == 0) {
    playerMoves = "Black";
  }
  if (Game.Board[Move.FromRow][Move.FromColumn].Code == PAWN) {
    playerPiece = "Pawn";
  }
  if (Game.Board[Move.FromRow][Move.FromColumn].Code == ROOK) {
    playerPiece = "Rook";
  }
  if (Game.Board[Move.FromRow][Move.FromColumn].Code == KNIGHT) {
    playerPiece = "Knight";
  }
  if (Game.Board[Move.FromRow][Move.FromColumn].Code == BISHOP) {
    playerPiece = "Bishop";
  }
  if (Game.Board[Move.FromRow][Move.FromColumn].Code == QUEEN) {
    playerPiece = "Queen";
  }
  if (Game.Board[Move.FromRow][Move.FromColumn].Code == KING) {
    playerPiece = "King";
  }

  save << endl;
  save << playerMoves;
  save << endl;
  save << playerPiece;
  save << endl;
  save << Move.FromRow;
  save << endl;
  save << Move.FromColumn;
  save << endl;
  save << Move.ToRow;
  save << endl;
  save << Move.ToColumn;

  return 0;
}
int loadMoves(GameData & Game, chessMove Move, string MovesHistory) {

  ifstream load(MovesHistory);

  load >> playerMoves;
  load >> playerPiece;
  load >> Move.FromRow;
  load >> Move.FromColumn;
  load >> Move.ToRow;
  load >> Move.ToColumn;
  cout << playerMoves << " " << playerPiece << " from ";
  cout << Move.FromRow << " " << Move.FromColumn;
  cout << " to " << Move.ToRow << " ";

  return Move.ToColumn;
}

int undoMove(GameData & Game, chessMove Move) {

  if (y >= 0) {

    PlayGameee();
  }

}

void isfacingChecke(GameData & Game, Color Player) {

  facecheck = 0;
  facechecke = 0;
  int k = 0, l = 0, q = 0, r = 0;
  int FR, FC, TR, TC;

  //New Conditions Here
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (Game.Board[i][j].Code == KING && Game.Board[i][j].PieceColor == BLACK) {
        k = i;
        l = j;
      }

    }
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (Game.Board[i][j].Code == KING && Game.Board[i][j].PieceColor == WHITE) {
        q = i;
        r = j;
      }

    }
  }

  /////////////////////////////////////BLACK KING THROUGH QUEEN AND ROOK//////////////////////////////////
  for (int m = k + 1, n = l; m < 8; m++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facecheck = 2;
        break;
      }

    }

  }
  for (int m = k - 1, n = l; m >= 0; m--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facecheck = 2;
        break;
      }

    }

  }
  for (int m = k, n = l + 1; n < 8; n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facecheck = 2;
        break;
      }

    }

  }
  for (int m = k, n = l - 1; n >= 0; n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facecheck = 2;
        break;
      }

    }

  }

  for (int m = k, n = l - 1; n >= 0; n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN && Game.Board[m][n].PieceColor == WHITE || Game.Board[m][n].Code == ROOK) {
        facecheck = 2;
        break;
      }

    }

  }

  ////////////////////////////////////////////white king through rook and queen////////////////////////////////////////////////////

  for (int m = q + 1, n = r; m < 8; m++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facechecke = 1;
        break;
      }

    }

  }
  for (int m = q - 1, n = r; m >= 0; m--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facechecke = 1;
        break;
      }

    }

  }
  for (int m = q, n = r + 1; n < 8; n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facechecke = 1;
        break;
      }

    }

  }
  for (int m = q, n = r - 1; n >= 0; n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == ROOK) {
        facechecke = 1;
        break;
      }

    }

  }

  for (int m = q, n = r - 1; n >= 0; n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != ROOK && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN && Game.Board[m][n].PieceColor == WHITE || Game.Board[m][n].Code == ROOK) {
        facechecke = 1;
        break;
      }

    }

  }

  /////////////////////////////////////////BLACK KING THROUGH BISHOP AND QUEEN//////////////////////////////
  /////down  (/)

  for (int m = k + 1, n = l - 1; n >= 0, m < 8; m++, n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facecheck = 2;
        break;
      }

    }

  }

  /////down  (\)
  for (int m = k + 1, n = l + 1; n < 8, m < 8; m++, n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facecheck = 2;
        break;
      }

    }

  }

  /////up (/)///////

  for (int m = k - 1, n = l + 1; n < 8, m >= 0; m--, n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facecheck = 2;
        break;
      }

    }

  }

  /////up (\)///////

  for (int m = k - 1, n = l - 1; n >= 0, m >= 0; m--, n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facecheck = 2;
        break;
      }

    }

  }

  ////////////////////////////////////(white king through queen and bishop)//////////////////////////

  for (int m = q + 1, n = r - 1; n >= 0, m < 8; m++, n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facechecke = 1;
        break;
      }

    }

  }

  /////down  (\)
  for (int m = q + 1, n = r + 1; n < 8, m < 8; m++, n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facechecke = 1;
        break;
      }

    }

  }

  /////up (/)///////

  for (int m = q - 1, n = r + 1; n < 8, m >= 0; m--, n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facechecke = 1;
        break;
      }

    }

  }

  /////up (\)///////

  for (int m = q - 1, n = r - 1; n >= 0, m >= 0; m--, n--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != QUEEN && Game.Board[m][n].Code != BISHOP && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == QUEEN || Game.Board[m][n].Code == BISHOP) {
        facechecke = 1;
        break;
      }

    }

  }

  ////////////////////black king through pawn////////////////////////////

  for (int m = k + 1, n = l + 1; m <= k + 1; m++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != PAWN && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == PAWN) {
        facecheck = 2;
        break;
      }

    }

  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////

  for (int m = k + 1, n = l - 1; m >= k - 1; m--) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != PAWN && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != WHITE) {

        break;
      }

      if (Game.Board[m][n].Code == PAWN) {
        facecheck = 2;
        break;
      }

    }

  }

  ////////////////////WHITE king through pawn////////////////////////////

  for (int m = q - 1, n = r + 1; n <= r + 1; n++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != PAWN && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == PAWN) {
        facechecke = 1;
        break;
      }

    }

  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////

  for (int m = q - 1, n = r - 1; m <= q - 1; m++) {
    if (Game.Board[m][n].Code != NONE) {

      if (Game.Board[m][n].Code != PAWN && Game.Board[m][n].Code != NONE || Game.Board[m][n].PieceColor != BLACK) {

        break;
      }

      if (Game.Board[m][n].Code == PAWN) {
        facechecke = 1;
        break;
      }

    }

  }

  //////////////////////////////WHITE KING THROUGH KNIGHT///////////////////////////////////////////////////

  if (q + 2 < 8 && r + 1 < 8) {

    if (Game.Board[q + 2][r + 1].Code == KNIGHT && Game.Board[q + 2][r + 1].PieceColor == BLACK) {
      facechecke = 1;

    }

  }

  if (q - 2 >= 0 && r + 1 < 8) {

    if (Game.Board[q - 2][r + 1].Code == KNIGHT && Game.Board[q - 2][r + 1].PieceColor == BLACK) {
      facechecke = 1;

    }

  }
  if (q - 2 >= 0 && r - 1 >= 0) {

    if (Game.Board[q - 2][r - 1].Code == KNIGHT && Game.Board[q - 2][r - 1].PieceColor == BLACK) {
      facechecke = 1;

    }

  }
  if (q + 2 < 8 && r - 1 >= 0) {

    if (Game.Board[q + 2][r - 1].Code == KNIGHT && Game.Board[q + 2][r - 1].PieceColor == BLACK) {
      facechecke = 1;

    }

  }
  if (q + 1 < 8 && r + 2 < 8) {

    if (Game.Board[q + 1][r + 2].Code == KNIGHT && Game.Board[q + 1][r + 2].PieceColor == BLACK) {
      facechecke = 1;

    }

  }
  if (q + 1 < 8 && r - 2 >= 0) {

    if (Game.Board[q + 1][r - 2].Code == KNIGHT && Game.Board[q + 1][r - 2].PieceColor == BLACK) {
      facecheck = 2;

    }

  }
  if (q - 1 >= 0 && r + 2 < 8) {

    if (Game.Board[q - 1][r + 2].Code == KNIGHT && Game.Board[q - 1][r + 2].PieceColor == BLACK) {
      facechecke = 1;

    }

  }

  if (q - 1 >= 0 && r - 2 >= 0) {

    if (Game.Board[q - 1][r - 2].Code == KNIGHT && Game.Board[q - 1][r - 2].PieceColor == BLACK) {
      facechecke = 1;

    }

  }

  if (q - 1 >= 0 && r + 2 < 8) {

    if (Game.Board[q - 1][r + 2].Code == KNIGHT && Game.Board[q - 1][r + 2].PieceColor == BLACK) {
      facechecke = 1;

    }

  }

  //////////////////////////////BLACK KING THROUGH KNIGHT///////////////////////////////////////////////////
  //1 column left and 2 rows upward from king

  if (k + 2 < 8 && l + 1 < 8) {

    if (Game.Board[k + 2][l + 1].Code == KNIGHT && Game.Board[k + 2][l + 1].PieceColor == WHITE) {
      facecheck = 2;

    }

  }

  if (k - 2 >= 0 && l + 1 < 8) {

    if (Game.Board[k - 2][l + 1].Code == KNIGHT && Game.Board[k - 2][l + 1].PieceColor == WHITE) {
      facecheck = 2;

    }

  }
  if (k - 2 >= 0 && l - 1 >= 0) {

    if (Game.Board[k - 2][l - 1].Code == KNIGHT && Game.Board[k - 2][l - 1].PieceColor == WHITE) {
      facecheck = 2;

    }

  }
  if (k + 2 < 8 && l - 1 >= 0) {

    if (Game.Board[k + 2][l - 1].Code == KNIGHT && Game.Board[k + 2][l - 1].PieceColor == WHITE) {
      facecheck = 2;

    }

  }
  if (k + 1 < 8 && l + 2 < 8) {

    if (Game.Board[k + 1][l + 2].Code == KNIGHT && Game.Board[k + 1][l + 2].PieceColor == WHITE) {
      facecheck = 2;

    }

  }

  if (k + 1 < 8 && l - 2 >= 0) {

    if (Game.Board[k + 1][l - 2].Code == KNIGHT && Game.Board[k + 1][l - 2].PieceColor == WHITE) {
      facecheck = 2;

    }

  }
  if (k - 1 >= 0 && l + 2 < 8) {

    if (Game.Board[k - 1][l + 2].Code == KNIGHT && Game.Board[k - 1][l + 2].PieceColor == WHITE) {
      facecheck = 2;
    }

  }

  if (k - 1 >= 0 && l - 2 >= 0) {

    if (Game.Board[k - 1][l - 2].Code == KNIGHT && Game.Board[k - 1][l - 2].PieceColor == WHITE) {
      facecheck = 2;

    }

  }

  if (k - 1 >= 0 && l + 2 < 8) {

    if (Game.Board[k - 1][l + 2].Code == KNIGHT && Game.Board[k - 1][l + 2].PieceColor == WHITE) {
      facecheck = 2;

    }

  }

  return;
}

bool isValideeMove(GameData & Game, int FR, int FC, int TR, int TC) {
  int nu, pu, lu, ku;

  nu = TR - FR;
  pu = FR - TR;
  if (TC > FC)
    lu = TC - FC;
  else
    lu = FC - TC;

  isfacingChecke(Game, Game.Board[TR][TC].PieceColor);

  if (Game.Board[FR][FC].Code == NONE) {

    //Empty Piece
    error = "EP";
    return false;
  }

  //Black Pawns

  if (Game.Board[FR][FC].Code == PAWN && Game.Board[FR][FC].PieceColor == BLACK) {
    ////////////////////////////////////is facing check//////////////////////////////////////////////////////////////

    if (Game.TurningPlayer == BLACK) {

      if (vow(Game, FR, FC, TR, TC) == false)
        return false;
    }
    //Enpassant Move from left (\)
    if (enpassant_white == 2) {
      if (TR == FR + 1 && TC == FC + 1 && Game.Board[TR][TC].Code == NONE) {
        capturedpieces_white[enpassant_capture_white] = Game.Board[TR - 1][TC].Code;
        Game.Board[TR - 1][TC].Code = NONE;
        enpassant_white = 0;
        enpassant_capture_white--;
        return true;
      }
    }
    //Enpassant Move from left(/)
    if (enpassant_white == 1) {
      if (TR == FR + 1 && TC == FC - 1 && Game.Board[TR][TC].Code == NONE) {
        capturedpieces_white[enpassant_capture_white] = Game.Board[TR - 1][TC].Code;
        Game.Board[TR - 1][TC].Code = NONE;
        enpassant_white = 0;
        enpassant_capture_white--;
        return true;
      }
    }

    if (TR <= FR) {
      error = "BPR";
      return false;
    }

    if (FC != TC) {

      if (lu > 1) {
        error = "BPC";
        return false;
      }

      if (Game.Board[TR][TC].Code == NONE) {
        error = "BPSP";
        return false;
      }

      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor == BLACK) {

        error = "BPR";
        return false;
      }
    }
    if (FR == 1) {
      if (nu > 2) {
        error = "BP2S";
        return false;
      }
    } else {

      if (nu > 1) {
        error = "BP1S";
        return false;
      }
    }
    if (FC == TC && Game.Board[TR][TC].Code != NONE) {
      error = "BPCS";
      return false;
    }

  }
  //White Pawns
  if (Game.Board[FR][FC].Code == PAWN && Game.Board[FR][FC].PieceColor == WHITE) {
    if (Game.TurningPlayer == WHITE) {

      if (vowe(Game, FR, FC, TR, TC) == false)
        return false;
    }

    //Enpassant Move from right (\)
    if (enpassant_black == 2) {
      if (TR == FR - 1 && TC == FC - 1 && Game.Board[TR][TC].Code == NONE) {
        capturedpieces_black[enpassant_capture_black] = Game.Board[TR + 1][TC].Code;
        Game.Board[TR + 1][TC].Code = NONE;
        enpassant_black = 0;
        enpassant_capture_black--;
        fiftymove_draw = 0;
        return true;
      }
    }
    //Enpassant Move from left(/)
    if (enpassant_black == 1 && Game.Board[TR][TC].Code == NONE) {
      if (TR == FR - 1 && TC == FC + 1) {
        capturedpieces_black[15] = Game.Board[TR + 1][TC].Code;
        Game.Board[TR + 1][TC].Code = NONE;
        enpassant_black = 0;
        fiftymove_draw = 0;
        return true;
      }
    }

    if (TR >= FR) {
      error = "WPR";
      return false;
    }
    if (lu > 1) {
      error = "WPD";
      return false;
    }
    if (FC != TC) {

      if (Game.Board[TR][TC].Code == NONE) {
        error = "WPC";
        return false;
      }

      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor == WHITE) {

        error = "WPROP";
        return false;
      }

    }
    if (FR == 6) {
      if (pu > 2) {
        error = "WP2S";
        return false;
      }
    } else {

      if (pu > 1) {
        error = "WP1S";
        return false;
      }

    }
    if (FC == TC && Game.Board[TR][TC].Code != NONE) {
      error = "WPCS";
      return false;
    }
  }

  //Black Rook
  if (Game.Board[FR][FC].Code == ROOK && Game.Board[FR][FC].PieceColor == BLACK) {

    /////////////////////////////CONDITION FOR IS FACING CHECK//////////////////////////////

    if (Game.TurningPlayer == BLACK) {

      if (vow(Game, FR, FC, TR, TC) == false)
        return false;
    }

    //For same column and rows
    if (TR == FR && TC == FC) {
      error = "BRSRC";
      return false;
    }

    //Horizontal Move

    if (TR == FR && TC != FC) {

      //Path is clear to right?
      if (FC < TC) {
        for (int i = FC + 1; i < TC; i++) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "BRPR";
            return false;
          }
        }
      }
      //Path is clear to left?

      if (FC > TC) {
        for (int i = FC - 1; i > TC; i--) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "BRPL";
            return false;
          }
        }
      }
      //Rook on Black piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
        error = "BRCOP";
        return false;
      }

      return true;

    }

    //Vertical Move
    if (TR != FR && TC == FC) {
      //Path is clear upwards?
      if (FR < TR) {
        for (int i = FR + 1; i < TR; i++) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "BRU";
            return false;
          }
        }
      }
      //Path is clear to down?

      if (FR > TR) {
        for (int i = FR - 1; i > TR; i--) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "BRD";
            return false;
          }
        }
      }
      //Rook On black piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
        error = "BRCOP2";
        return false;
      }

      return true;
    }

    //Rook Diagonal Move error
    else {
      error = "BRVH";
      return false;
    }

  }

  ////////////////////////////////////WHITE ROOK/////////////////////////////////////////////////////	 
  if (Game.Board[FR][FC].Code == ROOK && Game.Board[FR][FC].PieceColor == WHITE) {

    /////////////////////////////////////check condition//////////////////////////////////////////

    if (Game.TurningPlayer == WHITE) {

      if (vowe(Game, FR, FC, TR, TC) == false)
        return false;
    }
    //For same column and rows
    if (TR == FR && TC == FC) {
      error = "WRSRC";
      return false;
    }

    //Horizontal Move
    if (TR == FR && TC != FC) {

      //Path is clear to right?
      if (FC < TC) {
        for (int i = FC + 1; i < TC; i++) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "WRPR";
            return false;
          }
        }
      }
      //Path is clear to left?

      if (FC > TC) {
        for (int i = FC - 1; i > TC; i--) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "WRPL";
            return false;
          }
        }
      }

      //Rook on White piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
        error = "WRCOP";
        return false;
      }

      return true;

    }

    //Vertical Move
    if (TR != FR && TC == FC) {
      //Path is clear downwards?
      if (FR < TR) {
        for (int i = FR + 1; i < TR; i++) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "WRD";
            return false;
          }
        }
      }
      //Path is clear upwards?

      if (FR > TR) {
        for (int i = FR - 1; i > TR; i--) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "WRU";
            return false;
          }
        }
      }
      //Rook On white piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
        error = "WRCOP2";
        return false;
      }

      return true;
    }

    //Rook Diagonal Move error
    else {
      error = "WRVH";
      return false;
    }

  }

  ////////////////////////////////////BLACK KNIGHT/////////////////////////////////////////////////////	 
  if (Game.Board[FR][FC].Code == KNIGHT && Game.Board[FR][FC].PieceColor == BLACK) {
    ////////////////////CHECK CONDITION ///////////////////////
    if (Game.TurningPlayer == BLACK) {

      if (vow(Game, FR, FC, TR, TC) == false)
        return false;
    }

    if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
      error = "BKNCROP";
      return false;
    }

    if (TR == FR && TC == FC) {
      error = "BKNSRC";
      return false;
    }

    if (((TR - FR == 1) || (FR - TR == 1)) && ((FC - TC != 2) && (TC - FC != 2))) {
      error = "BKNCMS1";
      return false;
    } else {
      if (((TC - FC == 1) || (FC - TC == 1)) && ((FR - TR != 2) && (TR - FR != 2))) {
        error = "BKNCMS2";
        return false;
      } else {
        if (((FR - TR != 1) && (TR - FR != 1)) && ((FC - TC != 1) && (TC - FC != 1))) {
          error = "BKNCMS3";
          return false;
        } else {
          if ((FR == TR) || (FC == TC)) {
            error = "BKNCMS4";
            return false;
          } else {
            return true;
          }
        }
      }
    }
    return true;
  }
  ////////////////////////////////////WHITE KNIGHT/////////////////////////////////////////////////////	 
  if (Game.Board[FR][FC].Code == KNIGHT && Game.Board[FR][FC].PieceColor == WHITE) {

    if (Game.TurningPlayer == WHITE) {

      if (vowe(Game, FR, FC, TR, TC) == false)
        return false;
    }
    if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
      error = "WKNCROP";
      return false;
    }

    if (TR == FR && TC == FC) {
      error = "WKNSRC";
      return false;
    }

    if (((TR - FR == 1) || (FR - TR == 1)) && ((FC - TC != 2) && (TC - FC != 2))) {
      error = "WKNCMS1";
      return false;
    } else {
      if (((TC - FC == 1) || (FC - TC == 1)) && ((FR - TR != 2) && (TR - FR != 2))) {
        error = "WKNCMS2";
        return false;
      } else {
        if (((FR - TR != 1) && (TR - FR != 1)) && ((FC - TC != 1) && (TC - FC != 1))) {
          error = "WKNCMS3";
          return false;
        } else {
          if ((FR == TR) || (FC == TC)) {
            error = "WKNCMS4";
            return false;
          } else {
            return true;
          }
        }
      }
    }
    return true;
  }
  ///////////////////////////////////WHITE BISHOP/////////////////////////////////////////////////////	 
  if (Game.Board[FR][FC].Code == BISHOP && Game.Board[FR][FC].PieceColor == WHITE) {
    if (Game.TurningPlayer == WHITE) {

      if (vowe(Game, FR, FC, TR, TC) == false)
        return false;
    }
    //upward right
    if (FR - TR == TC - FC && FR > TR && TC > FC) {
      if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
        error = "WBCML1";
        return false;
      }
      for (int i = FR - 1, j = FC + 1; i > TR; i--, j++) {

        if (Game.Board[i][j].Code != NONE) {
          error = "WBCML2";
          return false;
        }
      }
      if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
        return true;
    } else {
      if (TR - FR == FC - TC && TR > FR && FC > TC) {
        if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
          error = "WBCML3";
          return false;
        }
        for (int i = FR + 1, j = FC - 1; i < TR; i++, j--) {

          if (Game.Board[i][j].Code != NONE) {
            error = "WBCML4";
            return false;
          }
        }
        if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
          return true;

      } else {
        if (FR - TR == FC - TC && FR > TR && FC > TC) {
          if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
            error = "WBCML5";
            return false;
          }
          for (int i = FR - 1, j = FC - 1; i > TR; i--, j--) {

            if (Game.Board[i][j].Code != NONE) {
              error = "WBCML6";
              return false;
            }
          }
          if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
            return true;
        } else {
          if (TR - FR == TC - FC && TR > FR && TC > FC) {
            if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
              error = "WBCML7";
              return false;
            }
            for (int i = FR + 1, j = FC + 1; i < TR; i++, j++) {

              if (Game.Board[i][j].Code != NONE) {
                error = "WBCML8";
                return false;
              }
            }
            if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
              return true;
          } else {
            error = "WBCML9";
            return false;
          }
        }
      }

    }

  }

  ////////////////////////////////////BLACK BISHOP/////////////////////////////////////////////////////	  
  if (Game.Board[FR][FC].Code == BISHOP && Game.Board[FR][FC].PieceColor == BLACK) {
    ////////////////////face chrck
    if (Game.TurningPlayer == BLACK) {

      if (vow(Game, FR, FC, TR, TC) == false)
        return false;
    }
    if (TR - FR == TC - FC && TR > FR && TC > FC) {
      if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
        error = "BBNES1";
        return false;

      }
      for (int i = FR + 1, j = FC + 1; i < TR; i++, j++) {

        if (Game.Board[i][j].Code != NONE) {
          error = "BBNES2";
          return false;
        }
      }
      if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
        return true;
    } else {
      if (FR - TR == FC - TC && FR > TR && FC > TC) {

        if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
          error = "BBNES3";
          return false;

        }

        for (int i = FR - 1, j = FC - 1; i > TR; i--, j--) {

          if (Game.Board[i][j].Code != NONE) {
            error = "BBNMP1";
            return false;
          }
        }
        if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
          return true;
      } else {
        if (TR - FR == FC - TC && TR > FR && FC > TC) {
          if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
            error = "BBNMP2";
            return false;
          }
          for (int i = FR + 1, j = FC - 1; i < TR; i++, j--) {

            if (Game.Board[i][j].Code != NONE) {
              error = "BBNMP3";
              return false;
            }
          }
          if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
            return true;

        } else {
          if (FR - TR == TC - FC && FR > TR && TC > FC) {

            if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
              error = "BBNMP4";
              return false;
            }
            for (int i = FR - 1, j = FC + 1; i > TR; i--, j++) {

              if (Game.Board[i][j].Code != NONE) {
                error = "BBNMP5";
                return false;
              }
            }
            if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
              return true;
          } else {
            error = "BBNMP6";
            return false;

          }

        }
      }

    }

  }

  ////////////////////////////////////WHITE KING/////////////////////////////////////////////////////
  if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == WHITE) {

    if (facechecke == 1) {
      if (Game.Board[TR][TC].Code == NONE) {

        Game.Board[TR][TC].Code = KING;
        Game.Board[TR][TC].PieceColor = WHITE;
        Game.Board[FR][FC].Code = NONE;

        isfacingChecke(Game, Game.Board[TR][TC].PieceColor);

        if (facechecke == 1) {
          Game.Board[TR][TC].Code = NONE;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

          return false;
        }
        if (facechecke == 0) {
          Game.Board[TR][TC].Code = NONE;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
        }

      }

      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {

        return false;
      }

    }
    if (facechecke == 1) {

      if (Game.Board[TR][TC].Code != NONE) {

        int h;
        if (Game.Board[TR][TC].Code == PAWN) {

          h = 1;

        }
        if (Game.Board[TR][TC].Code == ROOK) {

          h = 2;

        }
        if (Game.Board[TR][TC].Code == BISHOP) {

          h = 3;

        }

        if (Game.Board[TR][TC].Code == KNIGHT) {

          h = 4;

        }
        if (Game.Board[TR][TC].Code == QUEEN) {

          h = 5;

        }

        if (Game.Board[TR][TC].Code == KING) {

          h = 6;
        }

        v = h;
      }

      Game.Board[TR][TC].Code = KING;
      Game.Board[TR][TC].PieceColor = WHITE;
      Game.Board[FR][FC].Code = NONE;

      isfacingChecke(Game, Game.Board[TR][TC].PieceColor);

      if (facechecke == 0) {
        if (v == 1)

        {

          Game.Board[TR][TC].Code = PAWN;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }

        if (v == 2) {

          Game.Board[TR][TC].Code = ROOK;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }
        if (v == 3) {

          Game.Board[TR][TC].Code = BISHOP;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }
        if (v == 4) {

          Game.Board[TR][TC].Code = KNIGHT;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }
        if (v == 5) {

          Game.Board[TR][TC].Code = QUEEN;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }
        if (v == 6) {

          Game.Board[TR][TC].Code = KING;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;

        }
      }
      if (facechecke == 1) {

        if (v == 1)

        {

          Game.Board[TR][TC].Code = PAWN;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }

        if (v == 2) {

          Game.Board[TR][TC].Code = ROOK;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }
        if (v == 3) {

          Game.Board[TR][TC].Code = BISHOP;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }
        if (v == 4) {

          Game.Board[TR][TC].Code = KNIGHT;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }
        if (v == 5) {

          Game.Board[TR][TC].Code = QUEEN;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }
        if (v == 6) {

          Game.Board[TR][TC].Code = KING;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          Game.Board[FR][FC].PieceColor = WHITE;
          return false;

        }

      }

    }

    if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
      error = "WKCROP";
      return false;
    }
    ////////////////////Castling with Right Rook
    if (FR == 7 && FC == 4 && TR == 7 && TC == 6) {
      if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == WHITE && Game.Board[7][5].Code == NONE && Game.Board[7][6].Code == NONE && Game.Board[7][7].Code == ROOK && Game.Board[7][7].PieceColor == WHITE) {
        Game.Board[7][5].Code = ROOK;
        Game.Board[7][7].Code = NONE;
        return true;
      }
    }
    /////////////////////Castling with Left Rook
    if (FR == 7 && FC == 4 && TR == 7 && TC == 2) {
      if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == WHITE && Game.Board[7][3].Code == NONE && Game.Board[7][2].Code == NONE && Game.Board[7][1].Code == NONE && Game.Board[7][0].Code == ROOK && Game.Board[7][0].PieceColor == WHITE) {
        Game.Board[7][3].Code = ROOK;
        Game.Board[7][0].Code = NONE;
        return true;
      }
    }

    int rowscheck, colscheck;

    if (FC == TC && FR < TR) {
      rowscheck = TR - FR;
      if (rowscheck == 1) {
        return true;
      } else {
        error = "WKM1SD1";
        return false;
      }
    } else if (FC == TC && FR > TR) {
      rowscheck = FR - TR;
      if (rowscheck == 1) {
        return true;
      } else {
        error = "WKM1SD2";
        return false;
      }
    }

    if (FR == TR && FC < TC) {
      colscheck = TC - FC;
      if (colscheck == 1) {
        return true;
      } else {
        error = "WKM1SD3";
        return false;
      }
    } else if (FR == TR && FC > TC) {
      colscheck = FC - TC;
      if (colscheck == 1) {
        return true;
      } else {
        cout << "WKM1SD4";
        return false;
      }
    }

    if (FR > TR) {
      rowscheck = FR - TR;
    } else if (FR < TR) {
      rowscheck = TR - FR;

    }

    if (FC > TC) {
      colscheck = FC - TC;
    } else if (FC < TC) {
      colscheck = TC - FC;
    }

    if (colscheck == 1 && rowscheck == 1) {
      return true;
    } else {
      error = "WKM1SD5";
      return false;
    }

  }

  ////////////////////////////////////BLACK KING/////////////////////////////////////////////////////
  if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == BLACK) {

    if (facecheck == 2) {
      if (Game.Board[TR][TC].Code == NONE) {

        Game.Board[TR][TC].Code = KING;
        Game.Board[TR][TC].PieceColor = BLACK;
        Game.Board[FR][FC].Code = NONE;

        isfacingChecke(Game, Game.Board[TR][TC].PieceColor);

        if (facecheck == 2) {
          Game.Board[TR][TC].Code = NONE;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
          return false;
        }
        if (facecheck == 0) {
          Game.Board[TR][TC].Code = NONE;
          Game.Board[TR][TC].PieceColor = BLACK;
          Game.Board[FR][FC].Code = KING;
        }

      }

      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {

        return false;
      }

    }
    if (facecheck == 2) {

      if (Game.Board[TR][TC].Code != NONE) {

        int h;
        if (Game.Board[TR][TC].Code == PAWN) {

          h = 1;

        }
        if (Game.Board[TR][TC].Code == ROOK) {

          h = 2;

        }
        if (Game.Board[TR][TC].Code == BISHOP) {

          h = 3;

        }

        if (Game.Board[TR][TC].Code == KNIGHT) {

          h = 4;

        }
        if (Game.Board[TR][TC].Code == QUEEN) {

          h = 5;

        }

        if (Game.Board[TR][TC].Code == KING) {

          h = 6;
        }

        v = h;
      }

      Game.Board[TR][TC].Code = KING;
      Game.Board[TR][TC].PieceColor = BLACK;
      Game.Board[FR][FC].Code = NONE;

      isfacingChecke(Game, Game.Board[TR][TC].PieceColor);

      if (facecheck == 0) {
        if (v == 1)

        {

          Game.Board[TR][TC].Code = PAWN;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }

        if (v == 2) {

          Game.Board[TR][TC].Code = ROOK;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }
        if (v == 3) {

          Game.Board[TR][TC].Code = BISHOP;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }
        if (v == 4) {

          Game.Board[TR][TC].Code = KNIGHT;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }
        if (v == 5) {

          Game.Board[TR][TC].Code = QUEEN;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }
        if (v == 6) {

          Game.Board[TR][TC].Code = KING;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;

        }
      }
      if (facecheck == 2) {

        if (v == 1)

        {

          Game.Board[TR][TC].Code = PAWN;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }

        if (v == 2) {

          Game.Board[TR][TC].Code = ROOK;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }
        if (v == 3) {

          Game.Board[TR][TC].Code = BISHOP;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }
        if (v == 4) {

          Game.Board[TR][TC].Code = KNIGHT;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }
        if (v == 5) {

          Game.Board[TR][TC].Code = QUEEN;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }
        if (v == 6) {

          Game.Board[TR][TC].Code = KING;
          Game.Board[TR][TC].PieceColor = WHITE;
          Game.Board[FR][FC].Code = KING;
          return false;

        }

      }

    }

    ////////////////////Castling with Right Rook
    if (FR == 0 && FC == 4 && TR == 0 && TC == 6) {
      if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == BLACK && Game.Board[0][5].Code == NONE && Game.Board[0][6].Code == NONE && Game.Board[0][7].Code == ROOK && Game.Board[0][7].PieceColor == BLACK) {
        Game.Board[0][5].Code = ROOK;
        Game.Board[0][7].Code = NONE;
        return true;
      }
    }
    /////////////////////Castling with Left Rook
    if (FR == 0 && FC == 4 && TR == 0 && TC == 2) {
      if (Game.Board[FR][FC].Code == KING && Game.Board[FR][FC].PieceColor == BLACK && Game.Board[0][3].Code == NONE && Game.Board[0][2].Code == NONE && Game.Board[0][1].Code == NONE && Game.Board[0][0].Code == ROOK && Game.Board[0][0].PieceColor == BLACK) {
        Game.Board[0][3].Code = ROOK;
        Game.Board[0][0].Code = NONE;
        return true;
      }
    }
    if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
      error = "BKCROP";
      return false;
    }

    int rowscheck, colscheck;

    if (FC == TC && FR < TR) {
      rowscheck = TR - FR;
      if (rowscheck == 1) {
        return true;
      } else {
        error = "BKM1SD1";
        return false;
      }
    } else if (FC == TC && FR > TR) {
      rowscheck = FR - TR;
      if (rowscheck == 1) {
        return true;
      } else {
        error = "BKM1SD2";
        return false;
      }
    }

    if (FR == TR && FC < TC) {
      colscheck = TC - FC;
      if (colscheck == 1) {
        return true;
      } else {
        error = "BKM1SD3";
        return false;
      }
    } else if (FR == TR && FC > TC) {
      colscheck = FC - TC;
      if (colscheck == 1) {
        return true;
      } else {
        error = "BKM1SD4";
        return false;
      }
    }

    if (FR > TR) {
      rowscheck = FR - TR;
    } else if (FR < TR) {
      rowscheck = TR - FR;

    }

    if (FC > TC) {
      colscheck = FC - TC;
    } else if (FC < TC) {
      colscheck = TC - FC;
    }

    if (colscheck == 1 && rowscheck == 1) {
      return true;
    } else {
      error = "BKM1SD5";
      return false;
    }

  }

  ////////////////////////////////////WHITE QUEEN/////////////////////////////////////////////////////

  if (Game.Board[FR][FC].Code == QUEEN && Game.Board[FR][FC].PieceColor == WHITE) {
    if (Game.TurningPlayer == WHITE) {

      if (vowe(Game, FR, FC, TR, TC) == false)
        return false;
    }
    //Rook Moves

    //For same column and rows
    if (TR == FR && TC == FC) {
      error = "WQCMSRC";
      return false;
    }

    //Horizontal Move
    if (TR == FR && TC != FC) {

      //Path is clear to right?
      if (FC < TC) {
        for (int i = FC + 1; i < TC; i++) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "WQR";
            return false;
          }
        }
      }
      //Path is clear to left?

      if (FC > TC) {
        for (int i = FC - 1; i > TC; i--) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "WQL";
            return false;
          }
        }
      }

      //Rook on White piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {

        error = "WQCROP";
        return false;
      }

      return true;

    }

    //Vertical Move
    if (TR != FR && TC == FC) {
      //Path is clear downwards?
      if (FR < TR) {
        for (int i = FR + 1; i < TR; i++) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "WQD";
            return false;
          }
        }
      }
      //Path is clear upwards?

      if (FR > TR) {
        for (int i = FR - 1; i > TR; i--) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "WQU";
            return false;
          }
        }
      }
      //Rook On white piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
        error = "WQCROP2";
        return false;
      }

    }

    //Bishop Moves

    if (FR - TR == TC - FC && FR > TR && TC > FC) {
      if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
        error = "WQNML1";
        return false;
      }
      for (int i = FR - 1, j = FC + 1; i > TR; i--, j++) {

        if (Game.Board[i][j].Code != NONE) {
          error = "WQNML2";
          return false;
        }
      }
      if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
        return true;
    } else {
      if (TR - FR == FC - TC && TR > FR && FC > TC) {
        if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
          error = "WQNML3";
          return false;
        }
        for (int i = FR + 1, j = FC - 1; i < TR; i++, j--) {

          if (Game.Board[i][j].Code != NONE) {
            error = "WQNML4";
            return false;
          }
        }
        if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
          return true;

      } else {
        if (FR - TR == FC - TC && FR > TR && FC > TC) {
          if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
            error = "WQNML5";
            return false;
          }
          for (int i = FR - 1, j = FC - 1; i > TR; i--, j--) {

            if (Game.Board[i][j].Code != NONE) {
              error = "WQNML6";
              return false;
            }
          }
          if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
            return true;
        } else {
          if (TR - FR == TC - FC && TR > FR && TC > FC) {
            if (Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE) {
              error = "WQNML7";
              return false;
            }
            for (int i = FR + 1, j = FC + 1; i < TR; i++, j++) {

              if (Game.Board[i][j].Code != NONE) {
                error = "WQNML8";
                return false;
              }
            }
            if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == BLACK)
              return true;
          } else {
            if (TR != FR && TC == FC) {
              //Path is clear downwards?
              if (FR < TR) {
                for (int i = FR + 1; i < TR; i++) {
                  if (Game.Board[i][TC].Code != NONE) {
                    error = "WQD2";
                    return false;
                  }
                }
              }
              //Path is clear upwards?

              if (FR > TR) {
                for (int i = FR - 1; i > TR; i--) {
                  if (Game.Board[i][TC].Code != NONE) {
                    error = "WQU2";
                    return false;
                  }
                }
              }
              //Rook On white piece
              if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {
                error = "WQCROP3";
                return false;
              }

            } else {
              error = "WQNMVHD";
              return false;
            }
          }
        }
      }

    }

  }

  ////////////////////////////////////BLACK QUEEN/////////////////////////////////////////////////////
  if (Game.Board[FR][FC].Code == QUEEN && Game.Board[FR][FC].PieceColor == BLACK) {

    if (Game.TurningPlayer == BLACK) {

      if (vow(Game, FR, FC, TR, TC) == false)
        return false;
    }

    //Rook Moves

    //For same column and rows
    if (TR == FR && TC == FC) {
      error = "BQNMSRC";
      return false;
    }

    //Horizontal Move

    if (TR == FR && TC != FC) {

      //Path is clear to right?
      if (FC < TC) {
        for (int i = FC + 1; i < TC; i++) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "BQR";
            return false;
          }
        }
      }
      //Path is clear to left?

      if (FC > TC) {
        for (int i = FC - 1; i > TC; i--) {
          if (Game.Board[TR][i].Code != NONE) {
            error = "BQL";
            return false;
          }
        }
      }
      //Rook on Black piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
        error = "BQNROP";
        return false;
      }

      return true;

    }

    //Vertical Move
    if (TR != FR && TC == FC) {
      //Path is clear upwards?
      if (FR < TR) {
        for (int i = FR + 1; i < TR; i++) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "BQU";
            return false;
          }
        }
      }
      //Path is clear to down?

      if (FR > TR) {
        for (int i = FR - 1; i > TR; i--) {
          if (Game.Board[i][TC].Code != NONE) {
            error = "BQD";
            return false;
          }
        }
      }
      //Rook On black piece
      if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
        error = "BQNROP2";
        return false;
      }

    }

    //Bishop Moves

    if (TR - FR == TC - FC && TR > FR && TC > FC) {
      if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
        error = "BQNES1";
        return false;

      }
      for (int i = FR + 1, j = FC + 1; i < TR; i++, j++) {

        if (Game.Board[i][j].Code != NONE) {
          error = "BQNES2";
          return false;
        }
      }
      if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
        return true;
    } else {
      if (FR - TR == FC - TC && FR > TR && FC > TC) {

        if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
          error = "BQNES3";
          return false;

        }

        for (int i = FR - 1, j = FC - 1; i > TR; i--, j--) {

          if (Game.Board[i][j].Code != NONE) {
            error = "BQNML1";
            return false;
          }
        }
        if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
          return true;
      } else {
        if (TR - FR == FC - TC && TR > FR && FC > TC) {
          if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
            error = "BQNML2";
            return false;
          }
          for (int i = FR + 1, j = FC - 1; i < TR; i++, j--) {

            if (Game.Board[i][j].Code != NONE) {
              error = "BQNML3";
              return false;
            }
          }
          if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
            return true;

        } else {
          if (FR - TR == TC - FC && FR > TR && TC > FC) {

            if (Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE) {
              error = "BQNML4";
              return false;
            }
            for (int i = FR - 1, j = FC + 1; i > TR; i--, j++) {

              if (Game.Board[i][j].Code != NONE) {
                error = "BQDNC";
                return false;
              }
            }
            if (Game.Board[TR][TC].Code == NONE || Game.Board[TR][TC].PieceColor == WHITE)
              return true;
          } else {
            if (TR != FR && TC == FC) {
              //Path is clear upwards?
              if (FR < TR) {
                for (int i = FR + 1; i < TR; i++) {
                  if (Game.Board[i][TC].Code != NONE) {
                    error = "BQU2";
                    return false;
                  }
                }
              }
              //Path is clear to down?

              if (FR > TR) {
                for (int i = FR - 1; i > TR; i--) {
                  if (Game.Board[i][TC].Code != NONE) {
                    error = "BQD2";
                    return false;
                  }
                }
              }
              //Rook On black piece
              if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {
                error = "BQNROP3";
                return false;
              }

            } else {
              error = "BQNMVHD";
              return false;
            }

          }

        }
      }

    }

  }

  //Add new conditions here
  return true;
}

bool vow(GameData & Game, int FR, int FC, int TR, int TC) {

  if (facecheck == 2) {
    if (Game.Board[TR][TC].Code == NONE) {

      Game.Board[TR][TC].Code = Game.Board[FR][FC].Code;
      Game.Board[TR][TC].PieceColor = BLACK;

      isfacingChecke(Game, Game.Board[TR][TC].PieceColor);

      Game.Board[TR][TC].Code = NONE;
      Game.Board[TR][TC].PieceColor = BLACK;

      if (facecheck == 2) {
        return false;
      }

    }

    if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != WHITE) {

      return false;
    }

  }
  if (facecheck == 2) {

    if (Game.Board[TR][TC].Code != NONE) {

      int h;
      if (Game.Board[TR][TC].Code == PAWN) {

        h = 1;

      }
      if (Game.Board[TR][TC].Code == ROOK) {

        h = 2;

      }
      if (Game.Board[TR][TC].Code == BISHOP) {

        h = 3;

      }

      if (Game.Board[TR][TC].Code == KNIGHT) {

        h = 4;

      }
      if (Game.Board[TR][TC].Code == QUEEN) {

        h = 5;

      }

      if (Game.Board[TR][TC].Code == KING) {

        h = 6;
      }

      v = h;
    }

    Game.Board[TR][TC].Code = Game.Board[FR][FC].Code;
    Game.Board[TR][TC].PieceColor = BLACK;

    isfacingChecke(Game, Game.Board[TR][TC].PieceColor);

    if (facecheck == 0) {
      if (v == 1)

      {

        Game.Board[TR][TC].Code = PAWN;
        Game.Board[TR][TC].PieceColor = WHITE;

      }

      if (v == 2) {

        Game.Board[TR][TC].Code = ROOK;
        Game.Board[TR][TC].PieceColor = WHITE;

      }
      if (v == 3) {

        Game.Board[TR][TC].Code = BISHOP;
        Game.Board[TR][TC].PieceColor = WHITE;

      }
      if (v == 4) {

        Game.Board[TR][TC].Code = KNIGHT;
        Game.Board[TR][TC].PieceColor = WHITE;

      }
      if (v == 5) {

        Game.Board[TR][TC].Code = QUEEN;
        Game.Board[TR][TC].PieceColor = WHITE;

      }
      if (v == 6) {

        Game.Board[TR][TC].Code = KING;
        Game.Board[TR][TC].PieceColor = WHITE;

      }
    }
    if (facecheck == 2) {

      if (v == 1)

      {

        Game.Board[TR][TC].Code = PAWN;
        Game.Board[TR][TC].PieceColor = WHITE;
        return false;

      }

      if (v == 2) {

        Game.Board[TR][TC].Code = ROOK;
        Game.Board[TR][TC].PieceColor = WHITE;
        return false;

      }
      if (v == 3) {

        Game.Board[TR][TC].Code = BISHOP;
        Game.Board[TR][TC].PieceColor = WHITE;
        return false;

      }
      if (v == 4) {

        Game.Board[TR][TC].Code = KNIGHT;
        Game.Board[TR][TC].PieceColor = WHITE;
        return false;

      }
      if (v == 5) {

        Game.Board[TR][TC].Code = QUEEN;
        Game.Board[TR][TC].PieceColor = WHITE;
        return false;

      }
      if (v == 6) {

        Game.Board[TR][TC].Code = KING;
        Game.Board[TR][TC].PieceColor = WHITE;
        return false;

      }

    }

  }

  return true;

}

bool vowe(GameData & Game, int FR, int FC, int TR, int TC) {

  if (facechecke == 1) {
    if (Game.Board[TR][TC].Code == NONE) {

      Game.Board[TR][TC].Code = Game.Board[FR][FC].Code;
      Game.Board[TR][TC].PieceColor = WHITE;

      isfacingChecke(Game, Game.Board[TR][TC].PieceColor);

      Game.Board[TR][TC].Code = NONE;
      Game.Board[TR][TC].PieceColor = BLACK;

      if (facechecke == 1) {
        return false;
      }

    }

    if (Game.Board[TR][TC].Code != NONE && Game.Board[TR][TC].PieceColor != BLACK) {

      return false;
    }

  }
  if (facechecke == 1) {

    if (Game.Board[TR][TC].Code != NONE) {

      int h;
      if (Game.Board[TR][TC].Code == PAWN) {

        h = 1;

      }
      if (Game.Board[TR][TC].Code == ROOK) {

        h = 2;

      }
      if (Game.Board[TR][TC].Code == BISHOP) {

        h = 3;

      }

      if (Game.Board[TR][TC].Code == KNIGHT) {

        h = 4;

      }
      if (Game.Board[TR][TC].Code == QUEEN) {

        h = 5;

      }

      if (Game.Board[TR][TC].Code == KING) {

        h = 6;
      }

      v = h;
    }

    Game.Board[TR][TC].Code = Game.Board[FR][FC].Code;
    Game.Board[TR][TC].PieceColor = WHITE;

    isfacingChecke(Game, Game.Board[TR][TC].PieceColor);

    if (facechecke == 0) {
      if (v == 1)

      {

        Game.Board[TR][TC].Code = PAWN;
        Game.Board[TR][TC].PieceColor = BLACK;

      }

      if (v == 2) {

        Game.Board[TR][TC].Code = ROOK;
        Game.Board[TR][TC].PieceColor = BLACK;

      }
      if (v == 3) {

        Game.Board[TR][TC].Code = BISHOP;
        Game.Board[TR][TC].PieceColor = BLACK;

      }
      if (v == 4) {

        Game.Board[TR][TC].Code = KNIGHT;
        Game.Board[TR][TC].PieceColor = BLACK;

      }
      if (v == 5) {

        Game.Board[TR][TC].Code = QUEEN;
        Game.Board[TR][TC].PieceColor = BLACK;

      }
      if (v == 6) {

        Game.Board[TR][TC].Code = KING;
        Game.Board[TR][TC].PieceColor = BLACK;

      }
    }
    if (facecheck == 2) {

      if (v == 1)

      {

        Game.Board[TR][TC].Code = PAWN;
        Game.Board[TR][TC].PieceColor = BLACK;
        return false;

      }

      if (v == 2) {

        Game.Board[TR][TC].Code = ROOK;
        Game.Board[TR][TC].PieceColor = BLACK;
        return false;

      }
      if (v == 3) {

        Game.Board[TR][TC].Code = BISHOP;
        Game.Board[TR][TC].PieceColor = BLACK;
        return false;

      }
      if (v == 4) {

        Game.Board[TR][TC].Code = KNIGHT;
        Game.Board[TR][TC].PieceColor = BLACK;
        return false;

      }
      if (v == 5) {

        Game.Board[TR][TC].Code = QUEEN;
        Game.Board[TR][TC].PieceColor = BLACK;
        return false;

      }
      if (v == 6) {

        Game.Board[TR][TC].Code = KING;
        Game.Board[TR][TC].PieceColor = BLACK;
        return false;

      }

    }

  }

  return true;

}
