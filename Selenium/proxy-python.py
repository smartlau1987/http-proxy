#Python selenium http/socks5:
#coding=utf-8
from selenium import webdriver
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities
import base64
# 代理服务器
proxyHost = "测试IP" #通过http://h.wandouip.com/get获取
proxyPort = "端口号"
proxyType='socks5' #socks5
username="用户名"
password="密码"
# 代理隧道验证信息
service_args = [
    "--proxy-type=%s" % proxyType,
    "--proxy=%(host)s:%(port)s" % {
        "host" : proxyHost,
        "port" : proxyPort,
    }
    ]
def base_code(username, password):
    str = '%s:%s' % (username, password)
    encodestr = base64.b64encode(str.encode('utf-8'))
    return '%s' % encodestr.decode()

authentication_token = "Basic " + base_code(username,password)
capa = DesiredCapabilities.PHANTOMJS
capa['phantomjs.page.customHeaders.Proxy-Authorization'] = authentication_token
driver = webdriver.PhantomJS(executable_path="D:\phpStudy\PHPTutorial\WWW\phantomjs-2.1.1-windows\phantomjs.exe",desired_capabilities=capa, service_args=service_args)
# 要访问的目标页面
targetUrl = "http://h.wandouip.com"
driver.get(targetUrl)
# //print (driver.title)
print (driver.page_source.encode("utf-8"))
driver.quit()