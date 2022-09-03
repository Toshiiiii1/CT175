# include <stdio.h>

# define MAX_N 100
# define oo 999999
# define NO_EDGE 0

typedef struct{
    int A[MAX_N][MAX_N];
    // n: so dinh, m: so cung
    int n, m;
}Graph;

// khoi tao ma tran
void initGraph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;

    int i, j;
    for (i=1; i <= n; i++){
        for (j=1; j <= n; j++){
            pG->A[i][j] = 0;
        }
    }
}

//  them cung vao do thi
void addEdge(Graph *pG, int x, int y, int w){
    pG->A[x][y] = w;
    pG->A[y][x] = w;
    pG->m += 1;
}

// doc do thi
void readGraph(Graph *pG){
    freopen("test.txt", "r", stdin);
    int n, m, u, v, w, i;
    scanf("%d %d", &n, &m);
    initGraph(pG, n);

    for (i=0; i < m; i++){
        scanf("%d %d %d", &u, &v, &w);
        addEdge(pG, u, v, w);
    }
}

// in do thi
void printGraph(Graph *pG){
    int i, j;
    for (i=1; i <= pG->n; i++){
        for (j=1; j <= pG->n; j++){
            printf("%d ", pG->A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* thuat toan Prim */
int pi[MAX_N], p[MAX_N], mark[MAX_N];
int Prim(Graph *pG, Graph *pT, int s){
    int i, u, v, x;
    for (u=1; u <= pG->n; u++){
        pi[u] = oo;
        p[u] = -1;
        mark[u] = 0;
    }
    pi[s] = 0;
    for (i=1; i < pG->n; i++){
        int min_dist = oo;
        for (x=1; x <= pG->n; x++)
            if (mark[x] == 0 && pi[x] < min_dist){
                min_dist = pi[x];
                u = x;
            }
        mark[u] = 1;
        for (v=1; v <= pG->n; v++){
            if (pG->A[u][v] != NO_EDGE && pi[v] > pG->A[u][v]){
                pi[v] = pG->A[u][v];
                p[v] = u;
            }
        }
    }

    initGraph(pT, pG->n);
    int total = 0;
    for (u=1; u <= pG->n; u++){
        if (p[u] != -1){
            int w = pG->A[p[u]][u];
            addEdge(pT, p[u], u, w);
            total += w;
        }
    }

    return total;
}

int main(){
    Graph G, T;
    readGraph(&G);
    int total = Prim(&G, &T, 1), i, j;
    printf("%d\n", total);
    for (i=1; i <= T.n; i++){
        for (j=i; j <= T.n; j++)
            if (T.A[i][j] != NO_EDGE)
                printf("%d %d %d\n", i, j, T.A[i][j]);
    }
    return 0;
}