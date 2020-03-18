#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<iomanip>						
									/*MUSTAFA TOKGÖZ 171044077 HOMEWORK 2*/
using namespace std;

enum direction{RIGHT=1,LEFT=2,UP=3,DOWN=4};				/*This enum shows directions */

void fill_the_puzzle(int goal_puzzle[][9],int y,int x,int puzzle[][9]);				/*This is filling puzzle with correct positions*/
void print_the_puzzle(int puzzle[][9],int y,int x);						/*This is printing the puzzle*/
void shuffle_the_puzzle(int puzzle[][9],int y,int x);				/*This is shuffling the puzzle with respect to blank since it need to be sovable*/
void move_the_blank_randomly(int puzzle[][9],int y,int x,int y_num,int x_num);		/*This is making the blank move around randomly*/
void find_the_blank_position(int puzzle[][9],int y,int x);					/*This is finding the blank positions*/
bool check_the_puzzle(const int puzzle[][9],const int goal_puzzle[][9],int y,int x);		/*This is checking the puzzle whether the puzzle is over or not*/
void gameplay(int puzzle[][9],int goal_puzzle[][9],int y_num,int x_num);			/*This is gameplay function*/
int  absolute_value(int number);						/*this is to find absolute value when I want to find distance*/
void swap(int &p1,int &p2);							/*This is to change value between  block and blank*/
bool checking_true_position(const int goal_puzzle[][9],int value,int y_pos,int x_pos);		/*This is to check whether the block is true positon or not*/
direction find_the_min(int right_block,int left_block,int up_block,int down_block);		/*This is finding the minimum distance */
void intelligent_move(int puzzle[][9],int goal_puzzle[][9],int y_num,int x_num);		/*This is intelligent move that I wrote*/
int read_the_file(int puzzle[][9],int &line,int &x,string file_name);			/*This reads the file*/
int line_number(string file_name);								/*this is founding the line number*/
int seperate_line_to_number(string one_line,int puzzle[][9],int line_number);			/*this is seperating line to number*/
int convert_to_number(string word);								/*this is converting words to number*/
int ten_power(int pow);										/*this is taking number of to the ten */
void blank_value(int puzzle[][9],int number,int y,int x);					/*This is putting -1 for blank*/
void fill_with_minus_one(int puzzle[][9],int y,int x);						/*This fills the puzzle with -1*/
void write_the_file(int puzzle[][9],int &line,int &x);					/*This is saves the file*/
void solves_all(int puzzle[][9],int goal_puzzle[][9],int y_num,int x_num,int &total_move);	/*this is solving problem completely*/



int main(int argc , char *argv[]){
 int puzzle[9][9];
 int goal_puzzle[9][9];
 int line=0;						/*I use in the middle part of code line as y_num and x as x_num*/
 int x=0;
 char temp='0';	
 int i=0;
 decltype(i) j=0;	/*I use the keyword decltype here!!*/
 srand(time(NULL));	/*This is for random number*/					

	if(argc==1){		/*If there is one arguman on the command line then the game start like hw1 but there are height and weight */
		cout << "\nWelcome to N-puzzle game !!\n\n" << "Let's start the game \n\n" << "Please enter the problem hight and width\n";
 		while(1){
			cout<<"hight : ";
 			cin >> temp;
			if(temp>='3' && temp<='9'){
				line=temp-48;		/*this is converting character to number*/
				break;
			}
			else
				cout << "Please enter a number from 3 to 9\n";
 		}
		while(1){
			cout<<"width : ";
 			cin >> temp;
			if(temp>='3' && x<='9'){
				x=temp-48;		/*this is converting character to number*/
				break;
			}
			else
				cout << "Please enter a number from 3 to 9\n";
 		}
			fill_with_minus_one(puzzle,line,x);		/*This fills the puzzle with -1*/
			fill_with_minus_one(goal_puzzle,line,x);	/*This fills the goal puzzle with -1*/
		fill_the_puzzle(goal_puzzle,line,x,puzzle);		/*This fills the goal puzzle with a correct number */
		fill_the_puzzle(puzzle,line,x,puzzle);		/*This fills the puzzle with a correct number*/
		shuffle_the_puzzle(puzzle,line,x);			/*This is shuffling the puzzle*/
		gameplay(puzzle,goal_puzzle,line,x);		/*This is starting the game*/
	}	
	else{			/*If there is 2 arguman on the command line*/
		if(read_the_file(puzzle,line,x,argv[1])==1){		/*Then it reads the file and check if the file is or not*/
			fill_the_puzzle(goal_puzzle,line,x,puzzle);	/*Then fills the goal puzzle with respect to puzzle's wall (00)*/
			gameplay(puzzle,goal_puzzle,line,x);		/*This is starting the game*/
		}	
	}
	
			

 return 0;
}
void fill_with_minus_one(int puzzle[][9],int y,int x){	/*This is filling all puzzle with -1 */
 int i=0,j=0;						/*Becouse I dont wanna confuse with 0 another junk value that is not defined variables*/
		for(i=0;i<y;i++){		
				for(j=0;j<x;j++){
					puzzle[i][j]=-1;
				}
			}


}
int read_the_file(int puzzle[][9],int &line,int &x,string file_name){		/*This reads the file*/
 string one_line="";
 ifstream readf;
 const string blank="bb";						/*I also use const here not to change the bb value*/
 int number_blank,i=0,success=1;
		number_blank=convert_to_number(blank); 			/*Blank string's integer number*/
	
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
			line=line_number(file_name);
			for(i=0;i<line;i++){
				getline(readf,one_line);
				x=seperate_line_to_number(one_line,puzzle,i);
				one_line="";	
			}
			blank_value(puzzle,number_blank,line,x);
					
				
		}
	 
 readf.close();
 return success;
}

