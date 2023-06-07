#ifndef UTILS_H
#define UTILS_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char* read_file(char* filename);
void write_file(char* filename,int num,char* ch_arr);
void write_file_for_HT(char* filename,char* ch_arr,int* w_arr,int num);
void read_file_for_HT(char* filename,char** ch_arr,int** w_arr,int* num);
char** auto_suffix(char* str);
#endif
