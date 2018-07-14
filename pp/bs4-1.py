# -*- coding : utf-8 -*-
'''导入bs4的爬虫模块'''

from bs4 import BeautifulSoup
import re

html = """
<html><head><title>The Dormouse's story</title></head>
<body>
<p class="title" name="dromouse"><b>The Dormouse's story</b></p>
<p class="story">Once upon a time there were three little sisters; and their names were
<a href="http://example.com/elsie" class="sister" id="link1"><!-- Elsie --></a>,
<a href="http://example.com/lacie" class="sister" id="link2">Lacie</a> and
<a href="http://example.com/tillie" class="sister" id="link3">Tillie</a>;
and they lived at the bottom of a well.</p>
<p class="story">...</p>
"""

#soup = BeautifulSoup(open('index2.html'),from_encoding="utf-8")
soup = BeautifulSoup(html)
#print (soup.prettify())  #调用prettify方法美化html文档

'''一'''
'''解析之后四大类之一的tag标签类
print(soup.head)
print(soup.p)
print(soup.p['class'].string)
'''

'''NavigableString字符串类'''
print(soup.head.string)

'''BeautifulSoup一个特殊的标签类'''

'''Comment一个特殊的NavigableString类'''
print(soup.a)
print(soup.a.string) #输出标签的内容

print("第二部分遍历节点树木")

'''二'''
'''遍历节点树'''
print(soup.head.contents) #以列表形式输出标签内容
print(soup.head.contents[0])

'''遍历子节点'''
for child in soup.body.children:
    print(child)

print("分界线")

'''遍历内容'''
for string in soup.strings:
    print(repr(string))

print("分界线")
for string in soup.stripped_strings: #stripped忽略筛选内容的空格换行符等
    print(repr(string))

print("分解线")
p = soup.p
print(p.parent.name)  #筛选父节点

content = soup.head.title.string
print(content.parent.name+'\n')
for parent in content.parents:
    print(parent.name)

print("兄弟节点分界线")
print(soup.p.next_sibling.next_sibling)

'''搜索文档树'''
'''find_all(name,attrs,recursive,text)'''

print("name参数可传入如下参数")

#print(soup.find_all('a'))  筛选所有的a标签以列表的形式打印--------(传入字符串参数)

'''传入正则表达式参数
bobj = re.compile('^b')
for tag in soup.find_all(bobj):
    print(tag.name)
'''

#print(soup.find_all(['a','b']))  传入列表参数

'''传入布伦值True获取所有的标签名称
for tag in soup.find_all(True):
    print(tag.name)
'''

'''传入方法--筛选含有class属性但不含有id属性的值
def check(tag):
    return tag.has_attr('class') and not tag.has_attr('id')

print(soup.find_all(check))
'''

'''keyword参数'''
#print("keyword参数")
#print(soup.find_all(class_='sister'))  #因为class在python是关键字所以可加一个下划线_


'''CSS选择器'''
print("CSS选择器")

print(soup.select('a'))  #标签筛选
print(soup.select('#link1'))  #id筛选
print(soup.select('.story'))  #.类选择器
print(soup.select('p[name="dromouse"]'))