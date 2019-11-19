all:
	gcc dirinfo.c

run:
	./a.out $(DIR)

clean:
	rm a.out
