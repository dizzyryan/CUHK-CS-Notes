#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNODES 105
#define QUEUESIZE 10000

int adj[MAXNODES][MAXNODES];
int color[MAXNODES];
int queue[QUEUESIZE];
int front, rear;

void enqueue(int x) {
	queue[rear++] = x;
}

int dequeue() {
	return queue[front++];
}

int isEmpty() {
	return front == rear;
}

int bfs(int start, int n) {
	enqueue(start);
	color[start] = 1;

	while (!isEmpty()) {
		int node = dequeue();
		for (int i = 1; i <= n; ++i) {
			if (adj[node][i]) {
				if (color[i] == 0) {
					color[i] = -color[node];
					enqueue(i);
				}
				else if (color[i] == color[node]) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int is_bipartite(int n) {
	memset(color, 0, sizeof(color));
	for (int i = 1; i <= n; ++i) {
		if (color[i] == 0) {
			front = rear = 0;  // reset queue
			if (!bfs(i, n)) 
				return 0;
		}
	}
	return 1;
}

int main() {
	int cases;
	scanf("%d", &cases);

	while (cases--) {
		int n;
		scanf("%d", &n);
		memset(adj, 0, sizeof(adj));

		int u, v;
		while (1) {
			scanf("%d", &u);
			if (u == -1) 
				break;
			scanf("%d", &v);
			adj[u][v] = adj[v][u] = 1;
		}

		if (is_bipartite(n))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
