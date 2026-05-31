#include <stdio.h>
#include <stdlib.h>/*for malloc*/
#include "BinaryTree.h"
#define MAGIC_NUM 159357
#define SWAP(a,b,t)\
	{\
	t temp;\
	temp = a;\
	a = b;\
	b = temp;\
	}

typedef struct Node
{
	int m_data;
	struct Node* m_left;
	struct Node* m_right;
	struct Node* m_father;
}Node;

struct Tree
{
	Node *m_root;
	int m_magicNum;
};

/*Assiting Functions:*/
static void DestroyNodeRec(Node *_node);
static Node* SearchNode(Node *_node, int _data);
static void InitializeNode(Node *_prevNode, Node *_newNode, int _data);
static void PrintPreOrder(Node *_node);
static void PrintInOrder(Node *_node);
static void PrintPostOrder(Node *_node);
static void PrintNode(Node *_node);
int IsFullTree(Tree *_tree);
static int FullNodeRec(Node *_node);
int AreSimilarTree(Tree *_tree1, Tree *_tree2);
static int NodeIsSimilar(Node *_node1, Node *_node2);
int CalcTreeLevel(Tree *_tree);
static int NodeLevelCalc(Node *_node);
void MirrorTree(Tree *_tree);
static void MirrorNode(Node *_node);
int IsPerfectTree(Tree* _tree);
static int CountNodes(Node *_node);

/*Get Functions:*/
int GetMagicNum();
int GetTreeMagicNum(Tree *_tree);
int GetRootData(Tree *_tree);

Tree* TreeCreate()
{
	Tree* newTree;
	newTree = (Tree*)malloc(sizeof(Tree));
	if(newTree == NULL)
	{
		return NULL;
	}
	newTree->m_root = NULL;
	newTree->m_magicNum = MAGIC_NUM;
	return newTree;
}

void TreeDestroy(Tree* _tree)/* Post Order*/
{
	Node* node = NULL;
	if(_tree == NULL || _tree->m_magicNum != MAGIC_NUM)
	{
		return;
	}
	node = _tree->m_root;
	DestroyNodeRec(node);
	_tree->m_magicNum = 0;
	free(_tree);
}

ADTErr TreeInsert(Tree* _tree, int _data)
{
	Node *newNode, *prevNode;
	if(_tree == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL)
	{
		return ERR_ALOCATION_FAILED;
	}
	if(_tree->m_root == NULL)
	{
		InitializeNode(_tree->m_root, newNode, _data);
		_tree->m_root = newNode;
		return ERR_OK;
	}
	prevNode = SearchNode(_tree->m_root, _data);
	if(prevNode == NULL)/*Duplicate*/
	{
		free(newNode);
		return ERR_DUPLICATE_INSERT;
	}
	InitializeNode(prevNode, newNode, _data);
	if(_data < prevNode->m_data)
	{
		prevNode->m_left = newNode;
	}
	if(_data > prevNode->m_data)
	{
		prevNode->m_right = newNode;
	}
	return ERR_OK;
}

int TreeIsDataFound(Tree* _tree, int _data)
{
	Node *temp;
	int returned;
	if(_tree == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	temp = SearchNode(_tree->m_root, _data);
	if(temp == NULL)
	{
		return TRUE;
	}
	return FALSE;
}

void TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
	if(_tree == NULL)
	{
		return;
	}
	switch (_traverseMode)
	{
		case PRE_ORDER:
			PrintPreOrder(_tree->m_root);
			break;
		
		case IN_ORDER:
			PrintInOrder(_tree->m_root);
			break;
			
		case POST_ORDER:
			PrintPostOrder(_tree->m_root);
			break;
	}
	printf("\n");
}

/*Assiting functions:*/
static void DestroyNodeRec(Node *_node)
{
	if(_node == NULL)
	{
		return;
	}
	DestroyNodeRec(_node->m_left);
	DestroyNodeRec(_node->m_right);
	free(_node);
}

static void InitializeNode(Node *_prevNode, Node *_newNode, int _data)
{
	_newNode->m_father = _prevNode;
	_newNode->m_right = NULL;
	_newNode->m_left = NULL;
	_newNode->m_data = _data;
}

static Node* SearchNode(Node *_node, int _data)
{
	if(_node == NULL)
	{
		return NULL;
	}
	if(_data < _node->m_data)
	{
		if(_node->m_left == NULL)
		{
			return _node;
		}
		return SearchNode(_node->m_left, _data);
	}
	if(_data > _node->m_data)
	{
		if(_node->m_right == NULL)
		{
			return _node;
		}
		return SearchNode(_node->m_right, _data);
	}
	if(_data == _node->m_data)
	{
		return NULL;
	}
}

