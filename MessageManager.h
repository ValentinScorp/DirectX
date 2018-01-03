#ifndef SOURCE_MESSAGEMANAGER_H_
#define SOURCE_MESSAGEMANAGER_H_

class Message
{
public:
    enum State {
        MS_NOT_HANDLED,
        MS_HANDLED
    };

	std::string type;
	std::string name;
	int x;
	int y;
	int delta;
	State state = MS_NOT_HANDLED;
public:
	Message(std::string t, std::string n, int ix, int iy, int d) {
		type = t;
		name = n;
		x = ix;
		y = iy;
		delta = d;
	}
	~Message() {
	}

	void SetMessageHandled(){
        state = MS_HANDLED;
	}

	bool IsMessageHandled() {
        return (state == MS_HANDLED);
	}
};

class MessageSender;

class MessageReceiver
{
public:
	MessageReceiver() {}
	virtual ~MessageReceiver() {}

	virtual Message::State OnMessage(Message message) = 0;

};

class MessageSender
{
protected:
	std::list<MessageReceiver*> receivers;
public:
	MessageSender() {
	}
	virtual ~MessageSender() {}

	virtual void SendMessage(Message message) {
		for (MessageReceiver *r : receivers) {
			r->OnMessage(message);
		}
	}
	virtual void RegisterListener(MessageReceiver *rec) final {
		receivers.push_back(rec);
	}
};

#endif /* SOURCE_MESSAGEMANAGER_H_ */
