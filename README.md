

      
  
<br/>     
<br/>     

      
编程语言之代理协议
----------

![代理协议汇总](./cssjs/mimvp-proxy-demo-1-lang-proxy-protocol.png)

![编程语言示例](./cssjs/mimvp-proxy-demo-2-lang-proxy-demo.png)
     
  
<br/>     
<br/>     

     
编程语言之代理示例
----------

#### 1. PHP 设置代理

```php
Php http/sock5:

// 要访问的目标页面
        $targetUrl = "http://baidu.com";

        // 代理服务器
        $proxyServer = "http://ip:port";

        // 隧道身份信息
        $ch = curl_init();

        curl_setopt($ch, CURLOPT_URL, $targetUrl);

        curl_setopt($ch, CURLOPT_HTTPPROXYTUNNEL, false);

        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);

        // 设置代理服务器
//        curl_setopt($ch, CURLOPT_PROXYTYPE, 0); //http

        curl_setopt($ch, CURLOPT_PROXYTYPE, 5); //sock5

        curl_setopt($ch, CURLOPT_PROXY, $proxyServer);

        // 设置隧道验证信息
        curl_setopt($ch, CURLOPT_PROXYAUTH, CURLAUTH_BASIC);

        curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727;)");

        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 3);

        curl_setopt($ch, CURLOPT_TIMEOUT, 5);

        curl_setopt($ch, CURLOPT_HEADER, true);

        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

        $result = curl_exec($ch);

        curl_close($ch);

        var_dump($result);
```
  
<br/>      
	
	
#### 2. Python 设置代理

```python
Python http/sock5:

#coding=utf-8
import requests

#请求地址
targetUrl = "http://baidu.com"

#代理服务器
proxyHost = "ip"
proxyPort = "port"

proxyMeta = "http://%(host)s:%(port)s" % {

    "host" : proxyHost,
    "port" : proxyPort,
}

#pip install -U requests[socks]  socks5代理
# proxyMeta = "socks5://%(host)s:%(port)s" % {

#     "host" : proxyHost,

#     "port" : proxyPort,

# }

proxies = {

    "http"  : proxyMeta,
    "https" : proxyMeta,
}

resp = requests.get(targetUrl, proxies=proxies)
print resp.status_code
print resp.text
```
	
<br/>      
	
	
#### 3. Java 设置代理

```java
@SuppressWarnings({ "serial" })
public static HashMap proxyMap = new HashMap() {
	{
		put("http", "138.68.161.14:3128");
		put("https", "104.236.120.183:8080");
		put("socks4", "113.7.118.112:2346");
		put("socks5", "61.135.155.82:1080");
	}
};

final static String proxyUrl = "http://proxy.mimvp.com/exist.php";
final static String proxyUrl2 = "https://proxy.mimvp.com/exist.php";
	
// 设置系统代理，支持全部协议 http，https，socks4，socks5
private static int proxy_property(String proxyType, String proxyStr) {
	int dataLen = 0;

	String proxy_ip = proxyStr.split(":")[0];
	String proxy_port = proxyStr.split(":")[1];
	
	Properties prop = System.getProperties();
	
	// http
	if(proxyType.equals("http")){
		prop.setProperty("http.proxySet", "true");
		prop.setProperty("http.proxyHost", proxy_ip);
		prop.setProperty("http.proxyPort", proxy_port);
		prop.setProperty("http.nonProxyHosts", "localhost|192.168.0.*");
	}
	
	// https
	if (proxyType.equals("https")) {
		prop.setProperty("https.proxyHost", proxy_ip);
		prop.setProperty("https.proxyPort", proxy_port);
	}
    
    // socks
	if(proxyType.equals("socks4") || proxyType.equals("socks5")){
        prop.setProperty("socksProxySet", "true");
        prop.setProperty("socksProxyHost", proxy_ip);
        prop.setProperty("socksProxyPort", proxy_port);
	}
    
    // ftp
	if(proxyType.equals("ftp")){
        prop.setProperty("ftp.proxyHost", proxy_ip);
        prop.setProperty("ftp.proxyPort", proxy_port);
        prop.setProperty("ftp.nonProxyHosts", "localhost|192.168.0.*");
	}
    
//        // auth 设置登录代理服务器的用户名和密码
//        Authenticator.setDefault(new MyAuthenticator("user", "pwd"));
    
	try{
		URL url = new URL(proxyUrl2);		// http://proxy.mimvp.com
		URLConnection conn = url.openConnection();
		conn.setConnectTimeout(30 * 1000);
		
		InputStream in = conn.getInputStream();
		InputStreamReader reader = new InputStreamReader(in);
		char[] ch = new char[1024];
		int len = 0;
		String data = "";
		while((len = reader.read(ch)) > 0) {
			String newData = new String(ch, 0, len);
			data += newData;
		}
		System.out.println("data : " + data);
		dataLen = data.length();
		
	} catch(Exception e) {
		e.printStackTrace();
	}
    return dataLen;
}

static class MyAuthenticator extends Authenticator {
    private String user = "";
    private String password = "";
    public MyAuthenticator(String user, String password) {
        this.user = user;
        this.password = password;
    }
    protected PasswordAuthentication getPasswordAuthentication() {
        return new PasswordAuthentication(user, password.toCharArray());
    }
}
```
 
