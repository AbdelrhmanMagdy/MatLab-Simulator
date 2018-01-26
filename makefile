all:
	g++ -g -w cMatrix.cpp main.cpp Matlab.cpp -o matrix
clean:
	rm matrix
