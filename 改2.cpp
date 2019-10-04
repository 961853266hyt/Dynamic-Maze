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

#define path "C:\\Users\\������\\Desktop\\���ݽṹ�Թ�����ҵ\\�Թ�����.txt"
typedef struct{            //������Ϣ 
	int x;
	int y;
}Position;

enum direction{  //���������ֱ�Ϊ2 3 4 5 
	east=2,
	south, 
	west,
	north	
};

typedef struct{           //�洢̽��������Ϣ�Ľṹ�� 
	int step;             //��ǰ�ǵڼ��� 
	enum direction dir;   //��һ���ķ��� 
	Position pos;         //��λ�õ����� 
}information;

typedef information ElemType;  //����ջ�д洢������Ϊ·����Ϣ�ṹ�� 
typedef struct stack{
	ElemType *bottom;
	ElemType *top;
	int stacksize;   //��ǰ�ѷ���ռ� 
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
	printf("\n 		��ӭ�����Թ���Ϸ��\n"); 
	printf("\t\t1���Զ����Թ�\n\t\t2����������Թ�\n\t\t3�����ļ��е����Թ�\n\t\t4������\n\t\t5������\n\t\t0���˳�\n\n\n\t\t��ѡ������:");
	scanf("%d",&choice);
	switch(choice){
		case 1: system("cls");
				printf("������һ��������100�������������Թ��Ŀ�ȣ�");
				scanf("%d",&l); 
				printf("������һ��������100�������������Թ��ĸ߶ȣ�");
				scanf("%d",&w);
				printf("������һ��С��100������������ǽ�ı���������ѡ��25-35֮�䣩:");
				scanf("%d",&prop);
				if(l<=2||l>=100||w<=2||w>=100||prop<0||prop>=100){
					printf("���ò������󣡰�������������˵���");
					system("pause"); 
					MainMenu(); 
				}
				printf("���óɹ���\n���ڴ�ӡ��ͼ��Ⱥ�...\n");
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
	printf("\n\t\t********�����˵�********\n");
	int choice;
	printf("\t\t1����δ��ļ��е����Թ�?\n\t\t2���Թ�����ʾ��*����ʲô?\n\t\t3��������Ʒ\n\t\t0������\n");
	scanf("%d",&choice);
	switch(choice){
		case 1:printf("�Թ���Ϣ�Զ�ά�������ʽ�����һ���ı��ļ��У�");
			   printf("��ֻ���޸����е���ֵ���ɴ������Լ����Թ�����1����ǽ��0����ͨ·��6��7�ֱ���������յ㣩");
			   break;
		case 2:printf("*�������Ѿ��߹����۷���·��");break;
		case 3:printf("����һ�����ڶ�̬���Թ���С�����Ǳ�����ѧУ���ݽṹ�γ��е�һ����ҵ��\n����GitHub�м�¼��һЩ���ԸĽ��Ĺ��̡���������https://github.com/961853266hyt/Dynamic-Maze\n");
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
	 	printf("�ļ���ʧ�ܣ�����\n");
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
	 printf("���óɹ���\n���ڴ�ӡ��ͼ��Ⱥ�...\n");
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
	printf("    ������      ��      ��      ��������      ��������\n");
	printf("  ��      ��    ��      ��      ��            ��    ��\n");
	printf("  ��      ��      ��  ��        ��������      ��������\n");
	printf("  ��      ��      ��  ��        ��            ����\n");
	printf("    ������          ��          ��������      ��  ��\n");
	return;
}

Position ChangePos(Position &pos,direction dir){
	if(pos.x<0||pos.y<0) {	
		over(); 
		printf("���Թ�û�н�!!!\n");
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
					printf("%d ",z);		 //��ӡ������ 
				else 
					printf("%d",z);
				} 
			printf("\n");
		}
		if(i<10)
			printf("%d ",i);            //��ӡ������ 
		else 
			printf("%d",i); 
		for(int j=0;j<l;j++){			
			switch(Maze[i][j]){
				case wall:printf("%c%c",0xa8,0x80);break;
				case pass:printf("  ",0xa8,0x80);break;
				case north:printf("��");break;
				case east:printf("��");break;
            	case south:printf("��"); break;
            	case west:printf("��");break;
            	case begin:printf("��");break;
            	case end:printf("��");break;
            	case back:printf("* ");break;
            	case Exit:printf("��");break;
			}
			
		}
		printf("\n");		
	}
	return;
}

void CreatMaze(int w,int l){
	int num;	
	srand(time(NULL));									
	//������ΧһȦ��ǽ 
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
	Position currpos;          //��ǰλ������ 
	information info;          //��¼̽��·���Ĺ��� 
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
		currpos=ChangePos(currpos,info.dir);         //ȷ����ǰ��λ�� 
		
		if(Maze[currpos.x][currpos.y]==end){   //����ҵ����� 
			info.step=step;
			info.pos=currpos;
			push(s,info);
			Maze[currpos.x][currpos.y]=Exit;
			system("cls");
            printf("\n");
            PrintMaze(w,l);
            printf("��ϲ���ҵ����ڣ�\n");
            PrintStack(s);
            printf("\n��������%d��\n",step); 
			break;
		}
		
		if(Maze[currpos.x][currpos.y]==pass){   //����ǰλ�ÿ�ͨ 
			info.step=step++;
			info.pos=currpos;
			info.dir=FindDir(currpos);
			push(s,info);			
		}
		
		else{              //����ǰ���鲻��ͨ 
			info=pop(s);
            currpos=info.pos;
            step=info.step-1;
            Maze[currpos.x][currpos.y]=back;    //����ǰλ�ñ��Ϊ���߹������� 			
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
            	printf("���ڶ�̬̽��·��...\n"); 
            	PrintStack(s);
                Sleep(500);
                system("cls");
            }while(!IsEmpty(s));  //do 
		}//else
		PrintMaze(w,l);
		printf("���ڶ�̬̽��·��..."); 
		PrintStack(s);
        Sleep(500);
        system("cls");
	}//while(1)	
	system("pause");
	MainMenu();
	return 0; 
}

//����ջ�Ĳ��� 
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
		printf("�Բ��𣬲�����·��������");
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
������������
ѧ�ţ�18041513
github����:https://github.com/961853266hyt/Dynamic-Maze(��ӭ������)
*/
