# include <stdio.h>

# define MAX_N 100
# define MAX_M 500

// khai bao ma tran dinh - cung
typedef struct{
    int A[MAX_N][MAX_M];
    int n, m; // n: so dinh, m: so cung
}Graph;

// khoi tao ma tran
void initGraph(Graph *pG, int n, int m){
    pG->n = n;
    pG->m = m;

    int i, j;
    for (i=1; i <= n; i++){
        for (j=1; j <= m; j++){
            pG->A[i][j] = 0;
        }
    }
}

// them cung
void addEdge(Graph *pG, int e, int x, int y){
    pG->A[x][e] = 1;
    pG->A[y][e] = 1;
}

// tinh bac cua dinh x
int degree(Graph *pG, int x){
    int degree = 0, e;
    for (e=1; e <= pG->m; e++){
        if (pG->A[x][e] == 1){
            degree++;
        }
    }

    return degree;
}

// kiem tra 2 dinh co ke nhau khong
int adjacent(Graph* pG, int x, int y){
    int e;
    for (e=1; e <= pG->m; e++){
        if (pG->A[x][e] == 1 && pG->A[y][e] == 1){
            return 1;
        }
    }

    return 0;
}

// in cac dinh ke voi dinh x
void neighbours(Graph *pG, int x){
    int y;
    for (y=1; y < pG->n; y++){
        if (adjacent(pG, y, x) == 1 && x != y){
            printf("%d ", y);
        }
    }
}

// in ma tran dinh - cung
void printGraph(Graph *pG){
    int i, j;
    for (i=1; i <= pG->n; i++){
        for (j=1; j <=pG->m; j++){
            printf("%d ", pG->A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    Graph G;
    initGraph(&G, 4, 4);
    addEdge(&G, 1, 1, 2);
    addEdge(&G, 2, 2, 3);
    addEdge(&G, 3, 2, 4);
    addEdge(&G, 4, 3, 4);
    printGraph(&G);
    
    return 0;
}