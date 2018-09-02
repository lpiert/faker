# -*- coding:utf-8 -*-

'''导入爬虫模块'''
from bs4 import BeautifulSoup
from urllib import request

'''导入通用模块'''
import time
import re
import random

'''IP代理池'''
proxy_list = [
    '119.254.11.50:80',
    '113.214.13.1:8000',
    '194.182.74.51:3128',
    '194.182.74.151:3128'
    '118.114.77.47:8080',
    '61.136.163.245:8104'
]

'''绑定某IP'''
proxy       = random.choice(proxy_list)
urlhandle   = request.ProxyHandler({'http':proxy})
opener      = request.build_opener(urlhandle)
request.install_opener(opener)

'''分析'''
url = 'https://www.647aa.com/'
headers = {
        'User-Agent' : "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:57.0) Gecko/20100101 Firefox/57.0"
    }
save = []

def f1():
    req = request.Request(url, headers=headers)  # 伪造代理
    content = request.urlopen(req).read().decode('utf-8')
    all_a = BeautifulSoup(content,'lxml').select('.newMovies li a')
    new_alla = re.compile(r'<a href=".*" target="_blank"')

    for i in all_a:
        str1 = new_alla.findall(str(i))
        print(str1)
        str1 = str(str1).replace('" target="_blank"','')
        print(str1)
        str2 = re.compile(r'/htm.*htm').findall((str1))


        '''拼接字符串'''
        str3 = re.compile(r'https.*com').findall(url)
        str4 = str3[0] + str2[0]
        save.append(str4)

'''获取子链接'''
def f2():
    for i in range(len(save)):
        req2 = request.Request(save[i], headers=headers)  # 伪造代理头
        get_chid_url= request.urlopen(req2).read().decode('utf-8')
        c1 = BeautifulSoup(get_chid_url)
        c2 = c1.find_all(id='downUL')
        print(c1.text)

f1()