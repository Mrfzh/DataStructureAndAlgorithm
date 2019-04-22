#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define UNSELECTED 0
#define SELECTED 1
#define INFINITY INT_MAX

//邻接链表的结点类型
typedef struct AdjVexNode {
	int adjvex;		//邻接顶点在顶点数组中的位序
	struct AdjVexNode *nextArc;		//指向下一邻接顶点（相邻景点）
	float length;			//道路长度
} AdjVexNode;

//景点
typedef struct{
	int id;
	struct AdjVexNode *firstArc;	//邻接链表的头指针
} ScenicSpot;

//校园地图
typedef struct{
	ScenicSpot * spots;	//景点数组
	int n;				//景点数
	int * tags;			//标志数组，用于在图的遍历中标记顶点访问与否
} Map;

//迪杰斯特拉算法所需：存储路径信息
typedef struct {
	int prev;	//当前最短路径上该顶点的前驱顶点的位序
	float lowcost;	//当前最短路径的长度
} DistInfo;

//迪杰斯特拉算法：求地图M中从i景点到其他所有景点的最短路径，并由Dist返回
void Dijkstra(Map M, int i, DistInfo **Dist) {
	//定义元素个数为n的DistInfo数组
    *Dist = (DistInfo *)malloc(M.n * sizeof(DistInfo));	
    //初始化
    for (int j = 0; j < M.n; j++) {
        (*Dist)[j].lowcost = INFINITY;
        M.tags[j] = UNSELECTED;
    }
    //将从源点i引出的所有边存入Dist
    for (AdjVexNode *p = M.spots[i].firstArc; p != NULL; p = p ->nextArc) {
        (*Dist)[p ->adjvex].prev = i;
        (*Dist)[p ->adjvex].lowcost = p->length;
    }
    //设置源点i的Dist信息
    (*Dist)[i].prev = -1;
    (*Dist)[i].lowcost = 0;
    //求源点到其他顶点的最短路径
	int k, min;
    for (int m = 1; m < M.n; m++) {
        min = INFINITY;
        k = 0;	//k顶点满足：未被选择，且到该顶点的最短路径长度在所有未被选择的顶点中最短
        for (int j = 0; j < M.n; j++) {
            if (UNSELECTED == M.tags[j] && (*Dist)[j].lowcost < min) {
                k = j;
                min = (*Dist)[k].lowcost;
            }
        }
        M.tags[k] = SELECTED;	//将k顶点标记为已选择
        //遍历k顶点的邻接表
        for (AdjVexNode *p = M.spots[k].firstArc; p != NULL; p = p ->nextArc) {
            int j = p ->adjvex; //j是邻接顶点的位序
            if (UNSELECTED == M.tags[j] && (*Dist)[k].lowcost + p ->length < (*Dist)[j].lowcost) {
                //当i->k->j的距离小于当前i->j的最短路径时，更新Dist
                (*Dist)[j].lowcost = (*Dist)[k].lowcost + p ->length;
                (*Dist)[j].prev = k;
            }
        }
    }
}

int main() {

	return 0;
}
