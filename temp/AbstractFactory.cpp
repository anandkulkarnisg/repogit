#include<iostream>
#include<vector>
#include<string>
#include<memory>

using namespace std;

class Message
{
	public:
		virtual ~Message() {  };
		virtual std::string get_message() = 0;
};

class MessageFactory
{

	public:
		virtual ~MessageFactory() { };
		virtual std::unique_ptr<Message> create_message() const = 0;
};

class HelloWorldMessage : public Message
{
	public:
		virtual std::string get_message()
		{ 
			return "Hello World!"; 
		}
};

class HelloWorldMessageFactory : public MessageFactory
{

	public:
		virtual ~HelloWorldMessageFactory() { }
		virtual std::unique_ptr<Message> create_message() const
		{
			return(std::unique_ptr<Message>(new HelloWorldMessage()));
		}
};

void hello_world(const MessageFactory & factory)
{
	std::unique_ptr<Message> message = factory.create_message();
	std::cout << message->get_message() << std::endl;
}

int main(int argc, char* argv[])
{
	hello_world(HelloWorldMessageFactory());
}
