%token MAIN
%token RETURN
%token NOMBRE
%%
program: fonction;

fonction: MAIN'('')'{ListeInstr};

ListeInstr:I\;ListeInstr
	|RETURN B { return $2)
	|PRINTF'('STRING')' { printf("%s\n",$3) }
	|PRINTI'('B')' { printf("%d\n",$3); }
	;

B: NOMBRE;

%%
int yyerror(void){
	fprintf(stderr,"erreur de syntaxe\n");return;
}
