#ifndef INTF_H
#define INTF_H

/* Ncurses library */
#include <ncurses.h>
/* Core game mechanics. */
#include "life.h"

/* Initialise the ncurses screen. */
void initScr();

/* Define the playfield by hand.
 * TODO: change defField()'s type to u8 to give user an option
 * to exit from definition screen. 
 */
void defField(p_Field *field);

/* Print the playfield */
void printField(p_Field field);

/* Process keypresses to interact with field. */
u8 Input(p_Field field);

/* Quit the ncurses mode */
void killScr();

#endif //INTF_H
