#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
typedef int Status;
int prop;
#define Stack_Size 100
#define StackIncrement 10
#define pass 0
#define wall 1
#define begin 6
#define end 7
#define back 8
#define Exit 9

#define path "C:\\Users\\胡逸藤\\Desktop\\数据结构迷宫大作业\\迷宫数据.txt"
typedef struct{            //坐标信息 
	int x;
	int y;
}Position;

enum direction{  //东南西北分别为2 3 4 5 
	east=2,
	south, 
	west,
	north	
};

typedef struct{           //存储探索过程信息的结构体 
	int step;             //当前是第几步 
	enum direction dir;   //下一步的方向 
	Position pos;         //该位置的坐标 
}information;

typedef information ElemType;  //定义栈中存储的类型为路径信息结构体 
typedef struct stack{
	ElemType *bottom;
	ElemType *top;
	int stacksize;   //当前已分配空间 
}sqstack,*ptostack;

ptostack push(ptostack s,ElemType data);
ElemType pop(ptostack s);
ElemType GetTop(ptostack s);
ptostack CreatStack();
Status IsEmpty(ptostack S);
Status FindPath(ptostack s,Position start,Position stop,int w,int l);
enum direction FindDir();
Position ChangePos(Position pos);
void CreatMaze(int w,int l);
void PrintStack(ptostack s); 
void MainMenu();
void ReadText();
void Set();
void ResetMaze(int w,int l);
void PrintMaze(int w,int l);
void over(); 
void HelpMenu();
int Maze[100][100];

int main(){
	MainMenu();
	return 0;
}

void MainMenu(){
	system("cls");
	int choice,l,w; 
	Position Start,End;
	ptostack s=CreatStack();
	printf("\n 		欢迎来到迷宫游戏！\n"); 
	printf("\t\t1、自定义迷宫\n\t\t2、随机生成迷宫\n\t\t3、从文件中导入迷宫\n\t\t4、设置\n\t\t5、帮助\n\t\t0、退出\n\n\n\t\t请选择数字:");
	scanf("%d",&choice);
	switch(choice){
		case 1: system("cls");
				printf("请输入一个不超过100的正整数代表迷宫的宽度：");
				scanf("%d",&l); 
				printf("请输入一个不超过100的正整数代表迷宫的高度：");
				scanf("%d",&w);
				printf("请输入一个小于100的正整数代表墙的比例（建议选择25-35之间）:");
				scanf("%d",&prop);
				if(l<=2||l>=100||w<=2||w>=100||prop<0||prop>=100){
					printf("设置参数有误！按任意键返回主菜单！");
					system("pause"); 
					MainMenu(); 
				}
				printf("设置成功！\n正在打印地图请等候...\n");
				CreatMaze(w,l);	
				Start.x=1;
				Start.y=0;
				End.x=w-2;
				End.y=l-1;
				FindPath(s,Start,End,w,l);
				break;
		case 2: Start.x=1;
				Start.y=0;
				End.x=8;
				End.y=9;
				prop=30;
				CreatMaze(10,10);
				FindPath(s,Start,End,10,10);
			    break;
		case 3:	ReadText();
				break; 
		case 4:	Set();
		case 5: HelpMenu();			
		case 0:	break;	 
	}
	return;
}

