#include<stdio.h>
#include<malloc.h>
typedef struct PolyNode * Polynomial;
struct PolyNode{
	int coef;	//系数 
	int expon;	//指数 
	Polynomial link;
};

void Attach(int c, int e, Polynomial * rear)
{
	Polynomial input = (Polynomial)malloc(sizeof(struct PolyNode));
	//申请新节点并赋初值 
	input->coef = c;
	input->expon = e;
	input->link = NULL;
	(*rear)->link = input;
	*rear = input; //修改末尾指针，因为是修改指针，故此处使用指针的指针 
}

Polynomial ReadPoly()
{
	Polynomial P1, rear, t;
	int N;//多项式项数 
	int c,e;//用来暂存系数和指数 
	P1 = (Polynomial)malloc(sizeof(struct PolyNode));//申请头节点 
	//申请头节点是为了方便使用Attach函数时，不用区分rear是空还是非空，有了头节点都是非空，插入方便 
	P1->link = NULL;
	
	rear = P1;//尾指针指向头节点 
	scanf("%d",&N);
	while(N--) 
	{
		scanf("%d %d",&c, &e);
		Attach(c, e, &rear);
	}
	t = P1; 
	P1 = P1->link;
	free(t);//头节点方便插入的使命完成，释放头节点
	return P1; 
}

Polynomial AddPoly(Polynomial P1, Polynomial P2)
{
	Polynomial t1,t2,rear,t;
	t1 = P1;
	t2 = P2;
	Polynomial P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	rear = P;
	while(t1 && t2)
	{
		if(t1->expon == t2->expon)//如果指数相同则进行相加 
		{
			if(t1->coef + t2->coef)//如果系数相加不为零，则将计算结果加入P中 
			{
				Attach(t1->coef + t2->coef, t1->expon, &rear);
			}
			t1 = t1->link;
			t2 = t2->link;
		}
		else if(t1->expon > t2->expon)//找到指数大的加入到P中 
		{

			Attach(t1->coef, t1->expon, &rear);
			t1 = t1->link;
		}
		else
		{
			Attach(t2->coef, t2->expon, &rear);
			t2 = t2->link;
		}
	}
	while(t1)//如果t1还有多余节点，则继续加入 
	{
		Attach(t1->coef, t1->expon, &rear);
		t1 = t1->link;
	}
	while(t2)//如果t2还有多余节点，则继续加入 
	{
		Attach(t2->coef, t2->expon, &rear);
		t2 = t2->link;
	}
	t = P;
	P = P->link;
	free(t);//释放头节点 
	return P;
}

Polynomial SubPoly(Polynomial P1, Polynomial P2)
{
	Polynomial t1,t2,rear,t;
	t1 = P1;
	t2 = P2;
	Polynomial P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	rear = P;
	while(t1 && t2)
	{
		if(t1->expon == t2->expon)//如果指数相同则进行相加 
		{
			if(t1->coef - t2->coef)//如果系数相加不为零，则将计算结果加入P中 
			{
				Attach(t1->coef - t2->coef, t1->expon, &rear);
			}
			t1 = t1->link;
			t2 = t2->link;
		}
		else if(t1->expon > t2->expon)//找到指数大的加入到P中 
		{

			Attach(t1->coef, t1->expon, &rear);
			t1 = t1->link;
		}
		else
		{
			Attach(-t2->coef, t2->expon, &rear);
			t2 = t2->link;
		}
	}
	while(t1)//如果t1还有多余节点，则继续加入 
	{
		Attach(t1->coef, t1->expon, &rear);
		t1 = t1->link;
	}
	while(t2)//如果t2还有多余节点，则继续加入 
	{
		Attach(-t2->coef, t2->expon, &rear);
		t2 = t2->link;
	}
	//t = P;
	//P = P->link;
	//free(t);//释放头节点 
	return P;
}

/*逆置算法1

void RePoly(Polynomial *L)   {
// L是带头结点的单链表的头指针；p、q、r是三个辅助指针
//在扫描链表的过程中进行逆置操作
    Polynomial t1,t2,t;
    if (!L->next ) return;        //空表
      t1=L->next;  t2=t1->next;  //原表中，*t1为*t2的前驱
      t1->next=NULL;              //a1的next置空指针，剥离头结点
      while (t2) {   t=t2->next ;   //修改t2->next之前，保存t2->next到t
                         t2->next=t1 ;   //逆置表中，*t2为*t1的前驱
                         t1=t2 ; t2=t ;    //参与扫描的指针都需后移
       }
       L->next=t1;
}  //ReverseLinkList2

*/

void RePoly(Polynomial *L)
{
	Polynomial t1, t2, t;

	t1=(*L)->link->link;t2=t1->link;
	if(t1==NULL) return;//有一个元素时，直接返回
	
	t=(*L)->link;
	t->link =NULL;
	
	while(t1->link!=NULL){  //每次将未逆置的链表中的首结点*t1，挂在部分逆置好的链表首结点*t之前，
	                        //在改变t1->link之前，将t1的后继结点存储在t2之中
	    t1->link=t;
	    t=t1;
	    t1=t2;t2=t1->link;
	}
	
	t1->link=t; //最后一结点的处理
	(*L)->link=t1;
}
void PrintPoly(Polynomial P)
{
	int flag = 0;
	if(!P)
	{
		printf("0 0\n");
		return;
	}
	while(P)
	{
		if(!flag)
			flag = 1;
		else
			printf(" ");
		printf("%d %d",P->coef, P->expon);
		P = P->link;		
	}
	printf("\n");
}

int main()
{
	Polynomial P1 = ReadPoly();
	Polynomial P2 = ReadPoly();
	Polynomial PA = AddPoly(P1, P2);
	PrintPoly(PA);
	Polynomial PB = SubPoly(P1, P2);
	PrintPoly(PB->link);
	RePoly(&PB);//逆置 
	PrintPoly(PB->link);
	return 0;
}
