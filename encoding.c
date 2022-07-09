#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct Node{
    char data;
    int fq;
    struct Node * left;
    struct Node * right;
    int * code;
};



struct minheap{
    struct Node** array;
    int size;
    // int cap;
};

struct Node * createnode(char c,int fq){
    struct Node * newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->data = c;
    newnode->fq = fq;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

void swap(struct Node **n1,struct Node ** n2){
    // printf("Entered swap..");
    struct Node *t = *n1;
    *n1 = *n2; //
    *n2 = t; //
}

int max(int a, int b){
    if(a>=b){
        return a;
    }
    return b;
}

int getheight(struct Node * root){
    if(root==NULL){
        return 0;
    }
    return 1+max(getheight(root->left),getheight(root->right));
}

void heapify(struct minheap * heap , int i){
    // printf("Entered heapify..");
    int smallest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left<heap->size && heap->array[left]->fq<heap->array[smallest]->fq){
        smallest = left;
    }

    if(right<heap->size && heap->array[right]->fq<heap->array[smallest]->fq){
        smallest = right;
    }

    if(smallest!=i){
        swap(&heap->array[smallest],&heap->array[i]);
        heapify(heap,smallest);
    }
}


struct Node * findmin(struct minheap * heap){
    struct Node * mini = heap->array[0];
    heap->array[0] = heap->array[heap->size-1];
    heap->size-=1;  
    heapify(heap,0);
    return mini; 
}

void insertion(struct minheap *heap,struct Node * new){

    heap->size+=1; 

    int j = heap->size-1;
    while(j && heap->array[(j-1)/2]->fq>new->fq){
        swap(&heap->array[(j-1)/2],&heap->array[j]);
        j = (j-1)/2;
    }
    heap->array[j] = new;
}

struct Node * createminheaptree(char finalarrchr[],int finalarrfq[],int count){
    struct minheap * heap = (struct minheap*)malloc(sizeof(struct minheap));
    heap->size = count;
    heap->array = (struct Node**)malloc(count*sizeof(struct Node));

    for(int i=0;i<count;i++){
        heap->array[i] = createnode(finalarrchr[i],finalarrfq[i]);
    }

    int n = count-1;

    for(int i = (n-1)/2;i>=0;i--){
        heapify(heap,i);
    }


    while(heap->size!=1){
        struct Node *l = findmin(heap);
        struct Node *r = findmin(heap);
        struct Node * new = createnode('$',l->fq+r->fq);
        new->left = l;
        new->right = r;

        insertion(heap,new);
    }
    return findmin(heap);

}

void codes(struct Node * root,int arr[],int c,int height,int codearr[95][height]){
    if(root->left){
        arr[c] = 0;
        codes(root->left,arr,c+1,height,codearr);
    }
    if(root->right){
        arr[c] = 1;
        codes(root->right,arr,c+1,height,codearr);
    }
    if(root->left==NULL && root->right==NULL){
        int sum=0;
        printf("%c: ",root->data);
        int k = c-1;
        int pos = (int)(root->data);
        // printf("%d\n",k);
        root->code = (int*)malloc((c-1)*sizeof(int));
        for(int i=0;i<c;i++){
            // sum+= arr[i]*(pow(10,k));
            // printf("%d ",sum);
            // printf("%d",arr[i]);
            root->code[i] = arr[i];
            // k-=1; 
        }
        for(int i=0;i<c;i++){
            printf("%d",root->code[i]);
        }
        codearr[pos-32] = root->code;
        printf("\n");
        // printf("\n%d\n",sum);
    }
}

void inorder(struct Node * root){
    if(root!=NULL){
    inorder(root->left);
    printf("%c ",root->data);
    inorder(root->right);
    }
}

struct Node * search(struct minheap * heap,char s){
    int size = sizeof(heap->array)/sizeof(struct Node);
    for(int i=0;i<size;i++){
        if(s==heap->array[i]){
            return heap->array[i];
        }
    }
}

int main(){
    char arrchr[95];
    int arrfq[95];

    FILE *f ;
    f= fopen("in.txt","r");
    for(int i=0;i<94;i++){
        arrchr[i] = ' ';
        arrfq[i] = 0;
    }
    while (!feof(f)){
        char m = fgetc(f);
        int posn = (int)(m);
        arrchr[posn - 32] = m;
        arrfq[posn - 32] += 1;
    }
    fclose(f);
    int count=0;

    for(int i=0;i<95;i++){
        if(arrchr[i]!=' '){
            count +=1;
        }
    }
    char finalarrchr[count];
    int finalarrfq[count];

    for(int i=0;i<count;i++){
        finalarrchr[i] = ' ';
        finalarrfq[i] = 0;
    }

    int j = 0;
    for(int i=0;i<94;i++){
        if(arrchr[i]!=' '){
            finalarrchr[j] = arrchr[i];
            finalarrfq[j] = arrfq[i];
            j+=1;
        }
    }
    count = count-1;
    // for(int i=0;i<count;i++){
    //     printf("%c %d\n",finalarrchr[i],finalarrfq[i]);
    // }


    struct Node * root  = createminheaptree(finalarrchr,finalarrfq,count);
    // inorder(root);
    int height = getheight(root);
    int arr[height];
    int c=0;
    int codearr[95][getheight(root)];
    codes(root,arr,c,codearr,height);



    return 0;
}
