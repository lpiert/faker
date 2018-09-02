# -*- coding: utf-8 -*-

"""
下载知乎视频：
依赖：
pip install requests

mac 安装 ffmpeg，其他平台请自行搜索安装，确保 ffmpeg 命令可用
    brew install ffmpeg

"""


import re
import uuid
import subprocess

import requests


# 下边 cookie 请打开知乎打开浏览器开发者工具随便找一个请求复制 cookie，千万不要泄露出去
# 如果遇到 400 把浏览器 Header 之类的都带上去
HEADERS = {
    'cookie': '_xsrf=cd2c861d-037b-440e-a7c9-667e2a8bd1e6; d_c0="AICkuBXVyw2PTpf09IsDkdnz2SnZvf0ce90=|1529797257"; q_c1=4c5d264d95204cac9834a6165f51204b|1529797257000|1529797257000; l_n_c=1; n_c=1; _zap=0068dfe1-ddb3-4ff5-bd15-cb65449f9d8d; l_cap_id="YTAxMWMzYmFmYTQ3NDY0NGE2ZWVjN2IyZGFkYTNmYmI=|1530406591|b89e3362d4936fed070305677d77f91481f0c8a2"; r_cap_id="NWEyODUzNDE1NjA0NDA2ZjhkNTRhOTQ5ZjI1YjU0ODI=|1530406591|6feac71a8e572737e9434e4acf654c8c25e1889c"; cap_id="NmY0YjQzNzAwMDliNGY5Zjg2YTBkOWM4NzNkN2Q4ZDk=|1530406591|1d1a4c6b089e02c686c48d986ed8fa58f5f1aed6"; capsion_ticket="2|1:0|10:1530406595|14:capsion_ticket|44:NjhhZDRmN2MyYTEwNDlmZjhiZjVhZDllNGNiMTQyYzQ=|918eb73a7b19e3d68f65b2883abfe5a8914fa9c4526ef0d189520d4865fca629"; z_c0="2|1:0|10:1530407088|4:z_c0|92:Mi4xVExrLUFnQUFBQUFBZ0tTNEZkWExEU2NBQUFDRUFsVk5zTFZmV3dDODFva1hGeTB3T3QzakUxUjBPUDA0T2dVY2xR|8fd62ad6ff8d39ef5cddf0373160d9a1f5f8863c2e385a45f48798b69d759dbc"; __utma=51854390.615809015.1530415036.1530415036.1530415036.1; __utmc=51854390; __utmz=51854390.1530415036.1.1.utmcsr=google|utmccn=(organic)|utmcmd=organic|utmctr=(not%20provided); __utmv=51854390.100--|2=registration_date=20151101=1^3=entry_date=20151101=1; tgw_l7_route=29b95235203ffc15742abb84032d7e75 '
}
QUALITY = 'ld'    # 支持是 'ld' 'sd' 'hd' 分别是低清、中清、高清


def get_video_ids_from_url(url):
    """
    回答或者文章的 url
    """
    html = requests.get(url, headers=HEADERS).text
    video_ids = re.findall(r'data-lens-id="(\d+)"', html)
    if video_ids:
        return set([int(video_id) for video_id in video_ids])
    return []


def yield_video_m3u8_url_from_video_ids(video_ids):
    for video_id in video_ids:
        api_video_url = 'https://lens.zhihu.com/api/videos/{}'.format(int(video_id))
        r = requests.get(api_video_url, headers=HEADERS)
        playlist = r.json()['playlist']
        m3u8_url = playlist[QUALITY]['play_url']
        yield m3u8_url


def download(url):
    video_ids = get_video_ids_from_url(url)
    m3u8_list = list(yield_video_m3u8_url_from_video_ids(video_ids))
    filename = '{}.mp4'.format(uuid.uuid4())
    for idx, m3u8_url in enumerate(m3u8_list):
        print('download {}'.format(m3u8_url))
        subprocess.call(['ffmpeg', '-i', m3u8_url, filename.format(str(idx))])


# 贴上你需要下载的 回答或者文章的链接
url = 'https://www.zhihu.com/question/275611095/answer/407984155'
download(url)