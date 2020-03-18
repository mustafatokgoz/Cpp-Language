#include<iostream>
#include<memory>
#include"gtucontainer.h"

using namespace std;
				/*This is GTUIterators implementations*/
namespace myGTUContainer{
	template<typename T>
	GTUContainer<T>::GTUIterator::GTUIterator(){		/*these are contructers*/
		it_ptr=shared_ptr<T>(new T[10],[](T *temp){delete[] temp;});
	}
	template<typename T>
	GTUContainer<T>::GTUIterator::GTUIterator(shared_ptr<T> other){
		it_ptr=other;
	}

	template<typename T>
	GTUContainer<T>::GTUIterator::GTUIterator(GTUIterator &other){
		it_ptr=other.it_ptr;
	}
	template<typename T>
	GTUContainer<T>::GTUIterator::GTUIterator(const GTUIterator &other){
		it_ptr=other.it_ptr;
	}


	template<typename T>
	T& GTUContainer<T>::GTUIterator::operator*(){	/*This is * operator*/
		return *it_ptr.get();
	}

	template<typename T>
	T& GTUContainer<T>::GTUIterator::operator->(){	/*This is -> operator*/
		return it_ptr;
	}

	template<typename T>
	typename GTUContainer<T>::GTUIterator GTUContainer<T>::GTUIterator::operator++(){	/*This is ++prefix operator*/
		shared_ptr<T> temp(it_ptr.get()+1,[](T *t){});	
		it_ptr=temp;
		return GTUContainer<T>::GTUIterator {temp};
	}
	template<typename T>
	typename GTUContainer<T>::GTUIterator GTUContainer<T>::GTUIterator::operator++(T ignore){	/*This is ++postfix operator*/
		shared_ptr<T> temp(it_ptr.get()+1,[](T *t){});
		shared_ptr<T> temp2(it_ptr.get(),[](T *t){});
		it_ptr=temp;
		return GTUContainer<T>::GTUIterator {temp2};
	}

	template<typename T>
	typename GTUContainer<T>::GTUIterator GTUContainer<T>::GTUIterator::operator--(){	
		shared_ptr<T> temp(it_ptr.get()-1,[](T *t){});
		it_ptr=temp;
		return GTUContainer<T>::GTUIterator {temp};
	}



	template<typename T>
	typename GTUContainer<T>::GTUIterator GTUContainer<T>::GTUIterator::operator--(T ignore){
		shared_ptr<T> temp(it_ptr.get()-1,[](T *t){});
		shared_ptr<T> temp2(it_ptr.get(),[](T *t){});
		it_ptr=temp;
		return GTUContainer<T>::GTUIterator {temp2};
	}

	template<typename T>
	bool GTUContainer<T>::GTUIterator::operator==(const GTUIterator &other){	/*This is == operator*/
		if(it_ptr==other.id_ptr)
			return true;
		else 
			return false;
	}
	template<typename T>
	bool GTUContainer<T>::GTUIterator::operator!=(const GTUIterator &other){
		if(it_ptr!=other.it_ptr)
			return true;
		else 
			return false;
	}


	template<typename T>
	typename GTUContainer<T>::GTUIterator& GTUContainer<T>::GTUIterator::operator=(const GTUIterator &other){
		it_ptr=other.it_ptr;	
		return *this;
	}
	template<typename T>
	typename GTUContainer<T>::GTUIterator& GTUContainer<T>::GTUIterator::operator=(shared_ptr<T> other){
		it_ptr=other;	
		return *this;
	}
	template<typename T>
	typename GTUContainer<T>::GTUIterator& GTUContainer<T>::GTUIterator::operator=(GTUIterator &other){
		it_ptr=other.it_ptr;
		return *this;
	}
	template<typename T>
	shared_ptr<T> GTUContainer<T>::GTUIterator::getSharedPtr()const{	/*This is for GTUIteratorConst assignment */
		return it_ptr;	
	}

	/* this is constant part*/
	/************************/



	template<typename T>
	GTUContainer<T>::GTUIteratorConst::GTUIteratorConst(){
		it_ptr=shared_ptr<T>(new T[10],[](T *temp){delete[] temp;});
	}
	template<typename T>
	GTUContainer<T>::GTUIteratorConst::GTUIteratorConst(shared_ptr<T> other){
		it_ptr=other;
	}

