#include <stdio.h>
#include <stdlib.h>


int main()
{
    int a = 10;
    int *p = &a; //解释：p是一个指针变量，它的类型是int *，它指向的变量是a，a的类型是int，所以p指向的变量的类型是int
    printf("%d\n", *p);  // 解释：*p表示p指向的变量的值，即a的值，所以*p的值是10
    printf("%d\n", p);  // 解释：p表示p指向的变量的地址，即a的地址，所以p的值是10的地址
    printf("%d\n", sizeof(a));  // 解释：a的类型是int，所以a的大小是4个字节
    printf("%d\n", sizeof(p));  // 解释：p的类型是int *，所以p的大小是8个字节

    // 数组 
    int arr[4] = {10,20,30,40};
    int *p1 = arr ; // 等价于 int *p1 = &arr[0];
    for(int *p=arr;p< arr + sizeof(arr)/sizeof(arr[0]);p++) // 解释：sizeof(arr)表示数组的大小，sizeof(arr[0])表示数组的元素大小，所以sizeof(arr)/sizeof(arr[0])表示数组的元素个数

    {
        printf("%d\n", *p);
    }
// 在Windows系统中，为了防止cmd窗口自动关闭，可添加如下代码
    system("pause"); // 解释：system("pause")表示暂停cmd窗口，等待用户按键后继续执行
    return 0; // 解释：return 0;表示程序正常结束

}


