%option main
%%
#.+\n		{ printf("%s",yytext); }
[ \t\r\n]+	{}	/* spaces */
.			{}	/* undetected chars */
%%
