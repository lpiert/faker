# -*-coding : utf-8 -*-

'''爬虫类模块'''
from urllib import request
from bs4 import BeautifulSoup

'''自动化模块'''
from selenium import webdriver

'''通用模块'''
import re
import time

url = 'https://www.zhihu.com/question/26830927/answer/34899272'

html = request.urlopen(url).read().decode('utf-8')
soup = BeautifulSoup(html , 'html.parser')
links = soup.find_all('img','origin_image zh-lightbox-thumb',src=re.compile(r'.jpg$'))

'''设置保存路径'''
path = r'F:\py专用\图片保存点'
for link in links:
    request.urlretrieve(link.attrs['src'],path + '\%s.jpg' % time.time())