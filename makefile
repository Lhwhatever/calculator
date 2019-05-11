all: calc.exe

calc.exe:
	g++ -o bin/calc.exe src/calculator.cpp