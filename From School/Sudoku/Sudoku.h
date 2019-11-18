//Conventions//
//First element of the vector is the value of that square; if 0 value then the
//      Sudoku value has not been determined yet.
//When a Sudoku value is determined there will be 0 and the value in the vector.  The 
//     zero will be updated and the value left in the list
//variable naming convention:
//         classes - first letter is capitalized
//         variables and methods - first letter is not capitalized, every important
//                                   word after that is caplitalized.
//debugging
//         there are 8 variables that can be used to print out what the alogrithm is doing
//         the most usefull are probably printUpdateCandidateWrapperCount and printGuesses
//         these variables are set by the constructor but they are public so they can be changed anytime
//End Conventions//

//Assumptions//
//
//
//End Assumptions//


#ifndef H_Sudoku
#define H_Sudoku

#include "Board.h"
#include "oneCell.h"
#include <fstream>
#include <iostream>

using namespace std;


class Sudoku{
      
      public:
             bool applyRules();
             bool applyRule1();
             //single candidate rule
             bool applyRule2(int, int);
             bool applyRule3();
             bool applyRule4();
             bool applyRule5();
             bool applyRule6();
             bool applyRule7();
             bool isValidateSudokuBoard();
             bool solve();
             bool isSolved();
             bool isUnSolveable();
             void generateBoard();             
             oneCell Guess();
             void makeMove(oneCell);
             bool isSoln(int, int);
             bool remove(int, vector<int> &);
             void initCell(int, int);
             void initBoard();
             bool toManyFilled();
             bool notDone();
             void removeElem(oneCell);
             void printCurrentBoard();
             void printCurrentBoardWithCandiates();
             void updateCandidateListWrapper(oneCell);
             void updateCandidateListRow(int, int);
             void updateCandidateListCol(int, int);
             void updateCandidateListQuadrand(int, int);
             int getQuad(int, int);
             ofstream fout;             
             Sudoku();
             ~Sudoku();
             bool printVectorAfterRemove;
             bool printVectorBeforeRemove;
             bool printUpdateCandidateWrapperCount;
             bool printCandColCount;
             bool printCandRowCount;
             bool printCandQuadCount;
             bool printSolve;
             bool printGuesses;
      private:
             Board prevBoard;
             Board savedBoard;
             Board currentBoard;
             Board tmpBoard; 
             int updateCandidateWrapperCount;
             int candColCount;
             int candRowCount;
             int candQuadCount;
      
};



#endif
