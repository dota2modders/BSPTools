#include"mapflagslump.h"

void mapflagslumpdescript(BSPheader* header) {
	void* lump = (void*)((uint)header + header->lumps[26].fileofs);
	printf("Map Flags: %.8X\n",*((int*)lump));
}
//returns true if command was handled, false otherwise.
bool mapflagslumphandler(BSPheader* header, char* arg) {
	//char* str = (char*)arg;
	return false;
}
