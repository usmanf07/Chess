#include<iostream>
#include<string>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<fstream>
#include <stdlib.h>
#include "GameData.cpp"
#include "GameErrors.cpp"

using namespace std;

struct Chess{
    GameData GameState;
    string PlayerNames[2];
    // This struct will evolve as we make progress in this project
};

void getFromRowFromColbyLeftClick(int &fxpos, int &fypos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			fxpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			fypos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}

void getToRowToColbyLeftClick(int &txpos, int &typos){
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			txpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			typos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}

void ShowGame(Chess Game){
    for(int r =0; r < 8; r++ ){
    	cout<<"----|--------|-------|-------|-------|-------|-------|-------|"<<endl;
        for(int c = 0; c < 8; c++){
            switch(Game.GameState.Board[r][c].Code){
                case NONE:
                	cout<<" .\t";
                break;
                default:
                    if(Game.GameState.Board[r][c].PieceColor == BLACK)
                        cout<<"B";
                    else
                        cout<<"W";

                    switch(Game.GameState.Board[r][c].Code){
                    case PAWN:
                        cout<<"P";
                    break;

                    case ROOK:
                        cout<<"R";
                    break;

                    case KNIGHT:
                        cout<<"kN";
                    break;

                    case BISHOP:
                        cout<<"B";
                    break;

                    case QUEEN:
                        cout<<"Q";
                    break;

                    case KING:
                        cout<<"K";
                    break;
                    }
                    cout<<"\t";
                break;
            }
        }
        cout<<r;
        cout<<endl;
        
    }
    cout<<endl;
    cout<<"0        1       2       3       4       5       6       7"<<"\n\n Save Game! (S)"<<"\t\t Undo Move! (U)"<<"\t\t Restart Game! (R)"<<endl;
    
    cout<<"\t\t\t";
    cout<< Game.PlayerNames[1]<<"\tvs\t"<<Game.PlayerNames[0]<<endl;
    
}

