build: main.c
	@gcc -Wall ./main.c -o ./builds/build -lSDL2 -lGL

.PHONY: clean run

clean:
	@rm -f build

run:
	@./builds/build