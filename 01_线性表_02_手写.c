#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义链表节点结构和类型别名
typedef struct node{
    int data;
    struct node *next;
}NODE,*LINKLIST;


// 函数声明（原型）
void Init_List(LINKLIST *head); // 初始化链表
int Get_Length(LINKLIST head); // 获取链表长度（移到前面）
LINKLIST Find_List(LINKLIST head, int i); // 查找元素
void Insert_List(LINKLIST head, int i, int e); // 插入元素
void Delete_List(LINKLIST head, int i); // 删除元素
int Get_Element(LINKLIST head, int i); // 获取链表元素
void Set_Element(LINKLIST head, int i, int e); // 设置链表元素
int Is_Empty(LINKLIST head); // 判断链表是否为空
void Print_List(LINKLIST head); // 打印链表
int Get_Head(LINKLIST head); // 获取链表头元素
int Get_Tail(LINKLIST head); // 获取链表尾元素
void Clear_List(LINKLIST head); // 清空链表
void Destroy_List(LINKLIST *head); // 销毁链表

int main()
{
    // 声明head变量
    LINKLIST head;

    // 初始化链表
    Init_List(&head);
    printf("初始链表是否为空: %s\n", Is_Empty(head) ? "是" : "否");

    // 插入元素
    Insert_List(head, 1, 10);
    Insert_List(head, 2, 20);
    Insert_List(head, 3, 30);
    Insert_List(head,4,40);

    // 打印链表
    printf("插入4个元素后: ");
    Print_List(head);
    printf("链表长度: %d\n", Get_Length(head));

    // 获取头元素和尾元素
    if (!Is_Empty(head)) {
        printf("头元素: %d\n", Get_Head(head));
        printf("尾元素: %d\n", Get_Tail(head));
    }

    // 删除元素
    Delete_List(head, 2);
    printf("删除第2个元素后: ");
    Print_List(head);
    printf("链表长度: %d\n", Get_Length(head));

    // 查找元素
    LINKLIST p = Find_List(head, 2);
    if (p != NULL) {
        printf("找到第2个元素: %d\n", p->data);
    } else {
        printf("查找位置错误\n");
    }

    // 获取元素

    int e = Get_Element(head,1);
    if(e == -1) printf("获取位置错误\n");
    else printf("获取位置1的元素为: %d\n",e);

    // 修改元素
    Set_Element(head, 1, 100);
    printf("修改第1个元素后: ");
    Print_List(head);

    // 清空链表
    Clear_List(head);
    printf("清空后链表是否为空: %s\n", Is_Empty(head) ? "是" : "否");

    // 销毁链表
    Destroy_List(&head);
    printf("销毁后head指针是否为空: %s\n", head == NULL ? "是" : "否");

    return 0; // 程序正常结束
}

// 线性表的初始化
void Init_List(LINKLIST *head)
{
    *head = (LINKLIST)malloc(sizeof(NODE));
    (*head)->data = 0 ;
    (*head)->next = NULL;
}

// 获取链表长度
int Get_Length(LINKLIST head)
{
   return head->data;
}

// 查找节点
LINKLIST Find_List(LINKLIST head, int i)
{
    if(i < 0 || i > Get_Length(head)) return NULL;
    if( i == 0 ) return head;
    LINKLIST p  = head -> next;
    int j = 1;
    while(p != NULL && j <i ){
        p=p->next;j++;
    }
    return p;
}

// 线性表的插入
void Insert_List(LINKLIST head, int i, int e)
{
    if(i<0 || i > Get_Length(head) +1) return;
    LINKLIST p = Find_List(head,i-1);
    if(p == NULL) return;
    LINKLIST s = (LINKLIST)malloc(sizeof(NODE));
    if(s == NULL) return ;
    s->data  = e ; 
    s ->next  = p -> next;
    p->next = s;
    head->data++;
}

// 线性表的删除
void Delete_List(LINKLIST head, int i)
{
    LINKLIST p = Find_List(head,i-1);
    if(p==NULL ) return ;
    LINKLIST q = p -> next;
    if(q == NULL) return;
    p->next  = q->next;
    free(q) ;
    head->data--;

}

// 打印链表
void Print_List(LINKLIST head)
{
    LINKLIST p = head->next;
    while(p != NULL){
        printf("%d, ",p->data);
        p= p ->next;
    }
    printf("\n");
}

// 获取链表元素
int Get_Element(LINKLIST head, int i)
{
    LINKLIST p = Find_List(head,i);
    if(p == NULL) return -1 ;
    return p->data;

}

// 设置链表元素
void Set_Element(LINKLIST head, int i, int e)
{
    LINKLIST p = Find_List(head,i);
    if(p==NULL) return;
    p->data = e;

}

// 判断链表是否为空
int Is_Empty(LINKLIST head)
{
    return head->next == NULL;
}

// 获取链表头元素
int Get_Head(LINKLIST head)
{
    return head->next->data;
}

// 获取链表尾元素
int Get_Tail(LINKLIST head)
{
    LINKLIST p  = head -> next;
    while( p->next != NULL){
        p=p->next;
    }
    return p ->data;
}

// 清空链表
void Clear_List(LINKLIST head)
{
    LINKLIST p = head->next;
    while(p != NULL){
        LINKLIST q = p;
        p = p->next;
        free(q);
    }
    head->next = NULL;
    head->data = 0;
    printf("清空成功\n");

}

// 销毁链表
void Destroy_List(LINKLIST *head)
{
   Clear_List( *head);
   free(*head);
   *head = NULL;
   printf("销毁成功\n");
}


