package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
)

//sock5����
func socksproxy() {
	urli := url.URL{}
	urlproxy, _ := urli.Parse("http://����ip:�˿�")
	client := &http.Client{
		Transport: &http.Transport{
			Proxy: http.ProxyURL(urlproxy),
		},
	}
	rqt, err := http.NewRequest("GET", "http://myip.top", nil)
	if err != nil {
		println("�ӿڻ�ȡIPʧ��!")
		return
	}

	rqt.Header.Add("User-Agent", "Lingjiang")
	//�����ؽ��
	response, _ := client.Do(rqt)
	defer response.Body.Close()
	body, err := ioutil.ReadAll(response.Body)
	if err != nil {
		return
	}

	fmt.Println("socks5:", string(body))
	return

}

//http����
func httpproxy() {
	urli := url.URL{}
	urlproxy, _ := urli.Parse("http://����ip:�˿�")
	client := &http.Client{
		Transport: &http.Transport{
			Proxy: http.ProxyURL(urlproxy),
		},
	}
	rqt, err := http.NewRequest("GET", "http://myip.top", nil)
	if err != nil {
		println("�ӿڻ�ȡIPʧ��!")
		return
	}

	rqt.Header.Add("User-Agent", "Lingjiang")
	//�����ؽ��
	response, _ := client.Do(rqt)
	defer response.Body.Close()
	body, err := ioutil.ReadAll(response.Body)
	if err != nil {
		return
	}

	fmt.Println("http:", string(body))
	return

}

//����IP
func httplocal() {
	client := &http.Client{}
	rqt, err := http.NewRequest("GET", "http://myip.top", nil)
	if err != nil {
		println("�ӿڻ�ȡIPʧ��!")
		return
	}

	rqt.Header.Add("User-Agent", "Lingjiang")
	//�����ؽ��
	response, _ := client.Do(rqt)
	defer response.Body.Close()
	body, err := ioutil.ReadAll(response.Body)
	if err != nil {
		return
	}

	fmt.Println("����:", string(body))
	return

}
func main() {
	httplocal()
	httpproxy()
	socksproxy()
}