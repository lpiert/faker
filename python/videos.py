from bs4 import BeautifulSoup
import re
import time

from urllib import request

url = ''
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0;Win64;x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36'}
rel = request.Request(url = url,headers=headers)
new_rel = request.urlopen(rel).read().decode('utf-8')
content = BeautifulSoup(new_rel,'html.parser')

def main():
	print(re.findall(r'https://www/.zhihu.com/videos/\d+',str(content.decode())))
	
if __name__ == '__main__':
	main()
	
	