static void PrintPreOrder(Node *_node)
{
	if(_node == NULL)
	{
		return;
	}
	PrintNode(_node);
	PrintPreOrder(_node->m_left);
	PrintPreOrder(_node->m_right);
}

static void PrintInOrder(Node *_node)
{
	if(_node == NULL)
	{
		return;
	}
	PrintInOrder(_node->m_left);
	PrintNode(_node);
	PrintInOrder(_node->m_right);
}

static void PrintPostOrder(Node *_node)
{
	if(_node == NULL)
	{
		return;
	}
	PrintPostOrder(_node->m_left);
	PrintPostOrder(_node->m_right);
	PrintNode(_node);
}

static void PrintNode(Node *_node)
{
	if(_node == NULL)
	{
		return;
	}
	printf("%d ",_node->m_data);
}

int IsFullTree(Tree *_tree)
{
	if(_tree == NULL)
	{
		return FALSE;
	}
	return FullNodeRec(_tree->m_root);
}

static int FullNodeRec(Node *_node)
{
	int returned1, returned2;
	if(_node == NULL)
	{
		return TRUE;
	}
	if((_node->m_left == NULL && _node->m_right != NULL) || (_node->m_left != NULL && _node->m_right == NULL))/*Not Full*/
	{
		return FALSE;
	}
	returned1 = FullNodeRec(_node->m_left);
	returned2 = FullNodeRec(_node->m_right);
	if(returned1 == FALSE || returned2 == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

int AreSimilarTree(Tree *_tree1, Tree *_tree2)
{
	if(_tree1 == NULL || _tree2 == NULL)
	{
		return FALSE;
	}
	return NodeIsSimilar(_tree1->m_root, _tree2->m_root);
}

static int NodeIsSimilar(Node *_node1, Node *_node2)
{
	int returned1, returned2;
	if((_node1 == NULL && _node2 != NULL) || (_node1 != NULL && _node2 == NULL))
	{
		return FALSE;
	}
	if((_node1 == NULL && _node2 == NULL))
	{
		return TRUE;
	}
	returned1 = NodeIsSimilar(_node1->m_left, _node2->m_left);
	returned2 = NodeIsSimilar(_node1->m_right, _node2->m_right);
	if(returned1 == FALSE || returned2 == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

int CalcTreeLevel(Tree *_tree)
{
	if(_tree == NULL || _tree->m_root == NULL)
	{
		return 0;
	}
	return NodeLevelCalc(_tree->m_root);
}

static int NodeLevelCalc(Node *_node)
{
	int countLeft = 0, countRight = 0;
	if(_node == NULL)
	{
		return 0;
	}
	if(_node->m_left == NULL && _node->m_right == NULL)
	{
		return 1;
	}
	countLeft += NodeLevelCalc(_node->m_left) + 1;
	countRight += NodeLevelCalc(_node->m_right) + 1;
	if(countLeft >= countRight)
	{
		return countLeft;
	}
	else if(countRight > countLeft)
	{
		return countRight;
	}
}

void MirrorTree(Tree *_tree)
{
	if(_tree == NULL)
	{
		return;
	}
	MirrorNode(_tree->m_root);
}

static void MirrorNode(Node *_node)
{
	if(_node == NULL)
	{
		return;
	}
	MirrorNode(_node->m_left);
	MirrorNode(_node->m_right);
	SWAP(_node->m_left, _node->m_right, Node*);
}

int IsPerfectTree(Tree* _tree)
{
	int nodeCount, levelCount, wantedNodeCount = 2, i;
	if(_tree == NULL)
	{
		return FALSE;
	}
	nodeCount = CountNodes(_tree->m_root);
	levelCount = CalcTreeLevel(_tree);
	for(i = 1;i < levelCount;++i)
	{
		wantedNodeCount *= 2;
	}
	wantedNodeCount -= 1;
	if(wantedNodeCount == nodeCount)
	{
		return TRUE;
	}
	return FALSE;
}

static int CountNodes(Node *_node)
{
	int count = 0;
	if(_node == NULL)
	{
		return 0;
	}
	if(_node->m_left == NULL && _node->m_right == NULL)
	{
		return 1;
	}
	count += CountNodes(_node->m_left) + 1;
	count += CountNodes(_node->m_right);
	return count;
}

/*Get Functions:*/
int GetMagicNum()
{
	return MAGIC_NUM;
}

int GetTreeMagicNum(Tree *_tree)
{
	return _tree->m_magicNum;
}

int GetRootData(Tree *_tree)
{
	return _tree->m_root->m_data;
}
