# include <stdio.h>

# define MAX_N 20
# define oo 999999

// tao kieu "Cung"
typedef struct{
    int u, v, w;
}Edge;

// khai bao kieu do thi (ap dung cho don do thi vo huong)
typedef struct{
    Edge edges[MAX_N];
    int n, m; // n: so dinh, m: so cung
}Graph;

// khoi tao danh sach cung
void initGraph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
}

// them cung
void addEdge(Graph *pG, int x, int y, int w){
    Edge temp;
    temp.u = x;
    temp.v = y;
    temp.w = w;
    pG->edges[pG->m] = temp;
    pG->m++;
}

// tinh bac cua 1 dinh
int degree(Graph *pG, int x){
    int degree = 0, i;
    for (i=0; i < pG->m; i++){
        if (pG->edges[i].u == x)
            degree++;
        if (pG->edges[i].v == x)
            degree++;
    }

    return degree;
}

// kiem tra 2 dinh co ke nhau khong
int adjacent(Graph *pG, int x, int y){
    int i;
    for (i=0; i < pG->m; i++){
        if ((pG->edges[i].u == x && pG->edges[i].v == y) || (pG->edges[i].u == y && pG->edges[i].v == x)){
            return 1;
        }
    }

    return 0;
}

// in cac dinh ke voi dinh x
void neighbours(Graph *pG, int x){
    int i;
    for (i=0; i < pG->m; i++){
        if (pG->edges[i].u == x)
            printf("%d ", pG->edges[i].v);
        else if (pG->edges[i].v == x)
            printf("%d ", pG->edges[i].u);
    }
    printf("\n");
}

// doc du lieu tu tap tin
void readGraph(Graph *pG){
    int n, m, u, v, w, i;
    // freopen("test.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    initGraph(pG, n);
    for (i=0; i < m; i++){
        scanf("%d %d %d", &u, &v, &w);
        addEdge(pG, u, v, w);
    }
}

// in do thi
void printGraph(Graph *pG){
    int i;
    for (i=0; i < pG->m; i++){
        printf("Cung %d: (%d, %d, %d)\n", i+1, pG->edges[i].u, pG->edges[i].v, pG->edges[i].w);
    }
}

int pi[MAX_N]; // luu tru chi phi duong di
int p[MAX_N]; // luu tru dinh cha
int circle, c = -1;

void BellmanFord(Graph *pG, int s){
    int u, v, w, it, k, i = 0, n = 0, c = -1;
    for (u=1; u <= pG->n; u++){
        pi[u] = oo;
    }

    pi[s] = 0;
    p[s] = -1;

    for (it=1; it < pG->n; it++){
        for (k=0; k < pG->m; k++){
            u = pG->edges[k].u;
            v = pG->edges[k].v;
            w = pG->edges[k].w;

            if (pi[u] == oo)
                continue;
            if (pi[u] + w < pi[v]){
                pi[v] = pi[u] + w;
                p[v] = u;
            }
        }
    }

    // for (u=1; u <= pG->n; u++){
    //     printf("pi[%d] = %d, p[%d] = %d\n", u, pi[u], u, p[u]);
    // }

    for (k=0; k < pG->m; k++){
        u = pG->edges[k].u;
        v = pG->edges[k].v;
        w = pG->edges[k].w;
        if (pi[u] + w < pi[v]){
            circle = 1;
            c = v;
            break;
        }
    }
}

void printPath(Graph *pG, int c){
    if (c != -1){
        int i, v, path[MAX_N], k = 0;

        for (i=0; i < pG->n; i++)
            c = p[c];
        v = c;
        while(1){
            path[k] = v;
            k++;
            if (v == c && k > 1)
                break;
            v = p[v];
        }
    }
    else
        printf("-1\n");
}

int main(){
    Graph G;
    circle = 0;
    int s;
    readGraph(&G);
    scanf("%d", &s);
    BellmanFord(&G, s);
    return 0;
}