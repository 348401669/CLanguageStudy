#include "02_线性表_05_链表应用_01_定义和函数原型.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 函数：创建新结点
// 功能：创建一个新的节点，节点的数据域为 elem，指针域为 NULL
// 参数：elem 节点的数据域
// 返回值：新创建的节点指针
Node *createNode(ElemType elem) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode) {
    printf("内存分配失败\n");
    return NULL;
  }
  newNode->data = elem;
  newNode->next = NULL;
  return newNode;
}

// 函数：初始化链表
// 使用二级指针，以便在函数内部修改头指针本身，同时分配内存
// 二级指针，是指向指针的指针，它可以用来修改指针本身的值，而不仅仅是指针指向的内存中的值
Status InitList(LinkList *L) {
  *L = (Node *)malloc(sizeof(Node)); // 分配头结点内存
  if (!(*L)) {
    printf("内存分配失败\n");
    return ERROR;
  }
  (*L)->next = NULL;
  printf("链表初始化成功\n");
  return OK;
}

// 函数：判断链表是否为空
bool isEmpty(LinkList L) {
  if (L == NULL) {
    printf("链表不存在\n");
    return true;
  }
  if (L->next == NULL) {
    printf("链表为空\n");
    return true;
  }
  printf("链表不为空\n");
  return false;
}

// 函数：求链表长度
int getLen(LinkList L) {
  int len = 0;
  Node *cur = L->next;
  while (cur != NULL) {
    len++;
    cur = cur->next;
  }
  return len;
}

// 函数：遍历打印链表
// 功能：遍历打印链表中的所有元素
// 参数：L 链表头指针
// 返回值：无
void printList(LinkList L) {
  if (L->next == NULL) {
    printf("链表为空\n");
    return;
  }

  Node *cur = L->next;
  printf("链表元素为：");
  while (cur != NULL) {
    printf("%d", cur->data);
    if (cur->next != NULL) {
      printf(" -> ");
    }
    cur = cur->next;
  }
  printf("\n链表长度为：%d\n", getLen(L));
}

// 函数：带头结点的链表插入元素
// 头插法：在头结点之后插入元素

Status insertFromHead(LinkList L, ElemType elem) {
  if (L == NULL) {
    printf("链表不存在\n");
    return ERROR;
  }
  Node *newNode = createNode(elem);
  if (!newNode) {
    printf("内存分配失败\n");
    return ERROR;
  }
  newNode->next = L->next;
  L->next = newNode;
  printList(L);
  return OK;
}

// 尾插法：在尾结点之后插入元素

Status insertFromTail(LinkList L, ElemType elem) {
  if (L == NULL) {
    printf("链表不存在\n");
    return ERROR;
  }

  Node *newNode = createNode(elem);
  if (!newNode) {
    return ERROR;
  }

  Node *cur = L;
  while (cur->next) {
    cur = cur->next;
  }

  newNode->next = cur->next;
  cur->next = newNode;
  printList(L);
  return OK;
}

// 指定位置插入法：在指定位置的插入元素
Status insert(LinkList L, int pos, ElemType elem) {
  // 如果插入位置小于等于0，直接报错
  if (pos <= 0 || L == NULL) {
    printf("插入位置错误或链表不存在\n");
    return ERROR;
  }
  Node *newNode = createNode(elem);
  if (newNode == NULL) {
    printf("内存分配失败\n");
    return ERROR;
  }
  // 如果插入位置为1，则是在头后面插入
  if (pos == 1) {
    newNode->next = L->next;
    L->next = newNode;
    printList(L);
    return OK;
  }

  // 如果插入位置不为1，则是在内部（或尾部）插入
  // 找到插入位置的前驱指针
  // 当pos大于列表的长度时，则是在尾部插入（下面的逻辑参插入到最后一个元素的后面）
  Node *cur = L->next;
  int i = 1;
  while (cur->next && i < pos - 1) {
    cur = cur->next;
    ++i;
  }
  // 插入元素逻辑
  newNode->next = cur->next;
  cur->next = newNode;
  printList(L);
  return OK;
}

// 删除头结点
Status deleteFirst(LinkList L) {
  if (L->next == NULL) {
    printf("链表为空，无法删除头结点\n");
    return ERROR;
  }
  Node *del = L->next;
  L->next = del->next;
  free(del);
  printList(L);
  return OK;
}

// 删除尾结点
Status deleteLast(LinkList L) {
  if (L->next == NULL) {
    printf("链表为空，无法删除尾结点\n");
    return ERROR;
  }
  Node *cur = L;
  // 找到尾结点的前驱结点
  while (cur->next && cur->next->next) {
    cur = cur->next;
  }
  Node *del = cur->next;
  cur->next = NULL;
  free(del);
  printList(L);
  return OK;
}

// 删除指定位置结点
Status deleteByPos(LinkList L, int pos) {
  if (pos < 1) {
    printf("删除位置错误,删除位置从1开始。\n");
    return ERROR;
  }
  Node *cur = L;
  int i = 0;
  // 找到要删除结点的前驱结点
  while (cur && i < pos - 1) {
    cur = cur->next;
    ++i;
  }
  if (cur->next == NULL) {
    printf("删除位置错误,删除位置超出链表长度。\n");
    return ERROR;
  }
  Node *del = cur->next;
  cur->next = del->next;
  free(del);
  printList(L);
  return OK;
}

// 清空链表
// 当前代码存在一个小问题，`cur` 初始化为 `L`
// 后，在循环里未使用到该初始化值，后续 `cur` 直接被赋值为 `L->next`。
// 这里可以直接在循环内部定义 `cur` 变量，逻辑更清晰。同时 `printList`
// 在链表为空时会引发逻辑问题，因为会尝试获取 `L->next` 并遍历。
// 以下是修正后的代码：
Status clearList(LinkList L) {
  Node *cur;
  while (L->next) {
    cur = L->next;
    L->next = cur->next;
    free(cur);
  }
  L->next = NULL;
  printf("链表已清空\n");
  return OK;
}

// 销毁链表
// 当前代码存在问题，`destroyList` 函数接收的是一级指针，
// 在调用该函数后，原链表头指针仍指向已释放的内存，会形成野指针。
// 应使用二级指针，以便在函数内部修改头指针本身，使其指向 NULL，避免野指针问题。
Status destroyList(LinkList *L) {
  if (L == NULL || *L == NULL) {
    return ERROR;
  }
  clearList(*L);
  free(*L);
  *L = NULL;
  printf("链表已销毁\n");
  return OK;
}