#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>

typedef struct{
	int len;
	int* r;
}SqList;
typedef struct{
	int cmpCount;//关键字比较次数
	int shifttCount;//移动次数
}Info;
//用于记录的全局变量
Info info[7]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
void clearInfo(){
	for(int i=0;i<7;i++){
		info[i].cmpCount=0;
		info[i].shifttCount=0;
	}
}
void showList(SqList* sqList){
	//printf("--------\n");
	for(int i=0;i<sqList->len;i++){
		if(i%10==0)printf("\n");
		printf("%d\t",sqList->r[i]);		
	}
	printf("\n--------\n");
}
//创建表
SqList* createList(int num){
	srand(clock());
	SqList* list=(SqList*)malloc(sizeof(SqList));
	list->len=num;
	list->r=(int*)malloc(sizeof(int)*num);
	for(int i=0;i<num;i++){//给初值
		list->r[i]=rand();
	}
	return list;
}

//0.起泡排序
void bubbleSort(SqList* sqList){
	int end=sqList->len-1;//end为冒泡排序交换的终点
	int* list=sqList->r;
	while(end>0){
		int end2=end;
		end=0;//防止有序后不交换时导致死循环
		for(int i=0;i<end2;i++){
			//record
			info[0].cmpCount++;
			//
			if(list[i]>list[i+1]){
				int tmp=list[i+1];//交换
				list[i+1]=list[i];
				list[i]=tmp;//交换
				end=i;
				//
				info[0].shifttCount+=3;
				//
			}
		}
	}
}
//1.直接插入排序
void insertSort(SqList* sqList){
	int* list=sqList->r;
	for(int i=1;i<sqList->len;i++){
		int target=list[i];//这是待插入的元素
		//遇到比待插入元素大的，向后移，直到遇到比待插入元素小的
		int j;
		//
		info[1].cmpCount++;
		//
		for(j=i-1;target<list[j] && j>=0;j--){
			//
			info[1].cmpCount++;
			info[1].shifttCount++;
			//
			list[j+1]=list[j];
		}
		list[j+1]=target;
	}
}
//2.简单选择排序
void selectSort(SqList* sqList){
	int* list=sqList->r;
	for(int i=0;i<sqList->len-1;i++){
		int min_idx=i;
		for(int j=i;j<sqList->len;j++){//从i到末尾选择最小的
			if(list[j]<list[min_idx])min_idx=j;
			//
			info[2].cmpCount++;
			//
		}
		if(i!=min_idx){
			int tmp=list[i];
			list[i]=list[min_idx];
			list[min_idx]=tmp;
			//
			info[2].shifttCount+=3;
			//
		}
	}
}
//3. 快速排序
int partition(SqList* sqList, int low, int high) {
	int* list=sqList->r;
	int pivot=list[low];
	while(low<high){
		while(low<high && list[high]>=pivot){
			//
			info[3].cmpCount++;
			//
			--high;
		}
		list[low]=list[high];
		//
		info[3].shifttCount++;
		//
		while(low<high && list[low]<=pivot){
			++low;
			//
			info[3].cmpCount++;
			//
		}
		list[high]=list[low];
		//
		info[3].shifttCount++;
		//
	}
	list[low]=pivot;
	//
	info[3].shifttCount++;
	//
	return low;
}
void quickSort(SqList* SqList,int low,int high){
	if(low<high){
		int pivot=partition(SqList,low,high);
		quickSort(SqList,low,pivot-1);
		quickSort(SqList,pivot+1,high);
	}
}
void useQuickSort(SqList* sqList){
	quickSort(sqList,0,sqList->len-1);
}
//4.堆排序
void heapAdjust(SqList* sqList,int s,int m){
	int* list=sqList->r;
	int rc=list[s];
	for(int i=2*s+1;i<=m;i=i*2+1){
		if(i<m && list[i]<list[i+1]){//如果左孩子比较小，则选择右孩子
			++i;
		}
		if(rc>=list[i]){//比所有孩子都大，调整结束
			break;
		}
		//
		info[4].cmpCount+=2;
		//
		list[s]=list[i];//交换
		s=i;//切换根结点
		//
		info[4].shifttCount++;
		//
	}
	list[s]=rc;//交换
	//
	info[4].shifttCount++;
	//
}
void HeapSort(SqList* sqList){
	int* list=sqList->r;
	for(int i=sqList->len/2-1;i>=0;i--){
		//从倒数第二层的最后一个结点(len/2-1)开始,向左再向上
		heapAdjust(sqList,i,sqList->len-1);//
	}
	//showList(sqList);
	for(int i=sqList->len-1;i>=0;i--){
		int tmp=list[0];
		list[0]=list[i];
		list[i]=tmp;//把最后一个结点放到第一个位置
		heapAdjust(sqList,0,i-1);//
	}
}

