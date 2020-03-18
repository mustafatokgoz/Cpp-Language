#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<iomanip>							/*MUSTAFA TOKGÖZ 171044077 HOMEWORK 3*/
using namespace std;

 class NPuzzle{
	public: void setSize(int hight,int width);				
		void reset();
		void print() const;
		int readFromFile(string file_name);
		bool move(char letter);
		void shuffle(int n);
		void printReport() const;
		bool moveRandom();
		void moveIntelligent();
		void solvePuzzle();
		void writeToFile();

		int lineNumber(string file_name);		/*This is finding line number of file*/		
		void gameplay();
		void isFileOpenedAtTheBeginning(int value);	/*This is assigning if there is a file at the beginnging then 1 ,else 0*/
		
	private:
		int findTheMin(int right_block,int left_block,int up_block,int down_block);	
		int total_move=0;					/*This is for total move*/
		class Board{
			public:	void setSize(int height,int width);
				void reset();
				void print() const;
				int readFromFile(string file_name);
				bool move(char letter);
				bool isSolved() const;
				void writeToFile();

				void calculateDistance(int &left_block,int &right_block,int &up_block,int &down_block);  /*this calculates the distances */
				int calculateN();
				void isFileOpenedAtTheBeginning(int value);			/*This is assigning if there is a file at the beginnging then 1 ,else 0*/

			private:
				int tenPower(int pow);
				void blankValue(int number);
				void swap(int &p1,int &p2);
				int seperateLineToNumber(string one_line,int cur_line_number);
				void findTheBlankPosition(int position[2]); 
				int convertToNumber(string word);
				bool checkingTruePosition(const int value,int y_pos,int x_pos);
				inline int absoluteValue(int number);				

				int puzzle[9][9],goal_puzzle[9][9];		/*This uses for puzzle part*/
				int linenumber=0,x=0,isfileopen=0;		/*linenumber is row , x is column*/
		};
		Board board;
 };


int main(int argc , char *argv[]){
 NPuzzle user;
 int height=0,width=0;
 decltype (width) n=0;
 char temp='0';
 srand(time(NULL));
	cout << "\nWelcome to N-puzzle game !!\n\n" << "Let's start the game \n\n";
	if(argc==1){
		 cout<<"Please enter the problem hight and width\n";
		while(1){
			cout<<"hight : ";
 			cin >> temp;
			if(temp>='3' && temp<='9'){
				height=temp-48;		/*this is converting character to number*/
				break;
			}
			else
				cout << "Please enter a number from 3 to 9\n";
 		}
		while(1){
			cout<<"width : ";
 			cin >> temp;
			if(temp>='3' && temp<='9'){
				width=temp-48;		/*this is converting character to number*/
				break;
			}
			else
				cout << "Please enter a number from 3 to 9\n";
 		}
		user.setSize(height,width);
		user.isFileOpenedAtTheBeginning(0);		 /*I assign 0 becouse there isn't file at the beginning*/
		user.reset();					/*This fills the puzzle and goal puzzle*/
		n=height*width;
		user.shuffle(n);
		user.gameplay();
 	}
	
	else{
		if(user.readFromFile(argv[1])==1){
			user.isFileOpenedAtTheBeginning(1); 	 /*I assign 1 becouse there is file at the beginning*/
			user.reset();				/*This fills the puzzle and goal puzzle*/
			user.gameplay();		
		}

	}



 return 0;
}

void NPuzzle::isFileOpenedAtTheBeginning(int value){
	board.isFileOpenedAtTheBeginning(value);
}
void NPuzzle::Board::isFileOpenedAtTheBeginning(int value){		/*This is assigning if there is a file at the beginnging then 1 ,else 0*/
	isfileopen=value;
}				
void NPuzzle::setSize(int height,int width){
 board.setSize(height,width);

}

void NPuzzle::Board::setSize(int height,int width){
  linenumber=height;
  x=width;
}


void NPuzzle::print() const{
 board.print();
}

