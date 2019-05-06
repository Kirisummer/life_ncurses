#ifndef INTF_H
#define INTF_H

#include <ncurses.h>
#include "life.h"

void initScr();
void defField(p_Field *field);
void printField(p_Field field);
u8 Input(p_Field field);
void killScr();

#endif //INTF_H
