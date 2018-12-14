#Python selenium http/socks5:
#coding=utf-8
from selenium import webdriver

# 代理服务器
proxyHost = "ip"
proxyPort = "port"
proxyType='http' #socks5

# 代理隧道验证信息
service_args = [
    "--proxy-type=%s" % proxyType,
    "--proxy=%(host)s:%(port)s" % {
        "host" : proxyHost,
        "port" : proxyPort,
    }
    ]

# 要访问的目标页面
targetUrl = "http://baidu.com"
driver = webdriver.PhantomJS(service_args=service_args)
driver.get(targetUrl)

print driver.title
print driver.page_source.encode("utf-8")
driver.quit()