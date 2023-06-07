#include"HuffmanTree.h"
void showHuffmanTree(HTNode* tree,int n){
	for(int i=1;i<n;i++){
		printf("%d_w:%d_p:%d_L:%d_R:%d\t",i,tree[i].weight,tree[i].p,tree[i].l,tree[i].r);
		if(i%3==0)puts("");
	}
	puts("");
}
HTNode* huffmanCoding(char*** result,int* w,int n){
	HTNode* HT;
	if(n<1)return NULL;
	int m=2*n-1;//节点是可以被计算的
	HT=(HTNode*)malloc((m+1)*sizeof(HTNode));//不用0号单元
	HTNode*p=HT;
	int i=1;
	for(; i<=n;   ++i){//初始化前面的几个
		p[i].weight=w[i-1];
		p[i].p=0;p[i].l=0;p[i].r=0;
	}
	for(;i<=m;++i){//初始化后面的
		p[i].weight=0;
		p[i].p=0;p[i].l=0;p[i].r=0;
	}

	for(i=n+1;i<=m;++i){//这个循环开始选取、构造
		int s1,s2;
		select_two_min2(HT,i-1,&s1,&s2);
		//printf("选取1~%d,s1:%d  s2:%d  ws1:%d  ws2: %d  sum: %d\n",
		//	i-1,s1,s2,HT[s1].weight,HT[s2].weight,HT[s1].weight+HT[s2].weight);
		HT[s1].p=i;HT[s2].p=i;
		HT[i].l=s1;HT[i].r=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}	
	//showHuffmanTree(HT,m+1);	
	char** HC;
	HC=(char**)malloc((n+1)*sizeof(char*));
	char* cd=(char*)malloc(n*sizeof(char));//临时存放字符串
	cd[n-1]='\0';
	for(int i=1;i<=n;i++){
		int start=n-1;		
		for(int c=i,f=HT[i].p;  f!=0;  c=f,f=HT[f].p){
			if(HT[f].l==c)cd[--start]='0';
			else cd[--start]='1';
		}
		HC[i]=(char*)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	//	printf("%d->%s\t",i,HC[i]);
	}	
	free(cd);
	*result=HC;
	return HT;
}

char* textToHaffumanCoding_v2(char** HC,char* text,char* ch_arr,int num){
	printf("----\n待编码：%s\n",text);
	int size=HCODE_SIZE;
	char* hc=(char*)malloc(sizeof(char)*size);
	int p=0;
	for(int i=0;text[i]!='\0';i++){
		int index=get_index(text[i],ch_arr,num);
		char* word=HC[index];
	//	printf("%c->%s\t",ch_arr[index-1],word);
	//	if(i%4==0)puts("");
		strcpy(hc+p,word);
		p+=strlen(word);		
	}
	hc[p]='\0';
	hc=(char*)realloc(hc,sizeof(char)*(p+1));
	printf("编码的结果：%s\n----\n",hc);
	return hc;
}

char* haffmanCodeToText_v2(HTNode* tree,int n,char* hc,char* ch_arr){
	//printf("----\n待解码：%s\n",hc);
	char* result=(char*)malloc(sizeof(char)*SRC_SIZE);
	int count=0;
	for(int i=0;hc[i]!='\0';){
		int p=2*n-1;
		//	printf("%d->",p);
		while(tree[p].l || tree[p].r){			
			if(hc[i]=='0')p=tree[p].l;
			else if(hc[i]=='1')p=tree[p].r;
			//	printf("%d->",p);
			i++;
		}
		result[count++]=ch_arr[p-1];
		//	printf("\b\b    ");
		//	if(i%4==0)puts("");
	}
	result[count]='\0';
	printf("解码结果：%s\n----\n",result);
	return result;
}

void test_select_two_min(){
	HTNode arr[4]={
		{0,0,0,0},
		{8,0,0,0},
		{13,0,0,0},
		{4,0,0,0}
	};
	int s1,s2;
	select_two_min2(arr,3,&s1,&s2);
	printf("%d,,%d\n",s1,s2);
}
void select_two_min2(HTNode* arr,int end,int* s1,int* s2){
	//对s1和s2先初始化
	//注意s1，s2是序号，不是weight
	//排除父节点为0的
	//s1<s2
	*s1=*s2=0;
	arr[0].weight=INT_MAX;
	for(int i=1;i<=end;i++){
		if(arr[i].p!=0)continue;//如果有父节点了，下一个
		if(arr[i].weight<arr[*s1].weight){//如果是最小的
			*s2=*s1;//倒一变倒二
			*s1=i;//更新倒一
		}
		else if(arr[i].weight<arr[*s2].weight){//如果是倒数第二小的
			*s2=i;
		}
	}
	//printf("选出来的是：%d(%d),%d(%d)\n",*s1,arr[*s1].weight,*s2,arr[*s2].weight);
}

//读取字符串，生成权重数组
//返回3个参数，字符数组，权重数组，个数
void readText(char* text,char** res_ch,int** res_w,int* num){
	int size=SRC_SIZE;
	char* ch_arr=(char*)malloc(sizeof(char)*size);
	int* w_arr=(int*)malloc(sizeof(int)*size);
	int len=0;
	for(int i=0;i<size;i++){
		ch_arr[i]=w_arr[i]=0;
	}
	for(int i=0;text[i]!='\0';i++){
		int has=0;
		for(int j=0;j<len;j++){
			if(ch_arr[j]==text[i]){
				w_arr[j]++;
				has=1;
				break;
			}			
		}
		if(!has){
			ch_arr[len]=text[i];
			w_arr[len]=1;
			len++;
		}
	}
	for(int i=0;i<len;i++){
	//	if(i%5==0)puts("");
	//	printf("%c---%d\t",ch_arr[i],w_arr[i]);
	}
	*res_ch=ch_arr;
	*res_w=w_arr;
	*num=len;
}
//由字符数组获得数字
int get_index(char ch,char* ch_arr,int num){
	for(int i=0;i<num;i++){
		if(ch_arr[i]==ch){
			return i+1;
		}
	}
	return -1;
}