int line_number(string file_name){	/*This is founding line  number */
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
	
void blank_value(int puzzle[][9],int number,int y,int x){	/*This founds and fills the balnk value that is -1*/
 int i=0,j=0;
	for(i=0;i<y;i++){
		for(j=0;j<x;j++){		
			if(puzzle[i][j]==number){
				puzzle[i][j]=-1;
			}
		}

	}
}

int  seperate_line_to_number(string one_line,int puzzle[][9],int line_number){	/*This is sapareting and converting from line to number*/
 int i=0;
 int temp=0;
 string word="";
 char space=' ';

		while(one_line[temp]!='\0'){			/*This is sapareting words*/
			if(one_line[temp]==space){
				puzzle[line_number][i]=convert_to_number(word);	/*Then converting word to number*/
				i++;
		  		word = "";
			}	
			else{
				word=word+one_line[temp];
			}
			temp++;
		}
		puzzle[line_number][i]=convert_to_number(word);	/*This is for the last word that we found*/
		i++;
          	word = "";	
		
 return i;			/*This returns number of words */
}
int ten_power(int pow){					/*This is founding power of the number for the converting string*/
 int i=0,t_p=1;
	 if(pow==1){
		return 1;
	 }
	 for(i=0;i<pow-1;i++){
		t_p=t_p*10;
	 }
 return t_p;
}

int convert_to_number(string word){				/*This is converting string to number*/
 int number=0,i=0,j=0;
	for(i=0;word[i]!='\0';i++);				/*This is founding end of the string number then I convert the string to number with ten_pow function */
	for(i;i>0;i--){
		number=number+(static_cast<int>(word[j])-48)*ten_power(i);
		j++;

	}
	
 return number;
}

void fill_the_puzzle(int goal_puzzle[][9],int y,int x,int puzzle[][9]){
 int i=0,j=0,k=0;
	for(j=0;j<y;j++){						/*This is loop that fills*/
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
	goal_puzzle[y-1][x-1]=-1;					/*This is blank that will be move*/

}

void print_the_puzzle(int puzzle[][9],int y,int x){
 int i=0,j=0;
	cout << "\n";
	for(j=0;j<y;j++){						/*This is loop that prints*/
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

void find_the_blank_position(int puzzle[][9],int position[2],int y,int x){	
 int j=0,k=0;
 int count=0;
		for(j=0;j<y;j++){
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

void shuffle_the_puzzle(int puzzle[][9],int y_num,int x_num){
 int i=0;
 int position[2]={y_num-1,x_num-1};					/*I put this y_num-1 x_num so that it shouldn't be junk number*/
	for(i=0;i<y_num*x_num*2;i++){				/*This y_num *x_num*2 is number so that it will shuffle a lot*/
			find_the_blank_position(puzzle,position,y_num,x_num);  /*This is finding blank positions*/
												/*Position[0] is equal y axis position[1] is equal x axis*/
			move_the_blank_randomly(puzzle,position[0],position[1],y_num,x_num);   			/*This is moving the blank*/	
	}
}

void move_the_blank_randomly(int puzzle[][9],int y,int x,int y_num,int x_num){
 int temp_random;
		temp_random=rand()%4;					/*This is random number that will be used randomly shuffle just below*/
									/*Here they are*/
			if(temp_random==0){		
				if(x!=x_num-1){				/*This is checking if there is room or not for right*/
					if(puzzle[y][x]!=0 && puzzle[y][x+1]!=0){			
						swap(puzzle[y][x],puzzle[y][x+1]);	/*This is changing blocks*/
					}		
				}
			}
			else if(temp_random==1){			
				if(x!=0){				/*This is checking if there is room or not for left*/
					if(puzzle[y][x]!=0 && puzzle[y][x-1]!=0){
							swap(puzzle[y][x],puzzle[y][x-1]);		
							
					}
				}
			}
			 else if(temp_random==2){
				if(y!=0){				/*This is checking if there is room or not for up*/
					if(puzzle[y][x]!=0 && puzzle[y-1][x]!=0){
						swap(puzzle[y][x],puzzle[y-1][x]);		
					
					}
				}
			} 
			 else {
				if(y!=y_num-1){				/*This is checking if there is room or not for the down*/
					if(puzzle[y][x]!=0 && puzzle[y+1][x]!=0){
						swap(puzzle[y][x],puzzle[y+1][x]);		
					}
				}
			}

}

bool check_the_puzzle(const int puzzle[][9],const int goal_puzzle[][9],int y,int x){	/*I use the keyword const here!!*/
 int i=0,j=0,k=0;	
	for(i=0;i<y;i++){						/*This loop is checking if puzzle is correct or not*/
		for(j=0;j<x;j++){
			if(puzzle[i][j]!=goal_puzzle[i][j]){		/*If there is any mismatch,then it returns 0,So puzzle is not over*/
				return false;		
			}
		}
	}
	
 return true;
}

void swap(int &p1,int &p2){						/*This is swapping values*/
 int temp;
	temp=p1;
	p1=p2;
	p2=temp;
}

void gameplay(int puzzle[][9],int goal_puzzle[][9],int y_num,int x_num){
 char selection='Q';							
 int total_move=0;
 int position[2]={y_num-1,x_num-1};
 int x=0,y=0;
 string file_name="";
		find_the_blank_position(puzzle,position,y_num,x_num);
		y=position[0];						/*These are blank positions*/
		x=position[1];
	if(check_the_puzzle(puzzle,goal_puzzle,y_num,x_num)==false){		/*This is checking if puzzle is over*/
			 cout << "Your initial random board is \n";
			print_the_puzzle(puzzle,y_num,x_num);
		cout << "Enter your move\n(R=Right, L=Left, U=Up, D=Down, I=Intelligent, V=Solve, T=Total Move, Y=Load File, E=Save Game, Q=Quit)\n";
		
		while(check_the_puzzle(puzzle,goal_puzzle,y_num,x_num)==false){	/*If puzzle is not over then,implemet below*/
			cout <<"Your move : ";
			cin >> selection;				
			switch (selection){
				
				case 'R' : if(x!=x_num-1){						/*This is for right move to move blank to right when you push the R*/
						if(puzzle[y][x]!=0 && puzzle[y][x+1]!=0){
							swap(puzzle[y][x],puzzle[y][x+1]);			/*This is swapping values*/
							total_move++;						/*total move is increasing*/
						}
						else
							cout <<"You hit the wall,Please be carefull\n";					
					   }
					   else
						cout <<"You hit the wall,Please be carefull\n"; /*If There isnt any room ,then it warn you*/
							
					break;
				case 'L' : if(x!=0){
						if(puzzle[y][x]!=0 && puzzle[y][x-1]!=0){	/*This is for left move to move blank to left when you push the L*/
							swap(puzzle[y][x],puzzle[y][x-1]);
							total_move++;
						}
						else
							cout <<"You hit the wall,Please be carefull\n";		
					   }
						else
							cout <<"You hit the wall,Please be carefull\n";
					break;
				case 'U' : if(y!=0){							/*This is for up move to move blank to up when you push the U*/
						if(puzzle[y][x]!=0 && puzzle[y-1][x]!=0){
							swap(puzzle[y][x],puzzle[y-1][x]);
							total_move++;
						}
						else
							cout <<"You hit the wall,Please be carefull\n";
					   }
						else
							cout <<"You hit the wall,Please be carefull\n";
					break;
				case 'D' : if(y!=y_num-1){						/*This is for down move to move blank to down when you push the D*/
						if(puzzle[y][x]!=0 && puzzle[y+1][x]!=0){
							swap(puzzle[y][x],puzzle[y+1][x]);	
							total_move++;
						}
						else
							cout <<"You hit the wall,Please be carefull\n";
					   }
						else
							cout <<"You hit the wall,Please be carefull\n";
					break;
				case 'I' : intelligent_move(puzzle,goal_puzzle,y_num,x_num);			/*This is intelligent function when you push the I*/
					   total_move++;
					break;
				case 'S' : fill_the_puzzle(puzzle,y_num,x_num,puzzle);				/*I am filling puzzle with goal puzzle then shuffling*/
					   shuffle_the_puzzle(puzzle,y_num,x_num);			/*This is shuffling the puzzle when you push the S*/
					break;
				case 'T' : cout << "Total number of moves is " << total_move << endl;	/*This shows total move of problem*/
					   cout << "Solution isn't found yet " << endl;			/*If it is found then the program already says Solution is found so*/
					break;								/*If user use the T selection then solution isnt found yet*/
				case 'Y' : if(read_the_file(puzzle,y_num,x_num,file_name)==1)		/*This reads the file*/
							total_move=0;					/*Total move resets*/
					   fill_the_puzzle(goal_puzzle,y_num,x_num,puzzle);		/*This is filling puzzle with respect to inside of the file*/
					break;
				case 'E' : write_the_file(puzzle,y_num,x_num);				/*This writes to file*/
					break; 
				case 'V' : solves_all(puzzle,goal_puzzle,y_num,x_num,total_move);	/*This is solves all problem*/
					break;
				case 'Q' : cout << "Total number of moves is " << total_move << endl;
					break;							/*When you push the Q then game will be over,*/
				default : cout << "Please enter a valid operation\n"
						<<"(R=Right, L=Left, U=Up, D=Down, I=Intelligent,V=Solve, T=Total Move, Y=Load File, E=Save Game, Q=Quit,)\n";
					break;
			}
			if(selection=='Q')
				break;									/*then you quit*/
			if(selection!='V')
				print_the_puzzle(puzzle,y_num,x_num);					/*Becouse I already print in V selection*/
			if(check_the_puzzle(puzzle,goal_puzzle,y_num,x_num)==true){				/*This is checking if puzzle is over or not*/
					cout << "Congratulations , Problem is solved ! :)\n";
					cout << "Total number of moves is " << total_move << endl;
					break;
			}
			find_the_blank_position(puzzle,position,y_num,x_num);					/*This is finding blank position again*/
			y=position[0];
			x=position[1];
		}

	}
	else{		
		fill_the_puzzle(puzzle,y_num,x_num,puzzle);		/*Im filling puzzle correctly*/	/*I am filling puzzle with goal puzzle then shuffling*/
		shuffle_the_puzzle(puzzle,y_num,x_num);							/*If initial game is goal game then it shuffle and start again gameplay*/
			gameplay(puzzle,goal_puzzle,y_num,x_num);
	}

}
inline int absolute_value(int number){		/*I use the keyword inline here!!*/	/*This is finding absolute value*/
	if(number<0)
		return (-1)*number;

	else 
		return number;	
}



direction find_the_min(int right_block,int left_block,int up_block,int down_block){			/*This is finding minimum distance from their real place around the blank*/
 int min;
 direction which_is_less;

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
					

return which_is_less;								/*Then I return the direction*/
}

bool checking_true_position(const int goal_puzzle[][9],int value,int y_pos,int x_pos){			/*I wrote the keyword const here!! becouse goal_puzzle shouldn't change*/
	if(goal_puzzle[y_pos][x_pos]==value)
		return true;							/*This is checking the number is true position or not*/	
	else 
		return false;
}


void intelligent_move(int puzzle[][9],int goal_puzzle[][9],int y_num,int x_num){
 int y=0,x=0;
 int position[2]={y_num-1,x_num-1};
 int size_square=y_num*x_num;							/*This is for below*/
 int left_block=size_square,right_block=size_square,up_block=size_square,down_block=size_square;	/*Becouse I don't want them be 0 ,So I assing size to the 2 */
 direction which_is_less;							/*İf this is 1 so the least move is right ,2 is left and so on*/
	
	find_the_blank_position(puzzle,position,y_num,x_num);
	y=position[0];
	x=position[1];
	
	if(x!=x_num-1){	
			if(checking_true_position(goal_puzzle,puzzle[y][x+1],y,x+1)==false)
				right_block=absolute_value((y*y_num+x+1)-puzzle[y][x+1]); 		/*This is calculating distance for right*/
		
	}
	if(x!=0){
			if(checking_true_position(goal_puzzle,puzzle[y][x-1],y,x-1)==false)			/*This is calculating distance for left*/
				left_block=absolute_value((y*y_num+x+1)-puzzle[y][x-1]);
		
	}
	if(y!=0){
		if(checking_true_position(goal_puzzle,puzzle[y-1][x],y-1,x)==false)				/*This is calculating distance for up*/
			up_block=absolute_value((y*y_num+x+1)-puzzle[y-1][x]);
	}
	if(y!=y_num-1){		
			if(checking_true_position(goal_puzzle,puzzle[y+1][x],y+1,x)==false)			/*This is calculating distance for down*/
				down_block=absolute_value((y*y_num+x+1)-puzzle[y+1][x]);
	}
	
		
		which_is_less=find_the_min(right_block,left_block,up_block,down_block);			/*This finding minimum distance for around the blank*/

			if(which_is_less==RIGHT){			
				if(x!=x_num-1){
					if(puzzle[y][x]!=0 && puzzle[y][x+1]!=0)
							swap(puzzle[y][x],puzzle[y][x+1]);	
				}
			}
			else if(which_is_less==LEFT){
				if(x!=0){
					if(puzzle[y][x]!=0 && puzzle[y][x-1]!=0)
						swap(puzzle[y][x],puzzle[y][x-1]);		
				}
			}
			else if(which_is_less==UP){
				if(y!=0){
					if(puzzle[y][x]!=0 && puzzle[y-1][x]!=0)
						swap(puzzle[y][x],puzzle[y-1][x]);		
				}
			}
			else{
				swap(puzzle[y][x],puzzle[y+1][x]);
			}

}

void write_the_file(int puzzle[][9],int &line,int &x){
 ofstream writef;
 string file_name="";
 const string blank="bb";
 int i=0,j=0;
 	cout <<"Enter the file name to save\n";
	cin >> file_name;
	
	writef.open(file_name);

	for(j=0;j<line;j++){						/*This is loop that writes to the file*/
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
		if(j!=line-1){				/*Becouse the last line doesnt have a \n */
			writef << "\n";
		}
	}
}

void solves_all(int puzzle[][9],int goal_puzzle[][9],int y_num,int x_num,int &total_move){
 auto i=0,j=0,how_manyi=10,how_manyr=5;	 /*how_manyi , how_manyr are number of how many move in the loop for intelligent andrandom*//*I use the keyword auto here!!*/		
 int position[2]={y_num-1,x_num-1};	

		while(check_the_puzzle(puzzle,goal_puzzle,y_num,x_num)==false){		/*this loop is solving the problem*/
			for(i=0;i<how_manyi;i++){
				if(check_the_puzzle(puzzle,goal_puzzle,y_num,x_num)==false){		/*this is for intelligent move*/
					intelligent_move(puzzle,goal_puzzle,y_num,x_num);
					print_the_puzzle(puzzle,y_num,x_num);				
					total_move++;	
				}
				else
					break;
			}		

			for(j=0;j<how_manyr;j++){
				if(check_the_puzzle(puzzle,goal_puzzle,y_num,x_num)==false){
					find_the_blank_position(puzzle,position,y_num,x_num);  		/*this is for random move*/				
					move_the_blank_randomly(puzzle,position[0],position[1],y_num,x_num);
					print_the_puzzle(puzzle,y_num,x_num);
					total_move++;
				
				}
				else
					break;
				
			}
		
		}
}












