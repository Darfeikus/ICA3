/*
	Oscar Barbosa Aquino A01329173
	Antonio Diaz Flores A01329256
	Main method for a binary search tree
	25/Oct/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*struct node for a binary tree*/

struct node
{
	char data[1025];
	struct node *left = NULL;
	struct node *right = NULL;
};

struct nodeQueue{
	struct node* pointer;
	struct nodeQueue *next;
	struct nodeQueue *previous;
};

struct nodeQueue *searchLast(struct nodeQueue *head){
	while(head){
		if(head->next == NULL)
			return head;
		head = head->next;
	}
}

int iint (char *x){
	return atoi(x);
}

/*Function that inserts a nodeQueue at the beginning*/

void iatb(struct nodeQueue **pth,struct node* ptr){
	struct nodeQueue *tmp = (struct nodeQueue*)malloc(sizeof(struct nodeQueue));
	tmp->pointer = ptr;
	tmp->next= *pth;
	tmp->previous= NULL;
	*pth = tmp;
}

/*Function that inserts a nodeQueue at the end*/

void push(struct nodeQueue **pth,struct node* ptr){
	if(*pth==NULL)
		iatb(pth,ptr);
	else{
		struct nodeQueue *tmp = (struct nodeQueue*)malloc(sizeof(struct nodeQueue));
		tmp->previous = searchLast(*pth);
		tmp->previous->next = tmp;
		tmp->next =NULL;
		tmp->pointer=ptr;
	}
}
/*Function to deletes a node at the beggining
and then returns it*/

struct node *get(struct nodeQueue **pth){
	struct node* x = 0;
	struct nodeQueue *p1 = *pth;
	x = (*pth)->pointer;
	if((*pth)->next!=NULL)
		(*pth) = (*pth)->next;
	else
		(*pth) = NULL;
	memset(p1,0,sizeof(struct nodeQueue));
	free(p1);
	return x;
}

/*Function that returns a pointer to a struct node that fulfills the task of 
parent for a new piece of data*/

struct node* parent(struct node* root, char *data){
	if(data > root->data){
		if( root->right ==NULL)
			return root;
		return parent((root)->right,data);
	}
	else{
		if( root->left ==NULL)
			return root;
		return parent(root->left,data);	
	}
}

/*Function to insert nodes to the binary tree*/

void insert(struct node** root, char *data){
	struct node* temp = (struct node*)(malloc(sizeof(struct node)));
	strcpy(temp->data,data);
	if((*root)!=NULL){
		struct node* nParent = parent(*root,data);
		if(nParent!=NULL)
			if(atoi(data) > atoi(nParent->data))
				nParent->right = temp;
			else
				nParent->left = temp;
	}
	else
		*root = temp;
}

/*Function to insert nodes to the binary tree*/

void insertPreFix(struct node** root, char *data){;
	
}

void insertInFix(struct node** root, char *data){
	
}

void insertPostFix(struct node** root, char *data){;
	
	struct node* temp = (struct node*)(malloc(sizeof(struct node)));
	
	while(*data){
		printf("%c\n",*data );
		if((*root)!=NULL){

		}
		else
			*root = temp;
		data++;
	}
}


/*Function to prints the nodes of the tree in PreOrder*/

void printPreOrder(struct node* root){
	if(root){
		printf("%s ",root->data);
		printPreOrder(root->left);
		printPreOrder(root->right);
	}	
}

/*Function to prints the nodes of the tree in PostOrder*/

void printPostOrder(struct node* root){
	if(root){
		printPostOrder(root->left);
		printPostOrder(root->right);
		printf("%s ",root->data);
	}
}

/*Function to prints the nodes of the tree in InOrder*/

void printInOrder(struct node* root){
	if(root){
		printInOrder(root->left);
		printf("%s ",root->data);
		printInOrder(root->right);
	}
}

/*Function to prints the nodes of the tree in LevelOrder*/

void printLevelOrder(struct node* root){
	struct nodeQueue* queue = NULL;
	push(&queue,root);
	while(queue){
		struct node *x = get(&queue);
		if(x->left)
			push(&queue,x->left);
		if(x->right)
			push(&queue,x->right);
		printf("%s ",x->data );
	}
	printf("\n");
}

void read(struct node** root ){
	char *data = (char *)(malloc(sizeof(char)));
	fgets(data,1024,stdin);
	if(*data == 40)
		insertInFix(root,data);
	else if(isdigit(*data))
		insertPostFix(root,data);
	else 
		insertPreFix(root,data);
}

//Main

int main(int argc, char const *argv[]){
	char *numberKeys  = (char *)(malloc(sizeof(char)));
	fgets(numberKeys,1024,stdin);
	for (int i = 0; i < atoi(numberKeys); ++i){
		struct node * root = NULL;
		read(&root);
		printf("PreOrder   = ");
		printPreOrder(root);
		printf("\n");
	
		printf("InOrder    = ");
		printInOrder(root);
		printf("\n");
	
		printf("PostOrder  = ");
		printPostOrder(root);
		printf("\n");
	
		printf("LevelOrder = ");
		printLevelOrder(root);
		printf("%d\n",i );
	}
	return 0;
}