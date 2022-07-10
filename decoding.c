    // #include<stdio.h>
    // #include<stdlib.h>


    // struct Node{
    //     char data;
    //     struct Node * left;
    //     struct Node * right;
    // };

    // struct Node * createnewnode(int data){
    //     struct Node * new = (struct Node *)malloc(sizeof(struct Node));
    //     new->data = data;
    //     new->left = NULL;
    //     new->right = NULL;
    //     return new;
    // }

    // void inorder(struct Node * node){
    //     if(node!=NULL){
    //         inorder(node->left);
    //         printf("%d\n",node->data);
    //         inorder(node->right);
    //     }
    // }

    // int main(){

    //     int a[] = {1,1,0,0};
    //     int b[] = {0,0,1,1};

    //     struct Node * head = (struct Node *)malloc(sizeof(struct Node));
    //     head->data = 10;
    //     head->left = NULL;
    //     head->right = NULL;
    //     struct Node * root = head;
    //     for(int i=0;i<4;i++){
    //         if(a[i]==0){
    //             if(root->left==NULL){
    //                 root->left = createnewnode(10);
    //                 root = root->left;
    //             }
    //             else{
    //                 root = root->left;
    //             }
    //         }
    //         else if(a[i]==1){
    //             if(root->right==NULL){
    //                 root->right = createnewnode(10);
    //                 root = root->right;
    //             }
    //             else{
    //                 root = root->right;
    //             }
    //         }
    //     }
    //     root->data = 'A';
    //     root = head;


    //     for(int i=0;i<4;i++){
    //         if(b[i]==0){
    //             if(root->left==NULL){
    //                 root->left = createnewnode(10);
    //                 root = root->left;
    //             }
    //             else{
    //                 root = root->left;
    //             }
    //         }
    //         else if(b[i]==1){
    //             if(root->right==NULL){
    //                 root->right = createnewnode(10);
    //                 root = root->right;
    //             }
    //             else{
    //                 root = root->right;
    //             }
    //         }
    //     }
    //     root->data = 'B';
    //     root = head;
    //     inorder(root);


    // }


    #include<stdio.h>
    #include<stdlib.h>

    struct Node{
        char data;
        struct Node * left;
        struct Node * right;
    };

    struct Node * createnode(char c){
        struct Node * new = (struct Node *)malloc(sizeof(struct Node));
        new->data = c;
        new->left = NULL;
        new->right = NULL;
        return new;
    }

    struct Node * buildtree(struct Node * head,char s,char arr2[],int count){
        // printf("Hi");
        struct Node * root = head;
        for(int i=0;i<count;i++){
            if(arr2[i]=='0'){
                // printf("if 1");
                if(root->left==NULL){
                    root->left = createnode('$');
                    printf("created new left node\n");
                    root = root->left;
                }
                else{
                    printf("Travesed to left node\n");
                    root = root->left;
                }
            }
            else if(arr2[i]=='1'){
                // printf("if 2");
                if(root->right==NULL){
                    root->right = createnode('$');
                    printf("created new right node\n");
                    root = root->right;
                }
                else{
                    printf("Travesed to right node\n");
                    root = root->right;
                }
            }
        }
        root->data = s;
        return head;
    }

    void inorder(struct Node * node){
        if(node!= NULL){
            inorder(node->left);
            printf("%c",node->data);
            inorder(node->right);
        }
    }


    int main(){
        struct Node * head = createnode('$');
        FILE *f;
        f = fopen("decode.txt","r");
        char m;
        while(!feof(f)){
            char arr[7];
            int count = 0;
            m = fgetc(f);
            printf("%c :",m);
            if(m!='1' && m!='0'){
            // if(65<=(int)(m)<=90 || 97<=(int)(m)<=122 && ((int)(m)!=48 && (int)(m)!=49)){
                char code = fgetc(f);
                code = fgetc(f);
                while(code!='\n'){
                    arr[count] = code;
                    count+=1;
                    code = fgetc(f);
                }
                char arr2[count];
                // printf("%c : ",m);
                for(int i=0;i<count;i++){
                    arr2[i] = arr[i];
                    // printf("%c",arr2[i]);
                }
                for(int i=0;i<count;i++){
                    printf("%c",arr2[i]);
                }
                printf("\n");
                printf("\ncreating New character code\n");
                // printf("%c",m);
                head = buildtree(head,m,arr2,count);
                
            }
            else{
                printf("----------Binary tree created------");
                break;
            }
        }
        inorder(head);
        FILE *k;
        k = fopen("encode.txt","w");
        struct Node * root = head;
        while(!feof(f)){
            if(m=='1'){
                if(root->right!=NULL){
                    root = root->right;
                }
                else{
                    if(root->right==NULL && root->left==NULL){
                        fprintf(k,"%c",root->data);
                        root = head;
                    }
                }
            }
            else if(m=='0'){
                if(root->left!=NULL){
                    root = root->left;
                }
                else{
                    if(root->right==NULL && root->left==NULL){
                        fprintf(k,"%c",root->data);
                        root = head;
                    }
                }
            }
        }
        fclose(k);
        return 0;
    }
