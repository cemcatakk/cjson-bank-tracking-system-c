tumu: derle calistir

derle:
	gcc -I ./include/ -o ./lib/cJSON.o -c ./src/cJSON.c
	gcc -I ./include/ -o ./lib/cJSON_Utils.o -c ./src/cJSON_Utils.c
	gcc -I ./include/ -o ./lib/Emir.o -c ./src/Emir.c
	gcc -I ./include/ -o ./lib/Banka.o -c ./src/Banka.c
	gcc -I ./include/ -o ./lib/Hisse.o -c ./src/Hisse.c
	gcc -I ./include/ -o ./lib/Portfoy.o -c ./src/Portfoy.c
	gcc -I ./include/ -o ./bin/main.exe ./lib/cJSON.o ./lib/cJSON_Utils.o ./src/main.c
calistir:
	bin/main