# -*- coding: utf-8-*-


class Solution(object):
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        valid = False
        stack = list()
        for ch in s:
            if ch in ('(', '{', '['):
                # 入栈
                stack.append(ch)
            else:
                # 出栈并比较与栈顶元素是否配对
                try:
                    top = stack.pop()
                except:
                    # 出栈异常
                    break
                if ch == ')' and top != '(':
                    break
                elif ch == '}' and top != '{':
                    break
                elif ch == ']' and top != '[':
                    break
        else:
            # 遍历结束未break，且stack为空栈则返回True
            valid = True if not stack else False
        return valid


if __name__ == '__main__':
    s = '()'
    o = Solution()
    print o.isValid(s)
