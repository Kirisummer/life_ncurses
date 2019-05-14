#include "intf.h"

/* Initialise the ncurses screen. */
void initScr(){
	initscr(); /* Initialise the screen */
	raw();	/* Catch all the signals, including ^C and others */
	noecho(); /* Do not echo keypresses */
	keypad(stdscr,TRUE); /* Use arrow keys */
}

/* Internal function, to be used only inside of library.
 * Edit the playfield.
 * TODO: Exit from the edit mode, discarding changes.
 */
u8 editField(p_Field field, u32 *x, u32 *y){
	/* 1. Print the field.
	 * 2. Move the cursor to (1,1), as the (0,0) is border.
	 * 3. Push changes to the screen.
	 * 4. Move the cursor, toggle the cell, save field or show 
	 *    brief help otherwise.
	 */
	printField(field);
	move(*x+1,*y+1);
	refresh();
	switch(getch()){
		case 'h':
		case KEY_LEFT:
			if(*y>0)
				*y-=1;
			break;
		case 'l':
		case KEY_RIGHT:
			if(*y<field->width-1)
				*y+=1;
			break;
		case 'k':
		case KEY_UP:
			if(*x>0)
				*x-=1;
			break;
		case 'j':
		case KEY_DOWN:
			if(*x<field->height-1)
				*x+=1;
			break;
		case 't':
			field->cells[*x*field->width+*y]=!field->cells[*x*field->width+*y];
			break;
		case 's':
			return 0;
		default:
			mvaddstr(field->height+2,0,"'hjkl' or arrows to move cursor, 't' to toggle a cell, 's' to continue");
			getch();
	}
	return 1;
}

/* Define the playfield by hand.
 * TODO: change defField()'s type to u8 to give user an option
 * to exit from definition screen. 
 */
void defField(p_Field *field){
	/* 1. Get maximum screen dimensions.
	 * 2. Prompt about dimensions until valid ones are gotten.
	 * 3. Edit the empty field.
	 * 4. Continue.
	 */

	u32 height,width; //dimensions to enter
	u32 t_height,t_width; //maximum dimensions
	u32 x,y; //current cursor coordinates. x is row, y is collumn

	getmaxyx(stdscr,t_height,t_width);
	echo(); //Turning echo on, so the user sees their input
	do{
		printw("Enter board dimensions (Your current terminal's maximum is %ux%u): ",t_height-2,t_width-2);
		scanw("%u %u",&height,&width);
	}while(height>t_height-2 || width>t_width-2);
	noecho(); //Turning it back off

	*field=allocField(height,width);
	x=y=0;
	while(editField(*field,&x,&y));
	return;
}

/* Print the playfield */
void printField(p_Field field){
	u32 i,j;
	clear(); // Reset the screen

	/* Draw the top of the border */
	move(0,0); 
	for(j=0; j<field->width+2; ++j){
		addch('*');
	}

	/* Drawing playfield contents, surrounded by the border */
	for(i=0; i<field->height; ++i){
		mvaddch(i+1,0,'*');
		for(j=0; j<field->width; ++j){
			if(field->cells[i*field->width+j])
				addch('O');
			else
				addch(' ');
		}
		addch('*');
	}
	/* Drawing the lower border. */
	move(i+1,0);
	for(j=0; j<field->width+2; ++j){
		addch('*');
	}
	/* Push updates to the screen. */
	refresh();
}

/* Quit the ncurses mode */
void killScr(){
	endwin();
}

/* Process keypresses to interact with field. */
u8 Input(p_Field field){
	/* 1. Print the field.
	 * 2. Go to the next iteration, edit, save the field, quit
	 *    or show a brief help otherwise.
	 */

	char fname[256];
	u32 x,y;

	printField(field);
	switch(getch()){
		case 'n':
			nextIter(field);
			return 1;
		case 's':
			mvaddstr(field->height+2,0,"Enter the file name to save a field to: ");
			echo();
			getstr(fname);
			noecho();
			saveField(field,fname);
			return 1;
		case 'q':
			killScr();
			return 0;
		case 'e':
			x=y=0;
			while(editField(field,&x,&y));
			return 1;
		default:
			mvaddstr(field->height+2,0,"'n' for next iteration, 's' for saving field, 'e' to edit field, 'q' to quit.");
			getch();
			return 1;
	}
}
