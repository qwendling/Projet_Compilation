%token MAIN
%token RETURN
%token NOMBRE
%token STRING
%token PRINTF
%token PRINTI
%%
program: fonction;

fonction: MAIN'('')''{'ListeInstr'}';

ListeInstr: ListeInstr';'ListeInstr
	|RETURN B';' { return $2;}
	|PRINTF'('STRING')'';' { printf("%s\n",$3) }
	|PRINTI'('B')'';' { printf("%d\n",$3); }
	;

B: NOMBRE;

%%
int yyerror(void){
	fprintf(stderr,"erreur de syntaxe\n");return;
}
