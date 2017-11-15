############################
# 		Style Variables	  	#
###########################

GREENBOX = \033[0;42m
REDBOX = \033[0;41m
END = \033[0m
BOLD = \033[0;01m
YELLOW = \033[1;33m
GREEN = \033[0;32m
CYAN = \033[0;36m
LIGHT_CYAN = \033[1;36m
ORANGE= \033[0;33m

SPRED = \n\-------------------------------------------------------\n\n
COLUMN = \033[10C

############################
# 		Files Variables	   	#
###########################

EXEC = sprint1
LEX = sprint1.lex
YACC = sprint1.y
ARBRE_C = arbre.c
ARBRE_H = arbre.h
SYMBOLE_C = table_symbole.c
SYMBOLE_H = table_symbole.h
GENERATIONCI_C = generationCI.c

############################
# 		Makefile Action			#
###########################

all: ${LEX} ${YACC} ${ARBRE_C} ${ARBRE_H} ${SYMBOLE_C} ${SYMBOLE_C}
	@printf "${BOLD}${SPRED}${END}"
	@printf "${ORANGE}Compiling in process ... ${END} \n\n"
	@printf "${YELLOW}YACC Compiling... \n${END}"
	@bison -d ${YACC}
	@printf "${CYAN}\t\t YACC Compiled ${END} \n"
	@#######
	@printf "${YELLOW}LEX Compiling... \n${END}"
	@flex ${LEX}
	@printf "${CYAN}\t\t LEX Compiled ${END} \n"
	@#######
	@printf "${YELLOW}Project Compiling... ${END} \n"
	@gcc -o ${EXEC} lex.yy.c ${EXEC}.tab.c ${ARBRE_C} ${GENERATIONCI_C} ${SYMBOLE_C} -ly
	@printf "\n${CYAN}\t\t Project Compiled ${END} \n\n"
	@#######

# Pass test
test: all
	@printf "${BOLD}${SPRED}${END} \n"
	@printf "${ORANGE}Testing in process ... ${END}\n\n"
	@for i in Test_Script/*.txt; do \
			./sprint1 $$i >> /dev/null \
			&& printf "%s""$$i ${GREENBOX} PASSED ${END} \n"\
			|| printf "%s""$$i ${REDBOX} FAILED ${END} \n" ; \
	done
	@printf "\n${GREEN}Great success can commit now ! ${END}\n\n"
	@gnome-terminal --maximize -e ./borat.sh
	

# Clean repository
clean:
	@rm *.yy.*
	@rm *.tab.*
	@rm ${EXEC}
	@printf " \n ${BOLD}Répertoire Nettoyer ! ${END}\n\n"

#help makefile
help:
	@echo "\n ${BOLD} Action disponible :"
	@echo "\t ${ORANGE}make      	${END}-> Compile le projet"
	@echo "\t ${ORANGE}make test 	${END}-> Passe les tests"
	@echo "\t ${ORANGE}make clean	${END}-> Nettoie le repertoire"
	@echo "\t ${ORANGE}make help	${END}-> Information Makefile \n"
