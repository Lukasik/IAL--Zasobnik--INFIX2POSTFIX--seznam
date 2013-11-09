#include "c204.h"

int solved;

void untilLeftPar ( tStack* s, char* postExpr, unsigned* postLen ) {
	char c = 0;

	while(c != '(' && !stackEmpty(s))
	{
		stackTop(s, &c);
		stackPop(s);

		if(c != '(' )
		{
			postExpr[(*postLen)++] = c;
		}
	}
}

void doOperation ( tStack* s, char c, char* postExpr, unsigned* postLen ) {

	int charInserted = 0;
	char stackTopChar;

	do
	{
		if(stackEmpty(s))
		{
			stackPush(s, c);
			charInserted = 1;
		}
		else if(!stackEmpty(s))
		{
			stackTop(s, &stackTopChar);
			if(stackTopChar == '(' || ((c == '*' || c == '/') && (stackTopChar == '+' || stackTopChar == '-')))
			{
				stackPush(s, c);
				charInserted = 1;
			}
			else
			{
				stackTop(s, &stackTopChar);
				stackPop(s);

				postExpr[(*postLen)++] = stackTopChar;
			}
		}
	} while(!charInserted);
}

char* infix2postfix (const char* infExpr) {

	char c;
	unsigned index = 0;
	char *postExpr = (char*) malloc(MAX_LEN);
	tStack *stack = (tStack*) malloc(sizeof(tStack));

	if(postExpr == NULL)
	{
		return NULL;
	}

	stackInit(stack);

	while((c = *(infExpr++)) != '\0')
	{
		switch(c)
		{
			case '(':
				stackPush(stack, c);
				break;

			case ')':
				untilLeftPar(stack, postExpr, &index);
				break;

			case '*':
			case '/':
			case '+':
			case '-':
				doOperation(stack, c, postExpr, &index);
				break;

			case '=':
				untilLeftPar(stack, postExpr, &index);
				postExpr[index++] = c;
				postExpr[index++] = '\0';
				break;

			default:
				postExpr[index++] = c;
				break;

		}
	}

	free(stack);

	return postExpr;
}
