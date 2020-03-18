
output: gtuvector.o gtucontainer.o gtuset.o test.o
	g++ gtuvector.o  gtucontainer.o  gtuset.o test.o -o output

gtuvector.o:gtuvector.cpp gtuvector.h
	g++ -c gtuvector.cpp -std=c++11

gtucontainer.o:gtucontainer.cpp gtucontainer.h
		g++ -c gtucontainer.cpp  -std=c++11

gtuset.o:gtuset.cpp gtuset.h
	g++ -c gtuset.cpp -std=c++11

test.o: test.cpp 
	g++ -c test.cpp -std=c++11

clean: 
	rm *.o output

