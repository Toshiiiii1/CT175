# include <stdio.h>

# define MAX_N 100
# define MAX_M 500

// khai bao danh sach cac dinh ke
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

// khai bao do thi
typedef struct{
    List A[MAX_M];
    int n, m; // n: so dinh, m: so cung
}Graph;

// khoi tao do thi (ap dung cho don do thi vo huong)
void initGraph(Graph *pG, int n, int m){
    pG->n = n;
    pG->m = m;
    List temp;
    
    int i;
    for (i=1; i <= n; i++){
        temp = pG->A[i];
        makeNullList(&temp);
    }
}

// them cung
void addEdge(Graph *pG, int x, int y){
    pushBack(&pG->A[x], y);
    pushBack(&pG->A[y], x);
}

// tinh bac cua dinh x trong do thi
int degree(Graph *pG, int x){
    return size(&pG->A[x]);
}

// kiem tra dinh x & dinh y co ke nhau khong
int adjacent(Graph *pG, int x, int y){
    int i;
    List temp = pG->A[x];

    for (i=1; i <= temp.size; i++){
        if (y == temp.data[i]){
            return 1;
        }
    }

    return 0;
}

// tra ve cac dinh ke voi dinh x
void neighbours(Graph *pG, int x){
    List temp = pG->A[x];
    int i;
    for (i=0; i < temp.size; i++){
        printf("%d ", temp.data[i]);
    }
}

// doc do thi
void readGraph(Graph *pG){
	int n, m, u, v, i;
	scanf("%d %d", &n, &m);
	initGraph(pG, n, m);

	for (i=1; i <= m; i++){
		scanf("%d %d", &u, &v);
		addEdge(pG, u, v);
	}
}

// in do thi
void printGraph(Graph *pG){
    int i, j;
    List temp;

    for (i=1; i <= pG->n; i++){
        temp = pG->A[i];
        printf("%d: ", i);
        for (j=0; j < temp.size; j++){
            printf("%d ", temp.data[j]);
        }
        printf("\n");
    }
}

int main(){
    Graph G;
    
    return 0;
}