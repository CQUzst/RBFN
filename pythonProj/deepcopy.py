import copy
a = [1,2,3,4,['a','b']] #定义一个列表a
b = a #赋值
c = copy.copy(a) #浅拷贝
d = copy.deepcopy(a) #深拷贝

a.append(5)
print(a)
# [1, 2, 3, 4, ['a', 'b'], 5] #a添加一个元素5
print(b) 
# [1, 2, 3, 4, ['a', 'b'], 5] #b跟着添加一个元素5
print(c)
# [1, 2, 3, 4, ['a', 'b']] #c保持不变
print(d)
# [1, 2, 3, 4, ['a', 'b']] #d保持不变

a[4].append('c')
print(a)
# [1, 2, 3, 4, ['a', 'b', 'c'], 5] #a中的list(即a[4])添加一个元素c
print(b)
# [1, 2, 3, 4, ['a', 'b', 'c'], 5] #b跟着添加一个元素c
print(c)
# [1, 2, 3, 4, ['a', 'b', 'c']] #c跟着添加一个元素c
print(d)
# [1, 2, 3, 4, ['a', 'b']] #d保持不变

#说明如下：
#1.外层添加元素时， 浅拷贝c不会随原列表a变化而变化；内层list添加元素时，浅拷贝c才会变化。
#2.无论原列表a如何变化，深拷贝d都保持不变。
#3.赋值对象随着原列表一起变化
