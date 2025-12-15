#include "headers/header.hpp"

/*
COLOR_BLACK
COLOR_RED
COLOR_GREEN
COLOR_YELLOW
COLOR_BLUE
COLOR_MAGENTA
COLOR_CYAN
COLOR_WHITE
*/

Game::Game(){
	f=false;
	//Colors initialize
	init_pair(PLAYER, COLOR_BLUE, COLOR_GREEN);
	init_pair(DISK, COLOR_RED, COLOR_CYAN);
	init_pair(BASE, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(TITEL, COLOR_RED, COLOR_BLACK);
	if(LINES<14||COLS<75){
		addstr("Sorry, your window is too small!!\nPress any key to continue");
		refresh();
		getch();
		Outro();
		f=true;
	}else{

		//Values initializer
		opt = 0;
		ui = 0;
		usr = 0;
		srand(clock());
		int t = COLS/8<LINES-13?COLS/8:LINES-13;
		int nd = rand()%(t) + 1;
		int ip = rand()%3;
		int fp = (ip + rand()%2+1)%3;

		//Windows initializer
		info = newwin(8, 55, 0, 0);
		menu = newwin(8, COLS-55, 0, 55);
		field = newwin(LINES-8, COLS, 8, 0);
		HT = new Hanoi(field,nd,ip,fp);
	}
}

bool Game::getf(){return f;}

void Game::Title(){
	attron(COLOR_PAIR(TITEL));
	timeout(200);
	move(0,0);
	clear();
	for(int i=0;i!=7;i++){
		mvaddstr(0,0,"\n\
		*     *       *       *      *     ***    *****\n\
		*     *      * *      **     *    *   *     *\n\
		*     *     *   *     * *    *   *     *    *\n\
		*******    *******    *  *   *   *     *    *\n\
		*     *   *       *   *   *  *   *     *    *\n\
		*     *  *         *  *    * *    *   *     * \n\
		*     * *           * *     **     ***    *****");
		refresh();
		if(~getch()){
			attroff(COLOR_PAIR(TITEL));
			timeout(-1);
			return;
		}
		mvaddstr(0,0,"\n\
		-     -       -       -      -     ---    -----\n\
		-     -      - -      --     -    -   -     -\n\
		-     -     -   -     - -    -   -     -    -\n\
		-------    -------    -  -   -   -     -    -\n\
		-     -   -       -   -   -  -   -     -    -\n\
		-     -  -         -  -    - -    -   -     -\n\
		-     - -           - -     --     ---    -----");
		refresh();
		if(~getch()){
			attroff(COLOR_PAIR(TITEL));
			timeout(-1);
			return;
		}
	}
	attroff(COLOR_PAIR(TITEL));
	timeout(-1);
	return;
}

void Game::Outro(){
	timeout(200);
	attron(COLOR_PAIR(TITEL));
	move(0,0);
	clear();
	for(int i=0;i!=7;i++){
		mvaddstr(0,0,"\n\
		******* *     *       *       *      * *    *         *     *   ***    *     *\n\
		   *    *     *      * *      **     * *   *           *   *   *   *   *     *\n\
		   *    *     *     *   *     * *    * *  *             * *   *     *  *     *\n\
		   *    *******    *******    *  *   * ***               *    *     *  *     *\n\
		   *    *     *   *       *   *   *  * *  *              *    *     *  *     *\n\
		   *    *     *  *         *  *    * * *   *             *     *   *    *   *\n\
		   *    *     * *           * *     ** *    *            *      ***      ***");
		refresh();
		if(~getch()){
			attroff(COLOR_PAIR(TITEL));
			timeout(-1);
			return;
		}
		mvaddstr(0,0,"\n\
		------- -     -       -       -      - -    -         -     -   ---    -     -\n\
		   -    -     -      - -      --     - -   -           -   -   -   -   -     -\n\
		   -    -     -     -   -     - -    - -  -             - -   -     -  -     -\n\
		   -    -------    -------    -  -   - ---               -    -     -  -     -\n\
		   -    -     -   -       -   -   -  - -  -              -    -     -  -     -\n\
		   -    -     -  -         -  -    - - -   -             -     -   -    -   -\n\
		   -    -     - -           - -     -- -    -            -      ---      ---");
		refresh();
		if(~getch()){
			attroff(COLOR_PAIR(TITEL));
			timeout(-1);
			return;
		}
	}
	timeout(-1);
	attroff(COLOR_PAIR(TITEL));
	return;
}

void Game::init(){
	Title();
	bool ff = true;
	while(ff){
		HT->reset();
		clear();
		printMM();

		opt = 0;
		while(opt != ' '){
			if(LINES<14||COLS<75){
				clear();
				addstr("Sorry, your window is too small!!\nPress any key to continue");
				refresh();
				getch();
				Outro();
				return;
			}
			printMMopts();
			opt = getch();
			switch(opt){
				case 'q':
					Outro();
					return;
					break;
				case KEY_RIGHT:
				case KEY_DOWN:
				case 's':
				case 'd':
					ui = (ui+1)%4;
					break;
				case KEY_LEFT:
				case KEY_UP:
				case 'w':
				case 'a':
					ui = (ui+4-1)%4;
					break;
				case ' ':
				case KEY_ENTER:
				case '\n':
					opt = ' ';
			}
		}

		switch(ui){
			case 0:
				wclear(info);
				wrefresh(info);
				wclear(menu);
				wrefresh(menu);
				move(4,0);
				printw("Play and win!!\nMove all disks to pivot %d to win\nPress any key to start playing\nţOr 'q' to quit or cancel move",HT->getfp()+1);
				refresh();
				if(getch()=='q') break;
				ui = HT->getip();
				opt = 0;
				HT->select(ui);
				while(opt != 'q'){
					if(HT->winval()){
						wclear(info);
						wrefresh(info);
						ui=1;
						for(int i=0;i<HT->getnd();i++)ui*=2;
						ui--;
						mvprintw(3,0,"You won!!\nFinished in %d moves!!\nBest play is %d moves!!",HT->getnm(),ui);
						refresh();
						getch();
						opt=0;
						break;
					}else{
						mvprintw(3,0,"You've made %d Moves!!",HT->getnm());
						refresh();
					}
					int sel=ui;
					opt = getch();
					HT->select(ui,false);
					if(opt == KEY_LEFT) ui=(ui+2)%3;
					else if(opt == KEY_RIGHT) ui=(ui+1)%3;
					else if(opt == ' ' || opt == '\n'){
						HT->get(ui);
						while(true){
							mvprintw(3,0,"You've made %d Moves!!",HT->getnm());
							refresh();
							opt = getch();
							move(0,0);
							clrtoeol();
							move(1,0);
							clrtoeol();
							if(opt == KEY_LEFT) ui=(ui+2)%3;
							else if(opt == KEY_RIGHT) ui=(ui+1)%3;
							else if(opt == ' ' || opt == '\n'){
								if(!HT->set(ui,true)){
									mvaddstr(0,0,"You cannot place a bigger disk on a smaller disk!\nIt's against the rules!!!");
									refresh();
									continue;
								}
								break;
							}
							else if(opt == 'q'){
								ui = sel;
								HT->move(ui);
								HT->set(ui,false);
								break;
							}
							HT->move(ui);
						}
						opt = ' ';
					}
					if(opt == 'q') break;
					for(int i=0;i<3;i++)
						if(!HT->select(ui)) ui = (ui+(opt==KEY_LEFT?2:1))%3;
						else break;
				}
				if(opt=='q'){
					wclear(info);
					wrefresh(info);
					mvprintw(6,0,"Exiting play mode after %d moves!!!",HT->getnm());
					refresh();
					getch();
				}
				ui = 0;
				break;
			case 1:
				//Solve the problem
				wclear(info);
				wrefresh(info);
				wclear(menu);
				wrefresh(menu);
				move(5,0);
				addstr("I will solve the puzzle!!\nPress any key to start watching me solve it\nţOr 'q' to cancel");
				refresh();
				if(getch()=='q') break;
				move(6,0);
				wclear(info);
				wrefresh(info);
				addstr("Solving...\nPress any key to speed it up, press 'q' to cancel");
				timeout((int)(42/HT->getnd()));
				ui = HT->resolve(HT->getnd(), HT->getfp());
				timeout(-1);
				move(6,0);
				wclear(info);
				wrefresh(info);
				if(ui){
					ui=1;
					for(int i=0;i<HT->getnd();i++)ui*=2;
					ui--;
					printw("Canceled by user after %d movements!!!!\n\
Would have finished after %d movements!!", HT->getnm()+1, ui);
					ui=0;
				}else{
					addstr("Solved!!!\n");
					printw("Solved in %d movements!!!!", HT->getnm());
				}
				refresh();
				napms(500);
				getch();
				ui = 1;
				break;
			case 2:
				wclear(menu);
				wrefresh(menu);
				wclear(info);
				wrefresh(info);
				move(0,0);
				addstr("Modify the game parameters!!\n\
(Press up or down to change the number of disks\n\
 Left and right to change starting pivot\n\
 Enter or space to exit)\n\n\n");
				refresh();
				while(true){
					if(LINES<14||COLS<75){
						clear();
						addstr("Sorry, your window is too small!!\nPress any key to continue");
						refresh();
						getch();
						Outro();
						return;
					}
					opt = getch();
					if(opt == ' ' || opt == '\n') break;
					else if(opt == KEY_UP)        HT->setnd(1);
					else if(opt == KEY_DOWN)      HT->setnd(-1);
					else if(opt == KEY_RIGHT)     HT->setip(1);
					else if(opt == KEY_LEFT)      HT->setip(-1);
					HT->print();
				}
				break;
			case 3:
				ff = false;
		}
	}
	Outro();
	return;
}

void Game::printMM(){
	move(0,0);
	wclear(info);
	printw("\
The game has begun!!\n\
The generated Hanoi tower has %d disks\n\
The goal is to move them from the base %d to %d\n\n\n\n\n\
The towers look like this:", HT->getnd(), HT->getip()+1, HT->getfp()+1);
	refresh();

	HT->print();
	return;
}

void Game::printMMopts(){
	wclear(menu);
	mvwaddstr(menu,0,0,"Main menu:\n\n\
	  Play!!  \n\
	  Watch it solve!!  \n\
	  Modify game parameters!!  \n\
	  Get out!!  \n\
(Use arrows to move, space or enter to select)");
	wrefresh(menu);

	wmove(menu,ui+2,0);
	wattron(menu,COLOR_PAIR(DISK));
	switch(ui){
		case 0:
			waddstr(menu,"\t**Play!!**");
			break;
		case 1:
			waddstr(menu,"\t**Watch it solve!!** ");
			break;
		case 2:
			waddstr(menu,"\t**Modify game parameters!!**");
			break;
		case 3:
			waddstr(menu,"\t**Get out!!**");
			break;
	}
	wattroff(menu,COLOR_PAIR(DISK));
	wrefresh(menu);
	return;
}