//5.希尔排序
void shellInsert(SqList* sqList,int dk){
	int* list=sqList->r;
	for(int i=dk;i<sqList->len;i++){
		//
		info[5].cmpCount++;
		//
		if(list[i]<list[i-dk]){
			int tmp=list[i];
			int j;
			for(j=i-dk;j>=0 && tmp<list[j];j-=dk){
				//
				info[5].cmpCount++;
				info[5].shifttCount++;
				//	
				list[j+dk]=list[j];
			}
			list[j+dk]=tmp;
			//
			info[5].shifttCount++;
			//
		}
	}
}
void shellSort(SqList* sqList){
	int dlta[]={5,3,2,1};
	for(int i=0;i<4;i++){
		shellInsert(sqList,dlta[i]);
	}
}
//6.归并排序
void merge(int* a,int l,int r,int mid,int n){
	//将两个有序序列合并为1个有序序列
	//temp[]是临时数组,n是a[]长度 
	int temp[n];
	int i=l;//左序列指针 
	int j=mid+1;//右序列指针 
	int k=0;//临时数组指针 
	while(i<=mid&&j<=r){
		//
		info[6].cmpCount++;
		//
		if(a[i]<=a[j])
			temp[k++]=a[i++];
		else
			temp[k++]=a[j++];
	}
	while(i<=mid){//将左边剩余元素填充进temp中 
		temp[k++]=a[i++];
	}
	while(j<=r){//将右边剩余元素填充进temp中
		temp[k++]=a[j++];
	}
	k=0;
	//将temp中的元素全部拷贝到原数组中
	while(l<=r){
		//
		info[6].shifttCount++;
		//
		a[l++]=temp[k++];
	}
}

void merge_sort(int* a,int l,int r){//归并排序，“分而治之”的过程，递归实现
	if(l>=r)//保证l是左边，r是右边 n是a[]长度 
		return ;	
	int mid=(l+r)/2;
	//将序列分为两个序列，分别排序 
	merge_sort(a,l,mid);//左边归并排序，使左子序列有序 
	merge_sort(a,mid+1,r);//右边归并排序，使右子序列有序 
	merge(a,l,r,mid,r-l+1);//将两个有序子序列合并 
}
void useMergeSort(SqList* sqList){
	merge_sort(sqList->r,0,sqList->len);
}

SqList* getCopy(SqList* sqList){
	int len=sqList->len;
	SqList* newList=createList(len);
	for(int i=0;i<len;i++){
		newList->r[i]=sqList->r[i];
	}
	return newList;
}
#define NUM 7
void showResult(){
	char* names[NUM]={
		"冒泡排序","插入排序","选择排序","快速排序","堆  排序",
		"希尔排序","归并排序"
	};
	for(int i=0;i<NUM;i++){
		printf("%s，比较次数：%10d，移动次数:%10d\n",names[i],info[i].cmpCount,info[i].shifttCount);
	}
	printf("*************\n");	
}
void reverse(SqList* sqList){
	int len=sqList->len;
	int* list=sqList->r;
	for(int i=0;i<len/2;i++){
		int tmp=list[i];
		list[i]=list[len-i-1];
		list[len-i-1]=tmp;		
	}
	
}
void test(int size){
	for(int i=0;i<5;i++){		
		SqList* list=createList(size);
		bubbleSort(getCopy(list));
		insertSort(getCopy(list));
		selectSort(getCopy(list));
		useQuickSort(getCopy(list));
		HeapSort(getCopy(list));
		shellSort(getCopy(list));
		useMergeSort(getCopy(list));
		printf("第%d次结果：\n",i);
		showResult();
		//store_matrix(m,5,NUM,&info[0]);
		clearInfo();
		free(list);
	}
}
void test_in_order(int size,int flag){
	SqList* list=createList(size);
	useQuickSort(list);
	clearInfo();
	//showList(list);
	if(flag==-1){
		reverse(list);
	}	
	bubbleSort(getCopy(list));
	insertSort(getCopy(list));
	selectSort(getCopy(list));
	useQuickSort(getCopy(list));
	HeapSort(getCopy(list));
	shellSort(getCopy(list));
	useMergeSort(getCopy(list));
	showResult();
	clearInfo();
	free(list);
}
void main_ui(){
	int num;
	puts("输入你要排序的数组大小：");
	scanf("%d",&num);
	printf("\n普通的测试(%d个元素)：\n",num);
	test(num);
	printf("正序(%d个元素)：\n",num);
	test_in_order(num,1);
	printf("逆序(%d个元素)：\n",num);
	test_in_order(num,-1);

}
int main() {
	main_ui();
}


