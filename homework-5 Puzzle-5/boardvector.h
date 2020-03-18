#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H

#include<iostream>
#include<string>
#include<vector>
#include"abstractboard.h"

using namespace std;


namespace inheritance{
	class BoardVector : public AbstractBoard {
		public : BoardVector();
			 BoardVector(int h,int w);
			 BoardVector(const BoardVector &other);
			 void setSize(int height,int width) override;
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

		private :
							
			vector<vector<int> > puzzle;
			vector<vector<int> > goal_puzzle;		/*This uses for puzzle part*/
	};
}

#endif



