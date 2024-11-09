#pragma once
#include<string>
class Message
{
public:
	Message()=default;
	Message(std::string msg, std::string rec, std::string snd);
	std::string getMessage();
	std::string getRecipient();
	std::string getSender();
private:
	std::string message; 
	std::string recipient; 
	std::string sender;
	
};

