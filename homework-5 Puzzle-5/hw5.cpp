#include<iostream>
#include<string>
#include"boardarray1D.h"		/*These are h files that I wrote*/
#include"boardarray2D.h"
#include"boardvector.h"
#include"abstractboard.h"
							/*Mustafa Tokgöz 171044077*/
using namespace std;

using namespace inheritance;				/*This is my namespace*/

int AbstractBoard::numofboard=0;			/*This is the static int for boards*/

bool isThere(int array[],int value,int size){			/*This is helper funtion for BoardValidity*/
	for(int j=0;j<size;j++){
		if(array[j]==value){			/*This is finding number and i change the number with zero becouse I check If The number is exactly one or not*/
			array[j]=0;
			return true;	
		}
	}
return false;
}


bool BoardValidity(AbstractBoard *boards[],int size){ 		/*The size is array of board pointer size*/
int count=0,control=0,position[2],counter=0;
	for(int i=0;i<size;i++){
		int arr[boards[i]->getColumn()*boards[i]->getRow()];
			for(int j=0;j<boards[i]->getColumn();j++){
				for(int k=0;k<boards[i]->getRow();k++){
					if(boards[i]->operator()(j,k)!=0){	/*This is counting how many number are there if it is not zero*/
						count++;
					}					
				}
			}	
			for(int j=0;j<count;j++){
				arr[j]=j+1;			/*I fill the numbers becouse of checking below*/
			}	
			arr[count-1]=-1;
			
			for(int j=0;j<boards[i]->getColumn();j++){
				for(int k=0;k<boards[i]->getRow();k++){
						if(boards[i]->operator()(j,k)!=0){
							if(isThere(arr,boards[i]->operator()(j,k),count)==true){	/*This is checking whether the number is there one ore more*/
								counter++;			/*If number is there 2 times and retruns false and counter doesnt increase*/
							}
						}
				}
			}
			if(counter!=count)		/*Then I check number of number is equal counter or not */
				return false;		/*Then I return  false*/
		if(i!=size-1){
			if(boards[i]==boards[i+1]){
				return false;			/*This is checking boards are equal or not*/
			}
			if(boards[i]->getColumn()!=boards[i+1]->getColumn() || boards[i]->getRow()!=boards[i+1]->getRow()){
				return false;		/*This is cheking column number and row numbers are same or not*/
			}
			boards[i]->findTheBlankPosition(position);	//position[0] is linenumber(coloumn), position[1]=x(row)
			/*This is checking next move is valid or not so I check space (-1) so that Whether it moves right left down or right or not*/			
			if(position[0]!=0){
				if(boards[i+1]->operator()(position[0]-1,position[1])==-1){
					control++;						
				}
			}
			if(position[0]!=boards[i]->getColumn()-1){
				if(boards[i+1]->operator()(position[0]+1,position[1])==-1){
					control++;						
				}
			}
			if(position[1]!=0){
				if(boards[i+1]->operator()(position[0],position[1]-1)==-1){
					control++;						
				}
			}
			if(position[1]!=boards[i]->getRow()-1){
				if(boards[i+1]->operator()(position[0],position[1]+1)==-1){
					control++;						
				}
			}
			if(control!=1){	/*If There are valid space move (control= 1) then it is true but if isnt then retruns false*/
				
				return false;
			}

		}
		
		count=0;control=0;counter=0;
	}
return true;	/*If everthing is fine then returns true*/
}

int main(int argc , char *argv[]){
 AbstractBoard *boards[4];
 boardarray1D one(4,4),two,three;			/*These are boardarray1d objects*/
 boardarray1D four=three;

 boardarray2D sone,stwo,sthree(3,3);			/*These are boardarray2d objects*/
 boardarray2D sfour=sthree;

 BoardVector vone,vtwo,vthree(3,4);			/*These are boardvector objects*/
 BoardVector vfour=vthree;

	cout << "\nThis is  BoardArray1D sequence.\n";		/*Below is checking board's validity*/
 one.readFromFile("trial");					/*I use a trail file for cheking boards*/
	boards[0]=&one;						/*I assing adresses of them to array of pointer*/
	boards[0]->move('D');
	boards[0]->print();
	two=one;
	two.move('R');
	two.print();
	boards[1]=&two;
	three=two;
	three.move('R');

	boards[2]=&three;
	boards[2]->print();
	four=three;
	boards[3]=&four;
	boards[3]->move('D');
	boards[3]->print();

	if(BoardValidity(boards,4)==true){	/*4 is array of board pointer size*/
		cout << "This sequance is valid .\n";
	}	
	else {
	cout << "This sequence is NOT valid. \n";
	}
		cout << "\nThis is  BoardArray2D sequence.\n";
  sone.readFromFile("trial");
	boards[0]=&sone;
	boards[0]->move('D');
	boards[0]->print();
	stwo=sone;
	stwo.move('R');
	stwo.print();
	boards[1]=&stwo;
	sthree=stwo;
	sthree.move('R');

	boards[2]=&sthree;
	boards[2]->print();
	sfour=sthree;
	boards[3]=&sfour;
	boards[3]->print();
	if(BoardValidity(boards,4)==true){	/*4 is array of board pointer size*/
		cout << "This sequance is valid .\n\n";
	}	
	else {
	cout << "This sequence is NOT valid. \n";
	}

		cout << "\nThis is  BoardVector sequence.\n";
    vone.readFromFile("trial");
	boards[0]=&vone;
	boards[0]->move('D');
	boards[0]->print();
	vtwo=vone;
	vtwo.move('R');
	vtwo.print();
	boards[1]=&vtwo;
	vthree=vtwo;
	vthree.move('R');

	boards[2]=&vthree;
	boards[2]->print();
	vfour=vthree;
	boards[3]=&vfour;
	boards[3]->move('D');
	boards[3]->move('R');
	boards[3]->print();
	
	if(BoardValidity(boards,4)==true){	/*4 is array of board pointer size*/
		cout << "This sequance is valid .\n";
	}	
	else {
	cout << "This sequence is NOT valid. \n";
	}

		cout << "There are  " << AbstractBoard::NumberOfBoards()<<" number of board until now." <<endl;

 return 0;
}

