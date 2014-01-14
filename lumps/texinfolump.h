#ifndef texinfolump_h
#define texinfolump_h
#include<stdbool.h>
#include<stdio.h>
#include"common.h"

typedef struct texinfo_t {
	float	textureVecs[2][4];
	float	lightmapVecs[2][4];
	int	flags;
	int	texdata;
} texinfo;

typedef struct texdata_t {
	vector	reflectivity;
	int 	nameStringTableID;
	int	width, height;
	int	view_width, view_height;
} texdata;

void texinfolumpdescript(BSPheader* header);
bool texinfolumphandler(BSPheader* header, char* arg);

#endif
