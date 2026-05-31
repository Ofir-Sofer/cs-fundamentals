#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#define MAGIC_NUM 159357
#include "ADTDefs.h"

typedef struct Tree Tree;

/*description- This function create a struct of Binary Tree
input- none
output- Tree pointer
	NULL
errors- NULL- In case allocation failed*/
Tree* TreeCreate();

/*description- This function destroys a struct of Binary Tree
input- Binary Tree pointer
output- none
errors- none*/
void TreeDestroy(Tree* _tree);

/*description- Insert new node to Tree
input- Binary Tree pointer
	_data to insert to new node
output- ERR_OK
	ERR_NOT_INITIALIZED
	ERR_ALOCATION_FAILED
errors- ERR_NOT_INITIALIZED- Tree pointer is NULL
	ERR_ALOCATION_FAILED- new node allocation failed*/
ADTErr TreeInsert(Tree* _tree, int _data);

/*description- Search data in binary tree
input- Binary Tree pointer
	_data to search in tree nodes
output- TRUE
	FALSE
	ERR_NOT_INITIALIZED
errors- ERR_NOT_INITIALIZED- Tree pointer is NULL*/
int TreeIsDataFound(Tree* _tree, int _data);

/*description- Print a binary tree
input- Tree pointer
	Type of traverse
output- none
errors- none*/
void TreePrint(Tree* _tree, TreeTraverse _traverseMode);
#endif/*__BINARYTREE_H__*/
