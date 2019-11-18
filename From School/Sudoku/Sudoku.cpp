//Conventions//
//
//
//variable naming convention:
//         classes - first letter is capitalized
//         variables and methods - first letter is not capitalized, every important
//                                   word after that is caplitalized.
//End Conventions//

//Assumptions//
// 
//
//End Assumptions//

#include "Sudoku.h"

//Globals
const int smr = 3;
const int smc = 3;
bool validPuzzle = true;
long Remove_Count = 0;
const int Max_Candidates = 10;
vector <int> newcand (Max_Candidates, 0);


Sudoku::Sudoku(){

	updateCandidateWrapperCount = 1;
	candColCount = 1;
	candRowCount = 1;
	candQuadCount = 1;
	printVectorBeforeRemove = false;
	printVectorAfterRemove = false;
	printUpdateCandidateWrapperCount = true;
	printCandColCount = false;
	printCandRowCount = false;
	printCandQuadCount = false;
	printSolve = false;
	printGuesses = true;
}

Sudoku::~Sudoku(){
                  //cout << "desconstructor sudoku" << endl;                  
   }

bool Sudoku::solve(){

	//solveCallCount ++; 

    Board savedBoard = currentBoard;

	if(isSolved()){
		return true;               
	}
	//incorrect guess
	else if(isUnSolveable()){

		return false;     
	}

	do{

		prevBoard = currentBoard; 

		for(int i=0;i < currentBoard.Size;i++){
			for(int j=0;j < currentBoard.Size;j++){
				//applyRule1();
				applyRule2(i, j);
				if(isUnSolveable()){

					return false;     
				}                             
			}        
		} 
	}while(!(prevBoard == currentBoard));     

	if(isSolved()){
                    
		return true;               
	}
	else{

		oneCell tmpCell = Guess();
		if(printGuesses){
			fout << "guess is " << tmpCell.row << " " << tmpCell.col << " " << tmpCell.value << endl;
		}
		//vector<int> prevData(currentBoard.data[tmpCell.row][tmpCell.col]);
		makeMove(tmpCell);
		bool tmpB = solve();
		if(tmpB){

            tmpBoard = currentBoard;                   
			return true;   
		}
		//otherwise un-wind guess
		else{

			currentBoard = savedBoard;
			removeElem(tmpCell);

			bool tmpB = solve();
			if(!tmpB){
                 return false;      
             }
             else{
                  return true;  
             }
		}     
	}
	return true;
}

oneCell Sudoku::Guess(){

	oneCell tmpGuess;

	tmpGuess.row = -1;

	for(int lstNum = 3; lstNum<12; lstNum ++){  
		for(int i =0; i < currentBoard.Size;i++){
			for(int j=0; j < currentBoard.Size;j++){
				if(currentBoard.data[i][j].size() == lstNum){
					tmpGuess.row = i;
					tmpGuess.col = j;
					tmpGuess.value =  currentBoard.data[i][j][1];
					return tmpGuess;
				}
			}
		}
	}            
	return tmpGuess;
} 

void Sudoku::removeElem(oneCell cellIn){

	if(printVectorBeforeRemove){
		fout << "Before remove" << endl;
		currentBoard.printVector(fout, cellIn);
	}
	vector<int>::iterator tmpIt;

	for(tmpIt = currentBoard.data[cellIn.row][cellIn.col].begin();tmpIt != currentBoard.data[cellIn.row][cellIn.col].end();tmpIt++){
		if(*tmpIt == cellIn.value){
			currentBoard.data[cellIn.row][cellIn.col].erase(tmpIt);
			break;          
		}
	}
	if(printVectorAfterRemove){
		fout << "After remove" << endl;
		currentBoard.printVector(fout, cellIn);       
	}
}

void Sudoku::makeMove(oneCell cellIn){

	currentBoard.data[cellIn.row][cellIn.col].clear();

	currentBoard.data[cellIn.row][cellIn.col].push_back(cellIn.value);
	currentBoard.data[cellIn.row][cellIn.col].push_back(cellIn.value);

	//Always keep candidate lists up to date
	updateCandidateListWrapper(cellIn);

} 

