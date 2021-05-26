#ifndef GAME_DATA
#define GAME_DATA
#include<iostream>
#include<string>
#include<vector>

using namespace std;

    enum PieceType {NONE, PAWN, ROOK, BISHOP, KNIGHT, QUEEN, KING};
    enum Color {BLACK, WHITE};
  
    struct chessPiece{
        PieceType Code = NONE;
        Color PieceColor = BLACK;
    };

    struct chessMove {
        int FromRow, FromColumn, ToRow, ToColumn;
    };

    struct GameData{
        chessPiece Board[8][8]; // WHITE ON HIGHER ROWS {moving towards lower rows} AND BLACK ON LOWER ROWS
        Color TurningPlayer = WHITE; // START WITH WHITE PLAYER
    };
    bool vow(GameData & Game,int FR,int FC,int TR,int TC);
    bool vowe(GameData & Game,int FR,int FC,int TR,int TC);
    string temp;
     int v;
	int fxpos, fypos, txpos, typos;
	int pawnpromote;
	int facecheck = 0;
		int facechecke = 0;
	int pawnpromo=0;
	string X;
	
	string Y;
	int i,pp;
	int pp_wh;
	int y;
	int pawn_promote_check=0;
	int pawn_promote_choice=0;
	string error = " ";
	string player1, player2;

	int capturedpieces_white[16] = {};
	int capturedpieces_black[16] = {};
	int p1 =0;
	int p2 = 0;
	int enpassant_black = 0;
	int enpassant_white = 0;
	int enpassant_capture_white = 16;
	int fiftymove_draw = 0;
	int enpassant_capture_black = 16;
	 bool isValideeMove(GameData & Game,int FR,int FC,int TR,int TC);
    void PromotePawn(GameData & Game, chessMove Move, Color Player);
    void isfacingCheck(GameData& Game, chessMove Move ,Color Player);
    bool isValidMove(GameData& Game, chessMove Move);
    int MakeMove(GameData& Game, chessMove Move);
    bool isCheckmate(GameData& Game, Color Player);
    void initGame(GameData& Game);
    void initNewGame(GameData& Game);
    int saveGame(GameData&Game, string File_Name);
    int saveeGame(GameData&Game, string File_Name);
    int saveMoves(GameData&Game, string MovesHistory);
    string playerMoves;
    string playerPiece;
    int loadMoves(GameData& Game, chessMove Move, string MovesHistory);
    int loadGame(GameData& Game, string File_Name);
    int load = 0;
    int undoMove(GameData& Game, chessMove Move);
    int oldrow, oldcol;
    int storeMoves[200][200];
    int  PlayGameee();
    int castling_check=0;
    
#endif
