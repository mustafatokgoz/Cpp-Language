#ifndef BOARDARRAY2D_H
#define BOARDARRAY2D_H

#include<iostream>
#include<string>
#include<cstdlib>
#include"abstractboard.h"

using namespace std;

namespace inheritance{
	class boardarray2D : public AbstractBoard{
		public:	
				/*Contructors*/
				boardarray2D();
				boardarray2D(int one,int second);
				/*Copy Constructor*/
				boardarray2D(const boardarray2D &other);
				/*Assignment operator */
				boardarray2D& operator=(const boardarray2D &other);
				/*Destructor*/
				~boardarray2D();

				void addElement(int a,int cur_line_num,int number);
				void deletePuzzle(int **puzzle,int **goal_puzzle);
				 
				 void setSize(int height,int widht) override;
				 void reset() override;
				 void print() const override;
				 int readFromFile(string file_name) override;	
				 bool move(char letter) override;
				 bool isSolved() const override;
				 void writeToFile() override;
				 int  operator () (int index1,int index2) const override;			/*this overload is taking two index and return corresponding cell*/
				 bool operator ==(const AbstractBoard &board2) const override;				/*This operator overload is comparing two object*/
				 void blankValue(int number) override;
				 int seperateLineToNumber(string one_line,int cur_line_number) override;
				 void findTheBlankPosition(int position[2]) override;

		private: 
				int **puzzle;
				int **goal_puzzle;		/*This uses for puzzle part*/


	};







}
#endif