void Sudoku::updateCandidateListWrapper(oneCell cellIn){

	updateCandidateListRow(cellIn.row, cellIn.col);

	updateCandidateListCol(cellIn.row, cellIn.col);

	updateCandidateListQuadrand(cellIn.row, cellIn.col);        

	if(printUpdateCandidateWrapperCount){
		if(updateCandidateWrapperCount == 1260){
			fout << " mike debug";
		}

		fout << "updateCandidateWrapperCount == " << updateCandidateWrapperCount << endl;
		printCurrentBoardWithCandiates();
	}

	updateCandidateWrapperCount ++;        

} 



void Sudoku::updateCandidateListRow(int rowIn, int colIn){

	oneCell tmpGuess;

	//iterate thru row which means row is fixed cols iterates by 1 
	for(int i =0; i < currentBoard.Size;i++){
		//if cell has not been determined then try to remove the new value from candidate list               
		if(currentBoard.data[rowIn][i][0] == 0){
			tmpGuess.row = rowIn;
			tmpGuess.col = i;
			tmpGuess.value = currentBoard.data[rowIn][colIn][0];
			removeElem(tmpGuess);                         
		}
	} 
	if(printCandRowCount){
		fout << "candRowCount == " << candRowCount << endl;
		printCurrentBoardWithCandiates();
	}

	candRowCount ++;


}

void Sudoku::updateCandidateListCol(int rowIn, int colIn){

	oneCell tmpCell;

	//iterate thru column which means col is fixed rows iterates by 1  
	for(int i =0; i < currentBoard.Size;i++){
		//if cell has not been determined then try to remove the new value from candidate list
		if(currentBoard.data[i][colIn][0] == 0){
			tmpCell.row = i;
			tmpCell.col = colIn;
			tmpCell.value = currentBoard.data[rowIn][colIn][0];
			removeElem(tmpCell);
			//fout << "after removeElem" << endl;
			//printCurrentBoardWithCandiates();

		}
	} 
	if(printCandColCount){
		fout << "candColCount == " << candColCount << endl;
		printCurrentBoardWithCandiates();
	}

	candColCount ++;


}

void Sudoku::updateCandidateListQuadrand(int rowIn, int colIn){

	int quad = getQuad(colIn, rowIn);

	int startCol;
	int startRow;

	oneCell tmpCell;

	switch(quad){

		  case 1:
			  startCol = 0;
			  startRow = 0;
			  break;
		  case 2:
			  startCol = 3;
			  startRow = 0;
			  break;
		  case 3:
			  startCol = 6;
			  startRow = 0;
			  break;
		  case 4:
			  startCol = 0;
			  startRow = 3;
			  break;
		  case 5:
			  startCol = 3;
			  startRow = 3;
			  break;
		  case 6:
			  startCol = 6;
			  startRow = 3;
			  break;
		  case 7:
			  startCol = 0;
			  startRow = 6;
			  break;
		  case 8:
			  startCol = 3;
			  startRow = 6;
			  break;
		  case 9:
			  startCol = 6;
			  startRow = 6;
			  break;                                    
	}
	for(int i = startRow;i < (startRow + 3);i++){
		for(int j = startCol;j < (startCol + 3);j++){
			if(currentBoard.data[i][j][0] == 0){
				tmpCell.row = i;
				tmpCell.col = j;
				tmpCell.value = currentBoard.data[rowIn][colIn][0];
				removeElem(tmpCell);                         
			}                             
		}        
	}
	if(printCandQuadCount){
		fout << "candQuadCount == " << candQuadCount << endl;
		printCurrentBoardWithCandiates();
	}

	candQuadCount++;        
}

bool Sudoku::isSolved(){

	for(int i =0; i < currentBoard.Size;i++){
		for(int j=0; j < currentBoard.Size;j++){
			if(currentBoard.data[i][j].size() != 2){
				return false;
			}          
		} 
	}       
	return true;
}