int PlayGame(){
	system("Color 70");
    Chess Game;
    if(load == 1){
    	string File_Name;
    	cout<<"Enter File name: ";
 		cin>>File_Name;
    	loadGame(Game.GameState,File_Name);
    	if(loadGame(Game.GameState,File_Name) !=0)
    	{
    		MovesError(error);
    		cout<<endl;
    		return 0;
		}
    		
    	Game.PlayerNames[1] = player1; 
    	Game.PlayerNames[0] = player2; 
    	system("CLS");
		ShowGame(Game);
	}
	else{
		cout<<"Enter First (WHITE) Player's Info"<<endl;
    cin>> Game.PlayerNames[1]; 
    player1 = Game.PlayerNames[1]; 
    cout<<"\n\nEnter Second(BLACK) Player's Info"<<endl;
    cin>>Game.PlayerNames[0];
    player2 = Game.PlayerNames[0]; 
    initGame(Game.GameState);
	}
    

    chessMove Move;
    system("CLS");
    ShowGame(Game);
    int save;

    while(!isCheckmate(Game.GameState, Game.GameState.TurningPlayer) ){
    	
    	if(fiftymove_draw == 50){
    		system("cls");
    		
    		cout<<"Game has been drawn according to Fifty Move rule!"<<endl;
    		cout<<"Well Played!"<<endl;
    		break;
		}
    	error=" ";
    	facecheck=0;
        cout<<Game.PlayerNames[Game.GameState.TurningPlayer];
        if(Game.GameState.TurningPlayer == WHITE)
            cout<<" (WHITE) To Move";
        else
            cout<<" (BLACK) To Move";

        cout<<", its your turn now!"<<endl;
        cout<<"Click which piece you want to move: "<<endl;
        getFromRowFromColbyLeftClick(fxpos, fypos);
        Move.FromRow = fypos/2;
    	Move.FromColumn = fxpos/8;
    	if(Move.FromRow==9 && Move.FromColumn==4){
			undoMove(Game.GameState, Move);
		}
		if(Move.FromRow==9 && Move.FromColumn==8){
			initGame(Game.GameState);
			cout<<"Game will restart in: "<<endl;
			Sleep(400);
			cout<<"3"<<endl;
			Sleep(400);
			cout<<"2"<<endl;
			Sleep(400);
			cout<<"1"<<endl;
			system("cls");
			ShowGame(Game);
		}
		
    	if(Move.FromRow==9 && Move.FromColumn==1){
    		system("CLS");
    		string File_Name;
    		while(saveGame(Game.GameState, File_Name) !=0){
    			cout<<"Enter File Name: "<<endl;
    		cin>>File_Name;
			saveGame(Game.GameState, File_Name);
			system("cls");
			MovesError(error);
    		cout<<endl;
			
			}
    		
			cout<<"File Saved Successfully!"<<endl;
			cout<<endl;
			cout<<"********************************************************"<<endl;
    		cout<<"*                Game Developed By Mad Men             *"<<endl;
    		cout<<"*                                                      *"<<endl;
    		cout<<"*			Hassan Rehman                  *"<<endl;
    		cout<<"*			Usman Faisal                   *"<<endl;
    		cout<<"*			Muhammad Abdullah              *"<<endl;
    		cout<<"*					   Version 1.0 *"<<endl;
    		cout<<"********************************************************"<<endl;
			cout<<"Thank you for playing! See you soon!"<<endl;
			Sleep(3000);
			exit(0);
		}
		
    	else{
    	cout<<"Click where you want to move: ";
        getToRowToColbyLeftClick(txpos, typos);
        Move.ToRow=typos/2;
    	Move.ToColumn = txpos/8;  
    	saveMoves(Game.GameState, Move, "moves.txt");
        MakeMove(Game.GameState, Move);
        system("CLS");
        ShowGame(Game);
        cout<<"Captured Pieces: ";
        for(int i=0;i<16; i++){
		if(capturedpieces_black[i] == 1){
			cout<<"BP"<<" ";
		}
		if(capturedpieces_black[i] == 2){
			cout<<"BR"<<" ";
		}
		if(capturedpieces_black[i] == 3){
			cout<<"BB"<<" ";
		}
		if(capturedpieces_black[i] == 4){
			cout<<"BkN"<<" ";
		}
		if(capturedpieces_black[i] == 5){
			cout<<"BQ"<<" ";
		}
	}
	for(int i=0;i<16; i++){
		if(capturedpieces_white[i] == 1){
			cout<<"WP"<<" ";
		}
		if(capturedpieces_white[i] == 2){
			cout<<"WR"<<" ";
		}
		if(capturedpieces_white[i] == 3){
			cout<<"WB"<<" ";
		}
		if(capturedpieces_white[i] == 4){
			cout<<"WkN"<<" ";
		}
		if(capturedpieces_white[i] == 5){
			cout<<"WQ"<<" ";
		}
	}
	cout<<endl;
	cout<<"Last Move: ";
        cout<<loadMoves(Game.GameState, Move, "moves.txt")<<endl;
        remove("moves.txt");
        cout<<endl;
        if(error!=" "){
        	cout<<"********************************************************************************"<<endl;
    		cout<<"       ";MovesError(error);cout<<endl;
    		cout<<"********************************************************************************"<<endl;
		}
		if(facechecke==1){
		cout<<"********************************************************************************"<<endl;
    	cout<<"                    WHITE KING IS FACING CHECK                                  "<<endl;
    	cout<<"********************************************************************************"<<endl;
		}
		if(facecheck==2){
		cout<<"********************************************************************************"<<endl;
    	cout<<"                    BLACK KING IS FACING CHECK                                  "<<endl;
    	cout<<"********************************************************************************"<<endl;
		}	
    }
}

if(isCheckmate(Game.GameState, Game.GameState.TurningPlayer) == true)
	if(Game.GameState.TurningPlayer == WHITE){
		cout<<"********************************************************************************"<<endl;
    	cout<<"                    BLACK HAS WON THE GAME!                                "<<endl;
    	cout<<"********************************************************************************"<<endl;
	}
        else{
        	cout<<"********************************************************************************"<<endl;
    	cout<<"                    WHITE HAS WON THE GAME!                                "<<endl;
    	cout<<"********************************************************************************"<<endl;
		}

    cout<<endl;

int option;

cout<<"Play Again or Enter 0 for main menu: ";
cin>>option;

if(option ==0){
	system("cls");
	return 0;
}
    

}

