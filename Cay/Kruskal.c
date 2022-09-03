# include <stdio.h>

# define MAX_N 100

// tao kieu "Cung"
typedef struct{
    int u, v, w;
}Edge;

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
    pG->edges[pG->m++] = temp;
}

// doc du lieu tu tap tin
void readGraph(Graph *pG){
    int n, m, u, v, w, i;
    freopen("test.txt", "r", stdin);

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
        printf("(%d, %d)\n", pG->edges[i].u, pG->edges[i].v);
    }
}

void swap(Edge *x, Edge *y){
	Edge temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void bubbleSort(Graph *pG){
	int i, j;
	for (i = pG->m-1; i >=1; i--){
		for (j=0; j < i; j++){
			if (pG->edges[j].w > pG->edges[j+1].w){
				swap(&pG->edges[j], &pG->edges[j+1]);
			}
		}
	}
}

/* thuat toan Kruskal tim cay khung nho nhat */
int parent[MAX_N]; // luu dinh cha cua cac dinh

int findRoot(int u){
    while (parent[u] != u)
        u = parent[u];
    return u;
}

int Kruskal(Graph *pG, Graph *pT){
    /* sap xep cac cung 
    theo thu tu tang dan */
    bubbleSort(pG);
    initGraph(pT, pG->n);
    int i, total = 0, u, v, w, root_u, root_v;
    /* khoi tao dinh cha cua cac dinh */
    for (i=1; i <= pG->n; i++)
        parent[i] = i;

    /* thuc hien tim kiem cay
    khung nho nhat */
    for (i=0; i < pG->m; i++){
        u = pG->edges[i].u;
        v = pG->edges[i].v;
        w = pG->edges[i].w;
        root_u = findRoot(u);
        root_v = findRoot(v);
        if (root_u != root_v){
            addEdge(pT, u, v, w);
            parent[root_v] = root_u;
            total += w;
        }
    }

    return total;
}

int main(){
    Graph G, T;
    readGraph(&G);
    int sum = Kruskal(&G, &T), i;
    printf("%d\n", sum);
    for (i=0; i < T.m; i++){
        if (T.edges[i].u > T.edges[i].v)
            printf("%d %d %d\n", T.edges[i].v, T.edges[i].u, T.edges[i].w);
        else
            printf("%d %d %d\n", T.edges[i].u, T.edges[i].v, T.edges[i].w);
    }
    return 0;
}