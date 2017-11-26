all:
	g++ -w cMatrix.cpp main.cpp Parse.cpp -o matrix
clean:
	rm matrix
