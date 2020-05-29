#include <iostream>
#include <vector>
#include <string>

#include "MessageBus.h"

using namespace std;

Message::Message(int type, string data)
{
	this->type = type;
	this->data = data;
}

int Message::getType()
{
	return this->type;
}

string Message::getData()
{
	return this->data;
}

void MessageBus::addListener(ListenerInterface* listener)
{
	listeners.push_back(listener);
}

void MessageBus::notify(Message message)
{
	for (auto listener : listeners)
	{
		listener->onNotify(message);
	}
}
