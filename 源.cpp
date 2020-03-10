#include <stdio.h>
#include <stdlib.h>
#define N 8 // ¶¥µãÊý
#define INF 999

int adj_arr[N][N] = { {0, 1, 2, INF, INF, INF, INF, INF},
					  {INF, 0, INF, 2, INF, INF, INF, INF},
					  {2, INF, 0, INF, INF,INF, INF,INF},
					  {INF, INF, 1, 0, INF, 8, INF, INF},
					  {INF, INF, INF, 2, 0, INF, 2, INF},
					  {INF, INF, INF, INF, 2, 0, INF, INF},
					  {INF, INF, INF, INF, INF, 3, 0, 3},
					  {INF, INF, INF, INF, INF, 2, INF, 0} };

void shortest_path(int start, int end);
void print_shortest_path(int * distance, int * path, int * used, int start, int end);

int main() {
	int start, end;
	printf("Input start & end: ");
	scanf_s("%d %d", &start, &end);
	shortest_path(start, end);

	return 0;
}

void shortest_path(int start, int end) {
	int distance[N];
	int path[N];
	int used[N] = { 0 };
	int i, j, min_node, min_dis, pass_flag = 0;
	for (i = 0; i < N; i++) {
		distance[i] = adj_arr[start][i];
		if (adj_arr[start][i] < INF) {
			path[i] = start;
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
				pass_flag++;
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

void print_shortest_path(int * distance, int * path, int * used, int start, int end) {
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

