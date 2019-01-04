#!/usr/bin/env python
# -*- coding:utf-8 -*-
#
# Python2 支持 http socks5
#


# coding=utf-8
import requests
import base64

# 请求地址
targetUrl = "http://h.wandouip.com"


# 请求头认证方式暂时不支持https协议
# 请通过添加ip白名单方式添加全局支持
# 添加白名单接口: https://h.wandouip.com/get/add-white-list?iplist=你的公网ip (登录状态下调用，公网ip请通过网络查询)

def base_code(username, password):
    str = '%s:%s' % (username, password)
    encodestr = base64.b64encode(str.encode('utf-8'))
    return '%s' % encodestr.decode()


if __name__ == '__main__':
    # 代理服务器(HTTP代理 SOCKE5代理)
    proxyHost = "测试IP" #通过http://h.wandouip.com/get获取
    proxyPort = "端口"
    username = "用户名"
    password = "密码"
    headers = {
        'Proxy-Authorization': 'Basic %s' % (base_code(username, password))
    }
# proxyMeta = "http://%(host)s:%(port)s" % {
#
#     "host": proxyHost,
#     "port": proxyPort,
# }

# pip install -U requests[socks]  socks5代理
proxyMeta = "socks5://%(host)s:%(port)s" % {

    "host" : proxyHost,

    "port" : proxyPort,

}

proxies = {

    "socks5": proxyMeta,
}

resp = requests.get(targetUrl, headers=headers, proxies=proxies)
print(resp.status_code)
print(resp.text)
