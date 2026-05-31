#ifndef __LISTINTERNAL_H__
#define __LISTINTERNAL_H__

typedef struct Node
{
	void* m_data;
	struct Node* m_next;
	struct Node* m_prev;
}Node;

struct List
{
	Node m_head;
	Node m_tail;
};

/*Assiting Functions:*/
void Insert(Node* _new, Node* _rightRef);
void Remove(Node* _remove);

#endif /* __LISTINTERNAL_H__ */
