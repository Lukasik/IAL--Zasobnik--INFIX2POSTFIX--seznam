#include "c202.h"

int STACK_SIZE = MAX_STACK;
int solved;

void stackError ( int error_code ){

	static const char* SERR_STRINGS[MAX_SERR+1] = {"Unknown error","Stack error: INIT","Stack error: PUSH","Stack error: TOP"};
	if ( error_code <= 0 || error_code > MAX_SERR )
		error_code = 0;
	printf ( "%s\n", SERR_STRINGS[error_code] );
	err_flag = 1;
}

void stackInit ( tStack* s ) {

	if(s == NULL) stackError(SERR_INIT);
	else
	{
		s->top = -1;
	}
}

int stackEmpty ( const tStack* s ) {

	return s->top==-1;

}

int stackFull ( const tStack* s ) {
	return s->top==(STACK_SIZE-1);
}

void stackTop ( const tStack* s, char* c ) {
	if(!stackEmpty(s))
	{
		*c = s->arr[s->top];
	}
	else
	{
		stackError(SERR_TOP);
	}
}


void stackPop ( tStack* s ) {
	if(!stackEmpty(s))
	{
		s->top--;
	}
}


void stackPush ( tStack* s, char c ) {
	if(stackFull(s))
	{
		stackError(SERR_PUSH);
	}
	else
	{
		s->arr[++s->top] = c;
	}
}
