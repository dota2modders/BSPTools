#include"texinfolump.h"

void texinfolumpdescript(BSPheader* header) {
	void* texinfolump = (void*)((uint)header + header->lumps[6].fileofs);
	void* texdatalump = (void*)((uint)header + header->lumps[2].fileofs);
	void* texdatastringtablelump = (void*)((uint)header + header->lumps[44].fileofs);
	void* texdatastringdatalump = (void*)((uint)header + header->lumps[43].fileofs);
	int len = header->lumps[6].filelen;
	int count = len/72;
	int i;
	for(i=0;i<count;i++) {
		texinfo* this = (texinfo*)(texinfolump+72*i);
		texdata* thistd = (texdata*)(texdatalump+32*this->texdata);
		int* stringindex = (int*)(texdatastringtablelump+4*thistd->nameStringTableID);
		char* thismat = (char*)(texdatastringdatalump + (*stringindex));
		printf("Texinfo %i:\n",i);
		printf("\tTextureVecs: (%f %f %f %f) (%f %f %f %f)\n",this->textureVecs[0][0],this->textureVecs[0][1],this->textureVecs[0][2],this->textureVecs[0][3],this->textureVecs[1][0],this->textureVecs[1][1],this->textureVecs[1][2],this->textureVecs[1][3]);
		printf("\tLightmapVecs: (%f %f %f %f) (%f %f %f %f)\n",this->lightmapVecs[0][0],this->lightmapVecs[0][1],this->lightmapVecs[0][2],this->lightmapVecs[0][3],this->lightmapVecs[1][0],this->lightmapVecs[1][1],this->lightmapVecs[1][2],this->lightmapVecs[1][3]);
		printf("\tFlags: %.8X\n",this->flags);
		printf("\tTexdata %i:\n",this->texdata);
		printf("\t\tReflectivity: (%f %f %f)\n",thistd->reflectivity.x,thistd->reflectivity.y,thistd->reflectivity.z);
		printf("\t\tDimensions: (%i %i)\n",thistd->width, thistd->height);
		printf("\t\tView Dimensions: (%i %i)\n",thistd->view_width, thistd->view_height);
		printf("\t\tTexture: %s\n",thismat);
	}
}
//returns true if command was handled, false otherwise.
bool texinfolumphandler(BSPheader* header, char* arg) {
	//char* str = (char*)arg;
	return false;
}
