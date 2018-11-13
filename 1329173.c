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
	struct node *pointer;
	struct nodeQueue *next;
	struct nodeQueue *previous;
};

void conc(char *c, char x){
	while(*c)
		c++;
	*c = x;
	*(c+1) = '\0';
}

int itsDigit(char* str){
	if (*str == 45)
		if ( isdigit(*(str+1)) )
			return 1;
	if ( isdigit(*str) )
			return 1;
	return 0;
}
struct nodeQueue *searchLast(struct nodeQueue *head){
	while(head){
		if(head->next == NULL)
			return head;
		head = head->next;
	}
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
	struct node* x = NULL;
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

struct node *pop(struct nodeQueue **pth){
	struct node* x = NULL;
	struct nodeQueue *p1 = NULL;
	p1 = *pth;
	while(p1->next)
		p1 = p1->next;

	x = p1->pointer;
	if(p1->previous)
		p1->previous->next = NULL;
	else
		*pth = NULL;
	memset(p1,0,sizeof(struct nodeQueue));
	free(p1);
	return x;
}

void parseBracket(struct nodeQueue** queuePost,struct nodeQueue** queueNums,struct nodeQueue** queueOper, char *data){
	int negative = 0;
	while(*data){
		int parAbierto = 1;
		if (*data != 10 && *data != 41){
			if (*data == 40)
					parAbierto=0;
			struct node* temp = (struct node*)(malloc(sizeof(struct node)));
			if ( (*data == 40 || *data == 45 || *data == 42 ||*data == 43 || *data == 47) && !negative){
				if (*(data+1) == 45)
					negative=1;
				conc(temp->data,*data);
				data++;
			}
			else{
				if (negative){
					conc(temp->data,*data);
					negative=0;
					data++;
				}
				while(isdigit(*data)){
					conc(temp->data,*data);
					data++;
				}
			}
			if (parAbierto){
				strcpy(temp->data,temp->data);
				if (itsDigit( temp->data)){
					push(queueNums,temp);
				}
				else
					push(queueOper,temp);
			}
		}
		else if(*data == 41){
			if(*queueNums){
				struct node* x1 = NULL;
				struct node* x2 = NULL;
				if (*queueNums)
					x1 = pop(queueNums);
				if (*queueNums)
					x2 = pop(queueNums);
				if(x2)
					push(queuePost,x2);
				if(x1)
					push(queuePost,x1);
			}
			if (*queueOper)
				push(queuePost,pop(queueOper));
			data++;
		}
		else
			data++;
	}
}


void parse(struct nodeQueue** queue, char *data){
	while(*data){
		struct node* temp = (struct node*)(malloc(sizeof(struct node)));
		while(*data != 32 && *data != 10){
			conc(temp->data,*data);
			data++;
		}
		strcpy(temp->data,temp->data);
		push(queue,temp);
		data++;
	}
}

int insertPost(struct node** root, struct node* data){
	if(*root){
		if(!itsDigit(  (*root) -> data)  ){
			if(insertPost(&(*root)->right,data))
				return 1;
			if(insertPost(&(*root)->left,data))
				return 1;
		}
		else
			return 0;
	}
	else{
		*root = data;
		return 1;
	}
}

/*Function that inserts the data with postfix input*/

void insertPostFix(struct node** root, char *data){;
	struct nodeQueue* queue = NULL;
	parse(&queue,data);
	while(queue)
		insertPost(root,pop(&queue));
}

int insertPre(struct node** root, struct node* data){
	if(*root){
		if(!itsDigit( (*root) -> data) ){
			if(insertPre(&(*root)->left,data))
				return 1;
			if(insertPre(&(*root)->right,data))
				return 1;
		}
		else
			return 0;
	}
	else{
		*root = data;
		return 1;
	}
}

/*Function that inserts the data with prefix input*/

void insertPreFix(struct node** root, char *data){;
	struct nodeQueue* queue = NULL;
	parse(&queue,data);
	while(queue)
		insertPre(root,get(&queue));
}

/*Function that inserts the data with infix input*/

void insertInFix(struct node** root, char *data){
	struct nodeQueue* queueNums = NULL;
	struct nodeQueue* queueOper = NULL;
	struct nodeQueue* queuePost = NULL;
	parseBracket(&queuePost,&queueNums,&queueOper,data);
	while(queuePost)
		insertPost(root,pop(&queuePost));
}

/*Function that reads the input of the user*/

void read(struct node** root ){
	char *data = (char *)(malloc(sizeof(char)));
	char *temp = (char *)(malloc(sizeof(char)));
	fgets(data,1024,stdin);
	if(*data == 40){ // = (
		insertInFix(root,data);
	}
	else if(*data == 45){ // Number
		if (isdigit(*(data+1)))
			insertPostFix(root,data);
	}
	else if (isdigit(*(data))){
		insertPostFix(root,data);
	}
	else{ // Operator
		insertPreFix(root,data);
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

void printInOrder(struct node* root,int side){
	if(root){
		if(!side)
			printf("(");
		printInOrder(root->left,0);
		printf("%s",root->data);
		printInOrder(root->right,1);
		if(side==1)
			printf(")");
	}	
}

/*Function that evaluates the result of the binary tree*/

int result(struct node* root){
	if(!itsDigit(root->data)){
		switch(*root->data){
			case 42://*
				return result(root->left) * result(root->right);
				break;
			case 43://+
				return result(root->left) + result(root->right);
				break;
			case 45://-
				return result(root->left) - result(root->right);
				break;
			case 47:///
				return result(root->left) / result(root->right);
				break;
		}
	}
	else{
		return atoi(root->data);
	}
}

//Main

int main(int argc, char const *argv[]){
	char *numberKeys  = (char *)(malloc(sizeof(char)));
	fgets(numberKeys,1024,stdin);
	for (int i = 0; i < atoi(numberKeys); ++i){
		printf("%d.\n", i+1);
		struct node * root = NULL;
		read(&root);

		printf("prefix   = ");
		printPreOrder(root);
		printf("\n");
	
		printf("infix    = ");
		printInOrder(root,-1);
		printf("\n");
	
		printf("postfix  = ");
		printPostOrder(root);
		printf("\n");

		printf("result: %d\n", result(root) );
	
	}
	return 0;
}