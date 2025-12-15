#include "headers/header.hpp"

int Hanoi::Disk::gets(){return S;}
int Hanoi::Disk::getx(){return X;}
int Hanoi::Disk::gety(){return Y;}
int Hanoi::Disk::getp(){return P;}

//Disk objects functions
Hanoi::Disk::Disk(int x, int y, int s, int p):X(x),Y(y), S(s), P(p){}

//Getters/Setters
void Hanoi::Disk::setp(int p){P = p;}
void Hanoi::Disk::set(int x,int y){
	X = x;
	Y = y;
}

void Hanoi::Disk::move(int x,int y){
	X += x;
	Y += y;
}

void Hanoi::Disk::print(WINDOW *field, bool f){
	//Print the disk
	f?wattron(field,COLOR_PAIR(PLAYER)):
		wattron(field,COLOR_PAIR(DISK));
	mvwprintw(field,Y, X-S, "(%d",S);
	for(int i=0;i!=S*2-(S>9?2:1);i++)waddstr(field,"=");
	waddstr(field,")");
	f?wattroff(field,COLOR_PAIR(PLAYER)):
		wattroff(field,COLOR_PAIR(DISK));
	wrefresh(field);
}

void Hanoi::Disk::clear(WINDOW *field, bool f){
	//clear the disk
	mvwprintw(field,Y, X-S, "  ",S);
	for(int i=0;i!=S*2+1;i++)waddstr(field," ");
	if(f){
		wattron(field,COLOR_PAIR(BASE));
		mvwaddstr(field,Y,X,"||");
		wattroff(field,COLOR_PAIR(BASE));
	}
	wrefresh(field);
}