void NPuzzle::Board::print() const{
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

void NPuzzle::reset(){
 board.reset();
}
void NPuzzle::Board::reset(){
 int i=0,j=0,k=0;
	if(isfileopen==1){
		for(j=0;j<linenumber;j++){						/*This is loop that fills*/
			for(i=0;i<x;i++){
				if(puzzle[j][i]!=0){				/*If in the file doesnt have the wall like 00 then it will fill*/
					goal_puzzle[j][i]=k+1;
					k++;		
				}
				else{
					goal_puzzle[j][i]=0;			/*Else there is 00  So goal puzzle is 0*/
				}
			}							/*-1 will be number to use blank that I chose*/
		}
		goal_puzzle[linenumber-1][x-1]=-1;		/*This is blank that will be move*/
	}		
	else{
		for(j=0;j<linenumber;j++){						/*This is loop that fills*/
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
}

int NPuzzle::readFromFile(string file_name){
	return  board.readFromFile(file_name);
}

int NPuzzle::Board::readFromFile(string file_name){
 NPuzzle temp;
 string one_line="";
 ifstream readf;
 const string blank="bb";			/*I also use const here not to change the bb value*/					
 int number_blank,i=0,success=1;
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
		else{
			linenumber=temp.lineNumber(file_name); /*This is for finding line number for loop*/
			for(i=0;i<linenumber;i++){
				getline(readf,one_line);
				x=seperateLineToNumber(one_line,i);
				one_line="";	
			}
			blankValue(number_blank);
					
				
		}
	
	 
 readf.close();
 return success;
}
int NPuzzle::Board::calculateN(){
	return linenumber*x;
}
int NPuzzle::lineNumber(string file_name){			/*This is finding the line number of file*/
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

int  NPuzzle::Board::seperateLineToNumber(string one_line,int cur_line_number){
 int i=0;
 int temp=0;
 string word="";
 char space=' ';

		while(one_line[temp]!='\0'){			/*This is sapareting words*/
			if(one_line[temp]==space){
				puzzle[cur_line_number][i]=convertToNumber(word);	/*Then converting word to number*/
				i++;
		  		word = "";
			}	
			else{
				word=word+one_line[temp];
			}
			temp++;
		}
		puzzle[cur_line_number][i]=convertToNumber(word);	/*This is for the last word that we found*/
		i++;
          	word = "";	
		
 return i;	 
}

void NPuzzle::Board::blankValue(int number){
  int i=0,j=0;
	for(i=0;i<linenumber;i++){
		for(j=0;j<x;j++){		
			if(puzzle[i][j]==number){
				puzzle[i][j]=-1;
			}
		}

  }
}


int NPuzzle::Board::tenPower(int pow){					/*This is founding power of the number for the converting string*/
 int i=0,t_p=1;
	 if(pow==1){
		return 1;
	 }
	 for(i=0;i<pow-1;i++){
		t_p=t_p*10;
	 }
 return t_p;
}



int NPuzzle::Board::convertToNumber(string word){
			/*This is converting string to number*/
 int number=0,i=0,j=0;
	for(i=0;word[i]!='\0';i++);				/*This is founding end of the string number then I convert the string to number with ten_pow function */
	for(i;i>0;i--){
		number=number+(static_cast<int>(word[j])-48)*tenPower(i);
		j++;
	}
	
 return number;
}
bool NPuzzle::move(char letter){
 return board.move(letter);
}
bool NPuzzle::Board::move(char letter){							/*This returns true if movement is success else false*/
 int position[2]={linenumber-1,x-1};
 int y_cur=0,x_cur=0;
	 findTheBlankPosition(position);
	 y_cur=position[0];
	 x_cur=position[1];
				if(letter=='R'){
					if(x_cur!=x-1){						/*This is for right move to move blank to right when you push the R*/
						if(puzzle[y_cur][x_cur]!=0 && puzzle[y_cur][x_cur+1]!=0){
							swap(puzzle[y_cur][x_cur],puzzle[y_cur][x_cur+1]);	/*This is swapping  values*/                   
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
						}
						else
							return false;
					  }
					  else
						return false;
				}
 return true;
}
void NPuzzle::Board::swap(int &p1,int &p2){						/*This is swapping values*/
 int temp;
	temp=p1;
	p1=p2;
	p2=temp;
}

void NPuzzle::Board::findTheBlankPosition(int position[2]){		/*This is finding blank position*/
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
		
bool NPuzzle::moveRandom(){			/*If movement is success then it will return true so that  solvePuzzle function count the moves*/
 int temp_random=0;
		temp_random=rand()%4;		/*This is random number that will be used randomly shuffle just below*/	/*Here they are*/
			if(temp_random==0){		
				if(move('R')==true)
					return true;
					
			}
			else if(temp_random==1){			
				if(move('L')==true)
					return true;
					
			}
			else if(temp_random==2){
				if(move('U')==true)
					return true;
					
			} 
			else {
				if(move('D')==true)
					return true;		
			}
 return false;
}


void NPuzzle::shuffle(int n){
 int i=0;				
	for(i=0;i<n;i++){				  		/*This shuffles the puzzle*/					
			if(moveRandom()==false)
					i--;   			
	}
}

bool NPuzzle::Board::isSolved() const{
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

void NPuzzle::gameplay(){				/*This is gameplay*/
 char selection='Q';							
 int x_cur=0,y_cur=0;
 int n=board.calculateN();				/*This calculate n that is row*column so linenumber*x */
 string file_name="";
	if(board.isSolved()==false){
		cout << "Your initial random board is \n";
		 	print();
		cout << "Enter your move\n(R=Right, L=Left, U=Up, D=Down, I=Intelligent, V=Solve, T=Total Move, Y=Load File, E=Save Game, Q=Quit)\n";
		while(board.isSolved()==false){
			cout <<"Your move : ";
			cin >> selection;
			switch (selection){
				
				case 'R' : if(move('R')==true)
						total_move++;
					   else 
						cout <<"You hit the wall,Please be carefull\n";		
					break;
				case 'L' : if(move('L')==true)
						total_move++;
					   else
						cout <<"You hit the wall,Please be carefull\n";	
					break;
				case 'U' : if(move('U')==true)
						total_move++;
					   else 
						cout <<"You hit the wall,Please be carefull\n";	
					break;
				case 'D' : if(move('D')==true)
						total_move++;
					   else
						cout <<"You hit the wall,Please be carefull\n";	
					break;
				case 'S' : isFileOpenedAtTheBeginning(0);
					   reset();				/*I am filling puzzle with goal puzzle then shuffling*/
					   n=board.calculateN();
					   shuffle(n);				/*This is shuffling the puzzle when you push the S*/
					   total_move=0;
					break;
				case 'O' : if(readFromFile(file_name)==1){	
							isFileOpenedAtTheBeginning(1);					/*This reads the file*/
							total_move=0;					/*Total move resets*/
					 		reset();		
					   }
					break;
				case 'E' : writeToFile();			/*This writes to file*/
					break;
				case 'T' : printReport();			/*This prints the move number*/
					break;
				case 'I' : moveIntelligent();			/*This is doing intelligent move*/
					break;
				case 'V' : solvePuzzle();			/*This is solving puzzle*/
					break;
				case 'Q' : printReport();			/*This prints the move number when you quit*/
					break;							
		
				default : cout << "Please enter a valid operation\n"
						<<"(R=Right, L=Left, U=Up, D=Down, I=Intelligent,V=Solve, T=Total Move, O=Load File, E=Save Game, Q=Quit,)\n";
					break;
				}
			if(selection=='Q')
				break;	
			if(selection!='V')			/*Becouse I already print the puzzle int solvePuzzle function*/
				print();
			if(board.isSolved()==true){				/*This is checking if puzzle is over or not*/
					cout << "Congratulations , Problem is solved ! :)\n";
					cout << "Total number of moves is " << total_move << endl;
					break;
			}
								
		}

	}
	else{
		reset();
		n=board.calculateN();			/*This calculate linenumber*x for shuffle*/
		shuffle(n);
		gameplay();
	}

}

void NPuzzle::printReport() const{
	cout << "Total number of moves is " << total_move << endl;
	if(board.isSolved()==true)				/*This is checking if puzzle is over or not*/
					cout << "Congratulations , Problem is solved ! :)\n";
	else 
		 cout << "Solution isn't found yet " << endl;
}

void NPuzzle::Board::calculateDistance(int &left_block,int &right_block,int &up_block,int &down_block){  /*this calculates the distances by changing places with blank*/
 int position[2]={linenumber-1,x-1};			/*This is inital position of blank*/
 int x_cur=0,y_cur=0;					/*This is for below algorithm*/
 int size_square=linenumber*x;				/*just for assigning maximum number becouse I want to find the least distance*/
	left_block=size_square; right_block=size_square; up_block=size_square; down_block=size_square;
	findTheBlankPosition(position);
	y_cur=position[0];
	x_cur=position[1];
	
	if(x_cur!=x-1){	
			if(checkingTruePosition(puzzle[y_cur][x_cur+1],y_cur,x_cur+1)==false)
				right_block=absoluteValue((y_cur*linenumber+x_cur+1)-puzzle[y_cur][x_cur+1]); 		/*This is calculating distance for right*/
		
	}
	if(x_cur!=0){
			if(checkingTruePosition(puzzle[y_cur][x_cur-1],y_cur,x_cur-1)==false)			/*This is calculating distance for left*/
				left_block=absoluteValue((y_cur*linenumber+x_cur+1)-puzzle[y_cur][x_cur-1]);
		
	}
	if(y_cur!=0){
		if(checkingTruePosition(puzzle[y_cur-1][x_cur],y_cur-1,x_cur)==false)				/*This is calculating distance for up*/
			up_block=absoluteValue((y_cur*linenumber+x_cur+1)-puzzle[y_cur-1][x_cur]);
	}
	if(y_cur!=linenumber-1){		
			if(checkingTruePosition(puzzle[y_cur+1][x_cur],y_cur+1,x_cur)==false)			/*This is calculating distance for down*/
				down_block=absoluteValue((y_cur*linenumber+x_cur+1)-puzzle[y_cur+1][x_cur]);
	}


}
bool NPuzzle::Board::checkingTruePosition(const int value,int y_pos,int x_pos){			/*I wrote the keyword const here!! becouse value shouldn't change*/
	if(goal_puzzle[y_pos][x_pos]==value)
		return true;							/*This is checking the number is true position or not*/	
	else 
		return false;
}


void NPuzzle::moveIntelligent(){
 int RIGHT=1,LEFT=2,UP=3,DOWN=4;						/*this is for which is less number to destination*/
 int left_block,right_block,up_block,down_block;
 int which_is_less;						
	
		board.calculateDistance(left_block,right_block,up_block,down_block);
		
		which_is_less=findTheMin(right_block,left_block,up_block,down_block);			/*This finding minimum distance for around the blank*/

			if(which_is_less==RIGHT){			
				if(move('R')==true)
					total_move++;
			}
			else if(which_is_less==LEFT){
				if(move('L')==true)
					total_move++;
			}
			else if(which_is_less==UP){
				if(move('U')==true)
					total_move++;
			}
			else{
				if(move('D')==true)
					total_move++;
			}

}
inline int NPuzzle::Board::absoluteValue(int number){		/*I use the keyword inline here!!*/	/*This is finding absolute value*/
	if(number<0)
		return (-1)*number;

	else 
		return number;	
}

int NPuzzle::findTheMin(int right_block,int left_block,int up_block,int down_block){	
 int min;
 int RIGHT=1,LEFT=2,UP=3,DOWN=4; 						/*this is for which is less number to destination*/
 int which_is_less;
		if(right_block==0)						/*If minimum distance is 0 then I needn't to know which is less*/
			which_is_less=RIGHT;
		else if(left_block==0)						/*So directly I moved the blanks*/
			which_is_less=LEFT;	
		else if(up_block==0)
			which_is_less=UP;
		else if(down_block==0)
			which_is_less=DOWN;
			
		else{								/*If noonne is 0 then i check which is less*/
			if(right_block<=left_block){
				min=right_block;
				which_is_less=RIGHT;
			}
			else{
				min=left_block;
				which_is_less=LEFT;
			}
			
			if(up_block<=down_block){
				if(up_block<=min){
					min=up_block;
					which_is_less=UP;
				}
			}		
			else{
				if(down_block<=min){
					min=down_block;
					which_is_less=DOWN;			
				}
			}
		}
 return which_is_less;											/*Then I return the direction*/
}

void NPuzzle::solvePuzzle(){
 auto i=0,j=0,how_manyi=10,how_manyr=5;	 /*how_manyi , how_manyr are number of how many move in the loop for intelligent and random*//*I use the keyword auto here!!*/			

		while(board.isSolved()==false){		/*this loop is solving the problem*/
			for(i=0;i<how_manyi;i++){
				if(board.isSolved()==false){		/*this is for intelligent move*/
					moveIntelligent();
					print();					
				}
				else
					break;
			}		

			for(j=0;j<how_manyr;j++){
				if(board.isSolved()==false){		/*this is for random move*/				
					if(moveRandom()==true){
					total_move++;
					print();
					}
				}
				else
					break;
				
			}
		
		}
}
void NPuzzle::writeToFile(){
	board.writeToFile();
}
void NPuzzle::Board::writeToFile(){
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





