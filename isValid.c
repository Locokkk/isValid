#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

typedef int STDataType;
struct Stack
{
	STDataType* _array;
	size_t _top;
	size_t _capacity;
};

typedef struct Stack Stack;

void StackInit(Stack *ps);
void StackDestory(Stack *ps);
void StackPush(Stack *ps, STDataType x);
void StackPop(Stack *ps);
STDataType StackTop(Stack *ps);
size_t StackSize(Stack *ps);
bool StackEmpty(Stack *ps);

void StackInit(Stack *ps)
{
	assert(ps);
	ps->_array = NULL;
	ps->_capacity = 0;
	ps->_top = 0;
}

void StackDestory(Stack *ps)
{
	assert(ps);
	if (ps->_array != NULL)
	{
		free(ps->_array);
		ps->_array = NULL;
		ps->_capacity = 0;
		ps->_top = 0;
	}
}

void StackPush(Stack *ps, STDataType x)
{
	assert(ps);
	if (ps->_top == ps->_capacity)
	{
		size_t newcapacity = (ps->_capacity == 0 ? 2 : ps->_capacity * 2);
		ps->_array = (STDataType*)realloc(ps->_array, sizeof(STDataType)*newcapacity);
		ps->_capacity = newcapacity;
	}
	ps->_array[ps->_top] = x;
	ps->_top++;
}

void StackPop(Stack *ps)
{
	assert(ps&&ps->_top > 0);
	--ps->_top;
}
STDataType StackTop(Stack *ps)
{
	assert(ps&&ps->_top > 0);
	return ps->_array[ps->_top - 1];
}

bool StackEmpty(Stack *ps)
{
	assert(ps);
	return ps->_top == 0;
}
size_t StackSize(Stack *ps)
{
	assert(ps);
	return ps->_top;
}


bool isValid(char * s)
{
	Stack st;
	int count_left = 0;
	int count_right = 0;
	StackInit(&st);
	char* symbol[3] = { "()","[]","{}" };
	while (*s)
	{
		if (*s == '(' || *s == '[' || *s == '{')
		{
			StackPush(&st, *s);// »Î’ª
			++count_left;
		}
		else if (*s == ')' || *s == ']' || *s == '}')
		{
			++count_right;

			if (StackEmpty(&st))
				return false;

			STDataType top = StackTop(&st);
			StackPop(&st);

			for (size_t i = 0;i < 3;++i)
			{
				if (*s == symbol[i][1])
				{
					if (top != symbol[i][0])
					{
						StackDestory(&st);
						return false;
					}
					else
					{
						break;
					}
				}
			}
		}
		++s;
	}

	if (count_left != count_right)
	{
		return false;
	}
	return true;

	return StackEmpty(&st);
}