<br/>      
	
	
#### 4. Go 设置代理

```
package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
)

//sock5代理
func socksproxy() {
	urli := url.URL{}
	urlproxy, _ := urli.Parse("http://测试ip:端口")
	client := &http.Client{
		Transport: &http.Transport{
			Proxy: http.ProxyURL(urlproxy),
		},
	}
	rqt, err := http.NewRequest("GET", "http://myip.top", nil)
	if err != nil {
		println("接口获取IP失败!")
		return
	}

	rqt.Header.Add("User-Agent", "Lingjiang")
	//处理返回结果
	response, _ := client.Do(rqt)
	defer response.Body.Close()
	body, err := ioutil.ReadAll(response.Body)
	if err != nil {
		return
	}

	fmt.Println("socks5:", string(body))
	return

}

//http代理
func httpproxy() {
	urli := url.URL{}
	urlproxy, _ := urli.Parse("http://测试ip:端口")
	client := &http.Client{
		Transport: &http.Transport{
			Proxy: http.ProxyURL(urlproxy),
		},
	}
	rqt, err := http.NewRequest("GET", "http://myip.top", nil)
	if err != nil {
		println("接口获取IP失败!")
		return
	}

	rqt.Header.Add("User-Agent", "Lingjiang")
	//处理返回结果
	response, _ := client.Do(rqt)
	defer response.Body.Close()
	body, err := ioutil.ReadAll(response.Body)
	if err != nil {
		return
	}

	fmt.Println("http:", string(body))
	return

}

//本机IP
func httplocal() {
	client := &http.Client{}
	rqt, err := http.NewRequest("GET", "http://myip.top", nil)
	if err != nil {
		println("接口获取IP失败!")
		return
	}

	rqt.Header.Add("User-Agent", "Lingjiang")
	//处理返回结果
	response, _ := client.Do(rqt)
	defer response.Body.Close()
	body, err := ioutil.ReadAll(response.Body)
	if err != nil {
		return
	}

	fmt.Println("本机:", string(body))
	return

}
func main() {
	httplocal()
	httpproxy()
	socksproxy()
}
```
	
<br/>


#### 5. CSharp 设置代理

```
using System;

using System.Net;
using System.Net.Http;
using System.Collections.Generic;

namespace ClientProxyDemo
{
    class TestProxy
    {
        static void Main(string[] args)
        {
            String proxyServer = "http://xxx:xxx"; // http://host:port, 例(http://1.2.3.4:7777), host可以是域名或者ip,port是代理端口号
            var proxy = new WebProxy(proxyServer);
            HttpClientHandler httpClientHandler = new HttpClientHandler()
            {
                Proxy = proxy
            };
            var httpCient = new HttpClient(httpClientHandler);
            // 增加头部
            httpCient.DefaultRequestHeaders.Add("Header-Key", "header-vaule");

            TestProxy testProxy = new TestProxy();
            testProxy.testGet(httpCient);
            // testProxy.testPost(httpCient);
        }


        // 测试get请求
        public void testGet(HttpClient httpClient)
        {
            String targetUrl = "http://httpbin.org/get";
            var httpResult = httpClient.GetStringAsync(targetUrl).Result;
        }

        // 测试post请求
        public void testPost(HttpClient httpClient)
        {
            String targetUrl = "http://httpbin.org/post";
            List<KeyValuePair<string, string>> formData = new List<KeyValuePair<string, string>>();
            formData.Add(new KeyValuePair<string, string>("key1", "vaule1"));
            formData.Add(new KeyValuePair<string, string>("key2", "vaule2"));
            var formContent = new FormUrlEncodedContent(formData.ToArray());
            var responseMsg = httpClient.PostAsync(targetUrl, formContent).Result;
            var httpResult = responseMsg.Content.ReadAsStringAsync().Result;
        }
    }
}
```
	
