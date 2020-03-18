#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<iomanip>	
#include<string>
#include<vector>
#include"abstractboard.h"

using namespace std;

namespace inheritance{

	AbstractBoard::AbstractBoard(){
		linenumber=0;
		x=0;
		last_move='S';
		numberofmove=0;
		numofboard++;
	}

	int AbstractBoard::NumberOfMoves(){
		return numberofmove;
	}
	char AbstractBoard::LastMove(){
		return last_move;
	}

	int AbstractBoard::lineNumber(string file_name){			/*This is finding the line number of file*/
	 string temp;
	 ifstream file;
	 int line=0;

		file.open(file_name);
		while(getline(file,temp)){
			line++;
		}
	 file.close();
	 return line;
	}

	int AbstractBoard::tenPower(int pow){					/*This is founding power of the number for the converting string*/
	 int i=0,t_p=1;
		 if(pow==1){
			return 1;
		 }
		 for(i=0;i<pow-1;i++){
			t_p=t_p*10;
		 }
	 return t_p;
	}

	int AbstractBoard::convertToNumber(string word){
				/*This is converting string to number*/
	 int number=0,i=0,j=0;
		for(i=0;word[i]!='\0';i++);				/*This is founding end of the string number then I convert the string to number with ten_pow function */
		for(i;i>0;i--){
			number=number+(static_cast<int>(word[j])-48)*tenPower(i);
			j++;
		}
		
	 return number;
	}
	int AbstractBoard::NumberOfBoards(){
		return 	numofboard;
	}
	void AbstractBoard::swap(int &p1,int &p2){						/*This is swapping values*/
	 int temp;
		temp=p1;
		p1=p2;
		p2=temp;
	}
	int AbstractBoard::getColumn(){
		return linenumber;
	}
	int AbstractBoard::getRow(){
		return x;
	}

	


}



