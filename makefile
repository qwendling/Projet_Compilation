all: sprint1.lex sprint1.y
	bison -d sprint1.y
	flex sprint1.lex
	gcc -o sprint1 sprint1.tab.c lex.yy.c -lfl

test: all
	for i in Test_Script/*.txt; do (./sprint1 $$i >> /dev/null && echo "$$i marche"); done

