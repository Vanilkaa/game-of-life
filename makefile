main.apk: main.o grid.o simulation.o
	g++ main.o grid.o simulation.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main.apk 

main.o: main.cpp
	g++ -c main.cpp

grid.o: grid.cpp
	g++ -c grid.cpp

simulation.o: simulation.cpp
	g++ -c simulation.cpp

clean:
	rm -f *.o main.apk
