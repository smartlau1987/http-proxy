// demo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "curl/curl.h"
#pragma comment(lib, "libcurl.lib")
static size_t write_buff_data(char *buffer, size_t size, size_t nitems, void *outstream)
{
	memcpy(outstream, buffer, nitems*size);
	return nitems*size;
}
/*
ʹ��http����
*/
int GetUrlHTTP(char *url, char *buff)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_PROXY,"http://����ip:�˿�");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buff);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buff_data);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50L);
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);/*��������ٶ�*/
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res == CURLE_OK){
			return res;
		}else {
			printf("�������:%d\n", res);
			MessageBox(NULL, TEXT("��ȡIP����"), TEXT("����"), MB_ICONINFORMATION | MB_YESNO);
		}
	}
	return res;
}
/*
ʹ��socks5����
*/
int GetUrlSocks5(char *url, char *buff)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_PROXY, "socks5://����ip:�˿�");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buff);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buff_data);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50L);
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);/*��������ٶ�*/
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res == CURLE_OK) {
			return res;
		}
		else {
			printf("�������:%d\n", res);
			MessageBox(NULL, TEXT("��ȡIP����"), TEXT("����"), MB_ICONINFORMATION | MB_YESNO);
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
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);/*��������ٶ�*/
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res == CURLE_OK)
		{
			return res;
		}
		else {
			printf("�������:%d\n", res);
			MessageBox(NULL, TEXT("��ȡIP����"), TEXT("����"), MB_ICONINFORMATION | MB_YESNO);
		}
	}
	return res;
}
int main()
{
	char *buff=(char*)malloc(1024*1024);
	memset(buff, 0, 1024 * 1024);

	GetUrl("http://baidu.com", buff);
	printf("��ʹ�ô���%s\n", buff);

	memset(buff, 0, 1024 * 1024);
	GetUrlHTTP("http://baidu.com", buff);
	printf("http�����%s\n", buff);

	memset(buff, 0,1024 * 1024);
	GetUrlSocks5("http://baidu.com", buff);
	printf("socks5�����%s\n", buff);


	Sleep(1000 * 1000);
	free(buff);
    return 0;
}

