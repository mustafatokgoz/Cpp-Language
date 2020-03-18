#include<iostream>
#include<cmath>
#include<memory>
#include<string>

#include"gtuvector.h"
using namespace std;			/*These are implementation of vector funcitons*/
namespace myGTUContainer{
	template <typename T>			
	T& GTUVector<T>::operator[](size_t index)	/*This throws index if index is greater than used*/
	{
	 int ind=index;
	 	if(index>used-1){
			throw ind;
		}
		else{

	   	 return data.get()[index];
		}
	}


	template<typename T>				/*These are constructers*/
	GTUVector<T>::GTUVector(){
		used=0;
		capacity=10;
	}

	template<typename T>
	GTUVector<T>::GTUVector(size_t n_capacity){
		if(n_capacity>0){
			data=shared_ptr<T>(new T[n_capacity],[](T *temp){delete[] temp;});	/*This is for shared pointer to use like array*/
			capacity=n_capacity;
			used=0;
		}
	}
	template<typename T>
	bool GTUVector<T>::empty() const{	
		if(used==0)
			return true;
		else 
			return false;
	}
	template<typename T>
	size_t GTUVector<T>::size() const{
		return used;
	}
	template<typename T>
	size_t GTUVector<T>::max_size(){	/*I decide the max size*/
		return 5000;
	}	

	template<typename T>
	void GTUVector<T>::insert(const T &value){		/*This is insert funciton*/
		if(used==capacity){
			if(capacity==0){
				capacity=1;
				data=shared_ptr<T>(new T[capacity],[](T *temp){delete[] temp;});
			}
			else{
				capacity=capacity*2;		/*If capacity is not enough then i rise the capacity*/
			}
			
			T *temp = new T[capacity];
			move(data.get(),data.get()+used,temp);	/*These are transporting data to temp*/
			data.reset(temp);			/*then I reset the function*/

		}
		if(used<=max_size()){				/*If used is bigger than max_size*/
			data.get()[used]=value;
			used++;
		}
		else
			throw max_size();			/*Then I throw an exeption*/
	}
	template<typename T>
	size_t GTUVector<T>::erase(const T &number){		/*This is erase funciton*/
		for(size_t i=0;i<used;i++){
			if(data.get()[i]==number){
				for(size_t j=i;j<used-1;j++){
					data.get()[j]=data.get()[j+1];
				}
				used--;
			}
		}

	}
	template<typename T>
	void GTUVector<T>::clear() {				/*This is clearing the vector*/
		data.reset();
		data=shared_ptr<T>(new T[10],[](T *temp){delete[] temp;});
		used=0;
	}

	template<typename T>
	typename GTUVector<T>::GTUIterator GTUVector<T>::begin(){	/*This returns iterator of begin*/
		 
		return typename GTUVector<T>::GTUIterator {data};

	} 
	template<typename T>
	typename GTUVector<T>::GTUIterator GTUVector<T>::end(){		/*This returns iterator of end*/
		shared_ptr<T> temp(data.get()+used,[](T *t){});
		return typename GTUVector<T>::GTUIterator {temp};;
	} 
}