<br/>      


#### 6. C 设置代理

```
#include "stdafx.h"
#include "curl/curl.h"
#pragma comment(lib, "libcurl.lib")
static size_t write_buff_data(char *buffer, size_t size, size_t nitems, void *outstream)
{
	memcpy(outstream, buffer, nitems*size);
	return nitems*size;
}
/*
使用http代理
*/
int GetUrlHTTP(char *url, char *buff)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_PROXY,"http://测试ip:端口");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buff);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buff_data);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50L);
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);/*下载最高速度*/
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res == CURLE_OK){
			return res;
		}else {
			printf("错误代码:%d\n", res);
			MessageBox(NULL, TEXT("获取IP错误"), TEXT("助手"), MB_ICONINFORMATION | MB_YESNO);
		}
	}
	return res;
}
/*
使用socks5代理
*/
int GetUrlSocks5(char *url, char *buff)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_PROXY, "socks5://测试ip:端口");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buff);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buff_data);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50L);
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);/*下载最高速度*/
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res == CURLE_OK) {
			return res;
		}
		else {
			printf("错误代码:%d\n", res);
			MessageBox(NULL, TEXT("获取IP错误"), TEXT("助手"), MB_ICONINFORMATION | MB_YESNO);
		}
	}
	return res;
}
int GetUrl(char *url, char *buff)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buff);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buff_data);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50L);
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);/*下载最高速度*/
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res == CURLE_OK)
		{
			return res;
		}
		else {
			printf("错误代码:%d\n", res);
			MessageBox(NULL, TEXT("获取IP错误"), TEXT("助手"), MB_ICONINFORMATION | MB_YESNO);
		}
	}
	return res;
}
int main()
{
	char *buff=(char*)malloc(1024*1024);
	memset(buff, 0, 1024 * 1024);

	GetUrl("http://baidu.com", buff);
	printf("不使用代理：%s\n", buff);

	memset(buff, 0, 1024 * 1024);
	GetUrlHTTP("http://baidu.com", buff);
	printf("http结果：%s\n", buff);

	memset(buff, 0,1024 * 1024);
	GetUrlSocks5("http://baidu.com", buff);
	printf("socks5结果：%s\n", buff);


	Sleep(1000 * 1000);
	free(buff);
    return 0;
}
```
	
<br/> 



#### 7. PhantomJs 设置代理

```
phantomjs --proxy=ip:port --proxy-type=[http|socks5|none] demo.js
```
	
<br/>


#### 8. Seleniumpython 设置代理

```
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
            
```
	
<br/>       	
	
#### 5. 易语言 设置代理

```php
' 易语言 支持 http
' 
' 米扑代理示例：
' https://proxy.mimvp.com/demo2.php
' 
' 米扑代理购买：
' https://proxy.mimvp.com
' 
' mimvp.com
' 2017-07-28
' 
' 易语言的安装与开发，请参考米扑博客：
' http://blog.mimvp.com/2017/08/yi-yu-yan-de-an-zhuang-yu-kai-fa/
' 
' 易语言的网络编程和代理示例，请参考米扑博客，附有源代码：
' http://blog.mimvp.com/2017/08/yi-yu-yan-de-wang-luo-bian-cheng-he-dai-li-shi-li/


' 变量声明（表格）
.局部变量 代理地址, 文本型
.局部变量 目标网址, 文本型
.局部变量 代理用户名, 文本型
.局部变量 代理密码, 文本型
 
 

' 获取目标网址
.如果 (目标网址编辑框.内容 ＝ “”)
    目标网址 ＝ “http://proxy.mimvp.com/exist.php”
.否则
    目标网址 ＝ 目标网址编辑框.内容
    
' 获取代理地址
.如果 (代理服务器编辑框.内容 ＝ “”)
    代理地址 ＝ “139.59.99.113:8080”
.否则
    代理地址 ＝ 代理服务器编辑框.内容
 
.如果结束
 
输出调试文本 (“代理地址： ” ＋ 代理地址)
 
' 设置代理方法1
网页_置浏览器代理 (代理地址)  ' 通过浏览器设置，一般只支持http代理
超文本浏览框.跳转 (目标网址编辑框.内容, , )
 
 
' 设置代理方法2
输出调试文本 (网页_访问S (目标网址, , , , , , , , , , 代理地址, , ))
 
 
' 设置代理方式3（用户名 +　密码）
输出调试文本 (网页_访问S (目标网址, , , , , , , , , , 代理地址, 代理用户名, 代理密码))
```

