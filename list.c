#include <stdio.h>
#include <stdlib.h>
#include "list.h"




struct LIST * ListCreate(){
    if (countList==listsize){
        return NULL;
    }
    else{
        struct LIST * head=& listarr[countList];
        countList= countList+1;
        return head;
    }

}

int ListCount(struct LIST* list){
    return list->count;
}

void *ListFirst(struct LIST* list){
    if(list->first==NULL)
	return NULL;
    list->current=list->first;
    return list->first->data;
}

void *ListLast(struct LIST*list){
    if(list->last==NULL)
	return NULL;
    list->current=list->last;
    return list->last->data;
}
void *ListNext(struct LIST* list){
    list->current=list->current->next;
    if (list->current==NULL){
        return NULL;}
    return list->current->data;
}

void *ListPrev(struct LIST* list){
   list->current=list->current->previous;
    if (list->current==NULL){
        return NULL;}
    return list->current->data;
}

void * ListCurr(struct LIST* list){

    if (list->current==NULL){return NULL;}
    return list->current->data;
}

int ListADD(struct LIST *list, void* item){

    if(nodeCount>=nodesize){
        return -1;
    }
    if(list->count==0){
        list->current=&Nodearr[nodeCount];
        list->first=list->current;
        list->last=list->current;
        list->count=list->count+1;
        list->current->data=item;
        nodeCount++;
        return 0;
    }
    if (((list->current) < (list->first))&( list->current->data==NULL)){

        list->current=&Nodearr[nodeCount];
        list->current->data=item;
        list->first->previous=list->current;
        list->current->previous=NULL;
        list->current->next=list->first;
        list->first= list->current;
        list->count=list->count+1;
        nodeCount++;
        return 0;
    }
    if (((list->current) > (list->last))&( list->current->data==NULL)){

        list->current=&Nodearr[nodeCount];
        list->current->data=item;
        list->last->next=list->current;
        list->current->previous=list->last;
        list->current->next=NULL;
        list->last= list->current;
        list->count=list->count+1;
        nodeCount++;
        return 0;
    }
    if (list->current==list->first){

        if(list->count>1){
            list->current=&Nodearr[nodeCount];
            list->current->data=item;
            list->current->next=list->first->next;
            list->current->previous=list->first;
            list->first->next=list->current;
            list->count=list->count+1;
            nodeCount++;
            return 0;
        }
    list->current=&Nodearr[nodeCount];
    list->current->data=item;
    list->first->next=list->current;
    list->current->previous=list->first;
    list->count=list->count+1;
    list->last=list->current;
    nodeCount++;
    return 0;
    }
    if(list->current==list->last){
       list->current=&Nodearr[nodeCount];
       list->current->data=item;
       list->last->next=list->current;
       list->current->previous=list->last;
       list->current->next=NULL;
       list->last=list->current;
       list->count=list->count+1;
       nodeCount++;
       return 0;
    }

    struct NODE * temp=NULL;
    temp->data=item;
    temp->next=list->current->next;
    temp->previous=list->current;
    list->current->next=temp;
    list->current->next->previous=temp;

    list->current=&Nodearr[nodeCount];
    list->current->data=item;
    list->current->previous=temp->previous;
    list->current->next=temp->next;
    temp->previous->next=list->current;
    temp->next->previous=list->current;
    list->count=list->count+1;
    nodeCount++;
    return 0;
}
int ListInsert(struct LIST *list,void* item){

}

int ListAppend(struct LIST *list,void * item){

  if (nodeCount>=nodesize){ return -1;}
  else
  {
    list->current=&Nodearr[nodeCount];
    list->current->data=item;
    list->last->next= list->current;
    list->current->next=NULL;
    list->current->previous=list->last;
    list->last=list->current;
    list->count=list->count+1;
    nodeCount++;
    return 0;
  }
}

int ListPrepend(struct LIST*list,void * item){

  if (nodeCount>=nodesize){return -1;}
  else
  {
    list->current=&Nodearr[nodeCount];
    list->current->data=item;
    list->first->previous=list->current;
    list->current->next=list->first;
    list->first=list->current;
    list->count=list->count+1;
    nodeCount++;
    return 0;
  }
}

void * ListRemove(struct LIST* list){

    void* ptr= list->last->data;

    if (nodeCount==0){return NULL;}

    if(list->count==1)
    {
        list->current->data=NULL;
        list->current->next=NULL;
        list->current->previous=NULL;
        list->count=list->count-1;
        list->current=list->first;
        list->first=NULL;
        list->last=NULL;
        nodeCount--;
        return ptr;
    }
    if(list->current==list->last)
    {
        list->last=list->current->previous;
        list->current->previous->next=NULL;
        list->current->data=NULL;
        list->current->next=NULL;
        list->current->previous=NULL;
        list->count=list->count-1;
        return ptr;
    }
    if(list->current==list->first)
    {
        list->first=list->current->next;
        list->current->next->previous=NULL;
        list->current->data=NULL;
        list->current->next=NULL;
        list->current->previous=NULL;
        list->current=list->first;
        list->count=list->count-1;
        return ptr;
    }
    if((list->current!=list->first) & (list->current!=list->last))
    {
        struct NODE* temp= list->current->next;
        list->current->previous->next=list->current->next;
        list->current->next->previous=list->current->previous;
        list->current->data=NULL;
        list->current->next=NULL;
        list->current->previous=NULL;
        list->current=temp;
        list->count=list->count-1;
        return ptr;
    }
}

void ListConcat(struct LIST* list1,struct LIST* list2){

    if((list1->count!=0) || (list2->count!=0)){
        list1->last->next=list2->first;
        list2->first->previous=list1->last;
        list1->count=(list1->count)+(list2->count);
        list1->last=list2->last;
        list2->current=NULL;
        list2->first=NULL;
        list2->count=0;
        list2->last=NULL;
    }
}
void *ListTrim(struct LIST* list){

    void* ptr= list->last->data;

    if (nodeCount==0){return NULL;}

    if(list->count==1)
    {
        list->last->data=NULL;
        list->last->next=NULL;
        list->last->previous=NULL;
        list->current=NULL;
        list->count=list->count-1;
        list->first=NULL;
        return ptr;
    }
    else
    {
        list->current=list->last->previous;
        list->last->data=NULL;
        list->last->next=NULL;
        list->last->previous=NULL;
        list->last=list->current;
        list->count=list->count-1;
        return ptr;
    }
}
void print(struct LIST* list){
        if(list->current==NULL){
        printf("No list exist\n");
        return ;
        }
	int count= list->count;
	int*first=ListFirst(list);
	printf("%d\n",*first);
	for(int i=1;i<count;i++){
		int*next=ListNext(list); 
		printf("%d\n",*next);
	}
}
void *ListSearch(struct LIST* list,int (*comparator)(void*,void*),void* comparisonArg)
{

	if(list->current==NULL || list->count==0){
         return NULL;}
        if(comparisonArg==NULL){
        return NULL;}

        int check=comparator(ListFirst(list),comparisonArg);
        while(ListNext(list)!=NULL && check!=1)
         {
		check= comparator(ListFirst(list),comparisonArg);
		if(check==1){return list->current->data;}	
	}
        return NULL;
}

