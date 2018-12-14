/**
C# 支持 http、https
*/
 
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
    