# include <stdio.h>

# define MAX_N 20

typedef struct{
    int data[MAX_N];
    int size;
}List;

// khoi tao danh sach
void makeNullList(List *pL){
    pL->size = 0;
}

// them p.tu vao cuoi danh sach
void pushBack(List *pL, int x){
    pL->data[pL->size++] = x;
}

// tra ve gia tri cua p.tu tai vi tri p
int elementAt(List *pL, int p){
    return pL->data[p-1];
}

// tra ve kich thuoc cua danh sach
int size(List *pL){
    return pL->size;
}

// sao chep danh sach 2 sang danh sach 1
void copyList(List *S1, List *S2){
	makeNullList(S1);
	int i, u;
	for (i=1; i <= S2->size; i++){
		u = elementAt(S2, i);
		pushBack(S1, u);
	}
}

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
void addEdge(Graph *pG, int x, int y){
    pG->A[x][y] = 1;
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
    return (pG->A[x][y] == 1);
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

// thuat toan xep hang do thi
int rank[MAX_N];
List topo;
void ranking(Graph *G){
	int d[MAX_N];
	int x, u;
	for (u=1; u <= G->n; u++)
		d[u] = 0;

	for (x=1; x <= G->n; x++){
		for (u=1; u <= G->n; u++)
			if (adjacent(G, x, u))
				d[u]++;
	}

	List S1, S2;
	makeNullList(&S1);

	for (u=1; u <= G->n; u++){
		if (d[u] == 0)
			pushBack(&S1, u);
	}

	int k = 1, i;
	while (S1.size > 0){
		makeNullList(&S2);
		for (i=1; i <= S1.size; i++){
			int u = elementAt(&S1, i);
			rank[u] = k;
			pushBack(&topo, u);
			int v;
			for (v=1; v <= G->n; v++){
				if (adjacent(G, u, v)){
					d[v]--;
					if (!d[v])
						pushBack(&S2, v);
				}
			}
		}
		copyList(&S1, &S2);
		k++;
	}
}

// doc do thi
void readGraph(Graph *pG){
	freopen("test.txt", "r", stdin);
    int n, m, u, v, i;
    scanf("%d %d", &n, &m);
    initGraph(pG, n);

    for (i=0; i < m; i++){
        scanf("%d %d", &u, &v);
        addEdge(pG, u, v);
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
}

int main(){
    Graph G;
	makeNullList(&topo);
	readGraph(&G);
	ranking(&G);
	// in cac dinh theo xep hang
	int i;
	for (i=1; i <= topo.size; i++){
		printf("%d - %d\n", elementAt(&topo, i), rank[elementAt(&topo, i)]);
	}
    return 0;
}