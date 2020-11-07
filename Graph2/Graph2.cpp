// Graph2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//实现以邻接表作为存储结构的图的基本操作
#define vex_num 20
#define vex_name_length 10	//定义顶点名字的长度
typedef char* VetexType;	//定义顶点的数据类型
typedef int InfoType;	//定义相关信息的数据类型
//定义弧
typedef struct Arc {
	int v;				//该弧所指向的顶点位置		
	struct Arc* next;			
	//InfoType* info;		//该弧相关信息的指针
};
//定义邻接表
typedef struct Node{
	VetexType v;		//定义顶点
	Arc* list;			//与顶点v相邻的边
}AdjList[vex_num];
//定义用邻接表实现的图
typedef struct AGraph {
	AdjList vexs;
	int vexnum, arcnum;
	int kind;
};
bool* flag;			//定义一个布尔型指针

//对顶点的访问操作
//访问顶点u在图中的位置
int LocateVex(AGraph* G, VetexType u) {
	int j;
	for (j = 0; j < G->vexnum; j++) {
		if (strcmp(G->vexs[j].v,u)==0) {
			return j;
		}
	}
	return -1;
}
//插入弧
void InsertArc(AGraph* G, int v, int w) {
	Arc*tmp,*a;
	a = (Arc*)malloc(sizeof(Arc));	//创建一个弧
	a->v = w;						//放入弧头所在的位置
	a->next = NULL;					
	tmp =G->vexs[v].list;
	if (tmp) {
		while (tmp->next) {
			tmp = tmp->next;
		}
		tmp->next = a;
	}
	else {
		G->vexs[v].list = a;
	}
}
//图的创建
AGraph CreateGraph(AGraph* G) {
	int n,m,i,j1,j2;
	char *nam,*n1,*n2;
	printf("Please input the number of vertexs:\n");
	scanf_s("%d", &n);
	G = (AGraph*)malloc(sizeof(AGraph));
	G->vexnum = n;
	flag = (bool*)malloc(sizeof(bool) * G->vexnum);
	for (int i = 0; i < G->vexnum; i++) {
		flag[i] = false;		//初始化标志数组,便于后面图的遍历
	}
	//初始化邻接表
	for (i = 0; i < G->vexnum; i++) {
		printf("Please input the name of vertex:\n");		
		//在循环体内分配指针指向的内存,不断更新指针指向的位置,否则指针指向的内存改变,数据也会改变
		nam = (char*)malloc(vex_name_length * sizeof(char));	//定义字符串指针时,一定要用malloc为其分配一个内存空间,否则会因为指向不明报错
		scanf_s("%s", nam, sizeof(nam));						//scanf_s和scanf的区别就是增加了一个边界的检测,为了防止溢出,因此需要增加一个,sizeof(nam)检测输入的边界值
		getchar();
		G->vexs[i].v = nam;
		G->vexs[i].list = NULL;
	}
	//初始化弧
	printf("Please input the number of arcs:\n");
	scanf_s("%d",&m,sizeof(m));
	G->arcnum = m;
	for (i = 0; i < G->arcnum; i++) {
		printf("Please input the name of the vertex adjacent to the arc:\n");
		n1 = (char*)malloc(vex_name_length * sizeof(char));
		n2 = (char*)malloc(vex_name_length * sizeof(char));
		scanf_s("%s", n1, sizeof(n1));							//先输入弧尾
		scanf_s("%s", n2, sizeof(n2));							//后输入弧头
		j1 = LocateVex(G, n1);
		j2 = LocateVex(G, n2);
		if (j1 >= 0 && j2 > 0) {
			InsertArc(G, j1, j2);								//插入边
			InsertArc(G, j2, j1);
		}
		else {
			printf("输入错误,该节点不存在！\n");
		}
	}
	return *G;
}
int FirstAdjVex(AGraph* G, int v) {
	//printf("%d\n",G->vexs[v].list);
	Arc* tmp;
	tmp = G->vexs[v].list;
	if (tmp)
		return tmp->v;								//返回链表中第一个节点的位置
	else
		return -1;
}
int NextAdjVex(AGraph* G, int v,int w) {
	Arc* node;
	node = G->vexs[v].list;
	if (node) {
		while (node->v != w) {
			node = node->next;
		}
		if (node->next) {
			return node->next->v;								//如果顶点w后面还有弧,返回下一条弧的邻接点
		}
		else {													//否则返回-1
			return -1;
		}
	}
}
void visit(AGraph*G,int v) {
	printf("%s\t",G->vexs[v].v);
}
//遍历
void DFSTraverse(AGraph* G,int v) {
	visit(G,v);
	flag[v] = true;
	int w;
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v,w)) {
		if(!flag[w]) DFSTraverse(G,w);
	}
}
int main()
{
	AGraph G;
	G=CreateGraph(&G);
	DFSTraverse(&G,0);
	return 0;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
