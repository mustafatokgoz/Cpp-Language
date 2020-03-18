#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<iomanip>	
#include<vector>						/*MUSTAFA TOKGÖZ 171044077 HOMEWORK 4*/
using namespace std;

 class NPuzzle{
										
	private:
		int total_move=0;					/*This is for total move*/
		class Board{
			public:	void setSize(int height,int width);
				void reset();
				void print();
				int readFromFile();
				bool move(char letter);
				bool isSolved() const;
				void writeToFile();
				int calculateN();
				void isFileOpenedAtTheBeginning(int value);			/*This is assigning if there is a file at the beginnging then 1 ,else 0*/

				int getRow(){return linenumber;};				/*This is returning linenumber so row number*/
				int getColumn(){return x;};					/*This is returning x so column number*/
				int  operator () (int index1,int index2);			/*this overload is taking two index and return corresponding cell*/
				bool operator ==(Board &board2);				/*This operator overload is comparing two object*/
				void setFileName(string a);					/*This is getting file name*/
				int isSuccess();						/*this is retruning if it is success*/

				char LastMove();						/*This is retruning last move*/
				void setLastMove(char letter);					/*this is setting last move*/
				void setNumberOfMove();						/*This is setting numberofmove*/
				int NumberOfMoves();						/*This is returning numberofmove*/
				int NumberOfBoards(vector<Board> objects);			/*Thşs is returning number of boards*/
				void copyToVector(Board &board2);				/*This is copying to vector obejcts*/
				
				
			private:
				int tenPower(int pow);
				void blankValue(int number);
				void swap(int &p1,int &p2);
				int seperateLineToNumber(string one_line,int cur_line_number);
				void findTheBlankPosition(int position[2]); 
				int convertToNumber(string word);				
				
				vector<vector<int> > puzzle;
				vector<vector<int> > goal_puzzle;		/*This uses for puzzle part*/

				int linenumber=0,x=0,isfileopen=0;		/*linenumber is row number , x is column number*/
				string file_name="";int success=1;
				char last_move='S'; int numberofmove=0;		/*These are datas for boards*/
		};
		Board board;
		vector<Board> objects;

	public: void setSize(int hight,int width);				
		void reset();
		void print() ;
		int readFromFile();
		bool move(char letter);
		void shuffle(int n);
		void printReport() const;
		bool moveRandom();
		void solvePuzzle();
		void writeToFile();

		void setFileName(string a);
		int isSuccess();		

		int lineNumber(string file_name);		/*This is finding line number of file*/		
		void gameplay(NPuzzle &user);
		void isFileOpenedAtTheBeginning(int value);	/*This is assigning if there is a file at the beginnging then 1 ,else 0*/
		bool checkIfThereis(Board &object);		/*This is checking Whether There is a board like current board*/
		

		friend ostream &operator << (ostream &outputStream,Board &board); 	/*This is for printing*/
		friend istream &operator >> (istream &inputStream,NPuzzle &user);	/*This is for taking file*/
 };


