#ifndef gamelump_h
#define gamelump_h
#include<stdbool.h>
#include<stdio.h>

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

void gamelumpdescript(void* lump, int len);
bool gamelumphandler(void* arg);

#endif