bool Sudoku::isUnSolveable(){

	for(int i =0; i < currentBoard.Size;i++){
		for(int j=0; j < currentBoard.Size;j++){
			if(currentBoard.data[i][j].size() < 2){
				return true;
			}          
		} 
	}       
	return false;
}

int Sudoku::getQuad(int rowIn, int colIn){

	switch(colIn){

		   case 0:
		   case 1:
		   case 2:
			   switch(rowIn){
		   case 0:
		   case 1:
		   case 2:              
			   return 1;
		   case 3:
		   case 4:
		   case 5:
			   return 2;
		   case 6:
		   case 7:
		   case 8:
			   return 3;                   
			   }
		   case 3:
		   case 4:
		   case 5:
			   switch(rowIn){
		   case 0:
		   case 1:
		   case 2:              
			   return 4;
		   case 3:
		   case 4:
		   case 5:
			   return 5;
		   case 6:
		   case 7:
		   case 8:
			   return 6;                   
			   }                 
		   case 6:
		   case 7:
		   case 8:
			   switch(rowIn){
		   case 0:
		   case 1:
		   case 2:              
			   return 7;
		   case 3:
		   case 4:
		   case 5:
			   return 8;
		   case 6:
		   case 7:
		   case 8:
			   return 9;                   
			   }                         
	} 
	return -1;   
}


void Sudoku::initCell(int i, int j){

	currentBoard.data[i][j].clear();
	for(int k=0;k <= currentBoard.Size;k++){
		currentBoard.data[i][j].push_back(k);           
	}            
} 

void Sudoku::initBoard(){

	for(int i=0;i < currentBoard.Size;i++){
		for(int j=0;j < currentBoard.Size;j++){
			initCell(i, j);        
		}        
	}     
}

void Sudoku::printCurrentBoard(){
	currentBoard.print(fout);     
}

void Sudoku::printCurrentBoardWithCandiates(){
	currentBoard.printWithCandiates(fout);     
}

bool Sudoku::applyRule2(int rowIn, int colIn){

	oneCell tmpCell;

	if(currentBoard.data[rowIn][colIn].size() == 2){

		tmpCell.row = rowIn;
		tmpCell.col = colIn;
		tmpCell.value = currentBoard.data[rowIn][colIn][1];
		bool tmpB = printUpdateCandidateWrapperCount;
		//printUpdateCandidateWrapperCount = false;
		makeMove(tmpCell);
		//printUpdateCandidateWrapperCount = tmpB;                                          
	}      
	return true;
}

