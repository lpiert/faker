# -*-coding:utf-8 -*-

'''导入模块'''
import requests
import re
import time
from bs4 import BeautifulSoup
import os


'''必备参数'''
HEADERS = {
    'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/62.0.3202.75 Safari/537.36',
}
QUALITY = 'ld'
url = "https://www.zhihu.com/question/267925961/answer/436484081"


'''获取视频链接的id值'''
def get_url(url):

    r = requests.get(url, headers=HEADERS)
    r.encoding='utf-8'
    html = r.text
    video_ids = re.findall(r'data-lens-id="(\d+)"', html)
    if video_ids:
        #获取本网页所有id值
        save_id = set([int(video_id) for video_id in video_ids])
    # return []
    get_json(save_id)


'''请求json，并获得返回的json'''
def get_json(video_ids):
    for video_id in video_ids:
        #构造请求伪造发送给后端
        headers = {}
        headers['Referer'] = 'https://v.vzuu.com/video/{}'.format(video_id)
        headers['Origin'] = 'https://v.vzuu.com'
        headers['Host'] = 'lens.zhihu.com'
        headers['Content-Type'] = 'application/json'
        headers['Authorization'] = 'oauth c3cef7c66a1843f8b3a9e6a1e3160e20'

        #接收从后端返回的json
        api_video_url = 'https://lens.zhihu.com/api/videos/{}'.format(int(video_id))

        r = requests.get(api_video_url, headers={**HEADERS, **headers})
        playlist = r.json()['playlist']
        m3u8_url = playlist[QUALITY]['play_url']
        # print(m3u8_url)
        dowmload(m3u8_url)


'''调用cmd下载视频'''
def dowmload(url):
    set_up_format = 'ffmpeg -i "{}" -c copy gszs.mp4'.format(url)
    os.system(set_up_format)

if __name__ == '__main__':
    get_url(url)



''' 爬取知乎小视频的总结
    1: 知乎的小视频格式是m3u8 , 可通过ffmpeg下载 (youtube , bilibili , 直播平台)的也一般是这种流媒体格式
    2: 抓这个关键方法fetch() , 他位于<script src="//unpkg.zhimg.com/zhihu-video-player@0.0.101/dist/zplayer.min.js"></script>这个js
    3: 后台返回的内容https://lens.zhihu.com/api/videos/998990773207035904 
    
'''