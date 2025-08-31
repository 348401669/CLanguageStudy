// 包含链表应用的定义和函数原型头文件，引入其中定义的类型和函数声明
#include "02_线性表_05_链表应用_01_定义和函数原型.h"
#include "02_线性表_05_链表应用_02_函数实现.c"
#include <stdio.h>

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
  deleteByPos(L, 1);
  deleteByPos(L, 3);
  deleteLast(L);
  deleteFirst(L);
  clearList(L);
  destroyList(&L);

  return 0;
}
