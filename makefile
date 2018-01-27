all:result

cal.o:cal.cpp
	g++ -c cal.cpp
result:cal.o
	g++ -g  -o cal cal.o
clean:
	rm -f cal.o cal
