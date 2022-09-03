# include <stdio.h>

# define MAX_N 100

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

typedef struct{
    int data[MAX_N];
    int front, rear;
}Queue;

void makenullQueue(Queue *pQ){
	pQ->front = 0;
	pQ->rear = -1;
}

int emptyQueue(Queue Q){
	return Q.front > Q.rear;
}

void pushQueue(Queue *pQ, int x){
    pQ->rear++;
    pQ->data[pQ->rear] = x;
}

int top(Queue Q){
    return Q.data[Q.front];
}

void pop(Queue *pQ){
    pQ->front++;
}

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
    printf("\n");
}

// thuat toan sap xep topo
void topoSort(Graph *pG, List *L){
	int d[MAX_N], u, x, v;
	
	// tinh bao vao cua moi dinh
	for (u=1; u <= pG->n; u++){
		d[u] = 0;
		for (x=1; x <= pG->n; x++){
			if (pG->A[x][u] != 0)
				d[u]++;
		}
	}

	Queue Q;
	makenullQueue(&Q);
	/* dua cac dinh co bac vao la 0 
	vao hang doi */
	for (u=1; u <= pG->n; u++)
		if (d[u] == 0)
			pushQueue(&Q, u);

	makeNullList(L);
	/* vong lap thuc hien sap xep cac dinh */
	while (!emptyQueue(Q)){
		int u = top(Q);
		pop(&Q);
		pushBack(L, u);
		for (v=1; v <= pG->n; v++){
			if (pG->A[u][v] != 0){
				d[v]--;
				if (d[v] == 0)
					pushQueue(&Q, v);
			}
		}
	}
}

int main(){
    Graph G;
    List result;
	readGraph(&G);
	topoSort(&G, &result);
	int i;
	for (i=1; i <= G.n; i++)
		printf("%d\n", elementAt(&result, i));
    return 0;
}