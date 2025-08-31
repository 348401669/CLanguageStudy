// 双向链表
// 双向链表的每个结点包含一个数据元素和两个指针，一个指向前驱结点，一个指向后继结点。
// 双向链表的头结点的前驱指针为空，尾结点的后继指针为空。

// todo 删指定位置 （ delete(L, 1)有问题，并没有邮删除）

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
Status deleteHead(LinkList L);
Status deleteTail(LinkList L);
Status delete(LinkList L, int pos);
Status clearList(LinkList L);
Status destroyList(LinkList *L);

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
  deleteHead(L);
  deleteTail(L);
  // delete (L, 1);
  delete (L, 3);
  delete (L, 5);
  delete (L, 7);
  delete (L, 10);
  // if (!isEmpty(L)) {
  //   delete (L, 1);
  // }
  // clearList(L);
  destroyList(&L);

  return 0;
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
    return true;
  }
  printf("链表不为空\n");
  return false;
}

// 5 打印链表
void printList(LinkList L) {
  if (!L) {
    printf("链表未初始化\n");
    return;
  }
  printf("Head");
  Node *cur = L->next;
  while (cur) {
    printf("<=>%d", cur->data);
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

// 9 删首元
Status deleteHead(LinkList L) {
  if (!L || !L->next)
    return ERROR;
  Node *del = L->next;
  L->next = del->next;
  free(del);
  printf("删除首元成功\n");
  printList(L);
  return OK;
}

// 10 删尾
Status deleteTail(LinkList L) {
  if (!L || !L->next)
    return ERROR;
  Node *cur = L;
  while (cur->next) {
    cur = cur->next;
  }
  cur->prev->next = NULL;
  free(cur);
  printf("删除尾结点成功\n");
  printList(L);
  return OK;
}

// 11 删指定位置 （todo: delete(L,1)有问题，并没有邮删除）
Status delete(LinkList L, int pos) {
  if (!L || !L->next || pos <= 0) {
    printf("参数错误或链表为空\n");
    return ERROR;
  }

  Node *cur = L->next; // 指向首元节点
  int i = 1;           // 从1开始计数

  // 找到第pos个节点
  while (cur != NULL && i < pos) {
    cur = cur->next;
    ++i;
  }

  if (cur == NULL) { // pos超出链表长度
    printf("位置%d超出链表范围\n", pos);
    return ERROR;
  }

  // 删除节点
  cur->prev->next = cur->next;
  if (cur->next != NULL) {
    cur->next->prev = cur->prev;
  }

  free(cur);
  printf("删除链表第%d个元素成功\n", pos);
  printList(L);
  return OK;
}

// 12 清空链表（循环删除首元结点）
Status clearList(LinkList L) {
  if (!L)
    return ERROR;
  // Node *cur = L->next;
  while (L->next) {
    deleteHead(L);
  }

  printf("链表已清空");
  return OK;
}

// 13 销毁链表
// 当前代码存在逻辑问题，判断条件 `!(*L)->next` 会导致空链表无法被销毁，
// 并且销毁后应该将指针置为 NULL 避免野指针。以下是修正后的代码。
Status destroyList(LinkList *L) {
  if (!(*L))
    return ERROR;
  clearList(*L);
  free(*L);
  *L = NULL; // 头指针置为空，避免野指针
  return OK;
}