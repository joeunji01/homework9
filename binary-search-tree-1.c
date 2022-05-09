/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
void freeNode(Node* ptr); 

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("[----- [조은지]  [2021076020] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) { 

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); 
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr){
	inorderTraversal(ptr->left); //leafnode 까지 내려감
	printf(" [%d}", ptr->key);
	//leftchild ->  parent -> rightchild 순으로 프린트
	inorderTraversal(ptr->right);
	}


}

void preorderTraversal(Node* ptr)
{
	if(ptr){
		printf(" [%d]",ptr->key); //headnode 먼저 프린트
		preorderTraversal(ptr->left); //leftchild 프린트 (leafnoded일 때까지)
		preorderTraversal(ptr->right); //위로 올라오면서 right child 프린트
		
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr){
		postorderTraversal(ptr->left); //leafnode 까지 내려감
		postorderTraversal(ptr->right); 
		//leftchild -> rightchild -> parent 순으로 프린트
		//headnode를 제일 마지막에
		printf(" [%d]", ptr->key);
		
	}
}


int insert(Node* head, int key)
{
	Node * new = (Node*)malloc(sizeof(Node));
	new->key=key;
	new->left=new->right=NULL;

	if(head->left==NULL){ //트리에 헤드노드만 존재
		head->left=new; //헤드노드의 leftchild에 삽입
		return 1;
	}

	Node *ptr=head->left;
	Node *pnode =NULL; //parent node pointer

	while(ptr!=NULL){
	
	if (ptr->key==key) return 1;
	//삽입하려는 값이 있음
	pnode=ptr;

	//비교할 노드의 key보다 크면 rightchild 쪽으로
	if(ptr->key<key) //key값이 큼
		ptr=ptr->right; //rightchild의 key와 비교
	else //비교할 노드의 key보다 작으면 leftchild 쪽으로
		ptr=ptr->left; //leftchild의 key와 비교

	} //탐색이 끝난 지점에서 ptr이 부모노드가 됨

	if(pnode->key>key) //부모노드의 key 값보다 작으면
		pnode->left=new; //왼쪽에 삽입
	else
		pnode->right=new; //크면 오른쪽에 삽입
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if(head==NULL){
		printf("\n Nothing to delete\n");
		return -1;
	}

	if (head->left==NULL){
		printf("\n Nothing to delete\n");
		return -1;
	}

	Node *ptr =head->left; 
	Node *pnode =head;
	
	while(ptr!=NULL){
		if(ptr->key==key){ 
			if(ptr->left==NULL && ptr->right==NULL){
				//leafnode

				if(pnode==head) //루트노드일 경우
					head->left=NULL; //연결 해제

				if(pnode->left==ptr) 
					pnode->left=NULL; //pnode를 leaf 노드로
				else
					pnode->right=NULL;
				
				free(ptr); //ptr 메모리 할당 해제
			}
			else
				printf("the node [%d] is not a leaf\n", ptr->key);
			return 1;
		}
		
		//ptr->key값과 다른경우
		pnode=ptr; //leftchild로 
		if(ptr->key<key) //범위에 맞게 ptr이 child로
			ptr=ptr->right; 
		else
			ptr=ptr->left;
	}

	printf("Cannot find the node for key [%d]\n",key);

	return 1;

}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr==NULL)
		return NULL;
	
	if (ptr->key<key)
		ptr=searchRecursive(ptr->right,key);
	else if (ptr->key>key)
		ptr=searchIterative(ptr->left,key);

	//ptr->key==key
	return ptr;

}

Node* searchIterative(Node* head, int key)
{
	Node *ptr=head->left;

	while(ptr!=NULL)
	{
		if (ptr->key==key)
			return ptr;

		if(ptr->key<key) //범위에 맞게 child로 ptr 변경
			ptr=ptr->right;
		else
			ptr=ptr->left;
	}
	//못찾을 경우
	return NULL;
}


int freeBST(Node* head)
{
	if(head->left==head) //트리에 헤드노드만 존재
	{
		free(head);
		return 1;
	}
	Node *p =head->left; 

	freeNode(p);
	free(head);
	return 1;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}
