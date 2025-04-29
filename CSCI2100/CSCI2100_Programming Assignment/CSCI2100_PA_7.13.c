#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 505

int adj[MAXSIZE][MAXSIZE];
int indegree[MAXSIZE];
int result[MAXSIZE];
int queue[MAXSIZE];

void topoSort(int n) {
  int visited[MAXSIZE] = {0};
  int idx = 0;

  for (int count = 0; count < n; count++) {
    for (int u = 1; u <= n; u++) {
      if (!visited[u] && indegree[u] == 0) {
        visited[u] = 1;
        result[idx++] = u;

        for (int v = 1; v <= n; v++) {
          if (adj[u][v]) {
            indegree[v]--;
          }
        }
        break;
      }
    }
  }
}

int main() {
  int cases;
  scanf("%d", &cases);

  while (cases--) {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    memset(adj, 0, sizeof(adj));
    memset(indegree, 0, sizeof(indegree));

    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d %d", &a, &b);
      if (!adj[a][b]) {
        adj[a][b] = 1;
        indegree[b]++;
      }
    }
    topoSort(n);
    for (int i = 0; i < n; i++) {
      printf("%d", result[i]);
      if (i != n - 1) printf(" ");
    }
    printf("\n");
  }
  return 0;
}