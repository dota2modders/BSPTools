#ifndef common_h
#define common_h

#define HEADER_LUMPS 64

typedef struct lump_t {
	int fileofs;
	int filelen;
	int version;
	char fourCC[4];
} lump;

typedef struct BSPheader_t
{
	int ident;
	int version;
	lump lumps[HEADER_LUMPS];
	int mapRevision;
} BSPheader;

typedef struct vector_t {
	float x;
	float y;
	float z;
} vector;
typedef struct vector_i_t {
	int x;
	int y;
	int z;
} vector_i;

typedef struct vector4f_t {
	float r;
	float g;
	float b;
	float a;
} vector4f;

#endif
