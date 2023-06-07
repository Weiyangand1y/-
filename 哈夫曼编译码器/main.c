#include <stdio.h>
#include <stdlib.h>
#include "HuffmanTree.h"
#include "Utils.h"
#include "draw.h"
void ui_encode();
void ui_decode();
void show_rate(char* hc,char* text,int num){
	int size1=(int)strlen(hc);
	int size2=(int)strlen(text)*8;
	int size3=num*(sizeof(int)+sizeof(char));
	printf("哈夫曼编码长%d,key文件长度：%dbyte,原文本占用%dbit,压缩率%f\n",\
		size1,size3,size2,(float)(size1+size3*8)/size2);
}
void encode(char* src,char* dist1,char* dist2){
	char* ch_arr;int* w_arr;int num;//字符数组、权重数组、数组大小	
	char* text=read_file(src);
	readText(text,&ch_arr,&w_arr,&num);//读文本文件
	//printf("num: %d\n",num);
	char** result;
	HTNode* tree= huffmanCoding(&result,w_arr,num);//生成树
	draw_tree(tree,2*num-1,ch_arr);
	
	char* r2=textToHaffumanCoding_v2(result,text,ch_arr,num);//对文本编码
	write_file_for_HT(dist1,ch_arr,w_arr,num);//写字符-权重文件
	write_file(dist2,strlen(r2),r2);//写哈夫曼编码文件
	show_rate(r2,text,num);
	fflush(stdout);
}
void decode(char* src1,char* src2,char* dist){
	char* ch2;int* w2;int num;//字符数组、权重数组、数组大小
	read_file_for_HT(src1,&ch2,&w2,&num);//读取字符-权重文件
	char* r2=read_file(src2);//读取哈夫曼编码	
	char ** result;
	HTNode* t= huffmanCoding(&result,w2,num);//生成树	
	char* r3=haffmanCodeToText_v2(t,num,r2,ch2);//解码
	write_file(dist,strlen(r3),r3);
	printf("r3: %s\n",r3);
}
void test0(){
	//ui_encode();
	//encode("t2.txt","t2.k","t2.hc");	
	//puts("*****************\n下面是解码部分");
	decode("t2.k","t2.hc","t2.out.txt");
	//ui_decode();
}
void ui_encode(){
	char buffer[48];
	char *dist1,*dist2;
	puts("输入源文件名:");
	scanf("%s",buffer);
//	puts("输出文件由两部分组成：用于解码的key和哈夫曼编码本身");
//	puts("输入目标文件名:key");
//	scanf("%s",dist1);
//	puts("输入目标文件名:哈夫曼编码");
//	scanf("%s",dist2);
	char** dist=auto_suffix(buffer);
	dist1=dist[0];
	dist2=dist[1];
	
	printf("%s",buffer);
	encode(buffer,dist1,dist2);
	puts("编码结束了");
	getchar();
}
void ui_decode(){
	char src1[64],src2[64],dist[64];
	puts("输入源文件key：");
	scanf("%s",src1);
	puts("输入源文件哈夫曼编码：");
	scanf("%s",src2);
	puts("输入目标文件名:");
	scanf("%s",dist);
	decode(src1,src2,dist);
	puts("解码结束了");
	getchar();
}
void main_ui(){
	puts("哈夫曼编译码器");
	char c;
	while(1){
		puts("1)编码\n2)译码\nq)退出");
		c=getchar();
		if(c=='\n')getchar();
		if(c=='q')break;
		else if(c=='1')ui_encode();
		else if(c=='2')ui_decode();
	}
}
int main() {
	main_ui();
	//test0();
	puts("程序结束，按任意键退出.........");
	getchar();	
}

