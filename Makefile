target: objects
	g++ ./*.o -Wall -Wextra -lsfml-window -lsfml-graphics -lsfml-system -o ./PhysBalls

objects:
	g++ -c ./*.cpp

clean:
	rm *.o -rf