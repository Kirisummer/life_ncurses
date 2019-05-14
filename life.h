#ifndef LIFE_H
#define LIFE_H

/* IO library */
#include <stdio.h>
/* fread() - read the field from file;
 * fwrite() - write the field to file.
 */

/* Standart integer definitions. */
#include <stdint.h>
typedef char u8;
typedef	uint32_t u32;
typedef	int32_t i32;
/* uint32_t and int32_t are for compatibility of field files. */

/* Memory allocation header. */
#include <malloc.h>
/* malloc() - allocate memory for cells of the field and the 
 *            field itself.
 * free() - free the cells and the field.
 */

/* Field atructure. */
typedef struct{
	u8 *cells;
	u32 height;
	u32 width;
}Field,*p_Field;
/* TODO: implement the borderless field. */

/* Next iteration of the field. */
void nextIter(p_Field field);
/* Allocate the memory for field of certain size. */
p_Field allocField(u32 height, u32 width);
/* Save field to file. */
u8 saveField(p_Field field, char *fname);
/* Load field from file. */
u8 loadField(p_Field *field, char *fname);

#endif //LIFE_H
