#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

/*Test Functions:*/
void TestCreateLegit();
void TestDestroyLegit();
void TestDestroyDouble();
void TestInsertLegit();
void TestInsertDuplicate();
void TestInsertNull();
void TestFindDataTrue();
void TestFindDataFalse();
void TestFindDataNull();
void TestPrint();
void TestIsFullFalse();
void TestIsFullTrue();
void TestIsFullNull();
void TestIsSimilarFalse();
void TestIsSimilarTrue();
void TestIsSimilarNull();
void TestCountUneven();
void TestCountEven();
void TestCountNull();
void TestMirrorTree();
void TestIsPerfectFalse();
void TestIsPerfectTrue();
void TestIsPerfectNull();

/*Get Funtions:*/
int GetMagicNum();
int GetTreeMagicNum(Tree *_tree);
int GetRootData(Tree *_tree);

int main(void)
{
	TestCreateLegit();
	TestDestroyLegit();
	TestDestroyDouble();
	TestInsertLegit();
	TestInsertDuplicate();
	TestInsertNull();
	TestFindDataTrue();
	TestFindDataFalse();
	TestFindDataNull();
	TestPrint();
	TestIsFullFalse();
	TestIsFullTrue();
	TestIsFullNull();
	TestIsSimilarFalse();
	TestIsSimilarTrue();
	TestIsSimilarNull();
	TestCountUneven();
	TestCountEven();
	TestCountNull();
	TestMirrorTree();
	TestIsPerfectFalse();
	TestIsPerfectTrue();
	TestIsPerfectNull();
}

void TestCreateLegit()
{
	Tree* tree = NULL; 
	tree = TreeCreate();
	if(GetTreeMagicNum(tree) == GetMagicNum())
	{
		printf("Test Create Legit PASSED\n");
	}
	else
	{
		printf("Test Create Legit FAILED\n");
	}
	TreeDestroy(tree);
}

void TestDestroyLegit()
{
	Tree* tree = NULL; 
	tree = TreeCreate();
	TreeDestroy(tree);
	if(GetTreeMagicNum(tree) != GetMagicNum())
	{
		printf("Test Destroy Legit PASSED\n");
	}
	else
	{
		printf("Test Destroy Legit FAILED\n");
	}
}

void TestDestroyDouble()
{
	Tree* tree = NULL; 
	tree = TreeCreate();
	TreeDestroy(tree);
	TreeDestroy(tree);
	if(GetTreeMagicNum(tree) != GetMagicNum())
	{
		printf("Test Double Destroy PASSED\n");
	}
	else
	{
		printf("Test Double Destroy FAILED\n");
	}
}

void TestInsertLegit()
{
	Tree* tree = NULL; 
	int data = 4728;
	tree = TreeCreate();
	TreeInsert(tree, data);
	if(GetRootData(tree) == data)
	{
		printf("Test Insert Legit PASSED\n");
	}
	else
	{
		printf("Test Insert Legit FAILED\n");
	}
	TreeDestroy(tree);
}

void TestInsertDuplicate()
{
	Tree* tree = NULL; 
	int data = 4728;
	tree = TreeCreate();
	TreeInsert(tree, data);
	if(TreeInsert(tree, data) == ERR_DUPLICATE_INSERT)
	{
		printf("Test Insert Duplicate PASSED\n");
	}
	else
	{
		printf("Test Insert Duplicate FAILED\n");
	}
	TreeDestroy(tree);
}

void TestInsertNull()
{
	Tree* tree = NULL; 
	int data = 4728;
	if(TreeInsert(tree, data) == ERR_NOT_INITIALIZED)
	{
		printf("Test Insert Null PASSED\n");
	}
	else
	{
		printf("Test Insert Null FAILED\n");
	}
}

void TestFindDataTrue()
{
	Tree* tree = NULL; 
	int data = 4728;
	tree = TreeCreate();
	TreeInsert(tree, data);
	if(TreeIsDataFound(tree, data) == TRUE)
	{
		printf("Test Find Data True PASSED\n");
	}
	else
	{
		printf("Test Find Data True FAILED\n");
	}
	TreeDestroy(tree);
}

void TestFindDataFalse()
{
	Tree* tree = NULL; 
	int data = 4728, notData = 24782;
	tree = TreeCreate();
	TreeInsert(tree, data);
	if(TreeIsDataFound(tree, notData) == FALSE)
	{
		printf("Test Find Data False PASSED\n");
	}
	else
	{
		printf("Test Find Data False FAILED\n");
	}
	TreeDestroy(tree);
}

