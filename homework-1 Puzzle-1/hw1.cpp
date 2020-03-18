#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>				
									/*MUSTAFA TOKGÖZ 171044077 HOMEWORK 1*/
using namespace std;

enum direction{RIGHT=1,LEFT=2,UP=3,DOWN=4};				/*This enum shows directions */

void fill_the_puzzle(int puzzle[][9],int size);				/*This is filling puzzle with correct positions*/
void print_the_puzzle(int puzzle[][9],int size);			/*This is printing the puzzle*/
void shuffle_the_puzzle(int puzzle[][9],int size);			/*This is shuffling the puzzle with respect to blank since it need to be sovable*/
void move_the_blank(int puzzle[][9],int y,int x,int size);		/*This is making the blank move around*/
void find_the_blank_position(int puzzle[][9],int size);			/*This is finding the blank positions*/
int check_the_puzzle(int puzzle[][9],int goal_puzzle[][9],int size);	/*This is checking the puzzle whether the puzzle is over or not*/
void gameplay(int puzzle[][9],int goal_puzzle[][9],int size);		/*This is gameplay function*/
int  absolute_value(int number);					/*this is to find absolute value when I want to find distance*/
void swap(int *p1,int *p2);						/*This is to change value between  block and blank*/
int checking_true_position(int goal_puzzle[][9],int value,int y_pos,int x_pos);			/*This is to check whether the block is true positon or not*/
direction find_the_min(int right_block,int left_block,int up_block,int down_block);		/*This is finding the minimum distance */
void intelligent_move(int puzzle[][9],int goal_puzzle[][9],int size);				/*This is intelligent move that I wrote*/




int main(){
 int puzzle[9][9];
 int goal_puzzle[9][9];
 int size=0;								/*This is puzzle board size that will be selected by the person */
 srand(time(NULL));							/*This is for random number*/
 cout << "\nWelcome to N-puzzle game !!\n\n" << "Let's start the game \n\n" << "Please enter the problem size\n";
 while(1){
 cin >> size;
	if(size>2 && size<10)						/*Size must be in these interval from given hw1*/
		break;
	else
		cout << "Please enter a number from 3 to 9\n";
 }
	fill_the_puzzle(goal_puzzle,size);				/*This is filling our goal puzzle*/
	fill_the_puzzle(puzzle,size);					/*This is filling our puzzle like goal puzzle becouse of shuffle*/
	shuffle_the_puzzle(puzzle,size); 				/*This is shuffling puzzle*/
	gameplay(puzzle,goal_puzzle,size);				/*This is game*/
 return 0;
}

void fill_the_puzzle(int puzzle[][9],int size){
 int i=0,j=0,k=0;
	for(j=0;j<size;j++){						/*This is loop that fills*/
		for(i=0;i<size;i++){
			puzzle[j][i]=k+1;
			k++;		
		}							/*0 will be number to use blank that I chose*/
	}
	puzzle[size-1][size-1]=0;					/*This is blank that will be move*/

}

void print_the_puzzle(int puzzle[][9],int size){
 int i=0,j=0;
	cout << "\n";
	for(j=0;j<size;j++){						/*This is loop that prints*/
		for(i=0;i<size;i++){
			if(puzzle[j][i]==0){
				cout<< setw(3) << " " <<" ";		/*This setw funcion is  giving 3 digit for the number*/
			}
			else 
				cout<< setw(3) << puzzle[j][i] <<" ";
		}		
		cout << "\n\n";
	}
}

