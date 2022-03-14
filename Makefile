all: main.cpp
	g++ main.cpp Thread_Pool.cpp -o cp



clean:
		rm cp
