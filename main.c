#include "life.h"
#include "intf.h"

int main(int argc, char **argv){
	p_Field field;

	if(argc-1==1){
		loadField(&field,argv[1]);
		initScr();
	}
	else{
		initScr();
		defField(&field);
	}
	while(Input(field));
	free(field->cells);
	free(field);
	return 0;
}
