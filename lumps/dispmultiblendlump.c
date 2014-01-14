#include"dispmultiblendlump.h"

void dispmultiblendlumpdescript(BSPheader* header) {
	void* lump = (void*)((uint)header + header->lumps[63].fileofs);
	int len = header->lumps[63].filelen;
	int count = len/((int)sizeof(ddispmultiblend));
	printf("length is %i\n",len);
	printf("%i multiblends of size %i found, listing...\n",count,sizeof(ddispmultiblend));
	ddispmultiblend (*disps)[count] = lump;
	int i;
	for(i=0;i<count;i++) {
		ddispmultiblend* this = &((*disps)[i]);
		printf("% .8X % .8X % .8X % .8X\n",this->multiblend.r, this->multiblend.g, this->multiblend.b, this->multiblend.a);
	}
	
	/*ddispmultiblendlumpheader* dispmultiblendlumpheader = (ddispmultiblendlumpheader*)lump;
	printf("%i game lumps\n",dispmultiblendlumpheader->lumpCount);
	int i;
	for(i=0;i<dispmultiblendlumpheader->lumpCount;i++) {
		ddispmultiblendlump* lp = (ddispmultiblendlump*)((&dispmultiblendlumpheader->lumps) + i*4);
		printf("Game lump %i:\n",i);
		printf("\tid: %.8X\n",lp->id);
		printf("\tflags: %hx\n",lp->flags);
		printf("\tversion: %hi\n",lp->version);
		printf("\tfileofs: %.8X\n",lp->fileofs);
		printf("\tfilelen: %i\n",lp->filelen);
	}*/
}
//returns true if command was handled, false otherwise.
bool dispmultiblendlumphandler(BSPheader* header, char* arg) {
	//char* str = (char*)arg;
	return false;
}
