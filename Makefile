agenda.exe : main.o menu1.o menu2.o date.o
	g++ -Wall -o agenda main.o menu1.o menu2.o date.o

main.o : main.cpp
	g++ -Wall -c main.cpp

menu1.o : menu1.cpp
	g++ -Wall -c menu1.cpp

menu2.o : menu2.cpp
	g++ -Wall -c menu2.cpp
date.o : date.cpp
	g++ -Wall -c date.cpp