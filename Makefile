SRC=$(wildcard *.c)

a.out: $(SRC)
	gcc -o $@ $^