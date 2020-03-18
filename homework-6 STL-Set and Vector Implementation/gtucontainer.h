#ifndef GTUCONTAINER_H
#define GTUCONTAINER_H
#include<iostream>
#include<memory>
				/*This is abstract container class header*/
using namespace std;
namespace myGTUContainer{
	template<typename T>
	class GTUContainer{

		public :  
			class GTUIterator{		/*This is GTUIterator inner class*/
				public:
					GTUIterator();
					GTUIterator(shared_ptr<T> other);
					GTUIterator(GTUIterator &other);
					GTUIterator(const GTUIterator &other);
					T& operator*();
					T& operator->();
					GTUIterator operator++();
					GTUIterator operator++(T ignore);
					GTUIterator operator--();
					GTUIterator operator--(T ignore);
					bool operator==(const GTUIterator &other);
					bool operator!=(const GTUIterator &other);
					GTUIterator& operator=(const GTUIterator &other);
					GTUIterator& operator=(GTUIterator &other);
					GTUIterator& operator=(shared_ptr<T> other);;
					shared_ptr<T> getSharedPtr() const;

				private:
					shared_ptr<T> it_ptr;	
				
			  };
			 class GTUIteratorConst{	/*This is GTUIteratorConst inner class*/
				public:
					GTUIteratorConst();
					GTUIteratorConst(shared_ptr<T> other);
					GTUIteratorConst(GTUIteratorConst &other);
					GTUIteratorConst(const GTUIteratorConst &other);
					const T& operator*();
					const T& operator->();
					GTUIteratorConst operator++();
					GTUIteratorConst operator++(T ignore);
					GTUIteratorConst operator--();
					GTUIteratorConst operator--(T ignore);
					bool operator==(const GTUIteratorConst &other);
					bool operator!=(const GTUIteratorConst &other);
					bool operator!=(const GTUIterator &other);
					GTUIteratorConst& operator=(const GTUIterator &other);
					GTUIteratorConst& operator=(GTUIterator &other);
					GTUIteratorConst& operator=(const GTUIteratorConst &other);
					GTUIteratorConst& operator=(GTUIteratorConst &other);
					GTUIteratorConst& operator=(shared_ptr<T> other);
				private:
					shared_ptr<T> it_ptr;	
				
			  };
			 virtual bool empty() const = 0;
			 virtual size_t size() const = 0;
			 virtual size_t max_size()  = 0;
			 virtual void insert(const T &value) = 0;
			 virtual size_t erase(const T &number) = 0; 
			 virtual void clear() = 0;
			 virtual GTUIterator begin() = 0;
			 virtual GTUIterator end() = 0;	
			
			
	};

}


#endif
