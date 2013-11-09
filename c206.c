
#include "c206.h"

int solved;
int errflg;

void DLError() {

    printf ("*ERROR* This program has performed an illegal operation.\n");
    errflg = TRUE;      
    return;
}

void DLInitList (tDLList *L)	{

	L->Act = L->First = L->Last = NULL;
}

void DLDisposeList (tDLList *L)	{

	tDLElemPtr element = L->First;

	if(element != NULL)
	{
		while(element != L->Last)
		{
			element = element->rptr;
			free(element->lptr);
		}

		free(L->Last);
	}

	L->Act = L->First = L->Last = NULL;
}

void DLInsertFirst (tDLList *L, int val)	{

	tDLElemPtr new = (tDLElemPtr) malloc(sizeof(struct tDLElem));

	if(new == NULL)
	{
		DLError();
	}
	else
	{
		new->data = val;
		new->lptr = NULL;
		new->rptr = L->First;

		if(L->First == NULL)
		{
			L->First = L->Last = new;
		}
		else
		{
			L->First->lptr = new;
			L->First = new;
		}
	}
}

void DLInsertLast(tDLList *L, int val)	{

	tDLElemPtr new = (tDLElemPtr) malloc(sizeof(struct tDLElem));

	if(new == NULL)
	{
		DLError();
	}
	else
	{
		new->data = val;
		new->lptr = L->Last;
		new->rptr = NULL;

		if(L->Last == NULL)
		{
			L->Last = L->First = new;
		}
		else
		{
			L->Last->rptr = new;
			L->Last = new;
		}
	}
}

void DLFirst (tDLList *L)	{

	L->Act = L->First;
}

void DLLast (tDLList *L)	{

	L->Act = L->Last;
}

void DLCopyFirst (tDLList *L, int *val)	{

	if(L->First == NULL)
	{
		DLError();
	}
	else
	{
		*val = L->First->data;
	}
}

void DLCopyLast (tDLList *L, int *val)	{

	if(L->Last == NULL)
	{
		DLError();
	}
	else
	{
		*val = L->Last->data;
	}
}

void DLDeleteFirst (tDLList *L)	{

	tDLElemPtr old = L->First;

	if(L->Act == L->First) L->Act = NULL;

	if(L->First != NULL)
	{
		if(L->First->rptr != NULL)
		{
			L->First = L->First->rptr;
			L->First->lptr = NULL;
		}
		else
		{
			L->First = NULL;
			L->Last = NULL;
		}
		free(old);
	}
}

void DLDeleteLast (tDLList *L)	{

	tDLElemPtr old = L->Last;

	if(L->Act == L->Last) L->Act = NULL;

	if(L->Last != NULL)
	{
		if(L->Last->lptr != NULL)
		{
			L->Last = L->Last->lptr;
			L->Last->rptr = NULL;
		}
		else
		{
			L->Last = NULL;
			L->First = NULL;
		}
		free(old);
	}
}

void DLPostDelete (tDLList *L)	{

	if(L->Act != NULL && L->Act != L->Last)
	{
		tDLElemPtr old = L->Act->rptr;

		L->Act->rptr = old->rptr;

		if(old->rptr != NULL)
		{
			old->rptr->lptr = L->Act;
		}
		else
		{
			L->Last = L->Act;
		}

		free(old);
	}
}

void DLPreDelete (tDLList *L)	{

	if(L->Act != NULL && L->Act != L->First)
	{
		tDLElemPtr old = L->Act->lptr;

		L->Act->lptr = old->lptr;

		if(old->lptr != NULL)
		{
			old->lptr->rptr = L->Act;
		}
		else
		{
			L->First = L->Act;
		}

		free(old);
	}
}

void DLPostInsert (tDLList *L, int val) {

	if(L->Act != NULL)
	{
		tDLElemPtr new = (tDLElemPtr) malloc(sizeof(struct tDLElem));

		if(new == NULL)
		{
			DLError();
		}
		else
		{
			new->lptr = L->Act;
			new->rptr = L->Act->rptr;
			new->data = val;

			if(L->Act->rptr == NULL)
			{
				L->Last = new;
			}
			else
			{
				L->Act->rptr->lptr = new;
			}

			L->Act->rptr = new;
		}
	}
}

void DLPreInsert (tDLList *L, int val)		{

	if(L->Act != NULL)
	{
		tDLElemPtr new = (tDLElemPtr) malloc(sizeof(struct tDLElem));

		if(new == NULL)
		{
			DLError();
		}
		else
		{
			new->lptr = L->Act->lptr;
			new->rptr = L->Act;
			new->data = val;

			if(L->Act->lptr == NULL)
			{
				L->First = new;
			}
			else
			{
				L->Act->lptr->rptr = new;
			}

			L->Act->lptr = new;
		}
	}
}

void DLCopy (tDLList *L, int *val)	{

	if(L->Act == NULL)
	{
		DLError();
	}
	else
	{
		*val = L->Act->data;
	}
}

void DLActualize (tDLList *L, int val) {
	if(L->Act != NULL)
	{
		L->Act->data = val;
	}
}

void DLSucc (tDLList *L)	{

	if(L->Act == L->Last && L->Act != NULL)
	{
		L->Act = NULL;
	}
	else if(L->Act != NULL)
	{
		L->Act = L->Act->rptr;
	}
}


void DLPred (tDLList *L)	{

	if(L->Act == L->First && L->Act != NULL)
	{
		L->Act = NULL;
	}
	else if(L->Act != NULL)
	{
		L->Act = L->Act->lptr;
	}
}

int DLActive (tDLList *L) {

	return L->Act != NULL;
}

