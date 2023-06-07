#ifndef DRAW_H
#define DRAW_H
//typedef struct{
//	int weight;
//	int p,l,r;//父节点，左孩子，右孩子
//}HTNode;
#include"HuffmanTree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void write_file2(char* filename,char** text,int n);
void draw_tree(HTNode* tree,int n,char* ch_arr);
#endif
