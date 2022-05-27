FO=./fichiers_o/
F=./fichiers/
exc=./exec/
EXEC=exercice1 exercice2 exercice3 exercice4 exercice5 exercice6 exercice7 exercice8 exercice9 main
O=exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o exercice8.o exercice9.o exercice1test.o exercice2main.o exercice3main.o exercice4main.o exercice5test.o exercice6test.o exercice7test.o exercice8test.o exercice9main.o main.o

all : $(O) $(EXEC)

o : $(O)

main : $(FO)exercice1.o $(FO)exercice2.o $(FO)exercice3.o $(FO)exercice4.o $(FO)exercice5.o $(FO)exercice6.o $(FO)exercice7.o $(FO)exercice8.o $(FO)exercice9.o $(FO)main.o 
	gcc $^ -o main  -lm -lssl -lcrypto

exercice1 : $(FO)exercice1.o $(FO)exercice1test.o
	gcc $^ -o $(exc)exercice1 -lm

exercice2 : $(FO)exercice1.o $(FO)exercice2.o $(FO)exercice2main.o
	gcc $^ -o $(exc)exercice2 -lm

exercice3 : $(FO)exercice1.o $(FO)exercice2.o $(FO)exercice3.o $(FO)exercice3main.o
	gcc $^ -o $(exc)exercice3 -lm

exercice4 : $(FO)exercice1.o $(FO)exercice2.o $(FO)exercice3.o $(FO)exercice4.o $(FO)exercice4main.o
	gcc $^ -o $(exc)exercice4 -lm
	
exercice5 : $(FO)exercice1.o $(FO)exercice2.o $(FO)exercice3.o $(FO)exercice4.o $(FO)exercice5.o $(FO)exercice5test.o
	gcc $^ -o $(exc)exercice5 -lm

exercice6 : $(FO)exercice1.o $(FO)exercice2.o $(FO)exercice3.o $(FO)exercice4.o $(FO)exercice5.o $(FO)exercice6.o $(FO)exercice6test.o 
	gcc $^ -o $(exc)exercice6 -lm

exercice7 : $(FO)exercice1.o $(FO)exercice2.o $(FO)exercice3.o $(FO)exercice4.o $(FO)exercice5.o $(FO)exercice6.o $(FO)exercice7.o $(FO)exercice7test.o 
	gcc $^ -o $(exc)exercice7 -lm -lssl -lcrypto

exercice8 : $(FO)exercice1.o $(FO)exercice2.o $(FO)exercice3.o $(FO)exercice4.o $(FO)exercice5.o $(FO)exercice6.o $(FO)exercice7.o $(FO)exercice8.o $(FO)exercice8test.o 
	gcc $^ -o $(exc)exercice8 -lm -lssl -lcrypto

exercice9 : $(FO)exercice1.o $(FO)exercice2.o $(FO)exercice3.o $(FO)exercice4.o $(FO)exercice5.o $(FO)exercice6.o $(FO)exercice7.o $(FO)exercice8.o $(FO)exercice9.o $(FO)exercice9main.o 
	gcc $^ -o $(exc)exercice9 -lm -lssl -lcrypto



exercice1test.o : $(F)exercice1test.c $(F)exercice1.h
	gcc -c $(F)exercice1test.c -o $(FO)exercice1test.o -lm

exercice2main.o : $(F)exercice2main.c $(F)exercice1.h $(F)exercice2.h
	gcc -c $(F)exercice2main.c -o $(FO)exercice2main.o -lm

exercice3main.o : $(F)exercice3main.c $(F)exercice1.h $(F)exercice2.h $(F)exercice3.h
	gcc -c $(F)exercice3main.c -o $(FO)exercice3main.o -lm

exercice4main.o : $(F)exercice4main.c $(F)exercice1.h $(F)exercice2.h $(F)exercice3.h $(F)exercice4.h
	gcc -c $(F)exercice4main.c -o $(FO)exercice4main.o -lm

exercice5test.o : $(F)exercice5test.c $(F)exercice1.h $(F)exercice2.h $(F)exercice3.h $(F)exercice4.h $(F)exercice5.h
	gcc -c $(F)exercice5test.c -o $(FO)exercice5test.o -lm

