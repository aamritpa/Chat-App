#ifndef LIST_H
#define LIST_H


#define listsize 1500
#define nodesize 200

struct NODE{
    void *data;
    struct NODE* next;
    struct NODE* previous;
};

struct LIST{
    struct NODE * current;
    struct NODE* first;
    struct NODE* last;
    int count;
};

struct LIST  listarr[listsize];
struct NODE  Nodearr[nodesize];

int nodeCount;
int countList;

struct LIST * ListCreate();

int ListCount(struct LIST* list);

void *ListFirst(struct LIST* list);

void *ListLast(struct LIST*list);

void *ListNext(struct LIST* list);

void *ListPrev(struct LIST* list);

void * ListCurr(struct LIST* list);

int ListADD(struct LIST *list, void* item);

int ListInsert(struct LIST *list,void* item);

int ListAppend(struct LIST *list,void * item);

int ListPrepend(struct LIST*list,void * item);

void * ListRemove(struct LIST* list);

void print(struct LIST* list);

void ListConcat(struct LIST* list1,struct LIST* list2);

void *ListTrim(struct LIST* list);

void *ListSearch(struct LIST* list,int (*comparator)(void*,void*),void* comparisonArg);


#endif