void HelpMenu(){
	system("cls");
	printf("\n\t\t********帮助菜单********\n");
	int choice;
	printf("\t\t1、如何从文件中导入迷宫?\n\t\t2、迷宫中显示的*代表什么?\n\t\t3、关于作品\n\t\t0、返回\n");
	scanf("%d",&choice);
	switch(choice){
		case 1:printf("迷宫信息以二维数组的形式存放在一个文本文件中，");
			   printf("您只需修改其中的数值即可创造您自己的迷宫。（1代表墙，0代表通路，6和7分别代表起点和终点）");
			   break;
		case 2:printf("*代表你已经走过并折返的路径");break;
		case 3:printf("这是一个关于动态走迷宫的小程序，是本人在学校数据结构课程中的一份作业。\n我在GitHub中记录了一些调试改进的过程。附上链接https://github.com/961853266hyt/Dynamic-Maze\n");
		case 0:MainMenu();break;
	}
	system("pause");
	HelpMenu();
	return;
}
void ResetMaze(int w,int l){
	for(int i=0;i<w;i++){
		for(int j=0;j<l;j++){
			Maze[i][j]=0;
		}
	}
	return;
}
void ReadText(){
	 FILE* fp;
	 int w,l;
	 Position Start,End;
	 ptostack s=CreatStack();
	 if((fp=fopen(path,"r"))==NULL){
	 	printf("文件打开失败！！！\n");
		system("pause");
		MainMenu(); 
	 }

	 fscanf(fp,"%d%d",&w,&l);
	 for(int i=0;i<w;i++){
	 	for(int j=0;j<l;j++){
	 	 	fscanf(fp,"%d",&Maze[i][j]);
	 	}
	 }
	 fclose(fp);
	 printf("设置成功！\n正在打印地图请等候...\n");
	 PrintMaze(w,l);	
	 Start.x=1;
	 Start.y=0;
	 End.x=w-2;
	 End.y=l-1;
	 FindPath(s,Start,End,w,l);
	 return;
}

void Set(){
	
	
	
	
	
	return;
}

void over(){
	printf("    ■■■      ■      ■      ■■■■      ■■■■\n");
	printf("  ■      ■    ■      ■      ■            ■    ■\n");
	printf("  ■      ■      ■  ■        ■■■■      ■■■■\n");
	printf("  ■      ■      ■  ■        ■            ■■\n");
	printf("    ■■■          ■          ■■■■      ■  ■\n");
	return;
}

Position ChangePos(Position &pos,direction dir){
	if(pos.x<0||pos.y<0) {	
		over(); 
		printf("该迷宫没有解!!!\n");
		system("pause");
		MainMenu();
	}
	switch(dir){
		case north:pos.x-=1;break;
		case west:pos.y-=1;break;
		case south:pos.x+=1;break;
		case east:pos.y+=1;break;
	}

	return pos;
}
void PrintStack(ptostack s){
	ElemType* t=s->bottom;
	information info;
	while(t<s->top){
		info=*t;
		printf("<%d,%d> ",info.pos.x,info.pos.y);
		t++;
	}
	return;
}
void PrintMaze(int w,int l){
	system("cls");
	for(int i=0;i<w;i++){
		if(i==0) {
			printf("  ");
			for(int z=0;z<l;z++){ 
				if(z<10) 
					printf("%d ",z);		 //打印横坐标 
				else 
					printf("%d",z);
				} 
			printf("\n");
		}
		if(i<10)
			printf("%d ",i);            //打印纵坐标 
		else 
			printf("%d",i); 
		for(int j=0;j<l;j++){			
			switch(Maze[i][j]){
				case wall:printf("%c%c",0xa8,0x80);break;
				case pass:printf("  ",0xa8,0x80);break;
				case north:printf("↑");break;
				case east:printf("→");break;
            	case south:printf("↓"); break;
            	case west:printf("←");break;
            	case begin:printf("起");break;
            	case end:printf("终");break;
            	case back:printf("* ");break;
            	case Exit:printf("终");break;
			}
			
		}
		printf("\n");		
	}
	return;
}

void CreatMaze(int w,int l){
	int num;	
	srand(time(NULL));									
	//生成周围一圈的墙 
	ResetMaze(w,l);
	for(int i=0;i<w;i++){
		if(i==0||i==w-1){
			for(int j=0;j<l;j++){	
				Maze[i][j]=wall;
			}
		}		
		else{
			Maze[i][0]=wall;
			Maze[i][l-1]=wall;
			
			for(int j=1;j<l-1;j++){
				num=rand()%100+1;
				if(num<=prop) Maze[i][j]=wall;
				else Maze[i][j]=pass;
			}
		}		
	}//for	
	Maze[1][0]=begin;
	Maze[w-2][l-1]=end;
	Maze[1][1]=pass;
	Maze[w-2][l-2]=pass;
	PrintMaze(w,l);
	return;
}