int main(int argc , char *argv[]){
 NPuzzle user;
 int height=0,width=0;
 decltype (width) n=0;
 srand(time(NULL));
	cout << "\nWelcome to N-puzzle game !!\n\n" << "Let's start the game \n\n";
	if(argc==1){
		 cout<<"Please enter the problem hight and width\n";
		while(1){
			cout<<"hight : ";
 			cin >> height;
			if(height>=3 && height<=9){
				break;
			}
			else
				cout << "Please enter a number from 3 to 9\n";
 		}
		while(1){
			cout<<"width : ";
 			cin >> width;
			if(width>=3 &&  width<=9){
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
		user.gameplay(user);
 	}
	
	else{
		user.setFileName(argv[1]);
		cin >> user;				/*This is taking the board from file*/
		if(user.isSuccess()==1){
			user.isFileOpenedAtTheBeginning(1); 	 	
			user.reset();					
			user.gameplay(user);		
		}
		
	}



 return 0;
}
void NPuzzle::setFileName(string a){
	board.setFileName(a);
}
void NPuzzle::Board::setFileName(string a){
	file_name=a;
}
int NPuzzle::isSuccess(){
	return board.isSuccess();
}
int NPuzzle::Board::isSuccess(){
	return success;
}

int NPuzzle::Board::operator () (int index1,int index2) {
	if(index1>=linenumber || index1<0 || index2>=x || index2<0)	/*This terminates the game if indexes are not true*/
			exit(0);
	return puzzle[index1][index2];					/*else returning*/
}


ostream &operator <<(ostream &outputStream,NPuzzle::Board &board){	/*This is for printing*/ /*I also use () operator to take indexes in this function*/
 int i=0,j=0;
 		outputStream << "\n";
			for(j=0;j<board.getRow();j++){	
				for(i=0;i<board.getColumn();i++){
					if(board(j,i)==-1){
						outputStream << setw(3) << " " <<" ";	
					}
					else{ 	
						if(board(j,i)>=0 && board(j,i)<=9){
							outputStream <<" 0"<<board(j,i) <<" ";
						}
						else
							outputStream << setw(3) << board(j,i) <<" ";
					}
				}		
				outputStream << "\n\n";
			}
	return outputStream;
}
		



int NPuzzle::Board::NumberOfMoves(){
	return numberofmove;
}
char NPuzzle::Board::LastMove(){
	return last_move;
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

void NPuzzle::print() {
 board.print();
}

void NPuzzle::Board::print() {
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
  objects.resize(0);	/*This is resising objects to 0 */
}
void NPuzzle::Board::reset(){
 int i=0,j=0,k=0;
	if(isfileopen==1){
			goal_puzzle.resize(0);			/*At the beginning puzzles resizing 0 */
		for(j=0;j<linenumber;j++){				/*This is loop that fills*/				
			goal_puzzle.push_back(vector<int>());		/*Then I push_back to vector*/
			for(i=0;i<x;i++){
				if( puzzle[j][i]!=0 ){				/*If in the file doesnt have the wall like 00 then it will fill*/
					goal_puzzle[j].push_back(k+1);
					k++;		
				}
				else{
		 		goal_puzzle[j].push_back(0);			/*Else there is 00  So goal puzzle is 0*/
				}
			}							/*-1 will be number to use blank that I chose*/
		}
		goal_puzzle[linenumber-1][x-1]=-1;		/*This is blank that will be move*/
	}		
	else{	goal_puzzle.resize(0);
		puzzle.resize(0);				/*At the beginning puzzles resizing 0 */
		for(j=0;j<linenumber;j++){							
				goal_puzzle.push_back(vector<int>());
				puzzle.push_back(vector<int>());			/*This is loop that fills*/
			for(i=0;i<x;i++){
					/*If in the file doesnt have the wall like 00 then it will fill*/
					puzzle[j].push_back(k+1);
					goal_puzzle[j].push_back(k+1);
					k++;		
				
				
			}							/*-1 will be number to use blank that I chose*/
		}
		puzzle[linenumber-1][x-1]=-1;
		goal_puzzle[linenumber-1][x-1]=-1;		/*This is blank that will be move*/

	}			
}

istream &operator >> (istream &inputStream,NPuzzle &user){	/*I use for taking the file board*/
	user.readFromFile();		
	return inputStream;
}


int NPuzzle::readFromFile(){
	objects.resize(1);			/*I resizes objects to 1*/
	board.readFromFile();
}

int NPuzzle::Board::readFromFile(){
 NPuzzle temp;
 string one_line="";
 ifstream readf;
 const string blank="bb";			/*I also use const here not to change the bb value*/					
 int number_blank,i=0;
	success=1;
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
		else{	puzzle.resize(0);
			linenumber=temp.lineNumber(file_name); /*This is for finding line number for loop*/
			
			for(i=0;i<linenumber;i++){
				puzzle.push_back(vector<int>());	/*I use the push back*/
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
		while(one_line[temp]!='\0'){		/*This is sapareting words*/
			if(one_line[temp]==space){
				puzzle[cur_line_number].push_back(convertToNumber(word));	/*Then converting word to number*/
				i++;
		  		word = "";
			}	
			else{	
				word=word+one_line[temp];
			}
			temp++;	
		}
		puzzle[cur_line_number].push_back(convertToNumber(word));	/*This is for the last word that we found*/
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
void NPuzzle::Board::setLastMove(char letter){
	last_move=letter;
}

void NPuzzle::Board::setNumberOfMove(){
		numberofmove++;
}

bool NPuzzle::move(char letter){
	objects.resize(1);
	if(board.move(letter)==true){
		objects[0].setLastMove(letter);		/*This is setting objects last move*/
		objects[0].setNumberOfMove();		/*This is setting objects numberofmove*/
		return true;
	}
 	else
		return false;
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
		objects.resize(1);
		temp_random=rand()%4;		/*This is random number that will be used randomly shuffle just below*/	/*Here they are*/
			if(temp_random==0){		
				if(move('R')==true){
					objects[0].setLastMove('R');
					return true;
				}
					
			}
			else if(temp_random==1){			
				if(move('L')==true){
					objects[0].setLastMove('L');
					return true;
				}
					
			}
			else if(temp_random==2){
				if(move('U')==true){
					objects[0].setLastMove('U');
					return true;
				}
					
			} 
			else {
				if(move('D')==true){
					objects[0].setLastMove('D');
					return true;
					}		
			}
 return false;
}


void NPuzzle::shuffle(int n){
 int i=0;
	objects.resize(1);				
	for(i=0;i<n;i++){				  		/*This shuffles the puzzle*/					
			if(moveRandom()==false)
					i--;   			
	}
}

bool NPuzzle::Board::operator == (Board &board2){
 int i=0,j=0;	
	for(i=0;i<linenumber;i++){						/*This loop is checking if puzzle is correct or not*/
		for(j=0;j<x;j++){
			if(puzzle[i][j]!=board2.puzzle[i][j]){		/*If there is any mismatch,then it returns 0,So puzzle is not over*/
				return false;		
			}
		}
	}
	
 return true;
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

void NPuzzle::gameplay(NPuzzle &user){				/*This is gameplay*/
 char selection='Q';							
 int x_cur=0,y_cur=0;
 int n=board.calculateN();				/*This calculate n that is row*column so linenumber*x */
	if(board.isSolved()==false){
		cout << "Your initial random board is \n";
		 	cout << board;
		cout << "Enter your move\n(R=Right, L=Left, U=Up, D=Down, S=Shuffle , V=Solve, T=Total Move, O=Load File, E=Save Game, Q=Quit)\n";
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
				case 'S' : isFileOpenedAtTheBeginning(1);
					   reset();				/*I am filling puzzle with goal puzzle then shuffling*/
					   n=board.calculateN();
					   shuffle(n);				/*This is shuffling the puzzle when you push the S*/
					   total_move=0;
					break;
				case 'O' : 	setFileName("");		/*Before I get the file name i m setting filename ""*/
						cin >> user;			/*This is taking the file*/
						setFileName("");
						if(board.isSuccess()==1){	
							isFileOpenedAtTheBeginning(1);
							total_move=0;					/*Total move resets*/
					 		reset();		
					  	 }
					break;
				case 'E' : writeToFile();			/*This writes to file*/
					break;
				case 'T' : printReport();			/*This prints the move number*/
					break;
				case 'V' : solvePuzzle();			/*This is solving puzzle with new algorithm*/
					break;
				case 'Q' : printReport();			/*This prints the move number when you quit*/
					break;							
		
				default : cout << "Please enter a valid operation\n"
						<<"(R=Right, L=Left, U=Up, D=Down, S=Shuffle ,V=Solve, T=Total Move, O=Load File, E=Save Game, Q=Quit,)\n";
					break;
				}
			if(selection=='Q')
				break;	
			if(selection!='V')			/*Becouse I already print the puzzle int solvePuzzle function*/
				cout << board;
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
		gameplay(user);
	}

}

void NPuzzle::printReport() const{
	cout << "Total number of moves is " << total_move << endl;
	if(board.isSolved()==true)				/*This is checking if puzzle is over or not*/
					cout << "Congratulations , Problem is solved ! :)\n";
	else 
		 cout << "Solution isn't found yet " << endl;
}

void NPuzzle::Board::copyToVector(Board &board2){		/*This is copying the object to vectors*/
 int i=0,j=0;
	board2.puzzle.resize(0);				/*This is resizing 0 becouse It is called  more than 1 */
	board2.goal_puzzle.resize(0);

	for(i=0;i<linenumber;i++){
		board2.puzzle.push_back(vector<int>());		/*I am pushing back to vector*/
		for(j=0;j<x;j++){
			board2.puzzle[i].push_back(puzzle[i][j]);
		}
	}
	for(i=0;i<linenumber;i++){
		board2.goal_puzzle.push_back(vector<int>());
		for(j=0;j<x;j++){
			board2.goal_puzzle[i].push_back(goal_puzzle[i][j]);
		}
	}
	
	board2.linenumber=linenumber;
	board2.x=x;
	board2.numberofmove=numberofmove;
}

bool NPuzzle::checkIfThereis(Board &obje){		/*This is checking Whether There is a board like current board*/
 int i=0;	
		for(i=0;i<objects.size();i++){
			if(objects[i]==obje){		/*I also use == operator here to control*/
				return true;
			}
		}

 return false;
		
}



int NPuzzle::Board::NumberOfBoards(vector<Board> objects){
	return objects.size(); 
}

void NPuzzle::solvePuzzle(){
 auto i=0,j=1;
 Board temp;		/*This is temporary object to copy to vector*/

 vector<char> a;
 int k=0,m=0;
 char t;		/*This is temporary char*/
 int nom=0;		/*This is number of moves to add total move*/
	objects.resize(1);

		board.copyToVector(objects[0]);		/*I copy original board to first vector*/
		/*Firstly I take the first element from this vector,Apply all possible moves to this board and push_back each result back to the vector.Before doing the push back, I check if the same board is already in the vector. Ifone of the pushed objects is the solution then my solution is found.*/
		while(objects[i].isSolved()==false){	/*I am checking if it is solution or not*/
			objects[i].copyToVector(temp);	/*I am copying to temp*//*I use temp for all possible moves*/
			if(temp.move('R')==true){	
				if(checkIfThereis(temp)==false){
					objects.resize(++j);		/*I increase the size*/
					temp.copyToVector(objects[j-1]);
					objects[j-1].setLastMove('R');		/*I set last move*/
					objects[j-1].setNumberOfMove();		/*I set the number of move*/
				}

			}
			objects[i].copyToVector(temp);			/*Below like upper */
			if(temp.move('L')==true){
				if(checkIfThereis(temp)==false){
					objects.resize(++j);
					temp.copyToVector(objects[j-1]);
					objects[j-1].setLastMove('L');
					objects[j-1].setNumberOfMove();
				}
				

			}
			objects[i].copyToVector(temp);
			if(temp.move('U')==true){
				if(checkIfThereis(temp)==false){
					objects.resize(++j);
					temp.copyToVector(objects[j-1]);
					objects[j-1].setLastMove('U');
					objects[j-1].setNumberOfMove();
				}


			}
			objects[i].copyToVector(temp);
			if(temp.move('D')==true){
				if(checkIfThereis(temp)==false){
					objects.resize(++j);
					temp.copyToVector(objects[j-1]);
					objects[j-1].setLastMove('D');
					objects[j-1].setNumberOfMove();
				}
			}
			i++;	
		}

		t=objects[i].LastMove();	/*I take the last object's last move*/

		nom=objects[i].NumberOfMoves();	/*I also take last object's number of move */

		while((objects[i]==board)==false){	/*Until I found the initial board ,I take the last moves by make it do inverse move*/
			if(t=='R'){
				a.push_back('L');	/*And I push back for using for original board*/
				objects[i].copyToVector(temp);
				temp.move('L');
			}
			else if(t=='L'){
				a.push_back('R');
				objects[i].copyToVector(temp);
				temp.move('R');
			}
			else if(t=='U'){
				a.push_back('D');
				objects[i].copyToVector(temp);
				temp.move('D');
			
			}
			else if(t=='D'){
				a.push_back('U');
				objects[i].copyToVector(temp);
				temp.move('U');
			}
			for(m=0;m<objects.size();m++){
				if(objects[m]==temp){
					i=m;
					break;
				}
			}
			t=objects[i].LastMove();
			
		}
		for(m=a.size()-1;m>=0;m--){	/*The last move in the vector a is the first move actually and I go back to a[0] and applying moves' inverses */
			if(a[m]=='R'){
				board.move('L');	
			}
			else if(a[m]=='L'){
				board.move('R');
			}
			else if(a[m]=='U'){
				board.move('D');
			}
			else if(a[m]=='D'){
				board.move('U');
			}
			cout << board; 
		}
		total_move=nom+total_move;	/*nom = solution vector's number of move and I add it with total move*/
	
		
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





