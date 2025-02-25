// 题目描述
// 输出7有关数字的个数，包括7的倍数，还有包含7的数字（如17，27，37...70，71，72，73...）的个数（一组测试用例里可能有多组数据，请注意处理）

// 输入描述:
// 一个正整数N。(N不大于30000)

// 输出描述:
// 不大于N的与7有关的数字个数，例如输入20，与7有关的数字包括7,14,17.

// 示例1
// 输入
// 20
// 输出
// 3

// 示例2
// 输入
// 9999
// 输出
// 4376

#include <stdio.h>
#include <stdbool.h>

bool hasSeven(int num)
{
    while (num > 0)
    {
        if (num % 10 == 7)
            return true;
        num /= 10;
    }

    return false;
}

int main(void)
{
    int N;
    int count = 0;

    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
    {
        if (i % 7 == 0 || hasSeven(i))
            count++;
    }

    printf("%d\n", count);
    return 0;
}