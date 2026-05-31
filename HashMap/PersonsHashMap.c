#include <stdio.h>
/*#include <stdlib.h>for malloc*/
#include <string.h>
#include "GenericDoubleLinkedList.h"
#include "list_itr.h"
#include "list_functions.h"

typedef struct Person
{
	int m_id;
	char m_name[50];
	int m_age;
}Person;

/*Main Functions:*/
void* InsertPerson (const HashMap* _map, char* _name);
int	FindNameActionFunc(const void* _key, void* _value, void* _context);

/*Assisting Functions:*/
size_t PersonHashFunc(const void* _key);
int PersonEqualityFunc(void* _firstKey, void* _secondKey);

int main (void)
{
	int i;
	HashMap *personHash = NULL;
	List *pValue;
	Person persons[] = {{123,"Ofir Sofer", 33}, {456,"Shir Sofer", 33}, {845,"Balu Sofer", 3}, {321,"Maor Sofer", 0}, {527,"Din Plombo", 26}, {865,"Or Shvartz", 30}, {369,"Yosi Cohen", 45}, {258,"Ofir Cohen", 33}, {456,"Shir Shvartz", 33}, {852,"Maor Cohen", 33}, {741,"Din koren", 16}};
	personHash = HashMap_Create(16, PersonHashFunc, PersonEqualityFunc);
	for(i = 0;i < 11;++i)
	{
		InsertPerson(personHash, persons[i]);
	}
	HashMap_Find(_map, persons[1], &pValue);/*find all Ofirs*/
	HashMap_Destroy(personHash, NULL, ListDestroy);
}
void* InsertPerson(const HashMap* _map, Person* _person)
{
	List *pValue;
	if(HashMap_Find(_map, _person, &pValue) != MAP_SUCCESS)/*key exist*/
	{
		pValue = ListCreate();
		
	}
	ListPushHead(pValue, void* _item_person);
}

int	FindNameActionFunc(const void* _key, void* _value, void* _context)
{
	if(HashMap_Find() == MAP_SUCCESS)
	{
		return 0;/*found*/
	}
	
	return 1;/* not found*/
}

/*Assisting Functions:*/

size_t PersonHashFunc(const void* _key)
{
	size_t index = 0;
	char* name = ((Person*)_key)->m_name
	while(name != ' ')
	{
		index += name;
		++name;
	}
	return index;
}

int PersonEqualityFunc(void* _firstKey, void* _secondKey)
{
	if(strcmp((char*)_firstKey, (char*)_secondKey))/*Not the Same*/
	{
		return 0;
	}
	return 1;
}
