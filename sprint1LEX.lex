%{
/* Declaration C */



%}

/* Declaration Lex */

/* ###### SPRINT 1 ###### */

MAIN "int main"
NOMBRE [0-9]*
COMMENT \/\*.*\*\/
ENDLIGNE [\n]
STRING   \"([^\"\\]|\\.)*\"

/* ##################### */




/* Regle syntaxique */
%%
{COMMENT}*
{ENDLIGNE}*

{MAIN} {return MAIN;}
{NOMBRE} {yyval.ival=atoi(yytext); return NOMBRE;}
{STRING} {yyval.sval=strdup(yytext); return STRING;}

{printf} {return PRINTF;}
{printi} {return PRINTI;}

%%


/* Code C additionnel */

