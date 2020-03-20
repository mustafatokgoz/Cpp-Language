
#include<iostream>
#include<fstream>
using namespace std;

enum shape{rect='R',circle='C',triangle='T'};




int main(){
ofstream dosya;
char i,j;
int height;
int width;
int width2,height2,many,many2,temp,temp2;
int check=0;
dosya.open("mustafa.svg");

	dosya << "<!DOCTYPE html> \n";
	dosya << "<html> \n";
	dosya << "<body> \n";
	cout<<"Enter width and hight of your rectangle\n";
		cout<<"width : ";
		cin>>width;
		cout<<"hight : ";
		cin>>height;
		dosya << "<svg  \n";
		dosya << " width=\""<< width <<"\" height=\""<< height <<"\" >\n";
		dosya << "<rect width=\"100%\" height=\"100%\" fill=\"red\" />\n";
	


		cout<<"\n Please Enter width and hight of your small rectangle \n"<<"width : ";
		cin>>width2;
		cout<<"hight : ";
		cin>>height2;
			many=width/width2;
			many2=height/height2;
			temp=1;
			temp2=1;
			for(j=0;j<many2;j++){
				for(i=0;i<many;i++){
					if(temp+width2<width){		
						dosya << "<rect x=\""<<temp<<"\" y=\"" <<temp2<<"\""<<" width=\""<<width2<<"\" height=\""<<height2<<"\" fill=\"darkblue\" />\n";			
						temp=temp+width2+1;
					}
				}
				temp=1;
						if(temp2+height2*2+1<height){
					dosya << "<rect x=\""<<temp<<"\" y=\"" <<temp2<<"\""<<" width=\""<<width2<<"\" height=\""<<height2<<"\" fill=\"darkblue\" />\n";
							temp2=temp2+height2+1;
						}
						else{
						  	int check=1;
							break;
						}
							
				if(check==1)
					break;
			}	
	
	dosya <<" </svg> \n";
	dosya << "</body> \n";
	dosya << "</html> \n";
	dosya << endl;
dosya.close();


		
	
	
return 0;

}



















