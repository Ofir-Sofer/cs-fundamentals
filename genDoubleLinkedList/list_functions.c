#include <stdlib.h>
#include "list_functions.h"

typedef int (*InnearFunction)(int _res, void* _innearContext);
/*innearContext will be used only to sum for countif*/
/*Assiting Functions:*/

static ListItr RunThroughList(ListItr _begin, ListItr _end, PredicateFunction _customeFunc, void* _context, InnearFunction _innearFunc, void* innearContext);
static int FindInnearFunc(int _res, void* _innearContext);
static int CountInnearFunc(int _res, void* _innearContext);
static int ForEachInnearFunc(int _res, void* _innearContext);

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	if(_begin == NULL || _end == NULL || _predicate == NULL)
	{
		return NULL;
	}
	return RunThroughList(_begin, _end, _predicate, _context, FindInnearFunc , NULL);
}

size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	size_t innearContext = 0;
	if(_begin == NULL || _end == NULL || _predicate == NULL)
	{
		return 0;
	}
	RunThroughList(_begin, _end, _predicate, _context, CountInnearFunc, &innearContext);
	return innearContext;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	if(_begin == NULL || _end == NULL || _action == NULL)
	{
		return NULL;
	}
	return RunThroughList(_begin, _end, _action, _context, ForEachInnearFunc, NULL);
}

/*Assiting Functions:*/

static ListItr RunThroughList(ListItr _begin, ListItr _end, PredicateFunction _customerFunc, void* _context, InnearFunction _innearFunc, void* innearContext)
{
	ListItr current = _begin;
	void* data = NULL;
	int res;
	while(current != _end)
	{
		data = ListItrGet(current);
		res = _customerFunc(data, _context);
		res = _innearFunc(res, innearContext);
		if(res == 0)
		{
			break;
		}
		current = ListItrNext(current);
	}
	return current;
}

static int FindInnearFunc(int _res, void* _innearContext)
{
	return !(_res);
}

static int CountInnearFunc(int _res, void* _innearContext)
{
	if(_res != 0)
	{
		*(size_t*)_innearContext += 1;
	}
	return 1;
}

static int ForEachInnearFunc(int _res, void* _innearContext)
{
	return _res;
}
