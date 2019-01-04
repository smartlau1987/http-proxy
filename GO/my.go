package main

import (
	"encoding/base64"
	_ "encoding/base64"
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
	_ "strings"
)

//sock5代理
func socksproxy() {
	urli := url.URL{}
	urlproxy, _ := urli.Parse("http://测试IP:端口") //通过http://h.wandouip.com
	client := &http.Client{
		Transport: &http.Transport{
			Proxy: http.ProxyURL(urlproxy),

		},
	}
	rqt, err := http.NewRequest("GET", "http://h.wandouip.com", nil)
	if err != nil {
		println("接口获取IP失败!")
		return
	}
	username := "用户名"
	password := "密码"
	str := username +":"+ password;
	basic := base64.StdEncoding.EncodeToString([]byte(str))
	basic1 :="Basic "
	value:=basic1+basic
	//fmt.Print(value);
	rqt.Header.Add("User-Agent", "Lingjiang")
	rqt.Header.Add("Proxy-Authorization",value)
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
	urlproxy, _ := urli.Parse("http://测试IP:端口号") //通过http://h.wandouip.com/get获取
	client := &http.Client{
		Transport: &http.Transport{
			Proxy: http.ProxyURL(urlproxy),
		},
	}
	rqt, err := http.NewRequest("GET", "http://h.wandouip.com", nil)
	if err != nil {
		println("接口获取IP失败!")
		return
	}
	//
	username := "用户名"
	password := "密码"
	str := username +":"+ password;
	basic := base64.StdEncoding.EncodeToString([]byte(str))
	basic1 :="Basic "
	value:=basic1+basic
	//fmt.Print(value);
	rqt.Header.Add("User-Agent", "Lingjiang")
	rqt.Header.Add("Proxy-Authorization",value)
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
	rqt, err := http.NewRequest("GET", "http://h.wandouip.com", nil)
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
	//httplocal()
	httpproxy()
	//socksproxy()
}