#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct node;
typedef struct node* p_node;

typedef struct node{
    int num;
    p_node L;
    p_node R;
}_node;

int generateRand();
p_node addNode(p_node, p_node);
p_node createNode(int);
void printInOrder(p_node);
int bufferSize(FILE*);
char* createBuffer(FILE*, int);
void removeNumbers(p_node, char*);
p_node delete(p_node, int);
p_node findMin(p_node);
p_node findMax(p_node);

int main()
{
    p_node root = NULL;
    int i;
    int broj;
    FILE* fp;
    char* buffer = NULL;
    int buffer_size = 0;
    srand(time(0));
    p_node new_node;

    for( i = 0; i < 100; i++){
       broj = generateRand();
       new_node = createNode(broj);
       root = addNode(root, new_node);
    }

    printInOrder(root);

    fp = fopen("datoteka.txt", "r");
    buffer_size = bufferSize(fp);
    buffer = createBuffer(fp, buffer_size);

    removeNumbers(root, buffer);
    //printInOrder(root);
    fclose(fp);
    
    return 0;
}

p_node delete(p_node root, int num)
{
     if (root == NULL)
        return root;
 
    // If the num to be deleted is 
    // smaller than the root's
    // num, then it lies in L subtree
    if (num < root->num)
        root->L = delete(root->L, num);
 
    // If the num to be deleted is
    // greater than the root's
    // num, then it lies in R subtree
    else if (num > root->num)
        root->R = delete(root->R, num);
 
    // if num is same as root's num, then This is the node
    // to be deleted
    else {
        
        // node with only one child or no child
        if (root->L == NULL) {
            struct node* temp = root->R;
            free(root);
            return temp;
        }
        else if (root->R == NULL) {
            struct node* temp = root->L;
            printf("brisem %d   \n", root->num);
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the R subtree)
        struct node* temp = findMin(root->R);
 
        // Copy the inorder successor's content to this node
        root->num = temp->num;
 
        // Delete the inorder successor
        root->R = delete(root->R, temp->num);
    }
    return root;
}

p_node findMax(p_node current)
{
    while(current->R != NULL){
        current = current->R;
    }
    
    return current;
}

p_node findMin(p_node current)
{
    while(current->L != NULL){
        current = current->L;
    }

    return current;
}

void removeNumbers(p_node root, char* buffer)
{
    int n = 0;
    int r = 0;
    int broj = 0;

    while( r != -1){
        r = sscanf(buffer,"%d%n", &broj, &n);

        if( r == -1){
            puts("Greska/kraj datoteke!");
        }
    
        if( r == 1){
            printf("Ucitan broj %d\n", broj);
            delete(root, broj);
        }

        buffer += n;
    
    }
}



char* createBuffer(FILE* fp, int buffer_size)
{
    char* buffer = (char*)calloc(sizeof(char), buffer_size + 10);

    fread(buffer,1,buffer_size, fp);

    //printf("Ispis buffera: %s\n", buffer);
    
    return buffer;
}

int bufferSize(FILE* fp)
{
    int buffer_size = 0;

    fseek(fp,0,SEEK_END);
    buffer_size = ftell(fp);
    rewind(fp);
    printf("Velicina buffera je: %d\n", buffer_size);
    
    return buffer_size;
}

void printInOrder(p_node current)
{
    if(current == NULL)
        return;

    printInOrder(current->L);
    printf("%d\n", current->num);
    printInOrder(current->R);
    
    return;
}

p_node addNode(p_node current, p_node new_node)
{
    if(current == NULL)
        return new_node;

    else if(current->num > new_node->num)
        current->L = addNode(current->L, new_node);

    else if(current->num < new_node->num)
        current->R = addNode(current->R, new_node);
    
    return current;
}

p_node createNode(int broj)
{
    p_node new_node = (p_node)malloc(sizeof(int));
    new_node->num = broj;
    new_node->L = NULL;
    new_node->R = NULL;

    return new_node;
}

int generateRand()
{
    int randNum = rand() % (700 - 300 + 1) + 300;

    //printf("Generiran broj %d\n", randNum);
    return randNum;
}
