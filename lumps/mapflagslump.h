#ifndef mapflagslump_h
#define mapflagslump_h
#include<stdbool.h>
#include<stdio.h>
#include"common.h"

void mapflagslumpdescript(BSPheader* header);
bool mapflagslumphandler(BSPheader* header, char* arg);

#endif
