#include"gamelump.h"

void gamelumpdescript(void* lump,int len) {
	dgamelumpheader* gamelumpheader = (dgamelumpheader*)lump;
	printf("%i game lumps\n",gamelumpheader->lumpCount);
	int i;
	for(i=0;i<gamelumpheader->lumpCount;i++) {
		dgamelump* lp = (dgamelump*)((&gamelumpheader->lumps) + i*4);
		printf("Game lump %i:\n",i);
		printf("\tid: %.8X\n",lp->id);
		printf("\tflags: %hx\n",lp->flags);
		printf("\tversion: %hi\n",lp->version);
		printf("\tfileofs: %.8X\n",lp->fileofs);
		printf("\tfilelen: %i\n",lp->filelen);
	}
}
//returns true if command was handled, false otherwise.
bool gamelumphandler(void* arg) {
	//char* str = (char*)arg;
	return false;
}