bool Sudoku::applyRule1(){

	int i  = 0;
	int j  = 0;
	int ii = 0;
	int jj = 0;
	int soln = 0;
	bool status = false;

	for (i = 0; i < currentBoard.Size; i++)
		for (j = 0; j < currentBoard.Size; j++)
			if (isSoln(i,j))
				if (!currentBoard.data[i][j][0])
				{
					soln = currentBoard.data[i][j][1];       // local variable for solution
					currentBoard.data[i][j][0] = soln;       // save into solution cell

					// check for invalid puzzle
					//
					// validate row
					for (jj = 0; jj < currentBoard.Size; jj++)
						if (j != jj)
							validPuzzle &= !(isSoln(i,jj) && currentBoard.data[i][jj][0] == soln);
					//
					// validate column
					for (ii = 0; ii < currentBoard.Size; ii++)
						if (i != ii)
							validPuzzle &= !(isSoln(ii,j) && currentBoard.data[ii][j][0] == soln);
					//
					// validate small region
					for (ii = (i/smr*smr); ii < (i/smr*smr+smr); ii++)  // process small region
						for (jj = (j/smc*smc); jj < (j/smc*smc+smc); jj++)
							if (!(ii == i || jj == j))                  // skip same row and col
								validPuzzle &= !(isSoln(ii,jj) && currentBoard.data[ii][jj][0] == soln);


					if (validPuzzle)
					{
						//outFile << "CandRemoveRow  soln="<< soln << "  (" << i << "," << j <<")\n\n";

						// remove from row
						for (jj = 0; jj < currentBoard.Size; jj++)
							if (!isSoln(i,jj))
								status |= remove(soln, currentBoard.data[i][jj]);

						//print();
						//outFile << "CandRemoveCol  soln="<< soln << "  (" << i << "," << j <<")\n\n";

						// remove from column
						for (ii = 0; ii < currentBoard.Size; ii++)
							if (!isSoln(ii,j))
								status |= remove(soln, currentBoard.data[ii][j]);

						//print();
						//outFile << "CandRemoveSmall  soln="<< soln << "  (" << i << "," << j <<")\n\n";

						for (ii = (i/smr*smr); ii < (i/smr*smr+smr); ii++)  // process small region
							for (jj = (j/smc*smc); jj < (j/smc*smc+smc); jj++)
								if (!(ii == i || jj == j))                  // skip same row and col
									status |= remove(soln, currentBoard.data[ii][jj]);   // remove from small
						//print();
					}
				}
				return status;   
} 
bool Sudoku::isSoln (int i, int j){

	return (currentBoard.data[i][j].size() == 2);
}
bool Sudoku::remove(int soln, vector <int> &dData)
{
	int Size = dData.size();
	int i = 0;
	int j = 1;
	bool removed = false;

	Remove_Count++;

	for (i = 0; i < Size; i++)
		newcand[i] = dData[i];


	if (Size > 2)
	{
		for (i = 1; i < Size; i++)
		{
			if (dData[i] != soln)
				newcand[j++] = dData[i];
			else
				removed = true;
		}
		if (removed)
		{
			if (Size > 3)
			{
				// reduce Size by 1 and build new candidate list
				dData.resize(--Size);
				for (i = 1; i < Size; i++)
					dData[i] = newcand[i];
			}
			else
			{
				// solution found
				dData.resize(2);
				//////          dData[0] = newcand[1];
				dData[1] = newcand[1];
			}
		}
	}
	return removed;
}
//not currently used
bool Sudoku::notDone(){

	int count = 0;

	//caculates rows that have more than 2
	for(int i=0; i < currentBoard.Size; i++){
		for(int j=0; j < currentBoard.Size; j++){
			if(currentBoard.data[i][j][0] != 0){
				count++;   
			}
			if(count >=2){
				break;   
			}   

		}   

		if(count < 2 ){
			return false;
		}
		count = 0;
	}


	//caculates cols that have more than 2
	count = 0;
	for(int i=0; i < currentBoard.Size; i++){
		for(int j=0; j < currentBoard.Size; j++){
			if(currentBoard.data[j][i][0] != 0){
				count++;   
			}
			if(count >=2){
				break;   
			}   

		}   

		if(count < 2 ){
			return false;
		}
		count = 0;
	}

	return true;
}
//not currently used
bool Sudoku::toManyFilled(){

	return false; 
}
//not currently used
bool Sudoku::isValidateSudokuBoard(){


	return true;    
}



bool Sudoku::applyRule3(){

	return false;
}

bool Sudoku::applyRule4(){

	return false;
}

bool Sudoku::applyRule5(){

	return false;
}

bool Sudoku::applyRule6(){

	return false;
}

bool Sudoku::applyRule7(){

	return false;
}
void Sudoku::generateBoard(){

	do{
		int rand1 = rand()%10;
		int rand2 = rand()%10;
		int rand3 = rand()%10;

		oneCell tmpGuess;
		tmpGuess.row = rand1;
		tmpGuess.col = rand2;
		tmpGuess.value = rand3;

		makeMove(tmpGuess);
		//data[rand1][rand2][0] = rand3; //make move

		//check board

		if(!isValidateSudokuBoard()){

			//reset cell

		}
		//else if(toManyFilled){

		//       reset cell   
		//  }   
	}  while (notDone());    
}