![易语言使用代理示例](./cssjs/eyuyan-demo-1.png)

![易语言使用代理示例](./cssjs/eyuyan-demo-2.png)

  
<br/>      
<br/>      
	

注意事项
----------

#### 1. 哪儿可找到代理使用示例里的引用包或依赖库？

解答：米扑代理示例的引用包或依赖库，已经放在了mimvp-proxy-demo开源项目里的目录下了，例如：Python2.7 使用socks4/5是引用了socks.py，已经放在了目录下：https://github.com/mimvp/mimvp-proxy-demo/tree/master/Python2/socks.py

  
<br/>     

#### 2. 如何安装配置编程语言的开发环境？

解答：米扑代理使用示例，全部由米扑科技编写代码、测试验证，因此米扑科技搭建了全部的开发测试环境，详细配置编程语言的开发环境，请参考米扑博客：[http://blog.mimvp.com](http://blog.mimvp.com)

* <a target="_blank" href="http://blog.mimvp.com/2017/09/autohotkey-an-zhuang-yu-kai-fa/">AutoHotkey 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/08/python-scrapy-an-zhuang-yu-kai-fa/">Python scrapy 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/08/python-requests-an-zhuang-yu-kai-fa/">Python requests 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/08/python-pyspider-an-zhuang-yu-kai-fa/">Python pyspider 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/08/python3-urllib-yong-fa-xiang-jie/">Python3 urllib 用法详解</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/10/phantomjs-an-zhuang-yu-kai-fa/">PhantomJS 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/10/phantomjs-selenium-she-zhi-dong-tai-dai-li/">PhantomJS Selenium 设置动态代理</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/10/node-js-an-zhuang-yu-kai-fa/">Node.js 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/10/nodejs-superagent-an-zhuang-yu-kai-fa/">Node.js SuperAgent 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/10/node-js-she-zhi-dai-li-de-liang-zhong-fang-shi-superagent-proxy-he-https-proxy-agent/">Node.js 设置代理的两种方式：superagent-proxy 和 https-proxy-agent</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/09/ruby-an-zhuang-yu-kai-fa/">Ruby 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/09/perl-an-zhuang-yu-kai-fa/">Perl 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/09/delphi-an-zhuang-yu-kai-fa/">Delphi 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/09/groovy-an-zhuang-yu-kai-fa/">Groovy 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/09/scala-an-zhuang-yu-kai-fa/">Scala 安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/09/r-yu-yan-de-an-zhuang-yu-kai-fa/">R语言的安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/09/go-yu-yan-xia-zai-an-zhuang-pei-zhi-shi-yong/">Go语言下载、安装、配置、使用</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/09/go-yu-yan-zhi-chi-http-httpssocks4socks4asocks5-yi-ji-qian-tao-dai-li/">Go语言支持 http、 https、socks4、socks4a、socks5，以及嵌套代理</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/10/httpie-gong-ju-shi-yong-ru-men/">HTTPie 工具使用入门</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/08/yi-yu-yan-de-an-zhuang-yu-kai-fa/">易语言的安装与开发</a>
* <a target="_blank" href="http://blog.mimvp.com/2017/08/yi-yu-yan-de-wang-luo-bian-cheng-he-dai-li-shi-li/">易语言的网络编程和代理示例</a>

  
<br/>     

#### 3. 代理使用示例里的代理从哪找？

解答：米扑代理使用示例（mimvp-proxy-demo）中的测试代理IP，全部来自米扑代理[https://proxy.mimvp.com](https://proxy.mimvp.com)，其支持http、https、socks4、socks5等全部协议的代理IP，而且米扑代理覆盖全球120多个国家，中国34个省市，代理非常丰富，为全球代理IP领导品牌，推荐！

  
<br/>      
<br/>      
	

米扑科技
----------

![mimvp-logo.png](./cssjs/mimvp-logo.png)

<a href="https://mimvp.com" target="_blank">https://mimvp.com</a>

