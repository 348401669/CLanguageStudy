// ###  指针运算
// 1. *
// 在指针声明时是类型的一部分，表示这是一个指针变量；在其他情况下是解引用运算符。
// 2. & 不能用于没有内存地址的表达式，如常量或表达式结果。例如： &(a + b)
// 是无效的。
// 3. 对未初始化的指针进行解引用（ *p ）是危险的，可能导致程序崩溃或未定义行为。
// 4. 指针变量本身也有地址，可以使用 & 获取： &p 表示指针变量 p 自己的地址。
// 5. 指针变量的大小是固定的，与所指向的变量类型无关。
// 6. 指针变量可以进行加减运算，结果是指针变量的地址。
// 7. 指针变量可以进行比较运算，结果是指针变量的地址。
// 8. 指针变量可以进行赋值运算，结果是指针变量的地址。
// 9. 指针变量可以进行解引用运算，结果是指针变量指向的变量的值。

#include <stdio.h>
#include <stdlib.h>
// 在文件开头添加头文件
#include <time.h>

#define MAXSIZE 10000
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef struct {
  ElemType *elem;
  int length;
} SqList;

// 函数声明
Status InitList(SqList *L);
Status printAllElem(SqList *L, ElemType *elem);
int isListEmpty(SqList *L);
int getListLength(SqList *L);
void insertListHead(SqList *L, ElemType elem);
void insertListTail(SqList *L, ElemType elem);
Status insertElem(SqList *L, int pos, ElemType elem);

/**
 * @brief 初始化顺序表
 *
 * @param L 顺序表指针
 * @return Status 初始化状态
 */
Status InitList(SqList *L) {
  L->elem = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
  if (!L->elem) {
    return ERROR;
  }
  L->length = 0;
  return OK;
}
/**
 * @brief 判断顺序表是否为空
 *
 * @param L 顺序表指针
 * @return int 0：空 1：非空 -1：顺序表不存在
 */
int isListEmpty(SqList *L) {
  if (!L)
    return -1;
  if (L->length == 0)
    return 0;
  return 1;
}
/**
 * @brief 获取顺序表的长度
 *
 * @param L 顺序表指针
 * @return int 顺序表长度
 */
int getListLength(SqList *L) {
  if (!L)
    return -1;
  return L->length;
}

// 在头部插入元素
void insertListHead(SqList *L, ElemType elem) {
  if (!L || !L->elem)
    return;
  int len = getListLength(L);
  // 检查顺序表是否已满
  if (len >= MAXSIZE)
    return;
  for (int i = len; i > 0; i--) {
    L->elem[i] = L->elem[i - 1];
  }
  L->elem[0] = elem;
  L->length++;
  // 打印顺序表
  printAllElem(L, L->elem);
}

// 在尾部插入元素
void insertListTail(SqList *L, ElemType elem) {
  if (!L || !L->elem)
    return;
  int len = getListLength(L);
  L->elem[len] = elem;
  L->length++;
  // 打印顺序表
  printAllElem(L, L->elem);
}

/**
 * @brief 插入元素
 *
 * @param L 顺序表指针
 * @param pos 插入位置
 * @param elem 插入元素
 * @return Status 插入状态
 */
Status insertElem(SqList *L, int pos, ElemType elem) {
  if (!L || !L->elem)
    return ERROR;
  int len = getListLength(L);
  if (pos < 1 || pos > len + 1)
    return ERROR;
  if (len >= MAXSIZE)
    return OVERFLOW;
  // 从后往前移动元素
  for (int i = len; i > pos; i--) {
    L->elem[i] = L->elem[i - 1];
  }
  // 插入元素
  L->elem[pos - 1] = elem;
  // 更新顺序表的长度
  L->length++;
  // 打印顺序表
  printAllElem(L, L->elem);
  return OK;
}

// 获取元素的位置
int getIndex(SqList *L, ElemType e) {
  if (!L || !L->elem)
    return -1;
  int len = getListLength(L);
  for (int i = 0; i < len; i++) {
    if (L->elem[i] == e) {
      return i + 1;
    }
  }
  return 0;
}

// 获取单个元素
// 当前代码存在问题，函数返回类型为 ElemType，却尝试返回 ERROR（类型为
// Status），这会引发类型不匹配。 修正方案：添加 pos < 1
// 的判断，且当出现错误时返回一个默认值，这里假设 ElemType 为 int，默认返回 -1
ElemType getElem(SqList *L, int pos) {
  int len = getListLength(L);
  if (!L || pos < 1 || pos > len || !L->elem)
    return -1;
  return L->elem[pos - 1];
}

// 删除单个元素
// 当前函数返回类型为 Status，能反馈删除操作的状态。
Status deleteElem(SqList *L, int pos) {
  if (!L || !L->elem)
    return ERROR;
  int len = getListLength(L);
  if (pos < 1 || pos > len)
    return ERROR;
  // 这里使用 len - 1 是因为我们要将删除位置之后的元素依次向前移动一位。
  // len 表示当前顺序表的长度，数组下标从 0 开始，最后一个元素的下标是 len - 1。
  // 我们需要将从 pos - 1
  // 位置之后的元素依次向前覆盖，所以循环到倒数第二个元素（即 len - 2）即可，
  // 因此循环条件为 i < len - 1，这样能确保所有需要移动的元素都被正确处理。
  for (int i = pos - 1; i < len - 1; i++) {
    L->elem[i] = L->elem[i + 1];
  }
  L->length--;
  // 打印顺序表
  printAllElem(L, L->elem);
  return OK;
}

