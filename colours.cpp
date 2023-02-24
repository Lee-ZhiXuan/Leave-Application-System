//Colour functions definitions file
//Colours are based on ANSI colour codes

#include<stdio.h>
#include<conio.h>


void clear() {
	printf("\033[m");
}


void white() {
	printf("\033[0;37m");
}
void white_bold() {
	printf("\033[1;37m");
}


void red() {
	printf("\033[0;31m");
}
void red_bold() {
	printf("\033[1;31m");
}


void yellow() {
	printf("\033[0;33m");
}
void yellow_bold() {
	printf("\033[1;33m");
}


void green() {
	printf("\033[0;32m"); 
}
void green_bold() {
	printf("\033[1;32m");
}