int PlayGameee(){
	
    string File_Name;
    Chess Game;
	
    chessMove Move;
    int save;
    
    string Y= to_string(y); 
    loadGame(Game.GameState,"hassan"+Y+".txt");
    for(int i=0; i<16; i++){
		capturedpieces_black[i] =0;
	}
	for(int i=0; i<16; i++){
		capturedpieces_white[i] =0;
	}
    Game.PlayerNames[1] = player1; 
    Game.PlayerNames[0] = player2; 
    system("CLS");
    ShowGame(Game);
    
   
    while(!isCheckmate(Game.GameState, Game.GameState.TurningPlayer) ){
    	
    	if(fiftymove_draw == 50){
    		system("cls");
    		
    		cout<<"Game has been drawn according to Fifty Move rule!"<<endl;
    		cout<<"Well Played!"<<endl;
    		break;
		}
    	error=" ";
    	facecheck=0;
        cout<<Game.PlayerNames[Game.GameState.TurningPlayer];
        if(Game.GameState.TurningPlayer == WHITE)
            cout<<" (WHITE) To Move";
        else
            cout<<" (BLACK) To Move";

        cout<<", its your turn now!"<<endl;
        cout<<"Click which piece you want to move: "<<endl;
        getFromRowFromColbyLeftClick(fxpos, fypos);
        Move.FromRow = fypos/2;
    	Move.FromColumn = fxpos/8;
    	if(Move.FromRow==9 && Move.FromColumn==4){
    		y--;
			undoMove(Game.GameState, Move);
		}
		if(Move.FromRow==9 && Move.FromColumn==8){
			initGame(Game.GameState);
			cout<<"Game will restart in: "<<endl;
			Sleep(400);
			cout<<"3"<<endl;
			Sleep(400);
			cout<<"2"<<endl;
			Sleep(400);
			cout<<"1"<<endl;
			system("cls");
			ShowGame(Game);
		}
		
    	if(Move.FromRow==9 && Move.FromColumn==1){
    		system("CLS");
    		string File_Name;
    		while(saveGame(Game.GameState, File_Name) !=0){
    			cout<<"Enter File Name: "<<endl;
    		cin>>File_Name;
			saveGame(Game.GameState, File_Name);
			system("cls");
			MovesError(error);
    		cout<<endl;
			
			}
    		
			cout<<"File Saved Successfully!"<<endl;
			cout<<endl;
			cout<<"********************************************************"<<endl;
    		cout<<"*                Game Developed By Mad Men             *"<<endl;
    		cout<<"*                                                      *"<<endl;
    		cout<<"*			Hassan Rehman                  *"<<endl;
    		cout<<"*			Usman Faisal                   *"<<endl;
    		cout<<"*			Muhammad Abdullah              *"<<endl;
    		cout<<"*					   Version 1.0 *"<<endl;
    		cout<<"********************************************************"<<endl;
			cout<<"Thank you for playing! See you soon!"<<endl;
			Sleep(3000);
			exit(0);
		}
		
    	else{
    	cout<<"Click where you want to move: ";
        getToRowToColbyLeftClick(txpos, typos);
        Move.ToRow=typos/2;
    	Move.ToColumn = txpos/8;  
    	saveMoves(Game.GameState, Move, "moves.txt");
        MakeMove(Game.GameState, Move);
        system("CLS");
        ShowGame(Game);
        cout<<"Captured Pieces: ";
        for(int i=0;i<16; i++){
		if(capturedpieces_black[i] == 1){
			cout<<"BP"<<" ";
		}
		if(capturedpieces_black[i] == 2){
			cout<<"BR"<<" ";
		}
		if(capturedpieces_black[i] == 3){
			cout<<"BB"<<" ";
		}
		if(capturedpieces_black[i] == 4){
			cout<<"BkN"<<" ";
		}
		if(capturedpieces_black[i] == 5){
			cout<<"BQ"<<" ";
		}
	}
	for(int i=0;i<16; i++){
		if(capturedpieces_white[i] == 1){
			cout<<"WP"<<" ";
		}
		if(capturedpieces_white[i] == 2){
			cout<<"WR"<<" ";
		}
		if(capturedpieces_white[i] == 3){
			cout<<"WB"<<" ";
		}
		if(capturedpieces_white[i] == 4){
			cout<<"WkN"<<" ";
		}
		if(capturedpieces_white[i] == 5){
			cout<<"WQ"<<" ";
		}
	}
	cout<<endl;
	cout<<"Last Move: ";
        cout<<loadMoves(Game.GameState, Move, "moves.txt")<<endl;
        remove("moves.txt");
        cout<<endl;
        if(error!=" "){
        	cout<<"********************************************************************************"<<endl;
    		cout<<"       ";MovesError(error);cout<<endl;
    		cout<<"********************************************************************************"<<endl;
		}
		if(facechecke==1){
		cout<<"********************************************************************************"<<endl;
    	cout<<"                    WHITE KING IS FACING CHECK                                  "<<endl;
    	cout<<"********************************************************************************"<<endl;
		}
		if(facecheck==2){
		cout<<"********************************************************************************"<<endl;
    	cout<<"                    BLACK KING IS FACING CHECK                                  "<<endl;
    	cout<<"********************************************************************************"<<endl;
		}	
    }
}

if(isCheckmate(Game.GameState, Game.GameState.TurningPlayer) == true)
	if(Game.GameState.TurningPlayer == WHITE){
		cout<<"********************************************************************************"<<endl;
    	cout<<"                    BLACK HAS WON THE GAME!                                "<<endl;
    	cout<<"********************************************************************************"<<endl;
	}
        else{
        	cout<<"********************************************************************************"<<endl;
    	cout<<"                    WHITE HAS WON THE GAME!                                "<<endl;
    	cout<<"********************************************************************************"<<endl;
		}

    cout<<endl;

int option;

cout<<"Play Again or Enter 0 for main menu: ";
cin>>option;

if(option ==0){
	system("cls");
	return 0;
}
}

