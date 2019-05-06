#include "life.h"

// Allocate the field of certain size
p_Field allocField(u32 height, u32 width){
	p_Field field;
	field=malloc(sizeof(Field));
	field->cells=calloc(height*width,sizeof(u8));
	field->height=height;
	field->width=width;
	return field;
}

// How many cells around the given one are alive?
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
	next=malloc(sizeof(u8)*field->height*field->width);

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
	free(field->cells);
	field->cells=next;
}

// Save field to file
u8 saveField(p_Field field, char *fname){
	FILE *file;

	file=fopen(fname,"w");
	if(file==NULL){
		return 0;
	}

	fwrite(&field->height,sizeof(u32),1,file);
	fwrite(&field->width,sizeof(u32),1,file);
	fwrite(field->cells,sizeof(u8),field->height*field->width,file);

	return 1;
}

// Load field from file
u8 loadField(p_Field *field, char *fname){
	FILE *file;
	u32 height,width;

	file=fopen(fname,"r");
	if(file==NULL){
		return 0;
	}

	height=width=0;
	fread(&height,sizeof(u32),1,file); 
	fread(&width,sizeof(u32),1,file);
	*field=allocField(height,width);
	if(!fread((*field)->cells,sizeof(u8),height*width,file)){
		return 0;
	}

	return 1;
}
