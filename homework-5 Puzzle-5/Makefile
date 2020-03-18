
output: 171044077.o boardvector.o boardarray1D.o boardarray2D.o abstractboard.o 
	g++ 171044077.o  boardvector.o boardarray1D.o boardarray2D.o abstractboard.o -o output

171044077.o:171044077.cpp 
	g++ -c 171044077.cpp -std=c++11

abstractboard.o:abstractboard.cpp abstractboard.h
		g++ -c  abstractboard.cpp -std=c++11

boardvector.o:boardvector.cpp boardvector.h
		g++ -c boardvector.cpp  -std=c++11

boardarray1D.o:boardarray1D.cpp boardarray1D.h
		g++ -c boardarray1D.cpp  -std=c++11

boardarray2D.o:boardarray2D.cpp boardarray2D.h
		g++ -c boardarray2D.cpp  -std=c++11

clean: 
	rm *.o output

