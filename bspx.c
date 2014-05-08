#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"lumps/common.h"

#define HEADER_LUMPS 64

unsigned long load_file(unsigned char** buf, char* fname, char* opts, char* errmsg) {
	FILE* file = fopen(fname,opts);
	if(file == NULL) {
		printf("%s",errmsg);
		exit(1);
	}
	fseek(file, 0, SEEK_END);
	unsigned long fsize = (unsigned long)ftell(file);
	fseek(file, 0, SEEK_SET);

	(*buf) = (unsigned char*)malloc((size_t)fsize);
	fread(*buf, fsize, 1, file);
	fclose(file);
	return fsize;
}

unsigned long load_bspfile(unsigned char** buf, char* fname) {
	unsigned long bspsize = load_file(buf, fname, "rb","Could not load BSP file\n");
	BSPheader* header = (BSPheader*)(*buf);
	printf("File %s loaded, general file info:\n",fname);
	printf("Sanity Check: %i ",header->ident);
	if(header->ident==1347633750) {
		printf("(passed)\n");
	} else {
		printf("(failed)\n");
	}
	printf("BSP File Version: %i\n",header->version);
	printf("Map Revision: %i\n",header->mapRevision);
	return bspsize;
}


int main(int argc, char* argv[]) {
	if(argc <5) {
		printf("usage: bspx <op> <lumpnum> <bspfile> <externfile>\nPossible values for op: insert extract\nExample: ./bspx extract 40 dota.bsp dota_pakfile.zip\n");
		return 0;
	}
	BSPheader* header = NULL;
	unsigned long bspsize = load_bspfile((unsigned char**)(&header),argv[3]);
	unsigned char* buf = (unsigned char*)header;
	if(!strncmp(argv[1],"insert",6)) {
		int i;
		int lumpnum = atoi(argv[2]);
		if(lumpnum<0 || lumpnum >= HEADER_LUMPS) {
			printf("bad lump number specified.\n");
			return 1;
		}
		unsigned char* newlump;
		unsigned long newlumpsize = load_file(&newlump,argv[4],"r","Error opening inserted file for reading\n");
		unsigned int newfilesize = (unsigned int)(bspsize + (newlumpsize - header->lumps[lumpnum].filelen));
		unsigned char* buf2 = (unsigned char*)malloc(newfilesize);
		BSPheader* header2 = (BSPheader*)buf2;
		memcpy(header2,header,sizeof(BSPheader));
		int index = sizeof(BSPheader);
		for(i=0;i<HEADER_LUMPS;i++) {
			if(i == lumpnum) {
				header2->lumps[i].fileofs = index;
				header2->lumps[i].filelen = newlumpsize;
				header2->lumps[i].version = header->lumps[i].version;
				memcpy(buf2+header2->lumps[i].fileofs,newlump,header2->lumps[i].filelen);
				index += header2->lumps[i].filelen;
			} else {
				header2->lumps[i].fileofs = index;
				header2->lumps[i].filelen = header->lumps[i].filelen;
				header2->lumps[i].version = header->lumps[i].version;
				memcpy(buf2+header2->lumps[i].fileofs,buf+header->lumps[i].fileofs,header2->lumps[i].filelen);
				index += header2->lumps[i].filelen;
			}
		}
		FILE* fp = fopen(argv[3],"wb");
		fwrite(buf2,newfilesize,1,fp);
		fclose(fp);
	} else if (!strncmp(argv[1],"extract",7)) {
		int lumpnum = atoi(argv[2]);
		if(lumpnum<0 || lumpnum >= HEADER_LUMPS) {
			printf("bad lump number specified.\n");
			return 1;
		}
		FILE* fp = fopen(argv[4],"wb");
		if(fp == NULL) {
			printf("Error, could not open output file for writing.\n");
			return 1;
		}
		fwrite(buf+header->lumps[lumpnum].fileofs,header->lumps[lumpnum].filelen,1,fp);
		fclose(fp);
	} else {
		printf("unrecognized op used, recognized ops are insert or extract\n");
	}
}
