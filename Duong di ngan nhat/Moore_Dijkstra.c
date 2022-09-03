# include <stdio.h>

# define MAX_N 20
# define NO_EDGE -1
# define oo 999999

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
            pG->A[i][j] = NO_EDGE;
        }
    }
}

//  them cung vao do thi
void addEdge(Graph *pG, int x, int y, int w){
    pG->A[x][y] = w;
    pG->A[y][x] = w;
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
    freopen("test.txt", "r", stdin);
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

int mark[MAX_N]; // danh dau 1 dinh da tim duoc dg di ngan nhat hay chua
int pi[MAX_N]; // luu tru tong chi phi khi di den 1 dinh
int p[MAX_N]; // luu tru dinh cha cua 1 dinh

void Dijkstra(Graph *pG, int s){
    int u, v, it;
    for (u=1; u <= pG->n; u++){
        pi[u] = oo;
        mark[u] = 0;
    }

    pi[s] = 0;
    p[s] = -1;

    for (it=1; it < pG->n; it++){
        int j, min_pi = oo;
        for (j=1; j <= pG->n; j++){
            if (mark[j] == 0 && pi[j] < min_pi){
                min_pi = pi[j];
                u = j;
            }
        }

        mark[u] = 1;

        for (v=1; v <= pG->n; v++){
            if (pG->A[u][v] != NO_EDGE && mark[v] == 0){
                if (pi[u] + pG->A[u][v] < pi[v]){
                    pi[v] = pi[u] + pG->A[u][v];
                    p[v] = u;
                }
            }
        }
    }

    for (u=1; u <= pG->n; u++){
        printf("pi[%d] = %d, p[%d] = %d\n", u, pi[u], u, p[u]);
    }
}

// in duong di tu dinh 1 den dinh u
void printPath(Graph *pG, int u){
    int path[MAX_N], k = 0, current = u, i;

    while (current != -1){
        path[k] = current;
        k++;
        current = p[current];
    }

    for (i=k-1; i >= 0; i--){
        printf("%d ", path[i]);
    }
    printf("\n");
}

int main(){
    Graph G;
    readGraph(&G);
    Dijkstra(&G, 1);
    return 0;
}