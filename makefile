all: sprint1.lex sprint1.y arbre.c arbre.h table_symbole.c table_symbole.h
	bison -d sprint1.y
	flex sprint1.lex
	gcc -o sprint1 sprint1.tab.c lex.yy.c arbre.c generationCI.c table_symbole.c -lfl

test: all
	for i in Test_Script/*.txt; do (./sprint1 $$i >> /dev/null && echo "$$i marche"); done
