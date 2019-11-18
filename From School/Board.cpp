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

#include "Board.h"
#include "oneCell.h"
#include <iomanip>

bool Board::operator==(const Board& boardIn) const{

       for(int i =0; i < Size;i++){
         for(int j=0; j < Size;j++){
                if(data[i][j].size() != boardIn.data[i][j].size()){
                    return false;
                }
                for(int k=0; k < data[i][j].size();k++){
                    if(data[i][j][k] != boardIn.data[i][j][k]){
                        return false;
                    }
                }
            }   
        }    
     return true;    
}

const Board& Board::operator=(const Board& bIn){
      
       for(int i =0; i < Size;i++){
         for(int j=0; j < Size;j++){
              data[i][j] = bIn.data[i][j];   
         }
       }    
}
Board::~Board(){
               // cout << "desconstructor board" << endl;                
}
void Board::printWithCandiates(ofstream& fout){
     
     vector<int>::iterator tmpIt;
     
     char tmpC[11] = "          ";
     char space = ' ';
       for(int i =0; i < Size;i++){
         for(int j=0; j < Size;j++){

            int k = 0;
            for(tmpIt = data[i][j].begin(); tmpIt != data[i][j].end();tmpIt++){
                    tmpC[k] = 48 + *tmpIt;
                    k++;           
            }
            for(;k < 11;k++){
                   tmpC[k] = space;       
            }
            fout << setw(11)  << left;
            fout << tmpC;
            for(int p = 0;p < 11;p++){
                    tmpC[p] = space;        
            }                      
            if((j + 1)%3 == 0){
                   fout << space << space << space;
            }            
         }
         if((i + 1)%3 == 0){
                fout << endl;       
         }
         fout.flush();
         fout << endl; 
       } 
      fout << endl << endl; 
   
}

void Board::print(ofstream& fout){
     
       for(int i =0; i < Size;i++){
         for(int j=0; j < Size;j++){
                    fout << data[i][j][0] << " ";
                    fout.flush();                    
         }
         fout << endl; 
       }
       fout << endl << endl;    
}

void Board::printVector(ofstream& fout, oneCell tmpCell){
     
     vector<int>::iterator tmpIt;
     
     for(tmpIt = data[tmpCell.row][tmpCell.col].begin();tmpIt != data[tmpCell.row][tmpCell.col].end();tmpIt++){
            fout << *tmpIt << " ";         
     } 
     
     fout << endl;    
}

