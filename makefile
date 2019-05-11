all: calc.exe

calc.exe:
	g++ -o bin/calc.exe src/calculator.cpp src/input.cpp

clean:
	rm bin/calc.exe