#include<iostream>
#include<string>
#include<memory>

using namespace std;

class Message
{
	public:
		virtual std::string get_message() = 0;
		virtual ~Message() { }
};

class MessageFactory
{
	public:
		virtual std::unique_ptr<Message> create_message() const = 0;
		virtual ~MessageFactory() { } 
};

class HelloWorldMessage : public Message
{
	public:
		virtual std::string get_message()
		{
			return("hello world!");
		}
};

class HelloWorldMessageFactory : public MessageFactory
{
	public:
		virtual std::unique_ptr<Message> create_message() const 
		{
			return(std::unique_ptr<Message>(new HelloWorldMessage()));
		}
};

void hello_world(const MessageFactory& factory)
{
	std::unique_ptr<Message> message = factory.create_message();
	cout << message->get_message() << endl;	
}

int main(int argc, char* argv[])
{
	hello_world(HelloWorldMessageFactory());
	return(0);
}






