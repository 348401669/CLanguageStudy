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
bool isEmpty(LinkList L);
int getLen(LinkList L);
void printList(LinkList L);
Status insertFromHead(LinkList L, ElemType elem);
Status insertFromTail(LinkList L, ElemType elem);
Status insert(LinkList L, int pos, ElemType elem);
Status deleteFromHead(LinkList L);
Status deleteFromTail(LinkList L);
Status delete(LinkList L, int pos);
Status clearList(LinkList L);
Status destroyList(LinkList *L);

int main() {
  // 指针
  LinkList L;
  //   初始化循环链表
  initList(&L);
  //   插入结点
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
  // 删除结点
  deleteFromHead(L);
  deleteFromTail(L);
  delete (L, 0);
  delete (L, 1);
  delete (L, 4);
  delete (L, 100);
  // 判空（其逻辑中包含获取链表长度）
  isEmpty(L);
  clearList(L);
  destroyList(&L);
  return 0;
}

// 1 初始化循环链表
Status initList(LinkList *L) { // *L 指向头指针
  *L = (LinkList)malloc(sizeof(Node));
  if (*L == NULL) {
    return ERROR;
  }
  (*L)->next = *L; // 头指针指向头结点
  return OK;
}

// 2 创建单个结点，返回结点指针
Node *createNode(ElemType elem) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    return NULL; // 内存分配失败时返回 NULL
  }
  node->data = elem;
  node->next = NULL;
  return node;
}
// 3 判空
bool isEmpty(LinkList L) {
  if (L->next == L) {
    printf("链表为空\n");
    return true;
  }
  printf("链表非空\n");
  getLen(L);
  return false;
}
// 4 求长
int getLen(LinkList L) {
  int len = 0;
  Node *cur = L;
  while (cur->next != L) {
    cur = cur->next;
    ++len;
  }
  printf("链表的长度为：%d\n", len);
  return len;
}

// 5 打印链表
void printList(LinkList L) {
  Node *cur = L->next;
  while (cur->next != L) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
  printf("%d ", cur->data); // 打印最后一个节点
  printf("\n");
}

// 6 在头部后面插入
Status insertFromHead(LinkList L, ElemType elem) {
  Node *newNode = createNode(elem);
  if (newNode == NULL)
    return ERROR;
  newNode->next = L->next; // 新节点的下一个指向头结点的下一个
  L->next = newNode;       // 头结点的下一个指向新节点
  printList(L);
  return OK;
}

// 7 在尾部后面插入
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

// 8 在任意位置pos插入
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

// 9 删除首元结点
Status deleteFromHead(LinkList L) {
  if (L->next == L) {
    return ERROR;
  }
  Node *del = L->next;
  L->next = del->next;
  free(del);
  printf("删除首元结点\n");
  printList(L);
  return OK;
}
// 10 删除尾结点
Status deleteFromTail(LinkList L) {
  // 如果链表不存在 或 是空链表，直接报错
  if (!L || L->next == L) {
    return ERROR;
  }
  // 找到尾结点的前驱结点
  Node *cur = L;
  while (cur->next->next != L) {
    cur = cur->next;
  }
  Node *del = cur->next;
  cur->next = L;
  free(del);
  printf("删除尾结点\n");
  printList(L);
  return 0;
}

// 11 删除任意结点
Status delete(LinkList L, int pos) {
  if (!L || L->next == L || pos <= 0) {
    printf("不能是空链表||pos不能小于等于0\n");
    return ERROR;
  }

  Node *cur = L;
  int i = 0;
  while (cur->next->next != L && i < pos - 1) {
    cur = cur->next;
    ++i;
  }
  Node *del = cur->next;
  cur->next = del->next;
  free(del);
  printf("删除pos=%d号结点\n", pos);
  printList(L);
  return 0;
}

// 12 清除所有节点（除了头结点）
Status clearList(LinkList L) {
  Node *cur = L;
  while (!isEmpty(L)) {
    deleteFromHead(L);
  }
  printf("链表已清空\n");
  return OK;
}

// 13 释放链表
// 销毁循环链表，释放链表占用的所有内存
Status destroyList(LinkList *L) {
  // 检查链表指针是否为空，若为空则返回错误
  if (*L == NULL) {
    return ERROR;
  }
  // 清除链表中除头结点外的所有节点
  clearList(*L);
  // 释放头结点的内存
  free(*L);
  // 悬空指针是指指针指向的内存已被释放，但指针仍然保留该内存地址。
  // 将链表指针置为 NULL，避免程序后续误操作已释放的内存，从而避免悬空指针问题。
  *L = NULL;
  // 操作成功，返回 OK
  return OK;
}
