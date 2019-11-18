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

#ifndef H_Board
#define H_Board

#include <vector>
#include <fstream>
#include <iostream>
#include "oneCell.h"

using namespace std;

//const int numRowsCols = 9;
             
class Board{

      public:
             static const int Size = 9;
             vector<int> data[Size][Size];
             bool operator==(const Board&) const;
             const Board& operator=(const Board&);             
             void print(ofstream&);
             void printWithCandiates(ofstream&);
             void printVector(ofstream&, oneCell);   
             //Board();
             ~Board();


};

#endif
