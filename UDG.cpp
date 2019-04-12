#include<stdio.h>
#include<stdlib.h>
#define UNVISITED   0
#define VISITED     1
#define OK          1
#define ERROR       0
#define OVERFLOW    -1
#define TRUE        1
#define FALSE        0
typedef int Status;
typedef char VexType;    //顶点类型
typedef int ElemType;    //队列结点的数据类型
//无向图的邻接数组定义
typedef struct{
    VexType * vexs;    //顶点数组
    int ** arcs;    //关系数组，用0或1表示相邻否
    int n;            //顶点数
    int e;            //边数
    int * tags;        //标志数组，用于在图的遍历中标记顶点访问与否
} UDG;
//边信息
typedef struct {
    VexType v, w;    //边的两端点
} ArcInfo;
//链队列结点
typedef struct LQNode {
    ElemType data;            //数据域
    struct LQNode *next;    //指向下一结点
} LQNode, *QuenePtr;
//链队列
typedef struct{
    QuenePtr front;        //队头指针
    QuenePtr rear;        //队尾指针
} LQueue;
//初始化含n个顶点且无边的无向图G
Status InitUDG(UDG &G, VexType * vexs, int n) {
    int i, j;
    //判断参数的合理性
    if (n < 0 || (n > 0 && NULL == vexs)) {
        return ERROR;
    }
    //设置G的成员
    G.n = n;
    G.e = 0;
    if (0 == n) {
        return OK;    //空图
    }
    if (NULL == (G.vexs = (VexType *)malloc(n * sizeof(VexType)))) {    //分配顶点数组
        return OVERFLOW;
    }
    for (i = 0; i < G.n; i++) {
        G.vexs[i] = vexs[i];    //初始化顶点数组
    }
    if (NULL == (G.arcs = (int **)malloc(n*sizeof(int *)))) {    //分配指针数组
        return OVERFLOW;
    }
    for (i = 0; i < n; i++) {    //分配每个指针所指向的数组
        if (NULL == (G.arcs[i] = (int *)malloc(n*sizeof(int)))) {
            return OVERFLOW;
        }
    }
    if (NULL == (G.tags = (int *)malloc(n*sizeof(int)))) {    //分配标志数组
        return OVERFLOW;
    }
    for (i = 0; i < n; i++) {   //初始化标志数组和关系数组
        G.tags[i] = UNVISITED;
        for (j = 0; j < n; j++) {
            G.arcs[i][j] = 0;
        }
    }
    return OK;
}
//查找顶点v在无向图G中的位序
int LocateVex_UDG(UDG G, VexType v) {
    int i;
    for (i = 0; i < G.n; i++) {
        if (v == G.vexs[i])
            return i;
    }
    return -1;
}
//创建含n个顶点和e条边的无向图G，vexs为顶点信息、arcs为边信息
Status CreateUDG(UDG &G, VexType * vexs, int n, ArcInfo * arcs, int e) {
    int i, j, k;
    VexType v, w;
    if (InitUDG(G, vexs, n) != OK) {    //初始化
        return ERROR;
    }
    G.e = e;
    for (k = 0; k < G.e; k++) {
        v = arcs[k].v;
        w = arcs[k].w;    //读入边(v, w)
        i = LocateVex_UDG(G, v);
        j = LocateVex_UDG(G, w);    //确定v和w在顶点数组中的位序为i和j
        if (i < 0 || j < 0) {
            return ERROR;
        }
        G.arcs[i][j] = G.arcs[j][i] = 1;    //对应行列的元素赋为1（即给关系数组赋值）
    }
    return OK;
}
//销毁无向图G
Status DestroyUDG(UDG &G) {
    free(G.vexs);
    int i;
    for (i = 0; i < G.n; i++) {
        free(G.arcs[i]);    //分别释放每一个指向相应数组的指针
    }
    free(G.arcs);
    free(G.tags);
    G.e = 0;
    G.n = 0;
    return OK;
}
//取无向图G的k顶点的值到w
Status GetVex_UDG(UDG G, int k, VexType &w) {
    if (k < 0 || k >= G.n) {
        return ERROR;
    }
    w = G.vexs[k];
    return OK;
}
//对无向图的k顶点赋值w
Status PutVex_UDG(UDG G, int k, VexType w) {
    if (k < 0 || k >= G.n) {
        return ERROR;
    }
    G.vexs[k] = w;
    return OK;
}
//求无向图G中k顶点的第一个邻接顶点的位序
int FirstAdjVex_UDG(UDG G, int k) {
    if (k < 0 || k >= G.n) {
        return -1;
    }
    int i;
    for (i = 0; i < G.n; i++) {
        if (G.arcs[k][i] != 0) {
            return i;
        }
    }
    return -1;
}
//m顶点为k顶点的邻接顶点，求无向图G中k顶点相对于m顶点的下一个邻接顶点的位序
int NextAdjVex_UDG(UDG G, int k, int m) {
    if (k < 0 || k >= G.n || m < 0 || m >= G.n || k == m) {
        return -1;
    }
    int i;
    for (i = m+1; i < G.n; i++) {
        if (G.arcs[k][i] != 0) {
            return i;
        }
    }
    return -1;
}
//在无向图G中增加k顶点到m顶点的边
Status AddArc_UDG(UDG &G, int k, int m) {
    if (k < 0 || k >= G.n || m < 0 || m >= G.n || k == m) {
        return ERROR;
    }
    if (G.arcs[k][m] == 1) {    //该边已存在
        return ERROR;
    }
    G.arcs[k][m] = 1;
    G.arcs[m][k] = 1;
    G.e++;
    return OK;
}
//在无向图G中删除k顶点到m顶点的边
Status RemoveArc_UDG(UDG &G, int k, int m) {
    if (k < 0 || k >= G.n || m < 0 || m >= G.n || k == m) {
        return ERROR;
    }
    if (G.arcs[k][m] == 0) {    //该边不存在
        return ERROR;
    }
    G.arcs[k][m] = 0;
    G.arcs[m][k] = 0;
    G.e--;
    return OK;
}
//打印无向图（邻接数组）
void PrintUDG(UDG G) {
    int i, j;
    for (i = 0; i < G.n; i++) {
            printf("%c  ", G.vexs[i]);
    }
    printf("\n");
    for (i = 0; i < G.n; i++) {
        for (j = 0; j < G.n; j++) {
            printf("%d  ", G.arcs[i][j]);
        }
        printf("\n");
    }
}
//访问k顶点
Status visit(int k) {
    if (k < 0) {
        return ERROR;
    }
    printf("%d  ", k);    //打印顶点位序
    return OK;
}
//从连通图G的k顶点出发进行深度优先遍历
Status DFS_UDG(UDG G, int k) {
    int i;
    if (ERROR == visit(k)) {    //访问k顶点
        return ERROR;
    }
    G.tags[k] = VISITED;    //标记为已访问
    for (i = FirstAdjVex_UDG(G, k); i >= 0; i = NextAdjVex_UDG(G, k, i)) {    //访问所有k的邻接顶点
        if (UNVISITED == G.tags[i]) {    //遍历未访问过的顶点
            if (ERROR == DFS_UDG(G, i)) {    //对未访问过的顶点进行递归遍历
                return ERROR;
            }
        }
    }
    return OK;
}
//对无向图进行深度优先遍历
Status DFSTraverse_UDG(UDG G) {
    int i;
    for (i = 0; i < G.n; i++) {    //初始化标记数组
        G.tags[i] = UNVISITED;
    }
    for (i = 0; i < G.n; i++) {    //遍历所有顶点
        if (UNVISITED == G.tags[i]) {
            if (ERROR == DFS_UDG(G, i)) {    //对未访问过的顶点进行递归遍历
                return ERROR;
            }
        }
    }
    return OK;
}
//构造一个空队列Q
void InitQuene_LQ(LQueue &Q) {
    Q.front = NULL;
    Q.rear = NULL;
}
//在队列Q的队尾插入元素v
Status EnQueue_LQ(LQueue &Q, ElemType v) {
    LQNode *p;
    p = (LQNode *)malloc(sizeof(LQNode));    //为新结点分配空间
    if (NULL == p) {
        return OVERFLOW;
    }
    p -> data = v;
    p -> next = NULL;
    if (NULL == Q.front) {    //插入空队列
        Q.front = p;
    } else {    //插入非空队列
        Q.rear -> next = p;    //之前的队尾结点的next域指向新结点
    }
    Q.rear = p;    //新结点为新的队尾
    return OK;
}
//若队列非空，则删除队头元素，并用v带回其值。
Status DeQueue_LQ(LQueue &Q, ElemType &v) {
    LQNode *p;
    if (NULL == Q.front) {    //若队列为空，则返回ERROR
        return ERROR;
    }
    p = Q.front;
    v = p -> data;    //保存队头结点的数据
    Q.front = p -> next;    //队头结点指向下一个结点
    if (Q.rear == p) {    //若原先队列只有一个结点，则删除队头结点后，队尾结点也为空
        Q.rear = NULL;
    }
    free(p);    //释放被删队头结点
    return OK;
}
//广度优先遍历无向图G
Status BFSTraverse_UDG(UDG G) {
    int i, j, k;
    LQueue Q;
    InitQuene_LQ(Q);    //初始化链队列Q
    for (i = 0; i < G.n; i++) {    //初始化标记数组
        G.tags[i] = UNVISITED;
    }
    for (i = 0; i < G.n; i++) {    //依次检查所有顶点（可以遍历含有多个连通分量的无向图）
        if (UNVISITED == G.tags[i]) {
            if (ERROR == visit(i)) {
                return ERROR;
            }
            G.tags[i] = VISITED;
            EnQueue_LQ(Q, i);    //访问i顶点，并入队
            while (OK == DeQueue_LQ(Q, k)) {    //不断出队，直到队列为空（即遍历完一个连通分量）
                for (i = j = FirstAdjVex_UDG(G, k); j >= 0; j = NextAdjVex_UDG(G, k, j)) {
                    //依次判断k顶点的所有邻接顶点j，若未曾访问，则访问它，并让它入队
                    if (UNVISITED == G.tags[j]) {
                        if (ERROR == visit(j)) {
                            return ERROR;
                        }
                        G.tags[j] = VISITED;
                        EnQueue_LQ(Q, j);
                    }
                }
            }
        }
    }
    return OK;
}
//指令表
void command() {
    printf("1.创建无向图\n2.销毁无向图\n");
    printf("3.查找顶点的位序\n4.取无向图某一顶点的值\n");
    printf("5.对无向图的某一顶点赋值\n");
    printf("6.求无向图中某一顶点的第一个邻接顶点\n");
    printf("7.求无向图G中k顶点相对于m顶点的下一个邻接顶点的位序\n");
    printf("8.在无向图中增加其中两个顶点间的边\n");
    printf("9.删除无向图其中两个顶点间的边\n");
    printf("10.深度优先遍历无向图\n");
    printf("11.广度优先遍历无向图\n");
    printf("12.打印无向图（邻接矩阵）\n");
    printf("13.退出\n");
}
//判断点v是否在点集vexs中
Status isExist(VexType v, VexType * vexs, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (vexs[i] == v) {
            return TRUE;
        }
    }
    return FALSE;
}
//清除之前的输入
void clearInput() {
    char c = getchar();
    while (c != '\n') {
        c = getchar();
    }
}
int main() {
    int code;
    int exit = 0;
    UDG G;
    int n = -1;
    int e = -1;
    VexType *vexs;
    ArcInfo *arcs;
    int i, k, m;
    VexType v, w;
    Status hasCreateUDG = FALSE;    //标记是否创建了无向图
    printf("对于无向图的操作指令如下：\n");
    command();
    while(!exit) {
        code = -1;    //重置命令
        printf("请输入操作指令（输入序号即可，若想查看指令表，请输入0）：");
        scanf("%d", &code);
        switch (code) {
            //显示指令
            case 0:
                command();
                break;
            //创建无向图
            case 1:
                if (hasCreateUDG == TRUE) {    //如果之前创建过无向图，先销毁之前的
                    DestroyUDG(G);
                }
                printf("请输入顶点数：");
                scanf("%d", &n);
                while (n < 0) {
                    printf("输入错误！\n");
                    printf("请重新输入：");
                    scanf("%d", &n);
                } 
                printf("请输入顶点元素(元素指定为字符类型，");
                printf("输入一个后按下回车即可输入下一个)：\n");
                vexs = (VexType *)malloc(n * sizeof(VexType));
                for (i = 0; i < n; i++) {
                    clearInput();   //清除之前的输入
                    scanf("%c", &vexs[i]);
                }
                printf("请输入边数：");
                scanf("%d", &e);   
                while (e < 0) {
                    printf("输入错误！\n");
                    printf("请重新输入：");
                    scanf("%d", &e);
                }
                printf("请输入边(分别输入边的两端点，中间以空格隔开，");
                printf("输入一条边后按下回车即可输入下一条边)：\n");
                arcs = (ArcInfo *)malloc(e * sizeof(ArcInfo));
                for (i = 0; i < e; i++) {
                    clearInput();
                    scanf("%c %c", &v, &w);
                    //判断边的两点是否存在
                    while ((isExist(v, vexs, n) == FALSE) || (isExist(w, vexs, n) == FALSE) || v == w) {
                        printf("输入错误！请重新输入\n");
                        clearInput();
                        scanf("%c %c", &v, &w);
                    }
                    arcs[i].v = v;
                    arcs[i].w = w;
                }
                //如果创建无向图成功就打印出来
                if (OK == CreateUDG(G, vexs, n, arcs, e)) {
                    printf("创建成功，邻接矩阵如下（第一行是元素顺序）:\n");
                    PrintUDG(G);
                    hasCreateUDG = TRUE;    //设置标记
                } else {
                    printf("创建失败\n");
                }
                break;
            //销毁无向图
            case 2:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    if (OK == DestroyUDG(G)) {
                        printf("销毁成功\n");
                        hasCreateUDG = FALSE;    //设置标记
                    } else {
                        printf("销毁失败\n");
                    }
                }
                break;
            //查找顶点的位序
            case 3:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    clearInput();
                    printf("请输入要查找的顶点：");
                    scanf("%c", &v);
                    i = LocateVex_UDG(G, v);
                    if (i < 0) {
                         printf("图中不存在该顶点\n");
                    } else {
                        printf("顶点%c在图G的位序为%d\n", v, i);
                    }
                }
                break;
            //取无向图某一顶点的值
            case 4:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    k = -1;
                    clearInput();
                    printf("请输入该顶点的位序：");
                    scanf("%d", &k);
                    if (OK == GetVex_UDG(G, k, w)) {
                        printf("图G中%d顶点的值为%c\n", k, w);
                    } else {
                        printf("取值失败\n");
                    }
                }
                break;
            //对无向图的某一顶点赋值
            case 5:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    k = -1;
                    clearInput();
                    printf("对无向图G的k顶点赋值w, k和w分别为（中间用空格隔开）：");
                    scanf("%d %c", &k, &w);
                    if (OK == PutVex_UDG(G, k, w)) {
                        printf("赋值成功，图G中%d顶点的值为%c\n", k, w);
                    } else {
                        printf("赋值失败\n");
                    }
                }
                break;
            //求无向图中某一顶点的第一个邻接顶点
            case 6:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    k = -1;
                    clearInput();
                    printf("该顶点的位序为：");
                    scanf("%d", &k);
                    i = FirstAdjVex_UDG(G, k);
                    if (-1 != i) {
                        printf("无向图G的%d顶点的第一个邻接顶点的位序为%d\n", k, i);
                    } else {
                        printf("图中不存在该顶点或该点不存在邻接顶点\n");
                    }
                }
                break;
            //求无向图G中k顶点相对于m顶点的下一个邻接顶点的位序
            case 7:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    k = m = -1;
                    clearInput();
                    printf("m顶点为k顶点的邻接顶点,k和m分别为（中间用空格隔开）：");
                    scanf("%d %d", &k, &m);
                    i = NextAdjVex_UDG(G, k, m);
                    if (-1 != i) {
                        printf("无向图G中%d顶点相对于%d顶点的下一个邻接顶点的位序为%d\n", k, m, i);
                    } else {
                        printf("输入参数不合法或不存在符号要求的邻接顶点\n");
                    }
                }
                break;
            //在无向图中增加其中两个顶点间的边
            case 8:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    k = m = -1;
                    clearInput();
                    printf("在无向图G中增加k顶点到m顶点的边,k和m分别为（中间用空格隔开）：");
                    scanf("%d %d", &k, &m);
                    if (OK == AddArc_UDG(G, k, m)) {
                        printf("成功，可输入12查看新的无向图\n");
                    } else {
                        printf("失败，输入的参数不正确或该边已存在\n");
                    }
                }
                break;
            //删除无向图其中两个顶点间的边
            case 9:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    k = m = -1;
                    clearInput();
                    printf("在无向图G中删除k顶点到m顶点的边,k和m分别为（中间用空格隔开）：");
                    scanf("%d %d", &k, &m);
                    if (OK == RemoveArc_UDG(G, k, m)) {
                        printf("删除成功，可输入12查看新的无向图\n");
                    } else {
                        printf("删除失败，输入的参数不正确或该边不存在\n");
                    }
                }
                break;
            //深度优先遍历无向图
            case 10:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    if (OK == DFSTraverse_UDG(G)) {
                        printf("深度优先遍历成功\n");
                    } else {
                        printf("深度优先遍历失败\n");
                    }
                }
                break;
            //广度优先遍历无向图
            case 11:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    if (OK == BFSTraverse_UDG(G)) {
                        printf("广度优先遍历成功\n");
                    } else {
                        printf("广度优先遍历失败\n");
                    }
                }
                break;
            //打印无向图（邻接矩阵）
            case 12:
                if (hasCreateUDG == FALSE) {
                    printf("您还未创建无向图！请先输入1创建无向图。\n");
                } else {
                    PrintUDG(G);
                }
                break;
            //退出
            case 13:
                exit = 1;
                break;
            default:
                printf("无效的操作指令，请重新输入！\n");
        }
    }
    printf("程序结束！\n");
    return 0;
}