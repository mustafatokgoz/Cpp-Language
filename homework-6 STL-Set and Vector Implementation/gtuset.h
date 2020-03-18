#ifndef GTUSET_h
#define GTUSET_H
#include<iostream>
#include<memory>

#include"gtucontainer.h"
					/*This is header file for set*/
using namespace std;
namespace myGTUContainer{
	template<typename T>
	class GTUSet : public GTUContainer<T>{

			public : 
				 GTUSet();
				 GTUSet(size_t n_capacity);
				 bool empty() const override;
			 	 size_t size() const override;
				 size_t max_size() override;
			 	 void insert(const T &value) override;
			 	 size_t erase(const T &number) override; 
			 	 void clear() override;
			 	 typename GTUSet<T>::GTUIterator begin() override;
			 	 typename GTUSet<T>::GTUIterator end() override;	
			private : 
				shared_ptr<T> data;
				size_t used=0;
				size_t capacity=0;
			

	};
}
#endif