enum direction FindDir(Position pos){
    if(Maze[pos.x][pos.y+1]==pass||Maze[pos.x][pos.y+1]==end) return east; 
    if(Maze[pos.x+1][pos.y]==pass||Maze[pos.x+1][pos.y]==end) return south;
    if(Maze[pos.x][pos.y-1]==pass||Maze[pos.x][pos.y-1]==end) return west;
	if(Maze[pos.x-1][pos.y]==pass||Maze[pos.x-1][pos.y]==end) return north;          
}

Status FindPath(ptostack s,Position start,Position stop,int w,int l){
	Position currpos;          //当前位置坐标 
	information info;          //记录探索路径的过程 
	currpos=start;
	int step=1;
	ptostack reverse=CreatStack();
	while(1){
		if(currpos.x==start.x&&currpos.y==start.y&&step==1){   
			info.dir=FindDir(currpos);            
			info.step=step++;
			info.pos=currpos;
			push(s,info);
		
		}
		Maze[currpos.x][currpos.y]=(int)info.dir;
		currpos=ChangePos(currpos,info.dir);         //确定当前的位置 
		
		if(Maze[currpos.x][currpos.y]==end){   //如果找到出口 
			info.step=step;
			info.pos=currpos;
			push(s,info);
			Maze[currpos.x][currpos.y]=Exit;
			system("cls");
            printf("\n");
            PrintMaze(w,l);
            printf("恭喜您找到出口：\n");
            PrintStack(s);
            printf("\n您共用了%d步\n",step); 
			break;
		}
		
		if(Maze[currpos.x][currpos.y]==pass){   //若当前位置可通 
			info.step=step++;
			info.pos=currpos;
			info.dir=FindDir(currpos);
			push(s,info);			
		}
		
		else{              //若当前方块不可通 
			info=pop(s);
            currpos=info.pos;
            step=info.step-1;
            Maze[currpos.x][currpos.y]=back;    //将当前位置标记为已走过，返回 			
			do
            {
                info=pop(s);
                currpos=info.pos;                         
                while(info.dir<=4)
                {
                    info.dir=(enum direction)(info.dir+1);
                    currpos=ChangePos(currpos,info.dir);
                    if(Maze[currpos.x][currpos.y]==pass)
                    {
                        break;
                    }
                };                
                if(Maze[currpos.x][currpos.y]==pass)
                {
                    currpos=info.pos;
                    info.step=step++;
                    info.pos=currpos;
                    push(s,info);
                    break;
                }
                else
                {
                    currpos=info.pos;
                    Maze[currpos.x][currpos.y]=back;    
                }
            	PrintMaze(w,l);
            	printf("正在动态探索路径...\n"); 
            	PrintStack(s);
                Sleep(500);
                system("cls");
            }while(!IsEmpty(s));  //do 
		}//else
		PrintMaze(w,l);
		printf("正在动态探索路径..."); 
		PrintStack(s);
        Sleep(500);
        system("cls");
	}//while(1)	
	system("pause");
	MainMenu();
	return 0; 
}

//关于栈的部分 
ptostack CreatStack(){
	ptostack s=(ptostack)malloc(sizeof(sqstack));
	s->bottom=(ElemType*)malloc(Stack_Size*sizeof(ElemType));
	s->top=s->bottom;
	s->stacksize=Stack_Size;
	return s;
}

ptostack push(ptostack s,ElemType data){
	if(s->top-s->bottom>=s->stacksize){
		s->bottom=(ElemType*)realloc(s->bottom,(s->stacksize+StackIncrement)*sizeof(ElemType));
		s->top=s->bottom+s->stacksize;
		s->stacksize+=StackIncrement;
	}	
	*(s->top)=data;
	s->top++; 
	return s;
}

ElemType pop(ptostack s){
	if(IsEmpty(s)){
		over();
		printf("对不起，不存在路径！！！");
	}
	return *(--s->top);
}

ElemType GetTop(ptostack s){
	return *(s->top-1);
}

Status IsEmpty(ptostack s){
	if(s->top-s->bottom==0) return 1;
	return 0;
} 

/*
姓名：胡逸藤
学号：18041513
github链接:https://github.com/961853266hyt/Dynamic-Maze(欢迎提出意见)
*/
