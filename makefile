# Style
GREEN = \033[0;42m
END = \033[0m
BOLD= \033[0;1m
YELLOW = \033[1;43m


# Makefile

all: sprint1.lex sprint1.y arbre.c arbre.h table_symbole.c table_symbole.h
	bison -d sprint1.y && echo " \n \t ${YELLOW} Compiled ${END}"
	flex sprint1.lex && echo " \n \t ${YELLOW} Compiled ${END}"
	gcc -o sprint1 sprint1.tab.c lex.yy.c arbre.c generationCI.c table_symbole.c -lfl && echo "\n \t${YELLOW} Compiled ${END}"


test: all
	for i in Test_Script/*.txt; do (./sprint1 $$i >> /dev/null; echo "$$i ${BOLD} ${GREEN} PASSED ${END}"); done
