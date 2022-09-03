# include <stdio.h>

# define MAX_N 20
# define MAX_LENGTH 20
# define MAX_ELEMENT 40

// khai bao danh sach
typedef struct{
    int A[MAX_LENGTH];
    int size;
}List;

// khoi tao danh sach
void makeNullList(List *pL){
    pL->size = 0;
}

// them p.tu vao cuoi danh sach
void pushBack(List *pL, int x){
    pL->A[pL->size] = x;
    pL->size++;
}

// tra ve gia tri cua p.tu tai vi tri p
int elementAt(List *pL, int p){
    return pL->A[p-1];
}

// tra ve kich thuoc cua danh sach
int size(List *pL){
    return pL->size;
}

// khai bao ma tran dinh - dinh
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
    pG->A[y][x] = 1;
    pG->m += 1;
}

// tinh bac cua 1 dinh
int degree(Graph *pG, int x){
    int degree = 0, y;
    for (y=1; y <= pG->n; y++){
        if (pG->A[x][y] == 1)
            degree++;
    }

    return degree;
}

// kiem tra dinh x & dinh y co ke nhau khong
int adjacent(Graph *pG, int x, int y){
    return (pG->A[x][y] == 1 || pG->A[y][x] == 1);
}

// in cac dinh ke voi dinh x
List neighbours(Graph *pG, int x){
    List L;
    makeNullList(&L);
    int y;
    for (y = pG->n; y >= 1; y--){
        if (adjacent(pG, x, y)){
            pushBack(&L, y);
        }
    }

    return L;
}

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

// khai bao ngan xep
typedef struct{
    int data[MAX_ELEMENT];
    int size;
}Stack;

void makenullStack(Stack *pS){
	pS->size = 0;
}

int emptyStack(Stack S){
	return S.size == 0;
}

void push(Stack *pS, int x){
	pS->data[pS->size] = x;
    pS->size++;
}

int top(Stack S){
	return S.data[S.size-1];
}

void pop(Stack *pS){
	pS->size--;
}

int mark[MAX_N];
// duyet do thi theo chieu sau
List DFS(Graph *pG, int x){
    Stack S;
    makenullStack(&S);
    push(&S, x);
    /* danh sach luu tru cac dinh
    da duoc duyet*/
    List L;
    makeNullList(&L);

    while (!emptyStack(S)){
        int u = top(S);
        pop(&S);
        if (mark[u] == 1)
            continue;
        pushBack(&L, u);
        mark[u] = 1;
        List neighbour = neighbours(pG, u);
        int i;
        for (i=1; i <= neighbour.size; i++){
            int v = elementAt(&neighbour, i);
            if (mark[v] == 0)
                push(&S, v);
        }
    }

    return L;
}

int main(){
    Graph G;
    readGraph(&G);
    
    // danh dau tat ca cac dinh trong do thi chua duoc duyet
    int i, j;
    for (i=1; i <= G.n; i++){
        mark[i] = 0;
    }

    // duyet tat ca cac dinh cua do thi
    for (i=1; i <= G.n; i++){
        if (mark[i] == 0){
            List L = DFS(&G, i);
            for (j=1; j <= L.size; j++)
                printf("Duyet: %d\n", elementAt(&L, j));
        }
    }
    return 0;
}