#include<iostream>
#include<cmath>
#include<memory>

#include"gtuset.h"

using namespace std;

namespace myGTUContainer{
	template<typename T>			/*These are contructers of set*/
	GTUSet<T>::GTUSet(){
		used=0;
		capacity=10;
	}

	template<typename T>
	GTUSet<T>::GTUSet(size_t n_capacity){
		if(n_capacity>0){
			data=shared_ptr<T>(new T[n_capacity],[](T *temp){delete[] temp;});
			capacity=n_capacity;
			used=0;
		}
	}
	template<typename T>
	bool GTUSet<T>::empty() const{
		if(used==0)
			return true;
		else 
			return false;
	}
	template<typename T>
	size_t GTUSet<T>::size() const{
		return used;
	}
	template<typename T>
	size_t GTUSet<T>::max_size(){		/*I decide the max size*/

		return 5000;
	}	

	template<typename T>
	void GTUSet<T>::insert(const T &value){
	 bool check=false;
		if(used==capacity){
			if(capacity==0){
				capacity=1;
				data=shared_ptr<T>(new T[capacity],[](T *temp){delete[] temp;});
			}
			else{
				capacity=capacity*2;	/*If capacity is not enough then i rise the capacity*/
			}
			
			T *temp = new T[capacity];
			move(data.get(),data.get()+used,temp);		/*These are transporting data to temp*/
			data.reset(temp);				/*then I reset the function*/

		}
		
		for(size_t i=0;i<used;i++){			/*If the value is same  then it doesnt insert it*/
			if(data.get()[i]==value){
				check=true;
			}
		}
		if(check==false){				/*If the value is not same  then it insert it*/
			if(used<=max_size()){
				data.get()[used]=value;
				used++;
			}
			else 
				throw max_size();
		}
	}
	template<typename T>
	size_t GTUSet<T>::erase(const T &number){	/*This funciton erases the value*/
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
	void GTUSet<T>::clear() {			/*This is clearing the set*/
		data.reset();
		data=shared_ptr<T>(new T[10],[](T *temp){delete[] temp;});
		used=0;
	}

	template<typename T>
	typename GTUSet<T>::GTUIterator GTUSet<T>::begin(){		/*This returns iterator of begin*/
		 
		return typename GTUSet<T>::GTUIterator {data};

	} 
	template<typename T>
	typename GTUSet<T>::GTUIterator GTUSet<T>::end(){
		shared_ptr<T> temp(data.get()+used,[](T *t){});
		return typename GTUSet<T>::GTUIterator {temp};		/*This returns iterator of end*/	
	} 	
}
