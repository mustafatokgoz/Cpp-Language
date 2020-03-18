#ifndef BOARDARRAY1D_H
#define BOARDARRAY1D_H

#include<iostream>
#include<string>
#include<cstdlib>
#include"abstractboard.h"

using namespace std;

namespace inheritance{
	class boardarray1D : public AbstractBoard{
		public:	
				/*Contructors*/
				boardarray1D();
				boardarray1D(int one,int second);
				/*Copy Constructor*/
				boardarray1D(const boardarray1D &other);
				/*Assignment operator */
				boardarray1D& operator=(const boardarray1D &other);
				/*Destructor*/
				~boardarray1D();

				
				void deletePuzzle(int *puzzle,int *goal_puzzle);
				 
				 void setSize(int height,int widht) override;
				 void reset() override;
				 void print() const override;
				 int readFromFile(string file_name) override;	
				 bool move(char letter) override;
				 bool isSolved() const override;
				 void writeToFile() override;
				 int  operator () (int index1,int index2) const override;			/*this overload is taking two index and return corresponding cell*/
				 bool operator ==(const AbstractBoard &board2) const override;	
				 int seperateLineToNumber(string one_line,int cur_line_number)override;						
				 void blankValue(int number) override;
				 void findTheBlankPosition(int position[2]) override;
				 int rowNumber(string file);


		private: 
				int *puzzle;
				int *goal_puzzle;		/*This uses for puzzle part*/


	};







}
#endif