exercice6test.o : $(F)exercice6test.c $(F)exercice1.h $(F)exercice2.h $(F)exercice3.h $(F)exercice4.h $(F)exercice5.h $(F)exercice6.h
	gcc -c $(F)exercice6test.c -o $(FO)exercice6test.o -lm

exercice7test.o : $(F)exercice7test.c $(F)exercice1.h $(F)exercice2.h $(F)exercice3.h $(F)exercice4.h $(F)exercice5.h $(F)exercice6.h $(F)exercice7.h
	gcc -c $(F)exercice7test.c -o $(FO)exercice7test.o -lm -lssl -lcrypto

exercice8test.o : $(F)exercice8test.c $(F)exercice1.h $(F)exercice2.h $(F)exercice3.h $(F)exercice4.h $(F)exercice5.h $(F)exercice6.h $(F)exercice7.h $(F)exercice8.h
	gcc -c $(F)exercice8test.c -o $(FO)exercice8test.o -lm -lssl -lcrypto

exercice9main.o : $(F)exercice9main.c $(F)exercice1.h $(F)exercice2.h $(F)exercice3.h $(F)exercice4.h $(F)exercice5.h $(F)exercice6.h $(F)exercice7.h $(F)exercice8.h $(F)exercice9.h
	gcc -c $(F)exercice9main.c -o $(FO)exercice9main.o -lm -lssl -lcrypto

main.o : $(F)main.c $(F)exercice1.h $(F)exercice2.h $(F)exercice3.h $(F)exercice4.h $(F)exercice5.h $(F)exercice6.h $(F)exercice7.h $(F)exercice8.h $(F)exercice9.h
	gcc -c $(F)main.c -o $(FO)main.o  -lm -lssl -lcrypto



exercice1.o : $(F)exercice1.c $(F)exercice1.h 
	gcc -c $(F)exercice1.c -o $(FO)exercice1.o -lm

exercice2.o : $(F)exercice2.c $(F)exercice2.h $(F)exercice1.h
	gcc -c $(F)exercice2.c -o $(FO)exercice2.o -lm

exercice3.o : $(F)exercice3.h $(F)exercice2.h $(F)exercice1.h
	gcc -c $(F)exercice3.c -o $(FO)exercice3.o -lm

exercice4.o : $(F)exercice4.h $(F)exercice3.h $(F)exercice2.h $(F)exercice1.h
	gcc -c $(F)exercice4.c -o $(FO)exercice4.o -lm

exercice5.o : $(F)exercice5.h $(F)exercice4.h $(F)exercice3.h $(F)exercice2.h $(F)exercice1.h
	gcc -c $(F)exercice5.c -o $(FO)exercice5.o -lm

exercice6.o : $(F)exercice6.h $(F)exercice5.h $(F)exercice4.h $(F)exercice3.h $(F)exercice2.h $(F)exercice1.h
	gcc -c $(F)exercice6.c -o $(FO)exercice6.o -lm

exercice7.o : $(F)exercice7.h $(F)exercice6.h $(F)exercice5.h $(F)exercice4.h $(F)exercice3.h $(F)exercice2.h $(F)exercice1.h
	gcc -c $(F)exercice7.c -o $(FO)exercice7.o -lm -lssl -lcrypto

exercice8.o : $(F)exercice8.h $(F)exercice7.h $(F)exercice6.h $(F)exercice5.h $(F)exercice4.h $(F)exercice3.h $(F)exercice2.h $(F)exercice1.h
	gcc -c $(F)exercice8.c -o $(FO)exercice8.o -lm -lssl -lcrypto

exercice9.o : $(F)exercice9.h $(F)exercice8.h $(F)exercice7.h $(F)exercice6.h $(F)exercice5.h $(F)exercice4.h $(F)exercice3.h $(F)exercice2.h $(F)exercice1.h
	gcc -c $(F)exercice9.c -o $(FO)exercice9.o -lm -lssl -lcrypto


data :
	rm ./data/*
	rm ./Blockchain/*.txt
	rm *.txt

clean :
	rm ./fichiers_o/* 
	rm ./exec/*
	rm main *.txt
	rm ./data/*
	rm ./Blockchain/*.txt

