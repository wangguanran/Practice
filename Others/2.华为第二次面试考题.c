// 力扣：3335 https://leetcode.cn/problems/total-characters-in-string-after-transformations-i/description/
// 此逻辑 502 / 824 个通过的测试用例

/*
题目

给你一个字符串 s 和一个整数 t，表示要执行的 转换 次数。每次 转换 需要根据以下规则替换字符串 s 中的每个字符：

如果字符是 'z'，则将其替换为字符串 "ab"。

否则，将其替换为字母表中的下一个字符。例如，'a' 替换为 'b'，'b' 替换为 'c'，依此类推。

返回 恰好 执行 t 次转换后得到的字符串的 长度。

由于答案可能非常大，返回其对 10^9 + 7 取余的结果。



示例 1：

输入： s = "abcyy", t = 2

输出： 7

解释：

第一次转换 (t = 1)

'a' 变为 'b'

'b' 变为 'c'

'c' 变为 'd'

'y' 变为 'z'

'y' 变为 'z'

第一次转换后的字符串为："bcdzz"

第二次转换 (t = 2)

'b' 变为 'c'

'c' 变为 'd'

'd' 变为 'e'

'z' 变为 "ab"

'z' 变为 "ab"

第二次转换后的字符串为："cdeabab"

最终字符串长度：字符串为 "cdeabab"，长度为 7 个字符。



提示：

1 <= s.length <= 105

s 仅由小写英文字母组成。

1 <= t <= 105



待编程题目

int lengthAfterTransformations(char* s,int t)

{

}
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace(char *s)
{
    int length, length_new = 0;

    if (s == NULL)
        return NULL;

    length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (s[i] == 'z')
            length_new += 2;
        else
            length_new += 1;
    }

    char *new = malloc(length_new + 1);
    if (new == NULL)
        return NULL;

    int index = 0;
    for (int i = 0; i < length; i++)
    {
        if (s[i] == 'z')
        {
            new[index++] = 'a';
            new[index++] = 'b';
        }
        else
        {
            new[index++] = s[i] + 1;
        }
    }

    return new;
}

int lengthAfterTransformations(char *s, int t)
{
    char *new = NULL;
    char *tmp;
    int result = 0;

    if (s == NULL || t <= 0)
        return 0;

    tmp = strdup(s);
    for (int i = 0; i < t; i++)
    {
        new = replace(tmp);
        free(tmp);
        if (new == NULL)
            return 0;
        tmp = new;
    }

    // 返回对10^9 + 7取余的结果
    result = strlen(new) % (1000000007LL);
    free(new);
    return result;
}

int main()
{
    // char s[] = "abcyy";
    // int t = 2;
    char s[] = "azbk";
    int t = 1;

    printf("%d\n", lengthAfterTransformations(s, t));

    return 0;
}