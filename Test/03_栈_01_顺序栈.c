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
int getLen(SqStack *s);
Status Push(SqStack *s, SElemType e);
Status Pop(SqStack *s, SElemType *e);
SElemType getTop(SqStack *s);

int main() {
  SqStack s;
  InitStack(&s);
  getLen(&s);
  getTop(&s);

  return 0;
}

// 函数名：InitStack
// 功能：初始化一个顺序栈
// 参数：
//     s：指向 SqStack 结构体的指针，代表要初始化的顺序栈
// 返回值：
//     Status 类型，初始化成功返回 OK(1)，内存分配失败返回 OVERFLOW(-2)
Status InitStack(SqStack *s) {
  // 为栈底指针分配 MAXSIZE 个 SElemType 类型元素的内存空间
  s->base = (SElemType *)malloc(MAXSIZE * sizeof(SElemType));
  // 检查内存分配是否成功，若分配失败，s->base 为 NULL
  if (!s->base) {
    // 内存分配失败，返回 OVERFLOW 表示溢出错误
    // 返回 OVERFLOW 更好。因为 OVERFLOW 专门定义为 -2 表示溢出错误，
    // 在此场景下内存分配失败属于溢出错误，用 OVERFLOW 表意更精确；
    // 而 ERROR 只是一个通用的错误标识，语义不如 OVERFLOW 明确。
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
  if ((*s).top == (*s).base)
    return true;
  return false;
}

int getLen(SqStack *s) {
  printf("顺序栈的长度为：%d\n", s->top - s->base);
  return (*s).top - (*s).base;
}

SElemType getTop(SqStack *s) {
  if (s->top != s->base) {
    // 由于栈顶指针 s->top 指向栈顶元素的下一个位置，减去 1 后指向栈顶元素
    // 解引用该指针获取栈顶元素的值并返回
    printf("%d\n", *(s->top - 1));
    return *(s->top - 1);
  }
}

Status Push(SqStack *s, SElemType e) {
  if (s->top - s->base >= s->stacksize) {
    return OVERFLOW;
  }
  // 先将元素 e 赋值给栈顶指针指向的位置
  *s->top = e;
  // 栈顶指针后移一位，指向下一个可用位置
  s->top++;
  return OK;
}

Status Pop(SqStack *s, SElemType *e) {
  if (s->top == s->base) {
    return ERROR;
  }
  // 栈顶指针先减一，指向栈顶元素
  s->top--;
  // 将栈顶元素赋值给 e
  *e = *s->top;
  return OK;
}
Status clearStack(SqStack *s) { s->top = s->base; }

Status destroyStack(SqStack *s) {
  free(s->base);
  s->base = NULL;
  s->top = NULL;
  s->stacksize = 0;
}