/**
 * @brief 打印所有元素
 *
 * @param L 顺序表指针
 * @param elem 元素数组
 * @return Status 打印状态
 */
Status printAllElem(SqList *L, ElemType *elem) {
  if (!L || !L->elem)
    return ERROR;
  for (int i = 0; i < L->length; i++) {
    printf("%d ", L->elem[i]);
  }
  printf("\n");
  return OK;
}

// 在main函数开始处添加
int main() {
  // 添加随机数种子初始化
  srand((unsigned int)time(NULL));

  // 声明一个顺序表变量 L，用于后续操作
  SqList *L = (SqList *)malloc(sizeof(SqList));
  if (!L) {
    printf("顺序表指针内存分配失败\n");
    return ERROR;
  }

  // （1）初始化线性表
  printf("（1）初始化线性表\n");

  // 调用 InitList 函数对顺序表 L 进行初始化
  Status result = InitList(L);

  // 根据初始化结果进行不同处理
  if (result == OK) {
    printf("顺序表初始化成功，初始化函数返回值: %d\n", result);
    printf("顺序表的长度为：%d\n", L->length);
    printf("顺序表的容量为：%d\n", MAXSIZE);
    printf("顺序表的地址为：%p\n", L);
    printf("顺序表第一个元素的地址为：%p\n", L->elem);

    // （2）判断线性表是否为空
    printf("（2）判断线性表是否为空\n");
    Status isEmpty = isListEmpty(L);
    if (isEmpty == 0) {
      printf("线性表为空\n");
    } else if (isEmpty == 1) {
      printf("线性表不为空\n");
    } else {
      printf("未知错误\n");
    }

    // (3)插入元素
    printf("（3）插入元素\n");
    // 1) 在尾部插入元素
    for (int i = 0; i < 10; i++) {
      printf("尾部插入，第%d次：", i + 1);
      insertListTail(L, (i + 1) * 10);
    }
    // 2) 在头部插入元素
    for (int i = 0; i < 5; i++) {
      printf("头部插入，第%d次：", i + 1);
      insertListHead(L, (i + 1) * 150);
    }

    // 3) 随机在任意位置插入元素
    // 循环 3 次，在顺序表的随机位置插入元素
    for (int i = 0; i < 5; i++) {
      // 生成一个 1 到 L->length + 1 之间的随机数作为插入位置
      int pos = rand() % (L->length + 1) + 1;
      // 生成一个随机数作为插入的元素值，1000——2000
      // 使用 rand() 函数生成一个随机数，rand() % 1000 会得到一个 0 到 999
      // 之间的整数 再加上 1000，最终得到一个 1000 到 1999
      // 之间的随机整数，将其赋值给 elem 变量
      int elem = rand() % 1000 + 1000;

      // 打印当前是第几次任意位置插入操作
      printf("任意位置插入，第%d次在%d插入：", i + 1, pos);
      // 调用 insertElem 函数在指定位置插入元素，插入元素的值为 elem
      insertElem(L, pos, elem);
    }

    insertElem(L, 12, 500);

    // （4）获取顺序表的长度
    printf("（4）获取顺序表的长度\n");
    int len = getListLength(L);
    printf("顺序表的长度为：%d\n", len);

    // （5）获取顺序表的单个元素
    printf("（5）获取顺序表的元素\n");
    printf("第5个元素是：%d\n", getElem(L, 5));
    printf("第10个元素是：%d\n", getElem(L, 10));
    printf("第12个元素是：%d\n", getElem(L, 12));

    // （6）打印顺序表的全部元素
    printf("（6）打印顺序表的全部元素\n");
    printAllElem(L, L->elem);

    // (7) 删除元素
    printf("（7）删除元素\n");
    deleteElem(L, 12);
    // (8) 查找元素的位置
    int search = 300;
    printf("（8）查找元素%d的位置\n", search);
    int pos = getIndex(L, search);
    if (pos == 0) {
      printf("元素不存在\n");
    } else {
      printf("元素的位置是：%d\n", pos);
    }

    printAllElem(L, L->elem);

    // printf("顺序表的长度为：%d\n", L->length);
    // for(int i=0;i<L->length;i++){
    //     printf("%d ",L->elem[i]);
    // }
    // printf("\n");

    // 使用完后释放内存
    free(L->elem);
    L->elem = NULL; // 防止野指针
    free(L);
    L = NULL; // 防止野指针
    printf("顺序表指针内存释放成功\n");
    printf("顺序表元素内存释放成功\n");
  } else {
    printf("\n程序执行失败，初始化函数返回值: %d\n", result);
    free(L); // 释放顺序表指针内存
    L = NULL;
  }

  // 程序正常结束，返回 0 表示程序成功执行
  return 0;
}