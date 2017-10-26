#include<stdio.h>
#include<malloc.h>
#include<conio.h>

#define maxsize 1000

typedef struct Node{
  int *elem;//elem�൱����������ʱ��δ���ٿռ�
  int length;
  int listsize;
}splist;

//��ʼ�� 
int intilist(splist *L){
  L->elem=(int*)malloc(maxsize*sizeof(int));
  if(!L->elem) return -1;
  L->length=0;
  L->listsize=maxsize;
  return 0;
} 

//�������� 
void insert(splist *L,int n){
    for(int i=0;i<n;i++)
        scanf("%d",&L->elem[i]);
    L->length=n;
}


//ȥ�� 
int Delete_Same(splist *L){
    if(L->length==0)
        return 0;
    int i,j;  //i�洢��һ������ͬ��Ԫ�أ�j����ָ��
    for(i=0,j=1; j<L->length; j++)
        if(L->elem[i] > L->elem[j])  //������һ�����ϸ�Ԫ��ֵ��ͬ��Ԫ��
    		L->elem[++i] = L->elem[j];  //�ҵ�����Ԫ��ǰ��
    L->length = i+1; 
	return 1;  
}


//˳������� 
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
    //�������� 
	insert(&L,n);
	display(&L);
	//ȥ�� 
	Delete_Same(&L);
	display(&L);
	//���� 
	Server_splist(&L);
	display(&L);
	free(L.elem);
	return 0;
}
