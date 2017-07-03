#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int value;
	int depth;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
} AdjList;

typedef struct {
	int v;
	AdjList *array;
} Graph;

Graph *createGraph(int vertices);
Node *makeNewNode(int val);
void addEdge(Graph *graph, int person1, int person2);
void freeAll(Graph *graph, int *array, int vertices);
void bfs(Graph *graph, int numNodes, int numVertices, int startingNode, int *depthArray);
void printInfo(int *depthArray, int arraySize);
void makeDepthInfo(int *numPerDepth, int *depthPerVertix, int numVertices);

int main() {
	Graph *graph = NULL;
	int people, collab, erdos, i, p1, p2;
	scanf("%d %d\n%d", &people, &collab, &erdos);
	int *perDepthInfo = (int *)calloc(people + 1, sizeof(int));
	graph = createGraph(people);
	for(i = 0; i < collab; i++) { 
		scanf("%d %d", &p1, &p2);
		addEdge(graph, p1, p2);
	}
	bfs(graph, 2 * collab, people, erdos, perDepthInfo);
	printInfo(perDepthInfo, people + 1);
	freeAll(graph, perDepthInfo, people);
	return 0;
}

Graph *createGraph(int vertices) {
	int i;
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	graph->v = vertices;
	graph->array = (AdjList *)malloc(sizeof(AdjList) * (vertices + 1));

	for(i = 0; i <= vertices; i++)
		graph->array[i].head = NULL;

	return graph;
}

Node *makeNewNode(int val) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->value = val;
	return newNode;
}

void addEdge(Graph *graph, int person1, int person2) {
	Node *newNode = makeNewNode(person1);
	newNode->next = graph->array[person2].head;
	graph->array[person2].head = newNode;

	newNode = makeNewNode(person2);
	newNode->next = graph->array[person1].head;
	graph->array[person1].head = newNode;
}

void freeAll(Graph *graph, int *array, int vertices) {
	int i;
	Node *aux = NULL, *next = NULL;
	for(i = 0; i <= vertices; i++)
		for(aux = graph->array[i].head; aux != NULL; aux = aux->next)
			free(aux);
	free(graph->array);
	free(graph);
	free(array);
}

void bfs(Graph *graph, int numNodes, int numVertices, int startingNode, int *depthArray) {
	int *queue = (int *)malloc(sizeof(int) * (numNodes + 1));
	int *visited = (int *)calloc(numVertices + 1, sizeof(int));
	int *depth = (int *)malloc(sizeof(int) * (numVertices + 1));
	int front = -1, rear = 0, curr;
	Node *aux = NULL;

	depth[startingNode] = 0;
	queue[0] = startingNode;
	visited[startingNode] = 1;

	while(front != rear) {
		curr = queue[++front];
		aux = graph->array[curr].head;

		while(aux != NULL) {
			if(visited[aux->value] == 0) {
				queue[++rear] = aux->value;
				visited[aux->value] = 1;
				depth[aux->value] = depth[curr] + 1;
			}
			aux = aux->next;
		}
	}
	free(queue);
	free(visited);
	makeDepthInfo(depthArray, depth, numVertices);
	free(depth);
} 

void printInfo(int *depthArray, int arraySize) {
	int maxDepth = depthArray[0], i;
	printf("%d\n", maxDepth);
	for(i = 1; i <= maxDepth; i++)
		printf("%d\n", depthArray[i]);
}

void makeDepthInfo(int *numPerDepth, int *depthPerVertix, int numVertices) {
	int maxDepth = 0, i;
	for(i = 1; i <= numVertices; i++) {
		numPerDepth[depthPerVertix[i]]++;
		if(depthPerVertix[i] > maxDepth)
			maxDepth = depthPerVertix[i];
	}
	numPerDepth[0] = maxDepth;
}