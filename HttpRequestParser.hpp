#ifndef  HTTPREQUESTPARSER_H
#define  HTTPREQUESTPARSER_H
#include <vector>
#include <string>

//parse
class HttpRequestParser {
public:
	HttpRequestParser(int clientFd) 
		: _clientFd(clientFd)
	{}
	
	~HttpRequestParser() {}
	
	bool isNextHeaderLine();
	const std::string getNextHeaderLine();

private:
	bool isConnected() const { return _isConnected; }
	void readData() ;
	void setConnectClosed() 
	{
		_isConnected = false;
	}

private:
	int _clientFd;
	bool _isConnected = true;
	std::string _buf; //save parsered data
	std::vector<std::string> _headers;
};


#endif   /* ----- #ifndef HTTPREQUESTPARSER_H ----- */