int main(){
	system("Color 20");
    cout<<endl;
	Sleep(100);cout << "    \t\t\t======================================\n";
   Sleep(100);cout << "     \t\t\t  _____ _    _ ______  _____ _____\n";
   Sleep(100);cout << "     \t\t\t / ____| |  | |  ____|/ ____/ ____|\n";
   Sleep(100);cout << "     \t\t\t| |    | |__| | |__  | (___| (___ \n";
   Sleep(100);cout << "     \t\t\t| |    |  __  |  __|  \\___ \\\\___ \\ \n";
   Sleep(100);cout << "     \t\t\t| |____| |  | | |____ ____) |___) |\n";
   Sleep(100);cout << "     \t\t\t \\_____|_|  |_|______|_____/_____/\n\n";
   Sleep(100);cout << "    \t\t\t======================================\n\n";
   cout<<endl;
   
   string File_Name;
     int choice = 0, playgame =0;
    do{
        do{
        	
            cout<<"\t\t\t1. Play Game\n\t\t\t2. Load Game\n\t\t\t3.Exit\n\n \t\t\tEnter Your Choice(1-3) \t\t\t"<<endl;
            cin>>choice;
            system("CLS");
        }while(choice< 1 || choice > 3);

        switch(choice){
        case 1:
        	cout<<endl;
	cout<<"*********************************************************************************"<<endl;
    cout<<"*                                                                               *"<<endl;
    cout<<"*   To move a piece:                                                            *"<<endl;
    cout<<"*   (1) Click the piece of your choice                                          *"<<endl;
    cout<<"*   (2) Click the dot where you want to move that specific piece                *"<<endl;
    cout<<"*                                                                               *"<<endl;
    cout<<"*    For Castling King & Rook:                                                  *"<<endl;
    cout<<"*   (1) Move King to the designated position & Rook will be moved automatically *"<<endl;
    cout<<"*                                                                               *"<<endl;
    cout<<"********************************************************************************"<<endl;
    	PlayGame(); 
        break;
        case 2:
        load = 1;
        PlayGame(); 
        break;
        case 3:
            return 0;
        break;
        }
    }while(1);

    return 0;
}

