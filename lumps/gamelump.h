#ifndef gamelump_h
#define gamelump_h
#include<stdbool.h>
#include<stdio.h>
#include"common.h"

typedef struct dgamelump_t {
	int id;
	unsigned short flags;
	unsigned short version;
	int fileofs;
	int filelen;
} dgamelump;

typedef struct dgamelumpheader_t {
	int lumpCount;
	dgamelump* lumps;
} dgamelumpheader;

void gamelumpdescript(BSPheader* header);
bool gamelumphandler(BSPheader* header, char* arg);

#endif
