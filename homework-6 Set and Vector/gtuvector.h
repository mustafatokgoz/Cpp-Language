#ifndef GTUVECTOR_H
#define GTUVECTOR_H

#include<iostream>
#include<memory>

#include"gtucontainer.h"
					/*This is header file for vector*/
using namespace std;
namespace myGTUContainer{
	template<typename T>
	class GTUVector : public GTUContainer<T>{

			public : 
				 GTUVector();
				 GTUVector(size_t n_capacity);
				 bool empty() const override;
			 	 size_t size() const override;
				 size_t max_size() override;
			 	 void insert(const T &value) override;
			 	 size_t erase(const T &number) override; 
			 	 void clear() override;
			 	 typename GTUVector<T>::GTUIterator begin() override;
			 	 typename GTUVector<T>::GTUIterator end() override;	
				 T& operator[](size_t index);
			private : 
				shared_ptr<T> data;
				size_t used=0;
				size_t capacity=0;
			

	};
}


#endif
