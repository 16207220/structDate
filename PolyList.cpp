#include<stdio.h>
#include<malloc.h>
typedef struct PolyNode * Polynomial;
struct PolyNode{
	int coef;	//ϵ�� 
	int expon;	//ָ�� 
	Polynomial link;
};

void Attach(int c, int e, Polynomial * rear)
{
	Polynomial input = (Polynomial)malloc(sizeof(struct PolyNode));
	//�����½ڵ㲢����ֵ 
	input->coef = c;
	input->expon = e;
	input->link = NULL;
	(*rear)->link = input;
	*rear = input; //�޸�ĩβָ�룬��Ϊ���޸�ָ�룬�ʴ˴�ʹ��ָ���ָ�� 
}

Polynomial ReadPoly()
{
	Polynomial P1, rear, t;
	int N;//����ʽ���� 
	int c,e;//�����ݴ�ϵ����ָ�� 
	P1 = (Polynomial)malloc(sizeof(struct PolyNode));//����ͷ�ڵ� 
	//����ͷ�ڵ���Ϊ�˷���ʹ��Attach����ʱ����������rear�ǿջ��Ƿǿգ�����ͷ�ڵ㶼�Ƿǿգ����뷽�� 
	P1->link = NULL;
	
	rear = P1;//βָ��ָ��ͷ�ڵ� 
	scanf("%d",&N);
	while(N--) 
	{
		scanf("%d %d",&c, &e);
		Attach(c, e, &rear);
	}
	t = P1; 
	P1 = P1->link;
	free(t);//ͷ�ڵ㷽������ʹ����ɣ��ͷ�ͷ�ڵ�
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
		if(t1->expon == t2->expon)//���ָ����ͬ�������� 
		{
			if(t1->coef + t2->coef)//���ϵ����Ӳ�Ϊ�㣬�򽫼���������P�� 
			{
				Attach(t1->coef + t2->coef, t1->expon, &rear);
			}
			t1 = t1->link;
			t2 = t2->link;
		}
		else if(t1->expon > t2->expon)//�ҵ�ָ����ļ��뵽P�� 
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
	while(t1)//���t1���ж���ڵ㣬��������� 
	{
		Attach(t1->coef, t1->expon, &rear);
		t1 = t1->link;
	}
	while(t2)//���t2���ж���ڵ㣬��������� 
	{
		Attach(t2->coef, t2->expon, &rear);
		t2 = t2->link;
	}
	t = P;
	P = P->link;
	free(t);//�ͷ�ͷ�ڵ� 
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
		if(t1->expon == t2->expon)//���ָ����ͬ�������� 
		{
			if(t1->coef - t2->coef)//���ϵ����Ӳ�Ϊ�㣬�򽫼���������P�� 
			{
				Attach(t1->coef - t2->coef, t1->expon, &rear);
			}
			t1 = t1->link;
			t2 = t2->link;
		}
		else if(t1->expon > t2->expon)//�ҵ�ָ����ļ��뵽P�� 
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
	while(t1)//���t1���ж���ڵ㣬��������� 
	{
		Attach(t1->coef, t1->expon, &rear);
		t1 = t1->link;
	}
	while(t2)//���t2���ж���ڵ㣬��������� 
	{
		Attach(-t2->coef, t2->expon, &rear);
		t2 = t2->link;
	}
	//t = P;
	//P = P->link;
	//free(t);//�ͷ�ͷ�ڵ� 
	return P;
}

/*�����㷨1

void RePoly(Polynomial *L)   {
// L�Ǵ�ͷ���ĵ������ͷָ�룻p��q��r����������ָ��
//��ɨ������Ĺ����н������ò���
    Polynomial t1,t2,t;
    if (!L->next ) return;        //�ձ�
      t1=L->next;  t2=t1->next;  //ԭ���У�*t1Ϊ*t2��ǰ��
      t1->next=NULL;              //a1��next�ÿ�ָ�룬����ͷ���
      while (t2) {   t=t2->next ;   //�޸�t2->next֮ǰ������t2->next��t
                         t2->next=t1 ;   //���ñ��У�*t2Ϊ*t1��ǰ��
                         t1=t2 ; t2=t ;    //����ɨ���ָ�붼�����
       }
       L->next=t1;
}  //ReverseLinkList2

*/

void RePoly(Polynomial *L)
{
	Polynomial t1, t2, t;

	t1=(*L)->link->link;t2=t1->link;
	if(t1==NULL) return;//��һ��Ԫ��ʱ��ֱ�ӷ���
	
	t=(*L)->link;
	t->link =NULL;
	
	while(t1->link!=NULL){  //ÿ�ν�δ���õ������е��׽��*t1�����ڲ������úõ������׽��*t֮ǰ��
	                        //�ڸı�t1->link֮ǰ����t1�ĺ�̽��洢��t2֮��
	    t1->link=t;
	    t=t1;
	    t1=t2;t2=t1->link;
	}
	
	t1->link=t; //���һ���Ĵ���
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
	RePoly(&PB);//���� 
	PrintPoly(PB->link);
	return 0;
}
