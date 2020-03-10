/*-------------------------------------------------------------
功能：求解从一个带权(权值大于0)有向图中的一点到另一点的最短路径
输入示例：
Input start & end: 0 5
输出示例：
The shortest length from 0 to 5 is: 22
The shortest path from 0 to 5 is:
0 -> 2 -> 3 -> 5
---------------------------------------------------------------
Author: Zhang Kaizhou
Date: 2019-3-9 18:04:39
--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#define N 8 // 顶点数
#define INF 999

int adj_arr[N][N] = { {0, 1, 2, INF, INF, INF, INF, INF},
					  {INF, 0, INF, 2, INF, INF, INF, INF},
					  {2, INF, 0, INF, INF,INF, INF,INF},
					  {INF, INF, 1, 0, INF, 8, INF, INF},
					  {INF, INF, INF, 2, 0, INF, 2, INF},
					  {INF, INF, INF, INF, 2, 0, INF, INF},
					  {INF, INF, INF, INF, INF, 3, 0, 3},
					  {INF, INF, INF, INF, INF, 2, INF, 0} }; // 用一个全局二维数组存储带权有向图的邻接矩阵

void shortest_path(int start, int end);
void print_shortest_path(int * distance, int * path, int * used, int start, int end);

int main() {
	int start, end;
	printf("Input start & end: ");
	scanf_s("%d %d", &start, &end);
	shortest_path(start, end);

	return 0;
}

void shortest_path(int start, int end) { // 基于Dijkstra算法的最短路径函数
	int distance[N]; // 用于存放起始点到其余各点的最短距离
	int path[N]; // 用于存放起始点到其余各点最短路径的前一个顶点
	int used[N] = { 0 }; // 用于标记该顶点是否已经找到最短路径
	int i, j, min_node, min_dis, pass_flag = 0;
	for (i = 0; i < N; i++) {
		distance[i] = adj_arr[start][i]; // 初始化距离数组
		if (adj_arr[start][i] < INF) {
			path[i] = start; // 初始化路径数组
		}
		else {
			path[i] = -1;
		}
	}
	used[start] = 1;
	path[start] = start;
	for (i = 0; i < N; i++) {
		min_dis = INF;
		for (j = 0; j < N; j++) {
			if (used[j] == 0 && distance[j] < min_dis) {
				min_node = j;
				min_dis = distance[j];
				pass_flag++; // 标记是否存在通路
			}
		}
		if (pass_flag != 0) {
			used[min_node] = 1;
			for (j = 0; j < N; j++) {
				if (used[j] == 0) {
					if (adj_arr[min_node][j] < INF && distance[min_node] + adj_arr[min_node][j] < distance[j]) {
						distance[j] = distance[min_node] + adj_arr[min_node][j];
						path[j] = min_node;
					}
				}
			}
		}
		else {
			printf("There is no path!\n");
			return;
		}
	}
	print_shortest_path(distance, path, used, start, end);
	return;
}

void print_shortest_path(int * distance, int * path, int * used, int start, int end) { // 输出最短路长并打印最短路径
	int i = 0, pre, inverse_path[N];
	printf("The shortest length from %d to %d is: %d\n", start, end, distance[end]);
	inverse_path[i] = end;
	pre = path[end];
	if (pre == -1) {
		printf("There is no path!\n");
	}
	else {
		while (pre != start) {
			inverse_path[++i] = pre;
			pre = path[pre];
		}
		inverse_path[++i] = start;
		printf("The shortest path from %d to %d is:\n", start, end);
		for (; i > 0; i--) {
			printf("%d -> ", inverse_path[i]);
		}
		printf("%d\n", inverse_path[i]);
	}
	return;
}