void TestFindDataNull()
{
	Tree* tree = NULL; 
	int data = 4728;
	if(TreeIsDataFound(tree, data) == ERR_NOT_INITIALIZED)
	{
		printf("Test Find Data Null PASSED\n");
	}
	else
	{
		printf("Test Find Data Null FAILED\n");
	}
}

void TestPrint()
{
	Tree* tree = NULL; 
	int data1 = 4728, data2 = 24782, data3 = 4637, data4 = 10, data5 = 235124516, data6 = 15;
	tree = TreeCreate();
	TreeInsert(tree, data1);
	TreeInsert(tree, data2);
	TreeInsert(tree, data3);
	TreeInsert(tree, data4);
	TreeInsert(tree, data5);
	TreeInsert(tree, data6);
	printf("Test Pre-Order:\n");
	TreePrint(tree, PRE_ORDER);
	printf("Test In-Order:\n");
	TreePrint(tree, IN_ORDER);
	printf("Test Post-Order:\n");
	TreePrint(tree, POST_ORDER);
	TreeDestroy(tree);
}

void TestIsFullFalse()
{
	Tree* tree = NULL; 
	int data1 = 4728, data2 = 24782, data3 = 4637, data4 = 10, data5 = 235124516, data6 = 15;
	tree = TreeCreate();
	TreeInsert(tree, data1);
	TreeInsert(tree, data2);
	TreeInsert(tree, data3);
	TreeInsert(tree, data4);
	TreeInsert(tree, data5);
	TreeInsert(tree, data6);
	if(IsFullTree(tree) == FALSE)
	{
		printf("Test Is Full False PASSED\n");
	}
	else
	{
		printf("Test Is Full False FAILED\n");
	}
	TreeDestroy(tree);
}

void TestIsFullTrue()
{
	Tree* tree = NULL; 
	int data1 = 10, data2 = 8, data3 = 12, data4 = 7, data5 = 9, data6 = 11, data7 = 13;
	tree = TreeCreate();
	TreeInsert(tree, data1);
	TreeInsert(tree, data2);
	TreeInsert(tree, data3);
	TreeInsert(tree, data4);
	TreeInsert(tree, data5);
	TreeInsert(tree, data6);
	TreeInsert(tree, data7);
	if(IsFullTree(tree) == TRUE)
	{
		printf("Test Is Full True PASSED\n");
	}
	else
	{
		printf("Test Is Full True FAILED\n");
	}
	TreeDestroy(tree);
}

void TestIsFullNull()
{
	Tree* tree = NULL;
	if(IsFullTree(tree) == FALSE)
	{
		printf("Test Is Full Null PASSED\n");
	}
	else
	{
		printf("Test Is Full Null FAILED\n");
	}
}

void TestIsSimilarFalse()
{
	Tree *tree1 = NULL, *tree2 = NULL; 
	int arr1[] ={4728, 24782, 4637, 10, 235124516, 15}, size1 = sizeof(arr1)/sizeof(arr1[0]);
	int arr2[] ={10, 8, 12, 7, 9, 11, 13}, size2 = sizeof(arr2)/sizeof(arr2[0]);
	int i;
	tree1 = TreeCreate();
	tree2 = TreeCreate();
	for(i = 0;i < size1;++i)
	{
		TreeInsert(tree1, arr1[i]);
	}
	for(i = 0; i < size2;++i)
	{
		TreeInsert(tree2, arr2[i]);
	}	
	if(AreSimilarTree(tree1, tree2) == FALSE)
	{
		printf("Test Is Similar False PASSED\n");
	}
	else
	{
		printf("Test Is Similar False FAILED\n");
	}
	TreeDestroy(tree1);
	TreeDestroy(tree2);
}

void TestIsSimilarTrue()
{
	Tree *tree1 = NULL, *tree2 = NULL; 
	int arr1[] ={4728, 24782, 4637, 10, 235124516, 15}, size1 = sizeof(arr1)/sizeof(arr1[0]);
	int i;
	tree1 = TreeCreate();
	tree2 = TreeCreate();
	for(i = 0;i < size1;++i)
	{
		TreeInsert(tree1, arr1[i]);
		TreeInsert(tree2, arr1[i]);
	}	
	if(AreSimilarTree(tree1, tree2) == TRUE)
	{
		printf("Test Is Similar True PASSED\n");
	}
	else
	{
		printf("Test Is Similar True FAILED\n");
	}
	TreeDestroy(tree1);
	TreeDestroy(tree2);
}

