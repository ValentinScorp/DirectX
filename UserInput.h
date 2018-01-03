#ifndef SOURCE_USERINPUT_H_
#define SOURCE_USERINPUT_H_

class UserInput : public MessageSender
{
private:
    MessageReceiver* guiSystem = nullptr;

public:
	UserInput();
	virtual ~UserInput();

	void RegisterGuiReceiver(MessageReceiver *mr);
    void SendMessage(Message mes);
};
#endif /* SOURCE_USERINPUT_H_ */
