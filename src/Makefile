quack: quack.tab.c lex.c
	g++ quack.tab.c utilities/Cuadruplo.cpp lex.c -o quack
quack.tab.c :
	bison sintax.y -d -r all -o quack.tab.c
lex : lex.c
	gcc lex.c -o tokenizer
lex.c : 
	flex -o lex.c tokens.l
clean: 
	rm *.c
	rm *.h
	rm quack
rebuild: clean quack