void TestIsSimilarNull()
{
	Tree *tree1 = NULL, *tree2 = NULL; 
	int arr1[] ={4728, 24782, 4637, 10, 235124516, 15}, size1 = sizeof(arr1)/sizeof(arr1[0]);
	int i;
	tree1 = TreeCreate();
	for(i = 0;i < size1;++i)
	{
		TreeInsert(tree1, arr1[i]);
	}	
	if(AreSimilarTree(tree1, tree2) == FALSE && AreSimilarTree(tree2, tree1) == FALSE)
	{
		printf("Test Is Similar Null PASSED\n");
	}
	else
	{
		printf("Test Is Similar Null FAILED\n");
	}
	TreeDestroy(tree1);
}

void TestCountUneven()
{
	Tree* tree = NULL; 
	int data1 = 4728, data2 = 24782, data3 = 4637, data4 = 10, data5 = 235124516, data6 = 15;
	int count;
	tree = TreeCreate();
	TreeInsert(tree, data1);
	TreeInsert(tree, data2);
	TreeInsert(tree, data3);
	TreeInsert(tree, data4);
	TreeInsert(tree, data5);
	TreeInsert(tree, data6);
	count = CalcTreeLevel(tree);
	if(count == 4)
	{
		printf("Test Count Uneven PASSED\n");
	}
	else
	{
		printf("Test Count Uneven FAILED\n");
	}
	TreeDestroy(tree);
}

void TestCountEven()
{
	Tree* tree = NULL; 
	int data1 = 10, data2 = 8, data3 = 12, data4 = 7, data5 = 9, data6 = 11, data7 = 13;
	int count;
	tree = TreeCreate();
	TreeInsert(tree, data1);
	TreeInsert(tree, data2);
	TreeInsert(tree, data3);
	TreeInsert(tree, data4);
	TreeInsert(tree, data5);
	TreeInsert(tree, data6);
	TreeInsert(tree, data7);
	count = CalcTreeLevel(tree);
	if(count == 3)
	{
		printf("Test Count Even PASSED\n");
	}
	else
	{
		printf("Test Count Even FAILED\n");
	}
	TreeDestroy(tree);
}

void TestCountNull()
{
	Tree* tree = NULL;
	int count;
	count = CalcTreeLevel(tree);
	if(count == 0)
	{
		printf("Test Count Null PASSED\n");
	}
	else
	{
		printf("Test Count Null FAILED\n");
	}
}

void TestMirrorTree()
{
	Tree* tree = NULL; 
	int data1 = 4728, data2 = 24782, data3 = 4637, data4 = 10, data5 = 235124516, data6 = 15;
	int count;
	tree = TreeCreate();
	TreeInsert(tree, data1);
	TreeInsert(tree, data2);
	TreeInsert(tree, data3);
	TreeInsert(tree, data4);
	TreeInsert(tree, data5);
	TreeInsert(tree, data6);
	TreePrint(tree, IN_ORDER);
	MirrorTree(tree);
	TreePrint(tree, IN_ORDER);
	TreeDestroy(tree);
}

void TestIsPerfectFalse()
{
	Tree* tree = NULL; 
	int data1 = 4728, data2 = 24782, data3 = 4637, data4 = 10, data5 = 235124516, data6 = 15;
	int count;
	tree = TreeCreate();
	TreeInsert(tree, data1);
	TreeInsert(tree, data2);
	TreeInsert(tree, data3);
	TreeInsert(tree, data4);
	TreeInsert(tree, data5);
	TreeInsert(tree, data6);
	if(IsPerfectTree(tree) == FALSE)
	{
		printf("Test Is Perfect False PASSED\n");
	}
	else
	{
		printf("Test Is Perfect False FAILED\n");
	}
	TreeDestroy(tree);
}

void TestIsPerfectTrue()
{
	Tree* tree = NULL; 
	int data1 = 10, data2 = 8, data3 = 12, data4 = 7, data5 = 9, data6 = 11, data7 = 13;
	int count;
	tree = TreeCreate();
	TreeInsert(tree, data1);
	TreeInsert(tree, data2);
	TreeInsert(tree, data3);
	TreeInsert(tree, data4);
	TreeInsert(tree, data5);
	TreeInsert(tree, data6);
	TreeInsert(tree, data7);
	if(IsPerfectTree(tree) == TRUE)
	{
		printf("Test Is Perfect True PASSED\n");
	}
	else
	{
		printf("Test Is Perfect True FAILED\n");
	}
	TreeDestroy(tree);
}

void TestIsPerfectNull()
{
	Tree* tree = NULL;
	if(IsPerfectTree(tree) == FALSE)
	{
		printf("Test Is Perfect True PASSED\n");
	}
	else
	{
		printf("Test Is Perfect True FAILED\n");
	}
	TreeDestroy(tree);
}
