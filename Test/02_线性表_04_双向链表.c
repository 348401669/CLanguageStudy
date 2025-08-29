#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef struct node {
  ElemType data;
  struct node *prev;
  struct node *next;
} Node, *LinkList;
Node *createNode(ElemType elem);
Status initList(LinkList *L);
int getLen(LinkList L);
bool isEmpty(LinkList L);
void printList(LinkList L);
Status insertHead(LinkList L, ElemType elem);
Status insertTail(LinkList L, ElemType elem);
Status insert(LinkList L, int pos, ElemType elem);

int main() {
  LinkList L;
  initList(&L);
  getLen(L);
  isEmpty(L);
  insertHead(L, 10);
  insertHead(L, 20);
  insertHead(L, 30);
  insertHead(L, 40);
  printList(L);
  insertTail(L, 50);
  insertTail(L, 60);
  insertTail(L, 70);
  insertTail(L, 80);
  insertTail(L, 90);
  printList(L);
  insert(L, 3, 999);
  insert(L, 6, 666);
  insert(L, 9, 333);
  insert(L, 100, 111);
  insert(L, 1, 1024);
  insert(L, 14, 2048);
  printList(L);
}

// 1 创建结点
Node *createNode(ElemType elem) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode) {
    printf("分配内存空间失败");
    return NULL;
  }
  newNode->data = elem;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

// 2 初始化双向链表
Status initList(LinkList *L) {
  *L = (Node *)malloc(sizeof(Node));
  if (!(*L))
    return ERROR;
  (*L)->prev = NULL;
  (*L)->next = NULL;
  printf("链表初始化成功\n");
  return OK;
}

// 3 获取链表长度
int getLen(LinkList L) {
  if (!L)
    return 0;
  int len = 0;
  Node *cur = L;
  while (cur->next) {
    ++len;
    cur = cur->next;
  }
  printf("链表长度为：%d\n", len);
  return len;
}

// 4 判空
bool isEmpty(LinkList L) {
  if (getLen(L) == 0) {
    printf("链表为空\n");
    return false;
  }
  printf("链表不为空\n");
  return true;
}

// 5 打印链表
void printList(LinkList L) {
  Node *cur = L;
  if (getLen(L) == 0) {
    printf("Head");
    return;
  }
  printf("Head");
  while (cur->next) {
    printf("<=>%d", cur->next->data);
    cur = cur->next;
  }
  printf("\n");
  return;
}

// 6 头插
Status insertHead(LinkList L, ElemType elem) {
  if (!L)
    return ERROR;
  Node *newNode = createNode(elem);
  if (!newNode)
    return ERROR;
  newNode->next = L->next;
  newNode->prev = L;
  if (L->next != NULL) {
    L->next->prev = newNode;
  }
  L->next = newNode;
  return OK;
}

// 7 尾插
Status insertTail(LinkList L, ElemType elem) {
  if (!L)
    return ERROR;
  Node *newNode = createNode(elem);
  if (!newNode)
    return ERROR;
  Node *cur = L;
  while (cur->next) {
    cur = cur->next;
  }
  cur->next = newNode;
  newNode->prev = cur;

  return OK;
}

// 8 任意位置插
Status insert(LinkList L, int pos, ElemType elem) {
  if (!L || pos <= 0)
    return ERROR;
  Node *newNode = createNode(elem);
  if (!newNode)
    return ERROR;
  Node *cur = L;
  int index = 0;
  while (cur->next && index < pos) {
    cur = cur->next;
    ++index;
  }
  if (cur->next == NULL) {
    insertTail(L, elem);
    return OK;
  }

  newNode->next = cur;
  newNode->prev = cur->prev;
  cur->prev->next = newNode;
  cur->prev = newNode;
  return OK;
}

// 9 删头

// 10 删尾

// 11 删指定位置

// 12 清空链表

// 13 销毁链表