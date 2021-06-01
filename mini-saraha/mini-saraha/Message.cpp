#include "Message.h"

Message::Message(int senderId, int recieverId, string messageBody)
{
	this->senderId = senderId;
	this->recieverId = recieverId;
	this->messageBody = messageBody;
}



string Message::getMessageBody()
{
	return messageBody;
}

int Message::getRecieverId()
{
	return recieverId;
}

int Message::getSenderId()
{
	return senderId;
}
