# include <stdio.h>

# define MAX_N 20
# define MAX_LENGTH 20
# define NO_COLOR 0
# define RED 1
# define BLUE 2

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

int color[MAX_N];
int conflict;
void colorize(Graph *pG, int u, int c){
    color[u] = c;

    int v;
    for (v=1; v <= pG->n; v++){
        if (adjacent(pG, u, v)){
            if (color[v] == NO_COLOR)
                colorize(pG, v, 3-c);
            else if (color[v] == color[u])
                conflict = 1;
        }
    }
}

int main(){
    Graph G;
    readGraph(&G);
    
    int i;
    for (i=1; i <= G.n; i++){
        color[i] = NO_COLOR;
    }
    conflict = 0;
    for (i=1; i <= G.n; i++){
        if (color[i] == NO_COLOR)
            colorize(&G, i, BLUE);
    }

    if (conflict)
        printf("NO\n");
    else
        printf("YES\n");
    return 0;
}