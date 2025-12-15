#include "headers/header.hpp"

int main(int argc, char *argv[]){

	//Window initializer
	initscr();
	noecho();
	keypad(stdscr,TRUE);
	//raw();
	cbreak();
	curs_set(false);
	clear();
	start_color();
	refresh();

	//Game initializer
	Game *G = new Game();
	if(G->getf()==false) G->init();

	delete G;

	//Window destroyer
	endwin();
	return 0;
}
