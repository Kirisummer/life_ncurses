#ifndef LIFE_H
#define LIFE_H

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>

typedef char u8;
typedef	uint32_t u32;
typedef	int32_t i32;

typedef struct{
	u8 *cells;
	u32 height;
	u32 width;
}Field,*p_Field;

// Next iteration of the field
void nextIter(p_Field field);
// Allocate the field of certain size
p_Field allocField(u32 height, u32 width);
// Save field to file
u8 saveField(p_Field field, char *fname);
// Load field from file
u8 loadField(p_Field *field, char *fname);

#endif //LIFE_H
