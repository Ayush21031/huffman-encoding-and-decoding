#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//---------------------------Encoding functions-----------------------------

struct Node{
    char data;
    int fq;
    struct Node * left;
    struct Node * right;
    int code;
};

struct minheap{
    struct Node** array;
    int size;
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
    struct Node *t = *n1;
    *n1 = *n2;
    *n2 = t;
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

void codes(struct Node * root,int arr[],int c,int height,int codearr[95]){
    if(root->left){
        arr[c] = 0;
        codes(root->left,arr,c+1,height,codearr);
    }
    if(root->right){
        arr[c] = 1;
        codes(root->right,arr,c+1,height,codearr);
    }
    if(root->left==NULL && root->right==NULL){
        printf("%c -> ",root->data);
        int k = c-1;
        int pos = (int)(root->data);
        int sum = 0;
        for(int i=0;i<c;i++){
            sum = sum + arr[i]*(pow(10,k) + 1e-9);
            k-=1;
            printf("%d",arr[i]); 
        }
        codearr[pos-32] = sum;
        printf("\n");
        // printf("%d",sum);
        // printf("\n");
    }
}

void inorder(struct Node * root){
    if(root!=NULL){
    inorder(root->left);
    printf("%c ",root->data);
    inorder(root->right);
    }
}


void writinginfile(int height,int codearr[95],char input[],char output[]){
    FILE *f ;
    f= fopen(input,"r");
    FILE *r;
    r = fopen(output,"w");
    while (!feof(f)){
        char m = fgetc(f);
        int posn = (int)(m);
        if(posn-32>=0){
        fprintf(r,"%d",codearr[posn-32]);
        }

    }
    fclose(r);
    fclose(f);
}

//-----------------------------------------Decoding functions--------------------------------------

struct Node1{
    char data;
    struct Node1 * left;
    struct Node1 * right;
};

struct Node1 * createnode1(char c){
    struct Node1 * new = (struct Node1 *)malloc(sizeof(struct Node1));
    new->data = c;
    new->left = NULL;
    new->right = NULL;
    return new;
}

struct Node1 * buildtree(struct Node1 * head,char s,char arr2[],int count){
    // printf("Hi");
    struct Node1 * root = head;
    for(int i=0;i<count;i++){
        if(arr2[i]=='0'){
            // printf("if 1");
            if(root->left==NULL){
                root->left = createnode1('$');
                // printf("created new left node\n");
                root = root->left;
            }
            else{
                // printf("Travesed to left node\n");
                root = root->left;
            }
        }
        else if(arr2[i]=='1'){
            // printf("if 2");
            if(root->right==NULL){
                root->right = createnode1('$');
                // printf("created new right node\n");
                root = root->right;
            }
            else{
                // printf("Travesed to right node\n");
                root = root->right;
            }
        }
    }
    root->data = s;
    return head;
}

void writing_file(char m,struct Node1 * head,FILE *f,char output[]){
    FILE *k;
    k = fopen(output,"w");
    struct Node1 * root = head;
    while(!feof(f)){
        if(m=='1'){
                if(root->left!=NULL && root->right!=NULL){
                    root = root->right;
                    m = fgetc(f);
                }
                else{
                    char s = root->data;
                    fprintf(k,"%c",root->data);
                    root = head;
            }
            }
        else if(m=='0'){
            if(root->left!=NULL && root->right!=NULL){
                root = root->left;
                m = fgetc(f);
            }
            else{
                char s = root->data;
                fprintf(k,"%c",root->data);
                root = head;
            }
        }
        
    }
    fprintf(k,"%c",root->data);
}

int main(){
    char input[128];
    char output[128];
    int choice;
    scanf("%s",&input);
    scanf("%s",&output);
    printf("Enter 0 for compression, 1 for decompression : ");
    scanf("%d",&choice);

    if(choice==0){ //------------------Encoding code--------------------------
    char arrchr[95];
    int arrfq[95];

    FILE *f ;
    f= fopen(input,"r");
    for(int i=0;i<94;i++){
        arrchr[i] = ' ';
        arrfq[i] = 0;
    }
    while (!feof(f)){
        char m = fgetc(f);
        if(m!='\n'){
        int posn = (int)(m);
        arrchr[posn - 32] = m;
        arrfq[posn - 32] += 1;
        }
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
 
    struct Node * root  = createminheaptree(finalarrchr,finalarrfq,count);
    // inorder(root);
    int height = getheight(root);
    int arr[height];
    int c=0;
    int codearr[95];

    codes(root,arr,c,height,codearr);
    writinginfile(height,codearr,input,output);
    }

    else if(choice==1){ //-------------Decoding code--------------------------
        struct Node1 * head = createnode1('$');
    FILE *f;
    f = fopen(input,"r");
    char m;
    while(!feof(f)){
        char arr[7];
        int count = 0;
        m = fgetc(f);
        if(m!='1' && m!='0'){
            char code = fgetc(f);
            code = fgetc(f);
            while(code!='\n'){
                arr[count] = code;
                count+=1;
                code = fgetc(f);
            }
            char arr2[count];
            for(int i=0;i<count;i++){
                arr2[i] = arr[i];
            }
            head = buildtree(head,m,arr2,count);
            
        }
        else{
            writing_file(m,head,f,output);
            printf("Generating %s file",output);
            // printf("----------Binary tree created------");
            break;
        }
    }
    // inorder(head);
    }
    return 0;
}