/***********************************************************************
Mike DePouw
Bill Ford
Scoott Summer
2005/12/14
***********************************************************************/
#include <cstdlib>
#include <iostream>
#include "Sudoku.h"
#include "Board.h"
#include "oneCell.h"
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

bool readInBoard(Sudoku&);
     
ifstream fin;

int main(int argc, char *argv[]){

    char tmpC[100];
    char tmpC2[100];
    /*
    for(int i=1;i < argc;i++){
        
        Sudoku tmpSud;  
        
        strcpy(tmpC, "out");
        strcat(tmpC, itoa(i, tmpC2, 10));
        strcat(tmpC, ".txt");
        cout << argv[i] << endl;
        fin.open(argv[i]);
        
        tmpSud.fout.open(tmpC);
    
        tmpSud.initBoard();
        tmpSud.fout << "After initBoard()" << endl;
        tmpSud.printCurrentBoard();
        //tmpSud.printCurrentBoardWithCandiates();
        
        readInBoard(tmpSud);
        tmpSud.fout << "After readInBoard()" << endl;
        tmpSud.printCurrentBoard();
        //tmpSud.printCurrentBoardWithCandiates();
        bool tmpB = tmpSud.solve();
        
        tmpSud.fout << endl << "After solve()" << endl;
        tmpSud.printCurrentBoard();
        fin.close();
        //delete tmpSud;
        //tmpSud = null;
    }
    */

    bool tmpB;
   
    Sudoku tmpSud, tmpSud2, tmpSud3;
    
    fin.open("in.txt");
    tmpSud.fout.open("out.txt");
    
    tmpSud.initBoard();
    tmpSud.fout << "After initBoard()" << endl;
    tmpSud.printCurrentBoard();
    //tmpSud.printCurrentBoardWithCandiates();
    
    readInBoard(tmpSud);
    tmpSud.fout << "After readInBoard()" << endl;
    tmpSud.printCurrentBoard();
    //tmpSud.printCurrentBoardWithCandiates();
    tmpB = tmpSud.solve();
    
    tmpSud.fout << endl << "After solve()" << endl;
    tmpSud.printCurrentBoard();
        
           
    //system("PAUSE");
    return EXIT_SUCCESS;
}

bool readInBoard(Sudoku& tmpSud){
     
     int row, col, value;
     oneCell tmpCell;
     
     while(fin >> row >> col >> value){

               tmpCell.row = row - 1;
               tmpCell.col = col - 1;
               tmpCell.value = value;
               tmpSud.makeMove(tmpCell);                 
     }
     
     return true;
}
