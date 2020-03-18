#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<iomanip>	
#include<string>
#include"boardarray2D.h"

using namespace std;

namespace inheritance{

boardarray2D::boardarray2D(){
	setSize(3,3);
	last_move='S';
	numberofmove=0;	
}	

boardarray2D::boardarray2D(int one,int second){
	setSize(one,second);
	last_move='S';
	numberofmove=0;
}

boardarray2D::boardarray2D(const boardarray2D &other){
	last_move=other.last_move;
	numberofmove=other.numberofmove;
	linenumber=other.linenumber;
	x=other.x;

	puzzle = new int*[linenumber];
	for(int i=0;i<linenumber;i++){
		puzzle[i] = new int[x];
	}	

	goal_puzzle = new int*[linenumber];
	for(int i=0;i<linenumber;i++){
		goal_puzzle[i] = new int[x];
	}


	
	for(int i=0;i<linenumber;i++){
		for(int j=0;j<x;j++){
			puzzle[i][j]=other.puzzle[i][j];	
		}
	}
	for(int i=0;i<linenumber;i++){
		for(int j=0;j<x;j++){
			goal_puzzle[i][j]=other.goal_puzzle[i][j];	
		}
	}
	

}
boardarray2D& boardarray2D::operator=(const boardarray2D &other){
	if(this==&other)
		return *this;
	else{
			deletePuzzle(puzzle,goal_puzzle);
			last_move=other.last_move;
			numberofmove=other.numberofmove;
			linenumber=other.linenumber;
			x=other.x;

			puzzle = new int*[linenumber];
			for(int i=0;i<linenumber;i++){
				puzzle[i] = new int[x];
			}	

			goal_puzzle = new int*[linenumber];
			for(int i=0;i<linenumber;i++){
				goal_puzzle[i] = new int[x];
			}
			
			
			for(int i=0;i<linenumber;i++){
				for(int j=0;j<x;j++){
					puzzle[i][j]=other.puzzle[i][j];	
				}
			}
			for(int i=0;i<linenumber;i++){
				for(int j=0;j<x;j++){
					goal_puzzle[i][j]=other.goal_puzzle[i][j];	
				}
			}
	}
}

boardarray2D::~boardarray2D(){
	deletePuzzle(puzzle,goal_puzzle);
	AbstractBoard::numofboard--;
}

void boardarray2D::setSize(int height,int width){
	linenumber=height;
	x=width;
	if(x<1 || linenumber<1){
		x=3;
		linenumber=3;
	}
	reset();
}

void boardarray2D::deletePuzzle(int **puzzle,int **goal_puzzle){
	for(int i=0;i<linenumber;i++)
		delete [] puzzle[i];
	delete [] puzzle;
	for(int i=0;i<linenumber;i++)
		delete [] goal_puzzle[i];
	delete [] goal_puzzle;

}


void boardarray2D::addElement(int a,int cur_line_num,int number){
int *temp;
	temp = new int[a];
		for(int i=0;i<a;i++)
			temp[i]=puzzle[cur_line_num][i];
	puzzle[cur_line_num] = new int[a+1];
	for(int i=0;i<a;i++)
		puzzle[cur_line_num][i]=temp[i];
	puzzle[cur_line_num][a]=number;
	
	delete [] temp;
}
void boardarray2D::reset(){
 int i=0,j=0,k=0;		
		puzzle = new int*[linenumber];
		for(int k=0;k<linenumber;k++){
			puzzle[k] = new int[x];
		}
		goal_puzzle = new int*[linenumber];
		for(int k=0;k<linenumber;k++){
			goal_puzzle[k] = new int[x];
		}
		for(j=0;j<linenumber;j++){				/*This is loop that fills*/
			for(i=0;i<x;i++){
					/*If in the file doesnt have the wall like 00 then it will fill*/
					puzzle[j][i]=k+1;
					goal_puzzle[j][i]=k+1;
					k++;
			}							/*-1 will be number to use blank that I chose*/
		}
		puzzle[linenumber-1][x-1]=-1;
		goal_puzzle[linenumber-1][x-1]=-1;		/*This is blank that will be move*/
			
}

void boardarray2D::print() const{
 int i=0,j=0;
	cout << "\n";
	for(j=0;j<linenumber;j++){						/*This is loop that prints*/
		for(i=0;i<x;i++){
			if(puzzle[j][i]==-1){
				cout<< setw(3) << " " <<" ";		/*This setw funcion is  giving 3 digit for the number*/
			}
			else{ 	
				if(puzzle[j][i]>=0 && puzzle[j][i]<=9){
					cout<<" 0"<<puzzle[j][i] <<" ";
				}
				else
					cout<< setw(3) << puzzle[j][i] <<" ";
			}
		}		
		cout << "\n\n";
	}	
 
}

int boardarray2D::readFromFile(string file_name){
 string one_line="";
 ifstream readf;
 const string blank="bb";			/*I also use const here not to change the bb value*/					
 int number_blank,i=0,k=0;
 int success=1;
		number_blank=convertToNumber(blank); 			/*Blank string's integer number*/
		if(file_name==""){	
			cout << "Please enter the your game name file\n";
			cin >> file_name;
		}
		readf.open(file_name);
		if(!readf.is_open() ){
			cout << "There isn't  any file as you've written!\n";	
			cout << "Please enter the valid file name \n";
			success=0;
		}
		else{	deletePuzzle(puzzle,goal_puzzle);
			linenumber=lineNumber(file_name); /*This is for finding line number for loop*/
			
			puzzle = new int*[linenumber];
			for(i=0;i<linenumber;i++){
				getline(readf,one_line);
				x=seperateLineToNumber(one_line,i);
				one_line="";	
			}
			blankValue(number_blank);
				goal_puzzle = new int*[linenumber];
				for(int l=0;l<linenumber;l++){
					goal_puzzle[l] = new int[x];
				}
				for(int j=0;j<linenumber;j++){				/*This is loop that fills*/				
					for(int m=0;m<x;m++){
						if( puzzle[j][m]!=0 ){				/*If in the file doesnt have the wall like 00 then it will fill*/
							goal_puzzle[j][m]=k+1;
							k++;		
						}
						else{
				 			goal_puzzle[j][m]=0;			/*Else there is 00  So goal puzzle is 0*/
						}
					}							/*-1 will be number to use blank that I chose*/
				}
				goal_puzzle[linenumber-1][x-1]=-1;		/*This is blank that will be move*/

		}

	
	 
 readf.close();
 return success;
}

int  boardarray2D::seperateLineToNumber(string one_line,int cur_line_number){
 int i=0;
 int temp=0;
 string word="";
 char space=' ';
		while(one_line[temp]!='\0'){		/*This is sapareting words*/
			if(one_line[temp]==space){
				addElement(i,cur_line_number,convertToNumber(word));
				i++;
		  		word = "";
			}	
			else{	
				word=word+one_line[temp];
			}
			temp++;	
		}
		addElement(i,cur_line_number,convertToNumber(word));	/*This is for the last word that we found*/
		i++;
          	word = "";	
 return i;	 
}

void boardarray2D::blankValue(int number){
  int i=0,j=0;
	for(i=0;i<linenumber;i++){
		for(j=0;j<x;j++){		
			if(puzzle[i][j]==number){
				puzzle[i][j]=-1;
			}
		}

  }
}
bool boardarray2D::move(char letter){							/*This returns true if movement is success else false*/
 int position[2]={linenumber-1,x-1};
 int y_cur=0,x_cur=0;
	 findTheBlankPosition(position);
	 y_cur=position[0];
	 x_cur=position[1];
				if(letter=='R'){
					if(x_cur!=x-1){						/*This is for right move to move blank to right when you push the R*/
						if(puzzle[y_cur][x_cur]!=0 && puzzle[y_cur][x_cur+1]!=0){
							swap(puzzle[y_cur][x_cur],puzzle[y_cur][x_cur+1]);	/*This is swapping  values*/    
							last_move=letter;   
							numberofmove++;         
						}
						else
							return false;				
					}
					else
						return false;
							
				}
				else if(letter=='L'){ 
					   if(x_cur!=0){
						if(puzzle[y_cur][x_cur]!=0 && puzzle[y_cur][x_cur-1]!=0){	/*This is for left move to move blank to left when you push the L*/
							swap(puzzle[y_cur][x_cur],puzzle[y_cur][x_cur-1]);
							last_move=letter;
							numberofmove++;
						}
						else
							return false;	
					   }
					   else
						return false;
				}	
				else if(letter=='U'){ 
					   if(y_cur!=0){							/*This is for up move to move blank to up when you push the U*/
						if(puzzle[y_cur][x_cur]!=0 && puzzle[y_cur-1][x_cur]!=0){
							swap(puzzle[y_cur][x_cur],puzzle[y_cur-1][x_cur]);
							last_move=letter;
							numberofmove++;						
						}
						else
							return false;
					   }
					   else
						return false;
				}
				else if(letter=='D'){
					 if(y_cur!=linenumber-1){						/*This is for down move to move blank to down when you push the D*/
						if(puzzle[y_cur][x_cur]!=0 && puzzle[y_cur+1][x_cur]!=0){
							swap(puzzle[y_cur][x_cur],puzzle[y_cur+1][x_cur]);
							last_move=letter;
							numberofmove++;	
						}
						else
							return false;
					  }
					  else
						return false;
				}
 return true;
}

void boardarray2D::findTheBlankPosition(int position[2]){		/*This is finding blank position*/
 int j=0,k=0;
 int count=0;
		for(j=0;j<linenumber;j++){
			for(k=0;k<x;k++){
				if(puzzle[j][k]==-1){			/*I am making the loop stop when I find the blank position*/
					count=1;			/*If count is 1 then loop will be stop just below*/
					position[0]=j;
					position[1]=k;
						break;
				}
					
			}
			if(count==1)					/*Here is it*/
				break;		
		}
}

bool boardarray2D::operator == (const AbstractBoard &board2) const{
 int i=0,j=0;	
	for(i=0;i<linenumber;i++){						
		for(j=0;j<x;j++){
			if(puzzle[i][j]!=board2(i,j)){		
				return false;		
			}
		}
	}
	
 return true;
} 

bool boardarray2D::isSolved() const{
 int i=0,j=0;	
	for(i=0;i<linenumber;i++){						/*This loop is checking if puzzle is correct or not*/
		for(j=0;j<x;j++){
			if(puzzle[i][j]!=goal_puzzle[i][j]){		/*If there is any mismatch,then it returns 0,So puzzle is not over*/
				return false;		
			}
		}
	}
	
 return true;
}
int boardarray2D::operator () (int index1,int index2) const {
	if(index1>=linenumber || index1<0 || index2>=x || index2<0)	/*This terminates the game if indexes are not true*/
			exit(0);
	return puzzle[index1][index2];					/*else returning*/
}
void boardarray2D::writeToFile(){
 ofstream writef;
 string file_name="";
 const string blank="bb";
 int i=0,j=0;
 	cout <<"Enter the file name to save\n";
	cin >> file_name;
	
	writef.open(file_name);

	for(j=0;j<linenumber;j++){						/*This is loop that writes to the file*/
		for(i=0;i<x;i++){
			if(puzzle[j][i]==-1){
				writef <<blank;				/*This is writing to file bb instead of -1*/
					if(i!=x-1)			/*if this is not end of the line becouse end of the line doesnt have a space*/
						writef << " ";			
			}
			else{ 	
				if(puzzle[j][i]>=0 && puzzle[j][i]<=9){		
					writef <<"0"<<puzzle[j][i];	/*If there is one digit then it adds a 0 to beginning of the number*/
						if(i!=x-1)
							writef << " ";	
				}
				else{
					writef << puzzle[j][i] ;	/*This writesthe number*/
						if(i!=x-1)
							writef << " ";	
				}
			}
		}
		if(j!=linenumber-1){				/*Becouse the last line doesnt have a \n */
			writef << "\n";
		}
	}
}




}
