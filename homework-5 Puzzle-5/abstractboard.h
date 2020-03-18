#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;
namespace inheritance{
	class AbstractBoard{
				public: AbstractBoard();
					virtual void setSize(int height,int width) = 0;
					virtual void reset() = 0;
					virtual void print() const = 0;
					virtual int readFromFile(string file_name) = 0;
					virtual bool move(char letter) = 0;
					virtual bool isSolved() const = 0;
					virtual void writeToFile() = 0;

					virtual int  operator () (int index1,int index2) const = 0;			/*this overload is taking two index and return corresponding cell*/
					virtual bool operator ==(const AbstractBoard &board2) const = 0;	/*This operator overload is comparing two object*/
					int getColumn();
					int getRow();	
					char LastMove();						/*This is retruning last move*/
					int NumberOfMoves();						/*This is returning numberofmove*/				
					static int NumberOfBoards();						/*This is returning number of boards*/
					virtual void findTheBlankPosition(int position[2]) = 0; 
				protected:
					void swap(int &p1,int &p2);
					int tenPower(int pow);
					int convertToNumber(string word);
					int lineNumber(string file_name);

					virtual void blankValue(int number) = 0;
					virtual int seperateLineToNumber(string one_line,int cur_line_number) = 0;
					

					static int numofboard;
					int linenumber=0,x=0;		/*linenumber is row number , x is column number*/
					char last_move='S'; int numberofmove=0;		/*These are datas for boards*/
					
	};

}
#endif

