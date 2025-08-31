/*
 * 文件名：02_线性表_05_链表应用_04_使用链表_合并.c
 * 作者：liuyunfei
 * 日期：2025年08月31日
 * 功能：合并两个有序链表（单链表版本）
 */

// 包含链表应用的定义和函数原型头文件，引入其中定义的类型和函数声明
#include "02_线性表_05_链表应用_01_定义和函数原型.h"
#include "02_线性表_05_链表应用_02_函数实现.c"
#include <stdio.h>

Status mergeList(LinkList L1, LinkList L2, LinkList *U);

// 主函数 实现合并两个有序链表 L1 L2 ,合并后的链表为U
int main() {
  LinkList U, L1, L2;
  // 调用InitList函数，初始化链表
  InitList(&L1);
  InitList(&L2);
  InitList(&U); // 新增：初始化U链表

  // 调用insertFromHead函数，在头结点之后插入元素
  for (int i = 9, j = 1; i <= 21; i += 2, j += 2) {
    insertFromTail(L1, i);
    insertFromTail(L2, j);
  }

  printf("L1: ");
  printList(L1);
  printf("L2: ");
  printList(L2);

  // 调用mergeList函数，合并两个有序链表
  mergeList(L1, L2, &U); // 修复：传递&U而不是U

  printf("合并后的链表: ");
  printList(U);

  // 调用destroyList函数，销毁链表
  destroyList(&U);
  destroyList(&L1);
  destroyList(&L2);

  return 0;
}

// 简洁版：合并两个有序链表并去重
Status mergeList(LinkList L1, LinkList L2, LinkList *U) {
  if (!L1 || !L2 || !U)
    return ERROR;

  Node *cur1 = L1->next;
  Node *cur2 = L2->next;
  Node *curU = *U;
  Node *newNode;

  // 合并两个有序链表并去重
  while (cur1 && cur2) {
    if (cur1->data == cur2->data) {
      // 值相同，只插入一个
      newNode = createNode(cur1->data);
      if (!newNode)
        return ERROR;
      curU->next = newNode;
      curU = curU->next;

      // 跳过重复值
      int val = cur1->data;
      while (cur1 && cur1->data == val)
        cur1 = cur1->next;
      while (cur2 && cur2->data == val)
        cur2 = cur2->next;
    } else if (cur1->data < cur2->data) {
      // 插入cur1的值
      newNode = createNode(cur1->data);
      if (!newNode)
        return ERROR;
      curU->next = newNode;
      curU = curU->next;
      cur1 = cur1->next;
    } else {
      // 插入cur2的值
      newNode = createNode(cur2->data);
      if (!newNode)
        return ERROR;
      curU->next = newNode;
      curU = curU->next;
      cur2 = cur2->next;
    }
  }

  // 处理剩余节点
  while (cur1) {
    newNode = createNode(cur1->data);
    if (!newNode)
      return ERROR;
    curU->next = newNode;
    curU = curU->next;
    cur1 = cur1->next;
  }

  while (cur2) {
    newNode = createNode(cur2->data);
    if (!newNode)
      return ERROR;
    curU->next = newNode;
    curU = curU->next;
    cur2 = cur2->next;
  }

  // 清空原链表
  clearList(L1);
  clearList(L2);

  return OK;
}
