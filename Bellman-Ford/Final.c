#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define FALSE 0
#define TRUE 1
 
typedef struct Edge {
    int src, dest, weight;
} Edge;
 
  
typedef struct Graph {
    int v, e;
    struct Edge* edge;
} Graph;
 

Graph* createGraph(int v, int e);
void bellmanFord(Graph* graph, int src);
void printInfo(int vector[], int n, int boolean[]);
void freeGraph(Graph* graph);

int main() {
    int vertices, edges, company, i, v1, v2;
    scanf("%d %d\n%d", &vertices, &edges, &company);
    Graph *graph = createGraph(vertices, edges);

    for(i = 0; i < edges; i++) { 
        scanf("%d %d %d", &v1, &v2, &graph->edge[i].weight);
        graph->edge[i].src = --v1;
        graph->edge[i].dest = --v2;
    }
    bellmanFord(graph, --company);
    freeGraph(graph);
    return 0;
}
 
Graph* createGraph(int v, int e) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->v = v;
    graph->e = e;
    graph->edge = (Edge*)malloc(graph->e*sizeof(Edge));
    return graph;
}
 
 
void printInfo(int vector[], int v, int boolean[]) {
    int i;
    for (i = 0; i < v; i++) {
        if (boolean[i] != FALSE){
            printf("%s\n", "I");
        }
        else if (vector[i] != INT_MAX) {
            printf("%d\n", vector[i]);
        }
        else {
        printf("%s\n", "U");
        }
    }
}

void bellmanFord(Graph* graph, int src) {
    int vert = graph->v, edg = graph->e;
    int distanceToSrc[vert], boolean[vert];
    int i, j, relaxed = TRUE, u, v, weight;

    for (i = 0; i < vert; i++) {
        distanceToSrc[i] = INT_MAX;
        boolean[i] = FALSE;
    }  
    distanceToSrc[src] = 0;
 
    for (i = 0; i < vert - 1 && relaxed == TRUE; i++) {
        relaxed = FALSE;
        for (j = 0; j < edg; j++) {
            u = graph->edge[j].src;
            v = graph->edge[j].dest;
            weight = graph->edge[j].weight;
            if (distanceToSrc[u] != INT_MAX && distanceToSrc[u] + weight < distanceToSrc[v]) {
                relaxed = TRUE;
                distanceToSrc[v] = distanceToSrc[u] + weight;
            }
        }
    }
    relaxed = TRUE;

    for (i = 0; i < vert - 1 && relaxed == TRUE; i++) {
        relaxed = FALSE;
        for (j = 0; j < edg; j++) {
            u = graph->edge[j].src;
            v = graph->edge[j].dest;
            weight = graph->edge[j].weight;

            if (distanceToSrc[u] != INT_MAX && distanceToSrc[u] + weight < distanceToSrc[v]){
                distanceToSrc[v] = distanceToSrc[u] + weight;
                boolean[v] = TRUE;
                boolean[u] = TRUE;
                relaxed = TRUE;
            }
        }
    }
	printInfo(distanceToSrc, vert, boolean);
}

void freeGraph(Graph* graph) {
    free(graph->edge);
    free(graph);
}