#pragma once

#include <vector>
#include <string>

using namespace std;

class Message
{
private:
	int type;
	string data;
public:
	static const int LOAD_MENU = 1;
	static const int EXIT_APP = 2;

	Message(int type, string data);
	int getType();
	string getData();
};

class ListenerInterface
{
public:
	virtual void onNotify(Message message) = 0;
	~ListenerInterface() {};
};

class MessageBus
{
private:
	vector<ListenerInterface*> listeners;
public:
	void addListener(ListenerInterface* listener);
	void notify(Message message);
};
