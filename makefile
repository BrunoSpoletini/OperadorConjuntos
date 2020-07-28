DIR = estructuras
TEMP = interprete.o ./$(DIR)/conjunto.o ./$(DIR)/ctree.o ./$(DIR)/dlist.o ./$(DIR)/hash.o interprete
ARG = -Wall -Wextra -Werror -std=c99


all: interprete

interprete: interprete.o ./$(DIR)/conjunto.o ./$(DIR)/ctree.o ./$(DIR)/dlist.o ./$(DIR)/hash.o
	gcc $(ARG) -o interprete interprete.o ./$(DIR)/conjunto.o ./$(DIR)/ctree.o ./$(DIR)/dlist.o ./$(DIR)/hash.o -lm

interprete.o: interprete.c interprete.h ./$(DIR)/dlist.o ./$(DIR)/ctree.o ./$(DIR)/conjunto.o ./$(DIR)/hash.o
	gcc $(ARG) -c interprete.c

conjunto.o: ./$(DIR)/conjunto.c ./$(DIR)/conjunto.h ./$(DIR)/dlist.o
	gcc $(ARG) -c ./$(DIR)/conjunto.c

ctree.o: ./$(DIR)/ctree.c ./$(DIR)/ctree.h
	gcc $(ARG) -c ./$(DIR)/ctree.c 

dlist.o: ./$(DIR)/dlist.c ./$(DIR)/dlist.h
	gcc $(ARG) -c ./$(DIR)/dlist.c

hash.o: ./$(DIR)/hash.c ./$(DIR)/hash.h ./$(DIR)/dlist.o ./$(DIR)/ctree.o ./$(DIR)/conjunto.o
	gcc $(ARG) -c ./$(DIR)/hash.c -lm

clean:
	-rm $(TEMP)

.PHONY : all
.PHONY : clean