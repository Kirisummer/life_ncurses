# Game of Life
## A few words to start
I've decided to write this simple program to practice my skills before exams. It came to my mind after writing the battleship bot as the programming project in the uni.
## User's guide
There are two ways to start the program.

### First: from scratch
You can create the field of desired height and width, limited by your screen, or rather terminal size. 
Once you start the program, you are to specify the field's dimension. Once done, your next task is to create field.  
#### Controls:  
* 'h', 'j', 'k', 'l' or arrow keys to go left, right, up or down;  
* 't' to toggle cell status;  
* 's' to proceed;  
* any other key to show help.  

### Second: from the file
The second way may not be portable between x86\_64 and AARCH64 computers, for example. You can use a save file as a cli argument. Example save files were made on x86\_64 Linux machine (big-endian).
The save file is a binary file that consists of two dimensions (4 bytes each, big-endian) and the field, each cell being marked as 0 or 1 byte (dead or alive). If there are less cells specified than needed, the rest of the cells are 0 (dead). If there are too much cells, the excess cells will not be read. 
Such files can be created with any text, hex or bin editors or the game itself.

### Main procedure  
#### Controls:  
* 'n' for next iteration of the field;  
* 's' to save the field to the specified file;  
* 'e' to enter editor mode, like in the first way of starting the program;  
* 'q' to quit;  
* any other key to show help.  

## Programmer's guide
The comments will be added a bit later, as well a this guide. Sorry :/
I'm looking forward for your help as I'm just a beginner in C programming and there's some memory leaking.
