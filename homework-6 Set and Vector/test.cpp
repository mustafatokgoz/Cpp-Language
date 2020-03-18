#include<iostream>
#include<memory>			/*Mustafa Tokgöz 171044077*/
#include<string>
#include"gtucontainer.cpp"		/*this is for container*/
#include"gtuvector.cpp"			/*this is for vector*/
#include"gtuset.cpp"			/*this is for set*/

using namespace std;
using namespace myGTUContainer;		/*this is my namespace*/

template<typename GTUIterator, typename T>			/*These are global function */
GTUIterator find(GTUIterator first,GTUIterator last, const T& value){
    while(first!=last){
        if (*first == value){
            return first;
        }
	++first;
    }
    return last;
}
template<typename GTUIterator,typename Tfunction>
GTUIterator find_if (GTUIterator first,GTUIterator last,Tfunction function){
  while (first!=last) {
    if (function(*first)) return first;
    ++first;
  }
  return last;
}
template<class GTUIterator, class Tfunction>
Tfunction for_each(GTUIterator first,GTUIterator last,Tfunction function){
  while (first!=last) {
    function(*first);
    ++first;
  }
  return function;      
}

void print(int i) {  	/*This is prints the values */
  cout << ' ' << i;
}
bool Even(int i) {
  return ((i%2)==0);	/*this returns true if number is even*/
}
int main(){			/*This is my test program that tests the funcitons in set and vector and iterator*/
	GTUVector<int> a(5);
	try{
        a.insert(8);
        a.insert(3);
        a.insert(1);
        a.insert(7);
        a.insert(2);


		for(int i=0;i<a.size();i++){
			cout << i<<". element of vector is " << a[i];
			cout << "\n";
		}
		cout <<"I try  a value in 6. index so that exeption is working or not\n";
		a[6]=10;
	cout<<"size = "<<a.size(); 
	}
	catch(size_t maxsize){
		cout <<"There is  "<<maxsize<<"object so you don't create a new one" << endl;
	}
	catch(int index){
		cout <<"There is no "<<index<<".index" << endl;
	}
	

	GTUVector<int>::GTUIterator p;
	p=a.begin();
	cout << "Iterator's first element  of vector "<<*p<<"\n";
	p=a.end();
	p--;
	cout << "Iterator's last element of vector "<<*(p)<<"\n";
	cout <<"Im changing last value to 3\n";
	(*p)=3;
	GTUVector<int>::GTUIteratorConst b;
	b=a.begin();
	cout << "ConstIterator's first element of vector "<<*b<<"\n";
	b=a.end();
	b--;
	cout << "ConstIterator's last element of vector "<<*(b)<<"\n";
	cout <<"I use find_if funciton here\n";
	GTUVector<int>::GTUIterator it=find_if(a.begin(),a.end(),Even);
	cout << "\n\nThe first even value is " << *it << '\n';
	cout <<"I use for_each funciton here\n";
	for_each(a.begin(),a.end(),print);
	a.erase(3);
	cout << "\nI erased 3 from vector\n";
	cout<<"\nmaxsize of vector = "<<a.max_size();
	cout <<"\n Vector is ";
	if(a.empty()==true)
		cout <<"empty\n";
	else 
		cout <<"not empty\n"; 

	for(auto p=a.begin();p!=a.end();++p){
		cout <<"inside of iterator of vector "<<*p<<"  \n";
	}
	cout << "I clear the vector\n";
	a.clear();
	cout <<"\n Vector is ";
	if(a.empty()==true)
		cout <<"empty\n";
	else 
		cout <<"not empty\n";
	
	
	GTUSet<int> set(5);
	try{
        set.insert(8);
        set.insert(3);
        set.insert(1);
        set.insert(7);
        set.insert(3);

	cout<<"size = "<<set.size(); 
	}
	catch(size_t maxsize){
		cout <<"\nThere is  "<<maxsize<<"object that is max ,so you don't create a new one\n" << endl;
	}

	GTUSet<int>::GTUIterator d;
	d=set.begin();
	cout << "\nIterator's first element of set "<<*d<<"\n";
	d=set.end();
	d--;
	cout << "Iterator's last elementof set "<<*(d)<<"\n";
	cout <<"Im changing last value to 4\n";
	(*d)=4;
	GTUSet<int>::GTUIteratorConst f;
	f=set.begin();
	cout << "ConstIterator's first element of set "<<*f<<"\n";
	f=set.end();
	f--;
	cout << "ConstIterator's last element of set "<<*(f)<<"\n";
	cout <<"I use find funciton here\n";
	auto result=find(set.begin(),set.end(),4);
	if (result != set.end()) {
        	cout << "\nSet contains: 4\n";
    	} 
	else {
        	cout << "set does not contain: \n";
   	}
	
	set.erase(4);
	cout << "\nI erased 4 from Set\n";
	cout<<"\nmaxsize of set = "<<set.max_size();
	cout <<"\n Set is ";
	if(set.empty()==true)
		cout <<"empty\n";
	else 
		cout <<"not empty\n"; 

	for(auto d=set.begin();d!=set.end();d++){
		cout <<"inside of iterator of set "<<*d<<"  \n";
	}
	cout << "I clear the set\n";
	set.clear();
	cout <<"\n Set is ";
	if(set.empty()==true)
		cout <<"empty\n";
	else 
		cout <<"not empty\n";


	
	

return 0;
}

