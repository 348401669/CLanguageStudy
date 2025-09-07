#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int SElemType;
typedef int Status;

// 定义顺序栈结构体
typedef struct {
  // 栈底指针，指向栈的起始位置，用于存储栈的第一个元素
  SElemType *base;
  // 栈顶指针，指向栈顶元素的下一个位置
  SElemType *top;
  // 栈的当前可使用的最大容量
  int stacksize;
} SqStack, *StackPtr;

Status InitStack(SqStack *s);
bool isEmpty(SqStack *s);
bool isFull(SqStack *s);
int getLen(SqStack *s);
Status Push(SqStack *s, SElemType e);
SElemType Pop(SqStack *s);
SElemType getTop(SqStack *s);
Status printStack(SqStack *s);
Status clearStack(SqStack *s);
Status destroyStack(SqStack *s);

int main() {
  SqStack s;
  InitStack(&s);
  getLen(&s);
  getTop(&s);
  for (int i = 10; i <= 100; i += 10) {
    Push(&s, i);
  }
  printStack(&s);

  for (int i = 0; i < 5; i++)
    Pop(&s);
  printStack(&s);
  clearStack(&s);
  printStack(&s);
  destroyStack(&s);
  printStack(&s);

  return 0;
}

// 函数名：InitStack
// 功能：初始化一个顺序栈
Status InitStack(SqStack *s) {
  // 为栈底指针分配 MAXSIZE 个 SElemType 类型元素的内存空间
  s->base = (SElemType *)malloc(MAXSIZE * sizeof(SElemType));
  // 检查内存分配是否成功，若分配失败，s->base 为 NULL
  if (!s->base) {
    return OVERFLOW;
  }
  // 初始化栈顶指针，使其指向栈底指针的位置，此时栈为空
  s->top = s->base;
  // 设置栈的当前可使用的最大容量为 MAXSIZE
  s->stacksize = MAXSIZE;
  // 输出栈初始化成功的信息，并打印栈的长度
  printf("栈初始化成功，容量为：%d\n", s->stacksize);
  // 初始化成功，返回 OK
  return OK;
}

bool isEmpty(SqStack *s) {
  if (s->top == s->base) // 修正：使用==而不是=
    return true;
  return false;
}

bool isFull(SqStack *s) {
  if (s->top - s->base >= s->stacksize) {
    return true;
  }
  return false;
}

int getLen(SqStack *s) {
  int len = s->top - s->base;
  printf("顺序栈的长度为：%d\n", len);
  return len;
}

SElemType getTop(SqStack *s) {
  if (s->top != s->base) {
    SElemType top = *(s->top - 1);
    printf("栈顶元素：%d\n", top);
    return top;
  }
  printf("栈为空，无栈顶元素\n");
  return 0; // 栈为空时返回0
}

Status printStack(SqStack *s) {
  if (s->base == NULL) {
    return ERROR;
  }
  printf("栈元素从栈底到栈顶为：");
  for (SElemType *p = s->base; p < s->top; p++) {
    printf("%d ", *p);
  }
  printf("\n");
  return OK;
}

Status Push(SqStack *s, SElemType e) {
  if (s->top - s->base >= s->stacksize) {
    return OVERFLOW;
  }
  // 先将元素 e 赋值给栈顶指针指向的位置
  *s->top = e;
  // 栈顶指针后移一位，指向下一个可用位置
  s->top++;
  printf("元素 %d 入栈成功\n", e);
  return OK;
}

SElemType Pop(SqStack *s) {
  if (s->top == s->base) {
    return ERROR;
  }
  // 栈顶指针先减一，指向栈顶元素
  s->top--;
  // 将栈顶元素赋值给 e
  SElemType e = *s->top;
  printf("元素 %d 出栈成功\n", e);
  return e;
}

Status clearStack(SqStack *s) {
  if (s->base == NULL) {
    return ERROR;
  }
  s->top = s->base;
  printf("栈已清空\n");
  return OK;
}

// 函数名：destroyStack
// 功能：销毁一个顺序栈，释放栈所占用的内存空间
// 参数：
//     s：指向 SqStack 结构体的指针，代表要销毁的顺序栈
// 返回值：
//     返回 Status 类型，销毁成功返回 OK，若栈已为空则返回 ERROR
Status destroyStack(SqStack *s) {
  // 检查栈底指针是否为 NULL，若为 NULL 说明栈已为空，返回 ERROR
  if (s->base == NULL) {
    return ERROR;
  }
  // 释放栈底指针指向的内存空间
  free(s->base);
  // 将栈底指针置为 NULL，避免悬空指针
  s->base = NULL;
  // 将栈顶指针置为 NULL，避免悬空指针
  s->top = NULL;
  // 将栈的容量置为 0
  s->stacksize = 0;
  // 输出栈已销毁的信息，包含栈底指针、栈顶指针和栈容量
  printf("栈已销毁，base：%p，top：%p，stacksize：%d\n", s->base, s->top,
         s->stacksize);
  // 销毁成功，返回 OK
  return OK;
}