#include "life.h"

/* Allocate the memory for field of certain size. */
p_Field allocField(u32 height, u32 width){
	/* 1. Allocate memory for the field.
	 * 2. Allocate memory for the cells of the field.
	 * 3. Fill in the height and width.
	 */
	p_Field field;
	field=malloc(sizeof(Field));
	field->cells=calloc(height*width,sizeof(u8));
	field->height=height;
	field->width=width;
	return field;
}

/* How many cells around the given one are alive? */
u8 radius(p_Field field, int32_t x, int32_t y){
	int32_t i,j;
	u8 rad;
	rad=0;
	for(i=x-1; i<=x+1; ++i){
		for(j=y-1; j<=y+1; ++j){
			if( (0<=i && i<field->height) && (0<=j && j<field->width) && field->cells[i*field->width+j]==1 && (i!=x || j!=y) ){
				rad++;
			}
		}
	}
	return rad;
}

// Next iteration of the field
void nextIter(p_Field field){
	u8 *next;
	u32 i,j;
	u8 rad;
	/* Allocate a new field */
	next=malloc(sizeof(u8)*field->height*field->width);

	/* Fill the new field.
	 * If there are two cells around the given one, it is
	 * alive. If there are less than two or more than three
	 * cells alive, the cell is dead. If there are three
	 * living cells around the given one, the cell becomes
	 * live.
	 */
	for(i=0; i<field->height; ++i){
		for(j=0; j<field->width; ++j){
			rad=radius(field,i,j);
			if(field->cells[i*field->width+j]==1 && rad==2 || rad==3){
				next[i*field->width+j]=1;
			}
			else if(field->cells[i*field->width+j]==0 || rad<2 || rad>3){
				next[i*field->width+j]=0;
			}
		}
	}

	/* Free the memory for old field and replace it with 
	 * a new one.
	 */
	free(field->cells);
	field->cells=next;
}

// Save field to file
u8 saveField(p_Field field, char *fname){
	FILE *file;

	/* If file was not opened, stop and return error */
	file=fopen(fname,"w");
	if(file==NULL){
		return 0;
	}

	/* Write the dimensions and the field */
	fwrite(&field->height,sizeof(u32),1,file);
	fwrite(&field->width,sizeof(u32),1,file);
	fwrite(field->cells,sizeof(u8),field->height*field->width,file);

	return 1;
}

// Load field from file
u8 loadField(p_Field *field, char *fname){
	FILE *file;
	u32 height,width;

	/* If file was not opened, stop and return error */
	file=fopen(fname,"r");
	if(file==NULL){
		return 0;
	}

	/* Read the dimensions and the field */
	height=width=0;
	fread(&height,sizeof(u32),1,file); 
	fread(&width,sizeof(u32),1,file);
	*field=allocField(height,width);
	if(!fread((*field)->cells,sizeof(u8),height*width,file)){
		return 0;
	}

	return 1;
}
