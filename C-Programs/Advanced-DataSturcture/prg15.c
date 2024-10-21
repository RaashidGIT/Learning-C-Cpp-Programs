// Objective: Implementation of a graph and graph traversal algorithms (BFS and DFS)

#include <stdio.h>
#include <stdlib.h>
#define MAX 20

void add(int item);
int delete();
void bfs(int s, int n);
void dfs(int x, int visited[], int adj[][MAX], int n);
void create_graph();
void display();
void insert_node();
void delete_node(int u);
void insert_edge(int u, int v);
void del_edge(int u, int v);

int adj[MAX][MAX] = {0}; 
int q[20], top = -1, front = -1, rear = -1, n;
int vis[MAX] = {0}; 
int visited[MAX] = {0}; 

void create_graph() {
    int i, max_edges, origin, destin;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    max_edges = n * (n - 1);
    for (i = 1; i <= max_edges; i++) {
        printf("Enter edge %d (Type 0 0 to quit): ", i);
        printf("\nFrom vertex: ");
        scanf("%d", &origin);
        printf("To vertex: ");
        scanf("%d", &destin);
        if (origin == 0 && destin == 0)
            break;
        if (origin > n || destin > n || origin <= 0 || destin <= 0) {
            printf("Invalid edge. Please enter valid vertices.\n");
            i--;
        } else {
            adj[origin][destin] = 1;
            printf("Edge added from %d to %d\n", origin, destin);
        }
    }
}

void display() {
    printf("\nAdjacency Matrix:\n");
    printf("   ");
    for (int j = 1; j <= n; j++)
        printf("%d ", j);
    printf("\n");

    for (int i = 1; i <= n; i++) {
        printf("%d: ", i);
        for (int j = 1; j <= n; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }
}

void insert_node() {
    n++;
    printf("Inserted node is %d\n", n);
    for (int i = 1; i <= n; i++) {
        adj[i][n] = 0; 
        adj[n][i] = 0;
    }
}

void delete_node(int u) {
    if (n == 0) {
        printf("Graph is empty\n");
        return;
    }
    if (u > n) {
        printf("This node is not present in the graph\n");
        return;
    }
    for (int i = u; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[j][i] = adj[j][i + 1]; // Shift columns left
        }
        for (int j = 1; j <= n; j++) {
            adj[i][j] = adj[i + 1][j]; // Shift rows up
        }
    }
    n--; // Reduce node count
    printf("Node %d deleted.\n", u);
}

void insert_edge(int u, int v) {
    if (u > n || v > n) {
        printf("Source or destination node does not exist\n");
        return;
    }
    adj[u][v] = 1; // Add edge
    printf("Edge added from %d to %d\n", u, v);
}

void del_edge(int u, int v) {
    if (u > n || v > n || adj[u][v] == 0) {
        printf("This edge does not exist\n");
        return;
    }
    adj[u][v] = 0; // Remove edge
    printf("Edge removed from %d to %d\n", u, v);
}

void add(int item) {
    if (rear == 19)
        printf("Queue full\n");
    else {
        if (rear == -1) {
            q[++rear] = item;
            front++;
        } else {
            q[++rear] = item;
        }
    }
}

int delete() {
    if ((front > rear) || (front == -1))
        return 0;
    else
        return q[front++];
}

void bfs(int s, int n) {
    int p, i;
    printf("BFS Traversal: ");
    add(s);
    vis[s] = 1;
    p = delete();
    while (p != 0) {
        printf("%d ", p);
        for (i = 1; i <= n; i++) {
            if (adj[p][i] != 0 && vis[i] == 0) {
                add(i);
                vis[i] = 1;
            }
        }
        p = delete();
    }
    printf("\n");
}

void dfs(int x, int visited[], int adj[][MAX], int n) {
    visited[x] = 1;
    printf("%d ", x);
    for (int j = 1; j <= n; j++) {
        if (adj[x][j] == 1 && visited[j] == 0)
            dfs(j, visited, adj, n);
    }
}

int main() {
    int choice, s;
    int origin, destin;
    create_graph();
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert a node\n");
        printf("2. Insert an edge\n");
        printf("3. Delete a node\n");
        printf("4. Delete an edge\n");
        printf("5. Display\n");
        printf("6. BFS\n");
        printf("7. DFS\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                insert_node();
                break;
            case 2:
                printf("Enter edge to be inserted (origin destination): ");
                scanf("%d %d", &origin, &destin);
                insert_edge(origin, destin);
                break;
            case 3:
                printf("Enter node to be deleted: ");
                scanf("%d", &origin);
                delete_node(origin);
                break;
            case 4:
                printf("Enter edge to be deleted (origin destination): ");
                scanf("%d %d", &origin, &destin);
                del_edge(origin, destin);
                break;
            case 5:
                display();
                break;
            case 6:
                printf("Enter source vertex for BFS: ");
                scanf("%d", &s);
                bfs(s, n);
                break;
            case 7:
                printf("DFS Traversal: ");
                for (int i = 1; i <= n; i++)
                    visited[i] = 0; // Reset visited for DFS
                for (int i = 1; i <= n; i++)
                    if (visited[i] == 0)
                        dfs(i, visited, adj, n);
                printf("\n");
                break;
            case 8:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}
