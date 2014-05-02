#include "overlaylump.h"

void overlaylumpdescript(BSPheader* header) {
	void* lump = (void*)((uint)header + header->lumps[45].fileofs);
	int len = header->lumps[45].filelen;
	if(header->version == 21) {
		int count = len/((int)sizeof(doverlay_21));
		printf("%i overlays found\n",count);
	} else if (header->version ==23) {
		int count = len/((int)sizeof(doverlay_23));
		printf("%i overlays found\n",count);
	} else {
		printf("unsupported bsp version\n");
	}
}
bool overlaylumphandler(BSPheader* header, char* arg) {
	return false;
}
