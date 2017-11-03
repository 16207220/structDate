#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define STACK_INIT_SIZE 1000
#define STACKINCREMENT 10
#define OK 1
#define OVERFLOW 0
#define ERROR 0
  
//typedef int SElemType;
struct SElemType{
    int x;int y;
};
typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
int InitStack(SqStack &S){
    S.base=(SElemType *)malloc(STACK_INIT_SIZE *sizeof(SElemType));
    if(!S.base) exit(OVERFLOW);
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return OK;
}
void Push(SqStack &S,SElemType &e){
    if(S.top-S.base>=S.stacksize){
        S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!S.base) exit (OVERFLOW);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;
}
SElemType Pop(SqStack &S,SElemType &e){
    //if(S.top==S.base) return ERROR;
    e=*--S.top;
    return e;
}
SElemType GetTop(SqStack S,SElemType &e){
    e=*(S.top-1);
    return e;
}
  
int StackEmpty(SqStack &S)
 {//��ջSΪ��ջ���򷵻�OK�����򷵻�ERROR
    if(S.base==S.top)
        return OK;
    else
        return ERROR;
}
  
  
int main()
{
    int m;
    SqStack S;
    InitStack(S);
    printf("�������Թ��Ĵ�С(m*m)");
    scanf("%d",&m);
    //�������ʽ��ʾ�˸�����
    int move[8][2]={{0,1},{1,1},{1,0},
                    {1,-1},{0,-1},{-1,-1},{-1, 0},{-1, 1}};
     
    //�ýṹ���ʾλ��
    struct position
    {
        int x,y;
    };
    //���ڼ�¼������Թ�̽·����ط��ţ�����1 .
    char maze[20][20];
    //��ջ���洢̽·�����е�����
    int i,x,y,ok;
    SElemType p;
    //��ά����ĵ�0�С���m+1�С���0�С���m+1��Ԫ��ȫ
    //�óɡ�1������ʾ�Թ��ı߽磻��1�е�1��Ԫ�غ͵�m�е�m��
    //Ԫ���óɡ�0������ʾ�Թ�����ںͳ��ڣ�����Ԫ��ֵ�����
    //����������
    srand(time(0));
    for(x=1;x<=m;x++)
        for(y=1;y<=m;y++)
            maze[x][y]=48+rand()%2;
    maze[1][1]='0';maze[m][m]='0';
    for(x=0;x<=m+1;x++)
    {
        maze[x][0]='1';maze[x][m+1]='1';
    }
    for(y=0;y<=m+1;y++)
    {
        maze[0][y]='1';maze[m+1][y]='1';
    }
    p.x=1;p.y=1;
    Push(S,p);
    maze[1][1]='.';
    printf("�Թ���ʼΪ��m*m��\n");
    for(x=1;x<=m;x++)
    {
        printf("\n");
        for(y=1;y<=m;y++) 
            printf("%c ",maze[x][y]);
             
    }
    printf("\n");
    
    //��ʼ̽·
    while((!StackEmpty(S))&&((p.x!=m)||(p.y!=m))) {
        GetTop(S,p);
        ok=0;i=0;
        while((ok==0)&&(i<8))
        {
            x=p.x+move[i][0];
            y=p.y+move[i][1];
            if(maze[x][y]=='0')
            {
                p.x=x;p.y=y;
                Push(S,p);
                maze[x][y]='.';
                ok=1;
            }
            i++;
        }
        if(i==8)
        {
            maze[p.x][p.y]='*';
            Pop(S,p);
        }
    }
    //���̽·���
    if(StackEmpty(S)) printf("û��·��\n");
    else printf("��·��\n");
    //���̽·�Թ����µ��ټ�
    for(x=1;x<=m;x++)
    {
        printf("\n");
        for(y=1;y<=m;y++) 
            printf("%c ",maze[x][y]);
             
    }
    printf("\n");
    system("pause"); 
}
