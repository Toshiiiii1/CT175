# include <stdio.h>

# define MAX_N 20
# define oo 999999
# define NO_EDGE 0

// khai bao ma tran dinh - dinh (ap dung cho don do thi vo huong)
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
    // pG->A[y][x] = 1;
    pG->m += 1;
}

// tinh bac cua 1 dinh
int degree(Graph *pG, int x){
    int degree = 0, y;
    for (y=1; y <= pG->n; y++){
        degree += pG->A[x][y];
    }

    return degree;
}

// kiem tra dinh x & dinh y co ke nhau khong
int adjacent(Graph *pG, int x, int y){
    return (pG->A[x][y] == 1 || pG->A[y][x] == 1);
}

// in cac dinh ke voi dinh x
void neighbours(Graph *pG, int x){
    int y;
    for (y=1; y <= pG->n; y++){
        if (pG->A[x][y] != 0){
            printf("%d ", y);
        }
    }
}

// doc do thi
void readGraph(Graph *pG){
    int n, m, u, v, w, i;
    // freopen("test.txt", "r", stdin);
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

int pi[MAX_N][MAX_N];
int next[MAX_N][MAX_N];

void FloydWarshall(Graph *pG){
    int u, v, k;
    for (u=1; u <= pG->n; u++){
        for (v=1; v <= pG->n; v++){
            pi[u][v] = oo;
            next[u][v] = -1;
        }
    }

    for (u=1; u <= pG->n; u++)
        pi[u][u] = 0;

    for (u=1; u <= pG->n; u++){
        for (v=1; v <= pG->n; v++){
            if (pG->A[u][v] != NO_EDGE){
                pi[u][v] = pG->A[u][v];
                next[u][v] = v;
            }
        }
    }

    for (k=1; k <= pG->n; k++){
        for (u=1; u <= pG->n; u++){
            for (v=1; v <= pG->n; v++){
                if ((pi[u][k] + pi[k][v] < pi[u][v]) && (pi[u][k] != oo) && (pi[k][v] != oo)){
                    pi[u][v] = pi[u][k] + pi[k][v];
                    next[u][v] = next[u][k];
                }
            }
        }
    }
}

void printPath(Graph *pG){
    int i, j;
    for (i=1; i <= pG->n; i++){
        for (j=1; j <= pG->n; j++){
            printf("%d -> %d: ", i, j);
            if (pi[i][j] != oo)
                printf("%d\n", pi[i][j]);
            else
                printf("NO PATH\n");
        }
    }
}

int main(){
    Graph G;
    readGraph(&G);
    FloydWarshall(&G);
    printPath(&G);
    return 0;
}