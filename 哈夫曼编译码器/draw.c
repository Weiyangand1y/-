#include"draw.h"
void write_file2(char* filename,char** text,int n){
	FILE* f=fopen(filename,"w");
	for(int i=0;i<n;i++){
	//	printf("-->%s\n",text[i]);
		fprintf(f,"%s\n",text[i]);
	}
	fclose(f);
}
int* create_arr(int n){
	int* arr=(int*)malloc(sizeof(int)*n);
	for(int i=0;i<n;i++){
		arr[i]=0;
	}
	return arr;
}
int max(int a,int b){
	if(a>=b)return a;
	else return b;
}
int draw_right(char** g,int x,int y){
	if(!(g[y][x]=='l' && g[y][x]=='n'))
		g[y][x+1]='-';	
	g[y][x+2]='-';
	return x+3;
}
int draw_down(char** g,int* height,int x,int y){
	int i;
	g[y+1][x]='a';
	for(i=y+1;i<max(height[x]+2,y+2);i++){
		g[i][x]='|';
	}
	g[i][x]='|';
	g[i][x+1]='-';
	g[i][x+2]='-';
	for(int i=0;i<=x;i++){
		height[i]=max(height[i]+2,y+2);
	}
	return height[x];
}
void travel(HTNode* tree,int index,int x,int y,char** g,int* height,char* ch_arr){
	HTNode current=tree[index];
	if(ch_arr[index-1]!='\0')
		g[y][x]=ch_arr[index-1];
	if(ch_arr[index-1]=='\n' || ch_arr[index-1]=='\r'){
		g[y][x]='l';
		g[y][x+1]='n';
	}
	//printf("index: %d  char: %c(%d) p:%d l:%d r:%d\n",index,g[y][x],ch_arr[index-1],current.p,current.l,current.r);
	if((current.l!=0 || current.r!=0) && current.p!=0){
		g[y][x]='*';
	}		
	if(current.r!=0){
		int nx=draw_right(g,x,y);
	//	puts("R");
		travel(tree,current.r,nx,y,g,height,ch_arr);
	}
	if(current.l!=0){
		int ny=draw_down(g,height,x,y);
	//	puts("L");
		travel(tree,current.l,x+3,ny,g,height,ch_arr);
	}
}
void draw_tree(HTNode* tree,int n,char* ch_arr){
	int* height=create_arr(n*3);
	char** g=(char**)malloc(sizeof(char*)*n*3);
	for(int i=0;i<n*3;i++){
		g[i]=(char*)malloc(sizeof(char)*n*3);
		for(int j=0;j<n*3;j++){
			g[i][j]=' ';
		}
		g[i][n*3-1]='\0';
	}
	travel(tree,n,0,0,g,height,ch_arr);
	g[0][0]='*';
//	puts("================");
//	for(int i=0;i<n*3;i++){
//		printf("%s\n",g[i]);
//	}
//	puts("================");
	write_file2("tree.txt",g,n*3);
}
