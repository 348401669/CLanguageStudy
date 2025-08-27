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

// 创建结点
Node *createNode(LinkList L, ElemType elem) {
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

// 初始化双向链表
Status initList(LinkList L) {}