#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define HCODE_SIZE 1024*800
#define SRC_SIZE 1024*32
typedef struct{
	int weight;
	int p,l,r;//父节点，左孩子，右孩子
}HTNode;
HTNode* huffmanCoding(char*** result,int* w,int n);//编码
void select_two_min2(HTNode* arr,int end,int* s1,int* s2);//选取函数
void test_select_two_min();
void test_haffmanCoding();
char* textToHaffumanCoding(char** HC,char* text);
char* haffmanCodeToText(HTNode* tree,int n,char* hc);
void readText(char* text,char** res_ch,int** res_w,int* num);
int get_index(char ch,char* ch_arr,int num);
char* textToHaffumanCoding_v2(char** HC,char* text,char* ch_arr,int num);
char* haffmanCodeToText_v2(HTNode* tree,int n,char* hc,char* ch_arr);
#endif
