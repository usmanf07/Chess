#include<iostream>


using namespace std;

int MovesError(string error_out){
	
	if(error_out == "MW"){
		cout<<"Invalid Move! it is still White's turn! Please try again!";
	}
	if(error_out == "MB"){
		cout<<"Invalid Move! it is still Black's turn! Please try again!";
	}
	if(error_out == "EP"){
		cout<<"There is no piece on the specified location! Please try again!";
	}
	if(error_out == "BPR"){
		cout<<"The column or row for the next space should be greater than the current!";
	}
	if(error_out == "BPC" ){
		cout<<"Inavlid Move! You cannot move diagonally unless there is a white piece";
	}
	if(error_out == "BPSP" ){
		cout<<"Invalid Move! Pawns can be moved in straight path only!";
	}
	if(error_out == "BPR" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "BP2S" ){
		cout<<"Invalid Move! Pawn can be moved upto 2 spaces only from the beginning space! ";
	}
	if(error_out == "BP1S" ){
		cout<<"Invalid Move! Pawn can be moved upto 1 spaces only after the beginning space!";
	}
	if(error_out == "BPCS" ){
		cout<<"Invalid Move! You cannot move straight now!";
	}
	if(error_out == "WPR" ){
		cout<<"The column or row for the next space should be greater than the current! ";
	}
	if(error_out == "WPD" ){
		cout<<"Inavlid Move! You cannot move diagonally unless there is a black piece";
	}
	if(error_out == "WPC" ){
		cout<<"Invalid Move! Pawns can be moved in straight path only!";
	}
	if(error_out == "WPROP" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "WP2S" ){
		cout<<"Invalid Move! Pawn can be moved upto 2 spaces only from the beginning space! ";
	}
	if(error_out == "WP1S" ){
		cout<<"Invalid Move! Pawn can be moved upto 1 spaces only after the beginning space!";
	}
	if(error_out == "WPCS" ){
		cout<<"Invalid Move! You cannot move straight now!";
	}
	if(error_out == "BRSRC" ){
		cout<<"Invalid Move! You cannot move the piece on same column and row!";
	}
	if(error_out == "BRPR" ){
		cout<<"Invalid Move! Path towards right is not clear!";
	}
	if(error_out == "BRPL" ){
		cout<<"Invalid Move! Path towards left is not clear!";
	}
	if(error_out == "BRCOP" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "BRU" ){
		cout<<"Invalid Move! Upwards path is not clear";
	}
	if(error_out == "BRD" ){
		cout<<"Invalid Move! Downwards path is not clear! ";
	}
	if(error_out == "BRCOP2" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "BRVH" ){
		cout<<"Invalid Move! Rook can be moved in either vertically or horizontally!";
	}
	if(error_out == "WRSRC" ){
		cout<<"Invalid Move! cannot move piece on same column and row!";
	}
	if(error_out == "WRPR" ){
		cout<<"Invalid Move! Path towards right is not clear!";
	}
	if(error_out == "WRPL" ){
		cout<<"Invalid Move! Path towards left is not clear!";
	}
	if(error_out == "WRCOP" ){
		cout<<"Invalid Move! You cannot replace your own piece ";
	}
	if(error_out == "WRD" ){
		cout<<" Invalid Move! Downwards path is not clear";
	}
	if(error_out == "WRU" ){
	    cout<<"Invalid Move! Upwards path is not clear";
	}
	if(error_out == "WRCOP2" ){
	 	cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "WRVH" ){
		cout<<"Invalid Move! Rook can be moved in either vertically or horizontally!";
	}
	if(error_out == "BKNCROP" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "BKNSRC" ){
		cout<<"Invalid move! cannot move piece on same column and row!";
	}
	if(error_out == "BKNCMS1" ){
		cout<<"Invalid Move! Knight cannot be moved to this space";
	}
	if(error_out == "BKNCMS2" ){
		cout<<"Invalid Move! Knight cannot be moved to this space";
	}
	if(error_out == "BKNCMS3" ){
		cout<<"Invalid Move! Knight cannot be moved to this space";
	}
	if(error_out == "BKNCMS4" ){
		cout<<"Invalid Move! Knight cannot be moved to this space";
	}
	if(error_out == "WKNCROP" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "WKNSRC" ){
		cout<<"Invalid move! cannot move piece on same column and row!";
	}
	if(error_out == "WKNCMS1" ){
		cout<<"Invalid Move! Knight cannot be moved to this space";
	}
	if(error_out == "WKNCMS2" ){
		cout<<"Invalid Move! Knight cannot be moved to this space";
	}
	if(error_out == "WKNCMS3" ){
		cout<<"Invalid Move! Knight cannot be moved to this space";
	}
	if(error_out == "WKNCMS4" ){
		cout<<"Invalid Move! Knight cannot be moved to this space";
	}
	if(error_out == "WBCML1" ){
		cout<<"you cannot move to this location ";
	}
	if(error_out == "WBCML2" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WBCML3" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WBCML4" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WBCML5" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WBCML6" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WBCML7" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WBCML8" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WBCML9" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "BBNES1" ){
		cout<<"THERE IS NO EMPTY SPACE THERE ";
	}
	if(error_out == "BBNES2" ){
		cout<<"THERE IS NO EMPTY SPACE THERE ";
	}
	if(error_out == "BBNES3" ){
		cout<<"THERE IS NO EMPTY SPACE THERE ";
	}
	if(error_out == "BBNMP1" ){
		cout<<"you cannot move to this location ";
	}
	if(error_out == "BBNMP2" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "BBNMP3" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "BBNMP4" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "BBNMP5" ){
		cout<<"Invalid move! this diagonal path is not clear!";
	}
	if(error_out == "BBNMP6" ){
		cout<<"Invalid move! Bishop cannot replace the same color's piece'!";
	}
	if(error_out == "WKCROP" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "WKM1SD1" ){
		cout<<"Invalid move! King can only be moved one space in any direction!";
	}
	if(error_out == "WKM1SD2" ){
		cout<<"Invalid move! King can only be moved one space in any direction!";
	}
	if(error_out == "WKM1SD3" ){
		cout<<"Invalid move! King can only be moved one space in any direction!";
	}
	if(error_out == "WKM1SD4" ){
		cout<<"Invalid move! King can only be moved one space in any direction!";
	}
	if(error_out == "WKM1SD5" ){
		cout<<"Invalid move! King can only be moved one space in any direction!";
	}
	if(error_out == "BKCROP" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "BKM1SD1" ){
		cout<<"Invalid move! King can only be moved one space in any direction!";
	}
	if(error_out == "BKM1SD2" ){
		cout<<"Invalid move! King can only be moved one space in any direction!";
	}
	if(error_out == "BKM1SD3" ){
		cout<<"Invalid move! King can only be moved one space in any direction!";
	}
	if(error_out == "BKM1SD4" ){
		cout<<"Invalid move! King can only be moved one space in any direction!";
	}
	if(error_out == "BKM1SD5" ){
		cout<<"Invalid move! King can only be moved one space in any direction!";
	}
	if(error_out == "WQCMSRC " ){
		cout<<"Invalid Move! cannot move piece on same column and row!";
	}
	if(error_out == "WQR" ){
		cout<<"Invalid Move! Path towards right is not clear!";
	}
	if(error_out == "WQL" ){
		cout<<"Invalid Move! Path towards left is not clear!";
	}
	if(error_out == "WQCROP" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "WQD" ){
		cout<<"Invalid Move! Downwards path is not clear";
	}
	if(error_out == "WQU" ){
		cout<<"Invalid Move! Upwards path is not clear";
	}
	if(error_out == "WQCROP2" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "WQNML1" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WQNML2" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WQNML3" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WQNML4" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WQNML5" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WQNML6" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WQNML7" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WQNML8" ){
		cout<<"you cannot move to this location";
	}
	if(error_out == "WQD2" ){
		cout<<"Invalid Move! Downwards path is not clear";
	}
	if(error_out == "WQU2" ){
		cout<<"Invalid Move! Upwards path is not clear";
	}
	if(error_out == "WQCROP3" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "WQNMVHD" ){
		cout<<"Invalid Move! Queen can be moved in either vertically & horizontally or Diagonaly!";
	}
	if(error_out == "BQNMSRC" ){
		cout<<"Invalid Move! cannot move piece on same column and row!";
	}
	if(error_out == "BQR" ){
		cout<<"Invalid Move! Path towards right is not clear!";
	}
	if(error_out == "BQL" ){
		cout<<"Invalid Move! Path towards left is not clear!";
	}
	if(error_out == "BQNROP" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "BQU" ){
		cout<<"Invalid Move! Upwards path is not clear";
	}
	if(error_out == "BQD" ){
		cout<<"Invalid Move! Downwards path is not clear";
	}
	if(error_out == "BQNROP2" ){
		cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "BQNES1" ){
		cout<<"THERE IS NO EMPTY SPACE THERE ";
	}
	if(error_out == "BQNES2" ){
		cout<<"THERE IS NO EMPTY SPACE THERE";
	}
	if(error_out == "BQNES3" ){
		cout<<"THERE IS NO EMPTY SPACE THERE";
	}
	if(error_out == "BQNML1" ){
		cout<<"you cannot move to this location ";
	}
	if(error_out == "BQNML2" ){
		cout<<"you cannot move to this location ";
	}
	if(error_out == "BQNML3" ){
		cout<<"you cannot move to this location ";
	}
	if(error_out == "BQNML4" ){
		cout<<"you cannot move to this location ";
	}
	if(error_out == "BQDNC" ){
		cout<<"Invalid move! Diagonal path is not clear!";
	}
	if(error_out == "BQU2" ){
		cout<<"Invalid Move! Upwards path is not clear";
	}
	if(error_out == "BQD2" ){
		cout<<"Invalid Move! Downwards path is not clear";
	}
	if(error_out == "BQNROP3" ){
	   cout<<"Invalid Move! You cannot replace your own piece";
	}
	if(error_out == "BQNMVHD" ){
		cout<<"Invalid Move! Queen can be moved in either vertically & horizontally or Diagonaly!";
	}
	if(error_out == "EOP" ){
		cout<<"Error opening file";
	}
	if(error_out == "IFE" ){
		cout<<"Invalid Output File extension. Use only txt files";
	}
	if(error_out == "CRF" ){
		cout<<"Error! Cannot read the file!";
	}
	if(error_out == "IFE2" ){
		cout<<"Invalid Input File extension. Use only txt files";
	}
	if(error_out == "CHK" ){
		cout<<"CHECKMATE";
	}
	if(error_out == "MEK" ){
		cout<<"You cannot make this move, because King is facing check";
	}
		
 return 0;
}
