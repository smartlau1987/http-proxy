// demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "curl/curl.h"
#include <string.h>
#pragma comment(lib, "libcurl.lib")
static size_t write_buff_data(char *buffer, size_t size, size_t nitems, void *outstream)
{
	memcpy(outstream, buffer, nitems*size);
	return nitems * size;
}
/*
使用http代理
*/
int GetUrlHTTP(char *url, char *buff, char *out_data)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_PROXY, "http://测试IP:端口");//通过http://h.wandouip.com/get获取
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buff);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buff_data);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50L);
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);/*下载最高速度*/
		curl_easy_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_BASIC);/*设置代理验证信息*/
		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, out_data);/*设置代理认证的用户名和密码*/
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
/*
使用socks5代理
*/
int GetUrlSocks5(char *url, char *buff,char *out_data)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		
		curl_easy_setopt(curl, CURLOPT_PROXY, "socks5://测试IP:端口");//通过http://h.wandouip.com/get获取
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buff);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buff_data);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl , CURLOPT_PROXYTYPE, 5); //sock5
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50L);
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);/*下载最高速度*/
		curl_easy_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_BASIC);/*设置代理验证信息*/
		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, out_data);/*设置代理认证的用户名和密码*/
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
	char *buff = (char*)malloc(1024 * 1024);
	memset(buff, 0, 1024 * 1024);

	//GetUrl("http://h.wandouip.com", buff);
	//printf("不使用代理：%s\n", buff);
	char *username = "用户账号";
	char *password = "用户密码";
	
	char *l = ":";
	char *out_data = (char *)malloc(strlen(username) + strlen(password) + strlen(l));
	sprintf(out_data, "%s%s%s", username, l, password);

	memset(buff, 0, 1024 * 1024);
	GetUrlHTTP("http://h.wandouip.com", buff,out_data);
	printf("http结果：%s\n", buff);
	
	memset(buff, 0,1024 * 1024);
	GetUrlSocks5("http://h.wandouip.com", buff,out_data);
	printf("socks5结果：%s\n", buff);


	Sleep(1000 * 1000);
	free(buff);
	return 0;
}

