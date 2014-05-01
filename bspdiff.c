#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"lumps/common.h"
#include"lumps/gamelump.h"
#include"lumps/overlaylump.h"

#define HEADER_LUMPS 64

typedef struct handlerdescript_t {
	char* name;
	void (*describe)(BSPheader*);
	bool (*parsecommand)(BSPheader*, char*);
} handlerdescript;

void basedescript(BSPheader* header) {
	printf("No further analysis of this chunk's format implemented.\n");
}
//returns true if command was handled, false otherwise.
bool basehandler(BSPheader* header, char* input) {
	//char* str = (char*)arg;
	return false;
}

handlerdescript statetable[] = {
	{"entities",&basedescript,&basehandler},
	{"planes",&basedescript,&basehandler},
	{"texdata",&basedescript,&basehandler},
	{"verticies",&basedescript,&basehandler},
	{"visibility",&basedescript,&basehandler},
	{"nodes",&basedescript,&basehandler},
	{"texinfo",&basedescript,&basehandler},
	{"faces",&basedescript,&basehandler},
	{"lighting",&basedescript,&basehandler},
	{"occlusion",&basedescript,&basehandler},
	{"leafs",&basedescript,&basehandler}, //10
	{"faceids",&basedescript,&basehandler},
	{"edges",&basedescript,&basehandler},
	{"surfedges",&basedescript,&basehandler},
	{"models",&basedescript,&basehandler},
	{"worldlights",&basedescript,&basehandler},
	{"leaffaces",&basedescript,&basehandler},
	{"leafbrushes",&basedescript,&basehandler},
	{"brushes",&basedescript,&basehandler},
	{"brushsides",&basedescript,&basehandler},
	{"areas",&basedescript,&basehandler}, //20
	{"areaportals",&basedescript,&basehandler},
	{"propcollision",&basedescript,&basehandler},
	{"prophulls",&basedescript,&basehandler},
	{"prophullverts",&basedescript,&basehandler},
	{"proptris",&basedescript,&basehandler},
	{"dispinfo",&basedescript,&basehandler},
	{"originalfaces",&basedescript,&basehandler},
	{"physdisp",&basedescript,&basehandler},
	{"physcollide",&basedescript,&basehandler},
	{"vertnormals",&basedescript,&basehandler}, //30
	{"vertnormalindicies",&basedescript,&basehandler},
	{"disp_lightmap_alphas",&basedescript,&basehandler},
	{"disp_verts",&basedescript,&basehandler},
	{"disp_lightmap_sample_positions",&basedescript,&basehandler},
	{"game_lump",&gamelumpdescript,&gamelumphandler},
	{"leafwaterdata",&basedescript,&basehandler},
	{"primitives",&basedescript,&basehandler},
	{"primverts",&basedescript,&basehandler},
	{"primindicies",&basedescript,&basehandler},
	{"pakfile",&basedescript,&basehandler}, //40
	{"clipportalverts",&basedescript,&basehandler},
	{"cubemaps",&basedescript,&basehandler},
	{"texdata_string_data",&basedescript,&basehandler},
	{"texdata_string_table",&basedescript,&basehandler},
	{"overlays",&overlaylumpdescript,&overlaylumphandler},
	{"LeafMinDistToWater",&basedescript,&basehandler},
	{"face_macro_texture_info",&basedescript,&basehandler},
	{"disp_tris",&basedescript,&basehandler},
	{"prop_blob",&basedescript,&basehandler},
	{"wateroverlays",&basedescript,&basehandler}, //50
	{"leaf_ambient_index_hdr",&basedescript,&basehandler},
	{"leaf_ambient_index",&basedescript,&basehandler},
	{"lighting_hdr",&basedescript,&basehandler},
	{"worldlights_hdr",&basedescript,&basehandler},
	{"leaf_ambient_lighting_hdr",&basedescript,&basehandler},
	{"leaf_ambient_lighting",&basedescript,&basehandler},
	{"xzippakfile",&basedescript,&basehandler},
	{"faces_hdr",&basedescript,&basehandler},
	{"map_flags",&basedescript,&basehandler},
	{"overlay_fades",&basedescript,&basehandler}, //60
	{"overlay_system_levels",&basedescript,&basehandler},
	{"physlevel",&basedescript,&basehandler},
	{"disp_multiblend",&basedescript,&basehandler},
	{"ROOT",&basedescript,&basehandler}, //internal use for state display
	{"header",&basedescript,&basehandler},
};

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
	if(argc <3) {
		printf("usage: BSPDiff <bspfile> <bspfile>\n");
		return 0;
	}
	BSPheader* header1 = NULL;
	BSPheader* header2 = NULL;
	unsigned long bsp1size = load_bspfile((unsigned char**)(&header1),argv[1]);
	unsigned long bsp2size = load_bspfile((unsigned char**)(&header2),argv[2]);
	printf("Lump information follows\n");
	int i;
	for(i=0;i<HEADER_LUMPS;i++) {
		if(header1->lumps[i].filelen==0 && header2->lumps[i].filelen==0)
			continue;
		if(header1->lumps[i].filelen == header2->lumps[i].filelen && memcmp(header1->lumps[i].fileofs+((unsigned char*)header1),header2->lumps[i].fileofs+((unsigned char*)header2),header1->lumps[i].filelen)==0)
			continue;
		printf("Difference on lump %i: %s\n",i,statetable[i].name);
		printf("File 1:\n");
		printf("\tLocation: %.8X\n",header1->lumps[i].fileofs);
		printf("\tLength:   %i\n",header1->lumps[i].filelen);
		printf("\tVersion:  %i\n",header1->lumps[i].version);
		if(0 != *((int*)(header1->lumps[i].fourCC)))
			printf("\tSpecial:  %.8X\n",*((int*)(header1->lumps[i].fourCC)));
		printf("File 2:\n");
		printf("\tLocation: %.8X\n",header2->lumps[i].fileofs);
		printf("\tLength:   %i\n",header2->lumps[i].filelen);
		printf("\tVersion:  %i\n",header2->lumps[i].version);
		if(0 != *((int*)(header2->lumps[i].fourCC)))
			printf("\tSpecial:  %.8X\n",*((int*)(header2->lumps[i].fourCC)));
	}
	int state=64;
	ssize_t string_length;
	size_t bufsize;
	char* line=NULL;
	/*while(1) {
		printf("BSPExplode (%s) > ",statetable[state].name);
		string_length=getline(&line,&bufsize,stdin);
		if(string_length==0)
			continue;
		if(!strncmp(line,"quit",4) || !strncmp(line,"exit",4)) {
			break;
		} else if(!strncmp(line,"help",4)) {
			printf("BSPExplode v0.1\nCommands:\nCore:\nquit/exit\tExits BSPExplode\nchlump <num>\tChange to the specified lump\ndump <file>\tDump current lump to file\nload <file>\tLoad a file and overwrite this lump with it.\nchversion <num>\tChange the bsp version\nwritemap <file>\tWrite the buffer to a map file\n");
		} else if(!strncmp(line,"chlump",6)) {
			int num,check;
			check = sscanf(line,"chlump %i",&num);
			if(check!=1) {
				printf("usage: chlump <lumpnum>\n");
				continue;
			}
			if(num < 0 || num >=HEADER_LUMPS) {
				printf("invalid lump number, use 0-63\n");
				continue;
			}
			state=num;
			printf("Lump %i: %s\n",state,statetable[state].name);
			printf("\tLocation: %.8X\n",header->lumps[state].fileofs);
			printf("\tLength:   %i\n",header->lumps[state].filelen);
			printf("\tVersion:  %i\n",header->lumps[state].version);
			if(0 != *((int*)(header->lumps[state].fourCC)))
				printf("\tSpecial:  %.8X\n",*((int*)(header->lumps[state].fourCC)));
			(*statetable[state].describe)((void*)header);
		} else if(!strncmp(line,"dump",4)) {
			int check;
			char fname[100];
			check = sscanf(line,"dump %[A-Za-z0-9._]",fname);
			if(check != 1) {
				printf("usage: dump <filename>\n");
				continue;
			}
			if(state<0 || state>=HEADER_LUMPS) {
				printf("Can only dump when a lump is selected!\n");
				continue;
			}
			FILE* out = fopen(fname,"wb");
			fwrite((char*)(((unsigned char*)header) + header->lumps[state].fileofs),1,header->lumps[state].filelen,out);
			fclose(out);
		} else if((*statetable[state].parsecommand)(header,line)) {
		} else {
			printf("Command not recognized\n");
		}
	}*/
	return 0;
}
