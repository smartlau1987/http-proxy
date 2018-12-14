<?php
/**
 * PHP 支持 http、socks5
 *
 * curl不是php原生库，需要安装库:
 * Ubuntu系统：sudo apt-get -y install php5-curl
 * CentOS系统：yum -y install php-curl
 * MacOS 系统：brew install php-curl
 *
 * CURLOPT_PROXYTYPE :
 * 	CURLPROXY_HTTP,    CURLPROXY_HTTP_1_0
 * 	CURLPROXY_SOCKS4,  CURLPROXY_SOCKS4A
 * 	CURLPROXY_SOCKS5,  CURLPROXY_SOCKS5_HOSTNAME
 */

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
?>