#ifndef dispinfolump_h
#define dispinfolump_h
#include<stdbool.h>
#include<stdio.h>
#include"common.h"
#include"dispmultiblendlump.h"

#define MAX_DISP_CORNER_NEIGHBORS 4

typedef struct CDispSubNeighbor_t {
	unsigned short Neighbor;
	unsigned char NeighborOrientation;
	unsigned char Span;
	unsigned char NeighborSpan;
} CDispSubNeighbor;

typedef struct CDispNeighbor_t {
	CDispSubNeighbor SubNeighbors[2];
} CDispNeighbor;

typedef struct CDispCornerNeighbors_t {
	unsigned short Neighbors[MAX_DISP_CORNER_NEIGHBORS];
	unsigned char nNeighbors;
} CDispCornerNeighbors;

typedef struct ddispinfo_21_t {
	vector startPos;
	int DispVertStart;
	int DispTriStart;
	int power;
	int minTess;
	float smoothingAngle;
	int contents;
	unsigned short MapFace;
	int LightmapAlphaStart;
	int LightmapSamplePositionStart;
	CDispNeighbor EdgeNeighbors[4];
	CDispCornerNeighbors CornerNeighbors[4];
	int AllowedVerts[10];
} ddispinfo_21;

typedef struct ddispinfo_23_t {
	vector startPos;
	int DispVertStart;
	int DispTriStart;
	int power;
	int minTess;
	float smoothingAngle;
	int contents;
	int m_nReferenceID;
	unsigned short MapFace;
	int m_nAltTexInfo;
	int LightmapAlphaStart;
	int LightmapSamplePositionStart;
	CDispNeighbor EdgeNeighbors[4];
	CDispCornerNeighbors CornerNeighbors[4];
	uint AllowedVerts[10];
} ddispinfo_23;

void dispinfolumpdescript(BSPheader* header);
bool dispinfolumphandler(BSPheader* header, char* arg);
void dispinfolumpdiff(BSPheader* header1, BSPheader* header2);

#endif
