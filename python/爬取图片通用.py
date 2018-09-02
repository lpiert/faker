# -*- coding:utf-8 -*-

'''导入模块'''
from urllib import request
from bs4 import BeautifulSoup
import re

'''开始'''
url = 'https://tuchong.com/explore/'
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36'}
req = request.Request(url=url, headers=headers)
loaded = request.urlopen(req).read().decode('utf-8')
self_attr = attrs={'data-lazy-url':re.compile('^https://photo.*.jpg$')}
analysis = BeautifulSoup(loaded,'html.parser').find_all('img',self_attr)


# 存放正则
get_id = re.compile(r'/\d+')


#设置保存点(图片)
def save():
    path = r'F:\python_bs4\28-爬虫\图片保存点\123\\'
    # f = open(path , 'w+' ,encoding='utf-8')
    for a_file in analysis:
        opener = request.build_opener()
        opener.addheaders = [('User-Agent',
                              'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36')]
        request.install_opener(opener)
        print(a_file['data-lazy-url'])
        # request.urlretrieve(a_file['data-lazy-url'],path+'%s.jpg' % time.time())
        # print(a_file.attrs['href'] , file=f)
save()





