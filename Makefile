run: clean bin/csv.out
		./bin/csv.out

bin/csv.out: bin
		gcc *.h *.c -o bin/csv.out -g

bin:
		mkdir -p bin

.PHONY: clean
clean:
		rm -f bin/csv