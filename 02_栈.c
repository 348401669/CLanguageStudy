#include <stdio.h>
#include <stdlib.h>



// 定义 ElemType 为 int 类型
typedef int ElemType;

// 定义栈结构
// #define 是 C 语言中的预处理器指令，用于定义宏。宏是一种文本替换机制，
// 在编译前，编译器会将代码中所有出现的宏名（这里是 MAX_STACK_SIZE）
// 替换为对应的宏值（这里是 100）。此处用于定义栈的最大容量。
#define MAX_STACK_SIZE 100  // 定义栈的最大容量

typedef struct {
    // 若 ElemType 未定义，需确保在 01_线性表.h 中正确定义该类型
    ElemType data[MAX_STACK_SIZE];  // 存储栈元素的数组，假设 ElemType 为 int 类型
    int top;  // 栈顶指针
} STACK;

// 函数声明
void Initial_Stack(STACK *s);
int isEmpty(STACK *s);
int Push(STACK *s, ElemType value);
int Pop(STACK *s, ElemType *value);



int main(){
    STACK s;  // 定义一个栈变量
    Initial_Stack(&s);  // 初始化栈

    // 模拟入栈操作
    printf("尝试入栈元素 10: ");
    if (Push(&s, 10)) {
        printf("入栈成功\n");
    } else {
        printf("入栈失败，栈已满\n");
    }

    printf("尝试入栈元素 20: ");
    if (Push(&s, 20)) {
        printf("入栈成功\n");
    } else {
        printf("入栈失败，栈已满\n");
    }

    ElemType value;
    // 模拟出栈操作
    printf("尝试出栈元素: ");
    if (Pop(&s, &value)) {
        printf("出栈成功，元素值为 %d\n", value);
    } else {
        printf("出栈失败，栈为空\n");
    }

    printf("尝试出栈元素: ");
    if (Pop(&s, &value)) {
        printf("出栈成功，元素值为 %d\n", value);
    } else {
        printf("出栈失败，栈为空\n");
    }

    printf("尝试再次出栈元素: ");
    if (Pop(&s, &value)) {
        printf("出栈成功，元素值为 %d\n", value);
    } else {
        printf("出栈失败，栈为空\n");
    }

}


// 初始化栈
void Initial_Stack(STACK *s) {
    s->top = -1;  // 栈顶指针初始化为 -1，表示栈为空
}

// 判断栈是否为空
int isEmpty(STACK *s) {
    return s->top == -1;  // 若栈顶指针为 -1，则栈为空
}

// 入栈操作
int Push(STACK *s, ElemType value) {
    if (s->top >= MAX_STACK_SIZE - 1) {
        return 0;  // 栈满，入栈失败
    }
    s->data[++(s->top)] = value;  // 栈顶指针加 1，然后存入元素
    return 1;  // 入栈成功
}

// 出栈操作
int Pop(STACK *s, ElemType *value) {
    if (isEmpty(s)) {
        return 0;  // 栈空，出栈失败
    }
    *value = s->data[(s->top)--];  // 取出栈顶元素，然后栈顶指针减 1
    return 1;  // 出栈成功
}


