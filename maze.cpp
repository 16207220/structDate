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
 {//若栈S为空栈，则返回OK，否则返回ERROR
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
    printf("请输入迷宫的大小(m*m)");
    scanf("%d",&m);
    //数组的形式表示八个方向
    int move[8][2]={{0,1},{1,1},{1,0},
                    {1,-1},{0,-1},{-1,-1},{-1, 0},{-1, 1}};
     
    //用结构体表示位置
    struct position
    {
        int x,y;
    };
    //用于记录和输出迷宫探路中相关符号，包括1 .
    char maze[20][20];
    //用栈来存储探路过程中的数据
    int i,x,y,ok;
    SElemType p;
    //二维数组的第0行、第m+1行、第0列、第m+1列元素全
    //置成“1”，表示迷宫的边界；第1行第1列元素和第m行第m列
    //元素置成“0”，表示迷宫的入口和出口；其余元素值用随机
    //函数产生。
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
    printf("迷宫初始为（m*m）\n");
    for(x=1;x<=m;x++)
    {
        printf("\n");
        for(y=1;y<=m;y++) 
            printf("%c ",maze[x][y]);
             
    }
    printf("\n");
    
    //开始探路
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
    //输出探路结果
    if(StackEmpty(S)) printf("没有路径\n");
    else printf("有路径\n");
    //输出探路迷宫留下的踪迹
    for(x=1;x<=m;x++)
    {
        printf("\n");
        for(y=1;y<=m;y++) 
            printf("%c ",maze[x][y]);
             
    }
    printf("\n");
    system("pause"); 
}
