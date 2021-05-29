#pragma once
#include <string>
using namespace std;

class Message
{
private:
	int senderId;
	int recieverId;
	string messageBody;

public:
	Message(int senderId, int recieverId, string messageBody);
	string getMessageBody();
	int getRecieverId();
	int getSenderId();
};