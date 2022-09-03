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
    pL->A[pL->size++] = x;
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
    // pG->A[y][x] = 1;
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
    return (pG->A[x][y] == 1);
}

// in cac dinh ke voi dinh x
List neighbours(Graph *pG, int x){
    List L;
    makeNullList(&L);
    int y;
    for (y=1; y <= pG->n; y++){
        if (pG->A[x][y] == 1){
            pushBack(&L, y);
        }
    }

    return L;
}

void readGraph(Graph *pG){
    // freopen("test.txt", "r", stdin);
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
	pS->data[pS->size++] = x;
}

int top(Stack S){
	return S.data[S.size-1];
}

void pop(Stack *pS){
	pS->size--;
}

int num[MAX_N], min_num[MAX_N];
int k;
Stack S;
int on_stack[MAX_N];

void SCC(Graph *pG, int u){
    //1. Đánh số u, đưa u vào ngăn xếp S
    num[u] = min_num[u] = k;
    k++;
    push(&S, u);
    on_stack[u] = 1;
    int v;
    //2. Xét các đỉnh kề của u
    for (v = 1; v <= pG->n; v++) {
        if (adjacent(pG, u, v)) {
            if (num[v] < 0) {
                SCC(pG, v);
                min_num[u] = min_num[u] < min_num[v]?min_num[u]:min_num[v];
            }
            else if (on_stack[v])
                min_num[u] = min_num[u] < num[v]?min_num[u]:num[v];
        }
    }
    //3. Kiểm tra u có phải là đỉnh khớp
    if (num[u] == min_num[u]){
        int w;
        do { //Lấy các đỉnh trong S ra cho đến khi gặp u
            w = top(S);
            pop(&S);
            on_stack[w] = 0;
        }while (w != u);
    }
}

int main(){
    Graph G;
    readGraph(&G);
    int u;
    for (u=1; u <= G.n; u++)
        num[u] = -1;
    k = 1;
    makenullStack(&S);
    for (u=1; u <= G.n; u++){
        if (num[u] == -1)
            SCC(&G, u);
    }

    for (u=1; u <= G.n; u++)
        printf("%d %d\n", num[u], min_num[u]);
    return 0;
}