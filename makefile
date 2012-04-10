main: main.o lyrics_processing.o connection.o user_interface.o 
	gcc main.o lyrics_processing.o connection.o user_interface.o -l curl -o main
main.o: ./src/main.c ./src/Headers/lyrics_processing.h
	gcc -x c -g -Wall -ansi -c ./src/main.c
lyrics_processing.o: ./src/lyrics_processing.c ./src/Headers/lyrics_processing.h ./src/Headers/connection.h ./src/user_interface.c
	gcc -x c -g -Wall -ansi -c ./src/lyrics_processing.c
connection.o: ./src/connection.c ./src/Headers/connection.h
	gcc -x c -g -Wall -ansi -c ./src/connection.c
user_interface.o: ./src/user_interface.c ./src/Headers/user_interface.h
	gcc -x c -g -Wall -ansi -c ./src/user_interface.c