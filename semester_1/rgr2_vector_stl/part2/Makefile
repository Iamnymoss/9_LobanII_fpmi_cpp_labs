all:
	g++ -Wall -Wextra -fsanitize=address,undefined,leak main.cpp time_utility.cpp -o main.out
	./main.out

clean:
	rm -f main.out