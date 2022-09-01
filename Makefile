# CC = gcc
# CFLAGS = -Wall -g -O2
# STD = -std=c99
NAME = available board otherfunc putImfo tree record#to add
DEPS = $(NAME:%=hs/%.h)
OBJ = $(NAME:%=objs/%.o)
TARGET = m r z main#to add

all: $(TARGET)

#to add
m: mosero.c $(OBJ)
	gcc -Wall -O2 -g -o m $(OBJ) mosero.c

r: rMatch.c $(OBJ)
	gcc -Wall -O2 -o r $(OBJ) rMatch.c

z: zmain.c $(OBJ)
	gcc -Wall -O2 -o z $(OBJ) zmain.c

main: main.c $(OBJ)
	gcc -Wall -O2 -g -o main $(OBJ) main.c

objs/%.o: %.c $(DEPS)
	gcc -g -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o objs/* m r z 
#to add