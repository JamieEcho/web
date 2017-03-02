/**
 * @file     HttpRequestParser.cpp
 *           
 *
 * @author   lili  <lilijreey@gmail.com>
 * @date     02/15/2017 08:01:29 PM
 *
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include "HttpRequestParser.hpp"

bool HttpRequestParser::isNextHeaderLine()  
{
	while (isConnected()) 
	{
		if (_buf.find("\r\n") != std::string::npos)/*用-1不好！！*/
		{
			if(_buf.length() == 2)
			{
				printf("fetch the finished token");
				setConnectClosed();
				return false;
			}
		
			return true;
		}
		
		readData();
	}
	return false;
}

const std::string HttpRequestParser::getNextHeaderLine() 
{
	if (not isNextHeaderLine())
		return ""; //FIXME use iterator 
	
	int pos = _buf.find("\r\n");
	
	std::string head = _buf.substr(0, pos);
	_buf.erase(0, pos+2);//将剩余的信息向前移
	
	_headers.push_back(head);
	
	return head;
}

void HttpRequestParser::readData() 
{
	if (not isConnected())
		return;
	
	constexpr int BUF_SIZE = 1024;
	char buf[BUF_SIZE];

again: /*阻塞IO (没有数据时调用recv会阻塞)*/
	int ret = recv(_clientFd, buf, BUF_SIZE, 0);
	if (ret == -1) 
	{
		if (errno == EINTR) 
			goto again;

		if(errno == EAGAIN)
			return;

		perror("recv");
		setConnectClosed();
		return;
	}

	if(ret == 0)
	{
		setConnectClosed();
		return ;
	}
	
	_buf.append(buf, ret);
}


