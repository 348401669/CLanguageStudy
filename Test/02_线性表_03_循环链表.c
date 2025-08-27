#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;
typedef struct node {
  ElemType data;
  struct node *next;
} Node, *LinkList;

// 函数原型签名
Status initList(LinkList *L);
Node *createNode(ElemType elem);
void printList(LinkList L);
Status insertFromHead(LinkList L, ElemType elem);
Status insertFromTail(LinkList L, ElemType elem);
Status insert(LinkList L, int pos, ElemType elem);

int main() {
  LinkList L;
  initList(&L);
  insertFromHead(L, 1);
  insertFromHead(L, 2);
  insertFromHead(L, 3);
  insertFromHead(L, 4);
  insertFromHead(L, 5);
  insertFromTail(L, 6);
  insertFromTail(L, 7);
  insertFromTail(L, 8);
  insertFromTail(L, 9);
  insertFromTail(L, 10);
  insert(L, 0, 100);
}

// 初始化循环链表
Status initList(LinkList *L) { // *L 指向头指针
  *L = (LinkList)malloc(sizeof(Node));
  if (*L == NULL) {
    return ERROR;
  }
  (*L)->next = *L; // 头指针指向头结点
  return OK;
}

// 创建单个结点，返回结点指针
Node *createNode(ElemType elem) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    return NULL; // 内存分配失败时返回 NULL
  }
  node->data = elem;
  node->next = NULL;
  return node;
}

// 打印链表
void printList(LinkList L) {
  Node *cur = L->next;
  while (cur->next != L) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
  printf("%d ", cur->data); // 打印最后一个节点
  printf("\n");
}

// 在头部后面插入
Status insertFromHead(LinkList L, ElemType elem) {
  Node *newNode = createNode(elem);
  if (newNode == NULL)
    return ERROR;
  newNode->next = L->next; // 新节点的下一个指向头结点的下一个
  L->next = newNode;       // 头结点的下一个指向新节点
  printList(L);
  return OK;
}

// 在尾部后面插入
Status insertFromTail(LinkList L, ElemType elem) {
  Node *newNode = createNode(elem);
  if (newNode == NULL)
    return ERROR;

  Node *cur = L;
  // 遍历到链表尾节点
  while (cur->next != L) {
    cur = cur->next;
  }
  // 将新节点插入到链表尾部
  cur->next = newNode;
  newNode->next = L;
  printList(L);
  return OK;
}

// 在任意位置pos插入
Status insert(LinkList L, int pos, ElemType elem) {
  // 参数验证：检查链表是否存在
  if (L == NULL) {
    printf("链表不存在\n");
    return ERROR;
  }
  //   创建一个新结点
  Node *newNode = createNode(elem);
  if (!newNode)
    return ERROR;
  // 如果 pos 小于 0 ，直接报错
  if (pos < 0)
    return ERROR;
  // 如果 pos 等于 0 ，其实就是把新结点添加到尾部
  if (pos == 0) {
    // 找到尾结点
    Node *cur = L;
    while (cur->next != L) {
      cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    printList(L);
    return OK;
  }

  // 找到插入点位置的前驱结点
  Node *cur = L;
  int i = 0;
  while (cur->next != L && i < pos - 1) {
    cur = cur->next;
    ++i;
  }
  // 如果 pos 大于 链表的长度，其实也是把新结点添加到尾部,当前的逻辑同样适用
  newNode->next = cur->next;
  cur->next = newNode;
  printList(L);
  return OK;
}
