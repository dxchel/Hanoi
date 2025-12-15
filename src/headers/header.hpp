#include <cstdio>
#include <cstdlib>
#include <ncurses.h>
#include <time.h>

enum{
	ZERO,
	PLAYER,
	DISK,
	BASE,
	TITEL,
};

class Hanoi{
	class Disk{
		int X,Y,S,P;
		public:
			Disk(int x=0, int y=0, int s=0, int p=0);
			void set(int x, int y);
			int gets();
			int getx();
			int gety();
			int getp();
			void setp(int p);
			void move(int x, int y);
			void print(WINDOW *field, bool f = false);
			void clear(WINDOW *field, bool f = false);
	};
	WINDOW *field;
	int nd, ip, fp, nm, o, sd, sp;
	int **p;
	Disk **d;

	public:
		Hanoi(WINDOW *win, int num_disks, int initial_pivot, int final_pivot);
		int  getnm();
		int  getnd();
		int  getip();
		int  getfp();
		void setnd(int n);
		void setip(int n);
		void print();
		void change(int l, int a, int b);
		void reset();
		int  resolve(int l, int tp);
		void get(int pi);
		bool select(int pi, bool f=true);
		void move(int pi);
		bool set(int pi,bool f=true);
		bool winval();
};

class Game{
	WINDOW *field,*menu,*info;
	Hanoi* HT;
	wchar_t opt;
	int ui;
	char usr;
	bool f;

	public:
		Game();
		bool getf();
		void init();
		void Title();
		void Outro();
		void printMM();
		void printMMopts();
};