	template<typename T>
	GTUContainer<T>::GTUIteratorConst::GTUIteratorConst(GTUIteratorConst &other){
		it_ptr=other.it_ptr;
	}

	template<typename T>
	GTUContainer<T>::GTUIteratorConst::GTUIteratorConst(const GTUIteratorConst &other){
		it_ptr=other.it_ptr;
	}


	template<typename T>
	const T& GTUContainer<T>::GTUIteratorConst::operator*(){
		return *it_ptr.get();
	}

	template<typename T>
	const T& GTUContainer<T>::GTUIteratorConst::operator->(){
		return it_ptr;
	}

	template<typename T>
	typename GTUContainer<T>::GTUIteratorConst GTUContainer<T>::GTUIteratorConst::operator++(){
		shared_ptr<T> temp(it_ptr.get()+1,[](T *t){});	
		it_ptr=temp;
		return GTUContainer<T>::GTUIteratorConst {temp};
	}
	template<typename T>
	typename GTUContainer<T>::GTUIteratorConst GTUContainer<T>::GTUIteratorConst::operator++(T ignore){	
		shared_ptr<T> temp(it_ptr.get()+1,[](T *t){});
		shared_ptr<T> temp2(it_ptr.get(),[](T *t){});
		it_ptr=temp;
		return GTUContainer<T>::GTUIteratorConst {temp2};
	}

	template<typename T>
	typename GTUContainer<T>::GTUIteratorConst GTUContainer<T>::GTUIteratorConst::operator--(){	
		shared_ptr<T> temp(it_ptr.get()-1,[](T *t){});
		it_ptr=temp;
		return GTUContainer<T>::GTUIteratorConst {temp};
	}



	template<typename T>
	typename GTUContainer<T>::GTUIteratorConst GTUContainer<T>::GTUIteratorConst::operator--(T ignore){
		shared_ptr<T> temp(it_ptr.get()-1,[](T *t){});
		shared_ptr<T> temp2(it_ptr.get(),[](T *t){});
		it_ptr=temp;
		return GTUContainer<T>::GTUIteratorConst {temp2};
	}

	template<typename T>
	bool GTUContainer<T>::GTUIteratorConst::operator==(const GTUIteratorConst &other){
		if(it_ptr==other.id_ptr)
			return true;
		else 
			return false;
	}
	template<typename T>
	bool GTUContainer<T>::GTUIteratorConst::operator!=(const GTUIteratorConst &other){
		if(it_ptr!=other.it_ptr)
			return true;
		else 
			return false;
	}
	template<typename T>
	bool GTUContainer<T>::GTUIteratorConst::operator!=(const GTUIterator &other){	/*This is for begin end end functions*/
		if(it_ptr!=other.getSharedPtr())
			return true;
		else 
			return false;
	}


	template<typename T>
	typename GTUContainer<T>::GTUIteratorConst& GTUContainer<T>::GTUIteratorConst::operator=(const GTUIterator &other){	/*This is for begin end end functions*/
		it_ptr=other.getSharedPtr();	
		return *this;
	}
	template<typename T>
	typename GTUContainer<T>::GTUIteratorConst& GTUContainer<T>::GTUIteratorConst::operator=(shared_ptr<T> other){
		it_ptr=other.getSharedPtr();
		return *this;
	}

	template<typename T>
	typename GTUContainer<T>::GTUIteratorConst& GTUContainer<T>::GTUIteratorConst::operator=(GTUIterator &other){
		it_ptr=other.getSharedPtr();
		return *this;
	}

	template<typename T>
	typename GTUContainer<T>::GTUIteratorConst& GTUContainer<T>::GTUIteratorConst::operator=(const GTUIteratorConst &other){	
		it_ptr=other.it_ptr;	
		return *this;
	}

	template<typename T>
	typename GTUContainer<T>::GTUIteratorConst& GTUContainer<T>::GTUIteratorConst::operator=(GTUIteratorConst &other){	
		it_ptr=other.it_ptr;	
		return *this;
	}




}








