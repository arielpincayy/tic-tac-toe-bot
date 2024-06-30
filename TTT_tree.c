#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node{
    char table[9];
    int win;
    struct node *father;
    struct node *next;
    struct node *child;
}Node;

typedef struct tree{
    Node *root;
}Tree;


Node *createNode(char table[]){
    Node *nnode;
    nnode = (Node *)malloc(sizeof(Node));
    if(nnode != NULL){
        nnode->father = NULL;
        nnode->next = NULL;
        nnode->child = NULL;
        for(int i=0; i<9; i++){
            nnode->table[i] = table[i];
        }
        nnode->win = 0;
    }
    return nnode;
}

void initializeTree(Tree *A){
    A->root = createNode((char[]){' ',' ',' ',' ',' ',' ',' ',' ',' '});
}

void printTable(char table[]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf(" %c ",table[(i*3)+j]);
            if(j!=2) printf("|");
        }
        printf("\n");
        if(i!=2){
            printf("------------");
            printf("\n");
        }
    }
}

Node *findTable(Node *current, char table[]){
    if(current==NULL) return NULL;
    Node *nnode = NULL;
    bool s = true;
    for(int i=0; i<9; i++){
        if(current->table[i] != table[i]){
            s = false;
            break;
        }
    }
    if(s) return current;
    if(current->child != NULL) nnode = findTable(current->child,table);
    if(nnode != NULL) return nnode;
    if(current->next != NULL) nnode = findTable(current->next,table);
    return nnode;
}

Node *player_turn(Node *father){
    char table[9];
    int pos = 0;
    scanf("%i",&pos);
    if(pos<0 || pos>8){
        printf("Gracioso? >:c");
        return NULL;
    }
    for(int i=0; i<9; i++){
        table[i] = father->table[i];
    }
    table[pos] = 'o';
    Node *turn_node = findTable(father,table);
    printTable(turn_node->table);
    return turn_node;
}

char winner(char table[]){
    for (int i = 0; i < 3; i++) {
        if (table[i * 3] != ' ' && table[i * 3] == table[i * 3 + 1] && table[i * 3 + 1] == table[i * 3 + 2]) return table[i * 3];
        if (table[i] != ' ' && table[i] == table[i + 3] && table[i + 3] == table[i + 6]) return table[i];
    }
    if (table[0] != ' ' && table[0] == table[4] && table[4] == table[8]) return table[0];
    if (table[2] != ' ' && table[2] == table[4] && table[4] == table[6]) return table[2];
    return ' ';
}


int createTables(Node *father, char turn){
    Node *nnode = NULL;
    char w = winner(father->table);
    if(w=='o'){
        father->win = -1;
        return -1;
    }else{
        if(w=='x'){
            father->win = 1;
            return 1;
        }
    }

    bool isFull = true;
    for (int i = 0; i < 9; i++) {
        if (father->table[i] == ' ') {
            isFull = false;
            break;
        }
    }
    if (isFull) {
        father->win = 0;
        return 0;
    }

    int min = 1;
    int max = -1;
    for(int i=0; i<9;i++){
        if(father->table[i]==' '){
            nnode = createNode(father->table);
            nnode->table[i] = turn;
            nnode->father = father;
            nnode->next = father->child;
            father->child = nnode;
            char nextTurn = turn;
            if(nextTurn =='x'){
                nextTurn = 'o';
            }else{
                nextTurn = 'x';
            } 
            int value = createTables(nnode,nextTurn);
            if(turn=='x'){
                if(value > max) max = value;
            }else{
                if(value < min) min = value;
            }
        }
    }
    father->win = (turn == 'x')? max:min;
    return father->win;
}

Node *responseMachine(Node *father){
    Node *ptr = father->child;
    if(ptr==NULL) return NULL;
    Node *max = NULL;
    int maxValue = -2;
    while(ptr != NULL){
        if(ptr->win > maxValue){
            max = ptr;
            maxValue = ptr->win;
        }
        ptr = ptr->next;
    }
    printTable(max->table);
    return max;
}

void match(Tree *A){
    Node *turn = A->root;
    char s = 0;
    while(true){
        printf("Player\n");
        turn = player_turn(turn);
        s = winner(turn->table);
        if(s=='x' || s=='o'){
            printf("End");
            break;
        }
        printf("Computer\n");
        turn = responseMachine(turn);
        if(turn==NULL){
            printf("Draw\n");
            return;
        }
        s = winner(turn->table);
        if(s=='x' || s=='o'){
            printf("End");
            break;
        }
    }
}

int main(void){
    Tree A;
    initializeTree(&A);
    createTables(A.root,'o');
    printf("Suceed\n");
    match(&A);
    return 0;
}