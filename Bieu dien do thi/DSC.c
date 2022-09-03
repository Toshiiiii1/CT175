# include <stdio.h>

# define MAX_N 500

// tao kieu "Cung"
typedef struct{
    int u, v;
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
void addEdge(Graph *pG, int x, int y){
    Edge temp;
    temp.u = x;
    temp.v = y;
    pG->edges[pG->m++] = temp;
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
        if ((pG->edges[i].u == x && pG->edges[i].v == y) || 
			(pG->edges[i].u == y && pG->edges[i].v == x)){
            return 1;
        }
    }

    return 0;
}

// in cac dinh ke voi dinh x
void neighbours(Graph *pG, int x){
    int y;
    for (y=1; y <= pG->n; y++){
        if (adjacent(pG, x, y))
			printf("%d ", y);
    }
    printf("\n");
}

// doc du lieu tu tap tin
void readGraph(Graph *pG){
    int n, m, u, v, i;
    freopen("text.txt", "r", stdin);

    scanf("%d%d", &n, &m);
    initGraph(pG, n);
    for (i=0; i < m; i++){
        scanf("%d %d", &u, &v);
        addEdge(pG, u, v);
    }
}

// in do thi
void printGraph(Graph *pG){
    int i;
    for (i=0; i < pG->m; i++){
        printf("(%d, %d)\n", pG->edges[i].u, pG->edges[i].v);
    }
}

int main(){
    Graph G;
    
    return 0;
}