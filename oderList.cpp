#include<stdio.h>
#include<malloc.h>
#include<conio.h>

#define maxsize 1000

typedef struct Node{
  int *elem;//elem相当于数组名此时还未开辟空间
  int length;
  int listsize;
}splist;

//初始化 
int intilist(splist *L){
  L->elem=(int*)malloc(maxsize*sizeof(int));
  if(!L->elem) return -1;
  L->length=0;
  L->listsize=maxsize;
  return 0;
} 

//插入数据 
void insert(splist *L,int n){
    for(int i=0;i<n;i++)
        scanf("%d",&L->elem[i]);
    L->length=n;
}


//去重 
int Delete_Same(splist *L){
    if(L->length==0)
        return 0;
    int i,j;  //i存储第一个不相同的元素，j工作指针
    for(i=0,j=1; j<L->length; j++)
        if(L->elem[i] > L->elem[j])  //查找下一个与上个元素值不同的元素
    		L->elem[++i] = L->elem[j];  //找到后，则将元素前移
    L->length = i+1; 
	return 1;  
}


//顺序表逆置 
void Server_splist(splist *L) {
	int i, j, mid, temp;
	mid = L->length/2;
	for(i = 0; i< mid; i ++){
		j = L->length-i-1;
		temp = L->elem[i];
		L->elem[i] = L->elem[j];
		L->elem[j] = temp; 
	}
}

void display(splist *l)
{ 
	printf("%d\n",l->length);
    for(int i=0;i<l->length-1;i++)
        printf("%d ",l->elem[i]);
    printf("%d\n",l->elem[l->length-1]);
}
int main() {
	splist L;
	intilist(&L);
	int n;
    scanf("%d",&n);
    //插入数据 
	insert(&L,n);
	display(&L);
	//去重 
	Delete_Same(&L);
	display(&L);
	//逆置 
	Server_splist(&L);
	display(&L);
	free(L.elem);
	return 0;
}
