// 链表：线性表的链式存储结构
// 链表是一种物理存储结构上非连续、非顺序的存储结构，数据元素的逻辑顺序是通过链表中的指针链接次序实现的
// 链表的每个元素都是一个节点，每个节点包含两个部分：数据域和指针域
// 数据域：存储元素的空间
// 指针域：指向下一个节点的指针
// 头指针：指向链表第一个节点的指针
// 头结点：链表第一个节点之前的节点，不存储数据
// 尾指针：指向链表最后一个节点的指针
// 尾结点：链表最后一个节点，指针域为空
// 空链表：头指针和尾指针都指向 NULL
// 单链表：每个节点只有一个指针域，指向下一个节点
// 双链表：每个节点有两个指针域，指向前一个节点和后一个节点
// 循环链表：最后一个节点的指针域指向头节点，形成一个环
// 单链表和双链表的区别：
// 单链表：每个节点只有一个指针域，指向下一个节点
// 双链表：每个节点有两个指针域，指向前一个节点和后一个节点
// 单链表的优点：
// 1. 简单方便，占用内存少
// 2. 插入和删除操作方便
// 双链表的优点：
// 1. 可以双向遍历
// 2. 插入和删除操作方便
// 3. 占用内存多
// 循环链表的优点：
// 1. 可以循环遍历
// 2. 插入和删除操作方便
// 3. 占用内存多

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
Status delete(LinkList L, int pos);
Status clearList(LinkList L);
Status destroyList(LinkList *L);

// 主函数
int main() {
  LinkList L;
  // 调用InitList函数，初始化链表
  InitList(&L);
  // 调用isEmpty函数，判断链表是否为空，返回值 bool值:true为空，false为不为空
  isEmpty(L);
  // 调用insertFromHead函数，在头结点之后插入元素
  insertFromHead(L, 10);
  insertFromHead(L, 20);
  insertFromHead(L, 30);

  // 调用insertFromTail函数，在尾结点之后插入元素
  insertFromTail(L, 40);
  insertFromTail(L, 50);
  insertFromTail(L, 60);

  // 当pos小于等于0时，直接返回错误信息
  insert(L, 0, 555);
  insert(L, -1, 555);
  // 当pos等于1时，直接在头结点之后插入
  insert(L, 1, 666);
  // 当pos在列表长度范围内时，在pos位置插入
  insert(L, 3, 777);
  // 当pos大于列表长度时，直接在尾部插入
  insert(L, 100, 999);

  delete (L, 3);
  deleteLast(L);
  deleteFirst(L);
  clearList(L);

  return 0;
}

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
Status delete(LinkList L, int pos) {
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