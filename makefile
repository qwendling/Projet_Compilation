all: Sprint1.lex Sprint1.y
	bison -d Sprint1.y
	flex Sprint1.lex
	gcc -o Sprint1 Sprint1.tab.c lex.yy.c -lfl