void find_the_blank_position(int puzzle[][9],int position[2],int size){	
 int j=0,k=0;
 int count=0;
		for(j=0;j<size;j++){
			for(k=0;k<size;k++){
				if(puzzle[j][k]==0){			/*I am making the loop stop when I find the blank position*/
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

void shuffle_the_puzzle(int puzzle[][9],int size){
 int i=0;
 int position[2]={size-1,size-1};					/*I put this size-1 so that it shouldn't be junk number*/
	for(i=0;i<size*size*size*size;i++){				/*This size*size*size*size is number so that it will shuffle a lot*/
			find_the_blank_position(puzzle,position,size);  /*This is finding blank positions*/
												/*Position[0] is equal y axis position[1] is equal x axis*/
			move_the_blank(puzzle,position[0],position[1],size);   			/*This is moving the blank*/	
	}
}

void move_the_blank(int puzzle[][9],int y,int x,int size){
 int temp_random;
		temp_random=rand()%4;					/*This is random number that will be used randomly shuffle just below*/
									/*Here they are*/
			if(temp_random==0){		
				if(x!=size-1){				/*This is checking if there is room or not for right*/
					puzzle[y][x]=puzzle[y][x+1];	/*This is changing blocks*/
					puzzle[y][x+1]=0;		/*I needn't to hold the blank's value becouse I know ,So I use only 0 to assign*/
				}
			}
			else if(temp_random==1){			
				if(x!=0){				/*This is checking if there is room or not for left*/
					puzzle[y][x]=puzzle[y][x-1];		
					puzzle[y][x-1]=0;
				}
			}
			 else if(temp_random==2){
				if(y!=0){				/*This is checking if there is room or not for up*/
					puzzle[y][x]=puzzle[y-1][x];		
					puzzle[y-1][x]=0;
				}
			} 
			 else {
				if(y!=size-1){				/*This is checking if there is room or not for the down*/
					puzzle[y][x]=puzzle[y+1][x];		
					puzzle[y+1][x]=0;
				}
			}

}

int check_the_puzzle(int puzzle[][9],int goal_puzzle[][9],int size){
 int i=0,j=0,k=0;	
	for(i=0;i<size;i++){						/*This loop is checking if puzzle is correct or not*/
		for(j=0;j<size;j++){
			if(puzzle[i][j]!=goal_puzzle[i][j]){		/*If there is any mismatch,then it returns 0,So puzzle is not over*/
				return 0;		
			}
		}
	}
	
 return 1;
}

void swap(int *p1,int *p2){						/*This is swapping values*/
 int temp;
	temp=*p1;
	*p1=*p2;
	*p2=temp;
}

void gameplay(int puzzle[][9],int goal_puzzle[][9],int size){
 char selection='Q';							
 int total_move=0;
 int position[2]={size-1,size-1};
 int x=0,y=0;
		find_the_blank_position(puzzle,position,size);
		y=position[0];						/*These are blank positions*/
		x=position[1];
	if(check_the_puzzle(puzzle,goal_puzzle,size)==0){		/*This is checking if puzzle is over*/
			 cout << "Your initial random board is \n";
			print_the_puzzle(puzzle,size);
		cout << "Enter your move\n(R=Right, L=Left, U=Up, D=Down, I=Intelligent, Q=Quit)\n";
		
		while(check_the_puzzle(puzzle,goal_puzzle,size)==0){	/*If puzzle is not over then,implemet below*/
			cout <<"Your move : ";
			cin >> selection;				
			switch (selection){
				
				case 'R' : if(x!=size-1){						/*This is for right move to move blank to right when you push the R*/
						swap(&puzzle[y][x],&puzzle[y][x+1]);			/*This is swapping values*/
						total_move++;						/*total move is increasing*/
						}
						else
							cout <<"You hit the wall,Please be carefull\n"; /*If There isnt any room ,then it warn you*/
							
					break;
				case 'L' : if(x!=0){							/*This is for left move to move blank to left when you push the L*/
						swap(&puzzle[y][x],&puzzle[y][x-1]);
						total_move++;		
						}
						else
							cout <<"You hit the wall,Please be carefull\n";
					break;
				case 'U' : if(y!=0){							/*This is for up move to move blank to up when you push the U*/
						swap(&puzzle[y][x],&puzzle[y-1][x]);
						total_move++;
						}
						else
							cout <<"You hit the wall,Please be carefull\n";
					break;
				case 'D' : if(y!=size-1){						/*This is for down move to move blank to down when you push the D*/
						swap(&puzzle[y][x],&puzzle[y+1][x]);	
						total_move++;
						}
						else
							cout <<"You hit the wall,Please be carefull\n";
					break;
				case 'I' : intelligent_move(puzzle,goal_puzzle,size);			/*This is intelligent function when you push the I*/
					   total_move++;
					break;
				case 'S' : 	fill_the_puzzle(puzzle,size);				/*I am filling puzzle with goal puzzle then shuffling*/
						shuffle_the_puzzle(puzzle,size);			/*This is shuffling the puzzle when you push the S*/
					break;
				case 'Q' : break;							/*When you push the Q then game will be over,*/
				default : cout << "Please enter a valid operation\n"
						<<"(R=Right, L=Left, U=Up, D=Down, I=Intelligent, Q=Quit)\n";
					break;
			}
			if(selection=='Q')
				break;									/*then you quit*/
			
			print_the_puzzle(puzzle,size);
			if(check_the_puzzle(puzzle,goal_puzzle,size)==1){				/*This is checking if puzzle is over or not*/
					cout << "Congratulations , Problem is solved ! :)\n";
					cout << "Total number of moves is " << total_move << endl;
					break;
			}
			find_the_blank_position(puzzle,position,size);					/*This is finding blank position again*/
			y=position[0];
			x=position[1];
		}

	}
	else{		
		fill_the_puzzle(puzzle,size);								/*I am filling puzzle with goal puzzle then shuffling*/
		shuffle_the_puzzle(puzzle,size);							/*If initial game is goal game then it shuffle and start again gameplay*/
			gameplay(puzzle,goal_puzzle,size);
	}

}

int absolute_value(int number){							/*This is finding absolute value*/
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

int checking_true_position(int goal_puzzle[][9],int value,int y_pos,int x_pos){				/*This is checking the number is true position or not*/
	if(goal_puzzle[y_pos][x_pos]==value)
		return 1;
	else 
		return 0;
}


void intelligent_move(int puzzle[][9],int goal_puzzle[][9],int size){
 int y=0,x=0;
 int position[2]={size-1,size-1};
 int size_square=size*size;							/*This is for below*/
 int left_block=size_square,right_block=size_square,up_block=size_square,down_block=size_square;	/*Becouse I don't want them be 0 ,So I assing size to the 2 */
 direction which_is_less;							/*İf this is 1 so the least move is right ,2 is left and so on*/
	
	find_the_blank_position(puzzle,position,size);
	y=position[0];
	x=position[1];
	
	if(x!=size-1){	
			if(checking_true_position(goal_puzzle,puzzle[y][x+1],y,x+1)==0)
				right_block=absolute_value((y*size+x+1)-puzzle[y][x+1]); 		/*This is calculating distance for right*/
		
	}
	if(x!=0){
			if(checking_true_position(goal_puzzle,puzzle[y][x-1],y,x-1)==0)			/*This is calculating distance for left*/
				left_block=absolute_value((y*size+x+1)-puzzle[y][x-1]);
		
	}
	if(y!=0){
		if(checking_true_position(goal_puzzle,puzzle[y-1][x],y-1,x)==0)				/*This is calculating distance for up*/
			up_block=absolute_value((y*size+x+1)-puzzle[y-1][x]);
	}
	if(y!=size-1){		
			if(checking_true_position(goal_puzzle,puzzle[y+1][x],y+1,x)==0)			/*This is calculating distance for down*/
				down_block=absolute_value((y*size+x+1)-puzzle[y+1][x]);
	}
	
		
		which_is_less=find_the_min(right_block,left_block,up_block,down_block);			/*This finding minimum distance for around the blank*/

			if(which_is_less==RIGHT){			
				if(x!=size-1){
					swap(&puzzle[y][x],&puzzle[y][x+1]);	
				}
			}
			else if(which_is_less==LEFT){
				if(x!=0){
					swap(&puzzle[y][x],&puzzle[y][x-1]);		
				}
			}
			else if(which_is_less==UP){
				if(y!=0){
					swap(&puzzle[y][x],&puzzle[y-1][x]);		
				}
			}
			else{
				swap(&puzzle[y][x],&puzzle[y+1][x]);
			}

}

















