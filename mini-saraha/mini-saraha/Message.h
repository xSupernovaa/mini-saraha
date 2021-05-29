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
		Message(int, int, string);
		string getMessageBody();
};
