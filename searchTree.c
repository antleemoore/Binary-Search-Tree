#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/*Made preorder, inorder, and postorder functions.  Made a create node function.
  Next is to make an insert node function recursively*/

/*Finished preoroder, inorder, postorder, and insert, search, and count before.  Next is delete.*/

typedef struct tree_node{
  char* name;
  struct tree_node *left;
  struct tree_node *right;
}nodeName;

void preorder(struct tree_node *p, FILE *fp);

void inorder(struct tree_node*p, FILE *fp);

void postorder(struct tree_node*p, FILE *fp);

struct tree_node* create_node(char *name);
struct tree_node*  insertNode(nodeName *root, nodeName *element);

int find(struct tree_node *current_ptr, char *val);
int count;
int CountBefore(nodeName *p, char *name);

struct tree_node * minValueNode(struct tree_node* node);
struct tree_node* deleteNode(struct tree_node* root, char* key);

int ic_strcmp(char *s1, char *s2) 
{ 
    int i; 
    for (i = 0; s1[i] && s2[i]; ++i) 
    { 
        if (s1[i] == s2[i] || (s1[i] ^ 32) == s2[i]) 
           continue; 
        else
           break; 
    } 
  
    if (s1[i] == s2[i]) 
        return 0; 
  
    if ((s1[i] | 32) < (s2[i] | 32))  
        return -1; 
    return 1; 
} 

int main(){
    int totalNames, searchNames, deleteNames;

    FILE *in, *out;
    in = fopen("in.txt","r");
    fscanf(in, "%d", &totalNames);
    char Names[50][20], search[50][20], deleteN[50][20];

    fscanf(in, "%d", &searchNames);
    fscanf(in, "%d", &deleteNames);
    for(int i = 0; i < totalNames; i++)
        fscanf(in, "%s", Names[i]);
    for(int i = 0; i < searchNames; i++)
        fscanf(in, "%s", search[i]);
    for(int i = 0; i < deleteNames; i++)
        fscanf(in, "%s", deleteN[i]);
    fclose(in);

    nodeName * root = create_node(Names[0]);
	
    for(int i = 1; i < totalNames; i++){
        nodeName *temp = create_node(Names[i]);
        root = insertNode(root, temp);
    }
	
    out = fopen("out.txt", "w");
    fprintf(out,"Preorder: "); preorder(root,out); fprintf(out,"\n");
    fprintf(out,"Inorder: ");inorder(root,out); fprintf(out,"\n");
    fprintf(out,"Postorder: "); postorder(root,out); fprintf(out,"\n\n");

    for(int i = 0; i < searchNames; i++){
        count = 0;
        if(!find(root,search[i]))
            fprintf(out,"%s...Not Found\n",search[i]);
        else
            fprintf(out,"%s...Found, Items before: %d\n", search[i], CountBefore(root, search[i]));
    }
    fprintf(out,"\n");

    for(int i = 0; i < deleteNames; i++){
        if(!find(root,deleteN[i]))
            fprintf(out,"%s...Not Found\n", deleteN[i]);
        else{
            root = deleteNode(root, deleteN[i]);
            fprintf(out,"%s: Deleted\n", deleteN[i]);
        }
    }
    fprintf(out, "\n");

    fprintf(out,"Preorder: "); preorder(root,out); fprintf(out,"\n");
    fprintf(out,"Inorder: ");inorder(root,out); fprintf(out,"\n");
    fprintf(out,"Postorder: "); postorder(root,out); fprintf(out,"\n\n");
    fclose(out);
    return 0;
}

void preorder(struct tree_node *p, FILE *fp) {
    if (p != NULL) {
        fprintf(fp,"%s ", p->name);
        preorder(p->left,fp);
        preorder(p->right,fp);
    }
}
void inorder(struct tree_node*p, FILE *fp) {
    if (p != NULL) {
        inorder(p->left,fp);
        fprintf(fp,"%s ", p->name);
        inorder(p->right,fp);
    }
}
void postorder(struct tree_node*p, FILE *fp) {
    if (p != NULL) {
        postorder(p->left,fp);
        postorder(p->right,fp);
        fprintf(fp,"%s ", p->name);
    }
}
struct tree_node* create_node(char *name) {
  struct tree_node* temp;
  temp = (struct tree_node*)malloc(sizeof(struct tree_node));
  temp->name = name;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}
struct tree_node*  insertNode(nodeName *root, nodeName *element){
	if(root == NULL){
	return element;
    }
    if(ic_strcmp(element->name, root->name) == 1){
	if(root->right == NULL){
            root->right = element;
        }
        else{
		root->right = insertNode(root->right, element);
	
	}
    }
    else{
	if(root->left == NULL){
            root->left = element;

        }
        else{
		root->left = insertNode(root->left, element);
	}
    }
return root;


}
int find(struct tree_node *current_ptr, char *val){
    if(current_ptr != NULL) {
        if(ic_strcmp(val,current_ptr->name) == 0){
            return 1;
        }

        if(ic_strcmp(val,current_ptr->name) == -1){
            return find(current_ptr->left, val);
        }

        else{
            return find(current_ptr->right, val);
        }
    }
    else
        return 0;
}
int CountBefore(nodeName *p, char *name){

    if (p != NULL){
        CountBefore(p->left,name);
        if(ic_strcmp(name,p->name) == 1){
            count++;
        }
        CountBefore(p->right,name);
    }
    return count;

}
struct tree_node * minValueNode(struct tree_node* node)
{
    struct tree_node* current = node;

    while (current != NULL && current->left != NULL)
        current = current->left;

    return current;
}
struct tree_node* deleteNode(struct tree_node* root, char* key)
{
    if (root == NULL) return root;

    if (ic_strcmp(key,root->name) == -1)
        root->left = deleteNode(root->left, key);
    else if (ic_strcmp(key,root->name) == 1)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            struct tree_node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct tree_node *temp = root->left;
            free(root);
            return temp;
        }

        struct tree_node* temp = minValueNode(root->right);

        root->name = temp->name;

        root->right = deleteNode(root->right, temp->name);
    }
    return root;
}


