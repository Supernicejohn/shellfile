#include "keyboard.h"
// credit to user jschmier (6 Jun 2010) from stack overflow (https://stackoverflow.com/questions/20154157/termios-vmin-vtime-and-blocking-non-blocking-read-operations)
// original code edited to suit application.
// Read on (26 Aug 2019)
char getKeyCode(int vtime, int vmin){
	struct termios origTerm;
	struct termios stdinpoll;


	tcgetattr(fileno(stdin),&origTerm);
	memcpy(&stdinpoll, &origTerm, sizeof(struct termios));
	stdinpoll.c_lflag &= ~(ECHO|ICANON);
	stdinpoll.c_cc[VTIME] = vtime;
	stdinpoll.c_cc[VMIN] = vmin;
	tcsetattr(fileno(stdin), TCSANOW, &stdinpoll);

	unsigned char key = fgetc(stdin);

	tcsetattr(fileno(stdin), TCSANOW, &origTerm);
	
	return key;
}


int isPrintable(char ScanIn){
	if (ScanIn > 31 && ScanIn < 127)
		return 1;
	return 0;
}
int getSpecialKey(char ScanIn){
	char buffer[10];
	for (int i=0; i<10; i++){
		buffer[i] = getKeyCode(0,0);
	}
	if (ScanIn == 27 && buffer[0] == 91){
		switch(buffer[1]){
			case 65: return KEYS_UP; break;
		  	case 66: return KEYS_DOWN; break;
			case 68: return KEYS_LEFT; break;
			case 67: return KEYS_RIGHT; break;
			case 72: return KEYS_HOME; break;
			case 53: return KEYS_PAGEUP; break;
			case 54: return KEYS_PAGEDOWN; break;
			case 70: return KEYS_END; break; 
			case 50: return KEYS_INSERT; break;
			case 51: return KEYS_DELETE; break; 
			default: return KEYS_NOKEY; break;
		}
	} else if (ScanIn == 27 && buffer[0] == -128){
		return KEYS_ESCAPE;
	} else if (ScanIn == 10){
		return KEYS_ENTER;
	} else if (ScanIn == 127) {
		return KEYS_BACKSPACE;
	} else {
		return KEYS_NOKEY;
	}
}
