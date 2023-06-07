#include"Utils.h"
#define MAX_READ_SIZE 1024*1024
#define TEXT_MAX_SIZE 1024*32
void check_file_exist(FILE* f){
	if(!f || ferror(f)){
		puts("no file!!!");
		getchar();
		getchar();
		exit(404);
	}
}
char** auto_suffix(char* str){
	char** result=(char**)malloc(sizeof(char*)*3);
	char* str1=(char*)malloc(sizeof(char)*48);
	char* str2=(char*)malloc(sizeof(char)*48);
	char* str3=(char*)malloc(sizeof(char)*48);
	strcpy(str3,str);
	int i=0;
	while(1){
		if(str3[i]=='.'){
			str3[i]='\0';
			break;
		}
		i++;
	}
	
	strcpy(str1,str3);
	str1=strcat(str1,".k");
	strcpy(str2,str3);
	str2=strcat(str2,".hc");

	result[0]=str1;
	result[1]=str2;
	return result;
}
char* read_file(char* filename){
	FILE* f;
	f=fopen(filename,"r");
	check_file_exist(f);
	char* text=(char*)malloc(sizeof(char)*MAX_READ_SIZE);
//	while(!feof(f)){
//		fgets(text,MAX_READ_SIZE,f);
//	}
	while(!feof(f)){
		fread(text,MAX_READ_SIZE,1,f);
	}	
	int end=(int)strlen(text);
	
	text=(char*)realloc(text,end);
	//printf("文件内容：%s\n",text);
	return text;
}
void write_file(char* filename,int num,char* ch_arr){
	FILE* f;
	f=fopen(filename,"w");
	for(int i=0;i<num;i++){
		fputc(ch_arr[i],f);
	}
	fclose(f);
}

void write_file_for_HT(char* filename,char* ch_arr,int* w_arr,int num){
	//printf("num------------is:%d\n\n",num);
	FILE* f=fopen(filename,"wb");
	for(int i=0;i<num;i++){
		fwrite(ch_arr+i,sizeof(char),1,f);
		fwrite(w_arr+i,sizeof(int),1,f);				
	//printf("write: %c %d %d\t",ch_arr[i],ch_arr[i],w_arr[i]);
	}
	fclose(f);
}
void read_file_for_HT(char* filename,char** ch_arr,int** w_arr,int* num){
	char* ch=(char*)malloc(sizeof(char)*TEXT_MAX_SIZE);
	int* w=(int*)malloc(sizeof(int)*TEXT_MAX_SIZE);
	if(!ch || !w)puts("error========\n");
	FILE* f=fopen(filename,"rb");
	
	check_file_exist(f);
	
	int i=0;

	int c;
	while (1) {
		c = fgetc(f);
		fread(&(w[i]), sizeof(int), 1, f);
		
		if(c==EOF){
			printf("%d %d EOF?\n",c,(int)ftell(f));
			break;
		}
		ch[i] = (char)c;
		//printf("%c %d<->%d\t", ch[i],ch[i], w[i]);
		++i;
	}
	*ch_arr=ch;
	*w_arr=w;
	*num=i;
	fclose(f);
}
//index,ch
