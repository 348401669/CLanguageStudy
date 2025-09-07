

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;
typedef struct node {
  ElemType data;
  struct node *next;
} Node, *LinkList;

// 函数原型
// 因函数调用在函数声明之前，所以需在调用之前提前声明函数原型，否则报错
Status InitList(LinkList *L);
bool isEmpty(LinkList L);
Status insertFromHead(LinkList L, ElemType elem);
void printList(LinkList L);
int getLen(LinkList L);
Status insertFromTail(LinkList L, ElemType elem);
Status insert(LinkList L, int pos, ElemType elem);
Status deleteFirst(LinkList L);
Status deleteLast(LinkList L);
Status deleteByPos(LinkList L, int pos);
Status clearList(LinkList L);
Status destroyList(LinkList *L);

