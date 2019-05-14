/* Convay's Game Of Life implementation,
 * Trykoz Eduard, 2019
 */

/* Game core functionality */
#include "life.h"
/* Input() - process keypresses to interact with field;
 * loadField() - load field from a given file.
 */

/* Ncurses interface */
#include "intf.h"
/* initSct() - initialise the ncurses screen;
 * defField() - define the playfield by hand.
 */

int main(int argc, char **argv){
	/* The playfield toninteract with */
	p_Field field;

	if(argc-1==1){
		/* If file name is specified, load the save file.
		 * TODO: implement error handling (file does not exist
		 * or invalid amount of arguments).
		 */
		loadField(&field,argv[1]);
		initScr();
	}
	else{
		/* Define the field by hand otherwise. 
		 * TODO: give user an option to exit from definition
		 * screen.
		 */
		initScr();
		defField(&field);
	}

	/* Interaction loop. */
	while(Input(field));

	/* Disposing of the playfield. */
	free(field->cells);
	free(field);

	return 0;
}
