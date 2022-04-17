#pragma once
#include <thread>
#include <chrono>
#include <conio.h>

#include "../../cppzmq/zmq.hpp"

enum class ClientMsg : uint32_t
{
	Send = 0,
	Stop = 1,
	Continue = 2,
	Deactivate = 4
};
enum class SendOptions : uint32_t
{
	SmallData = 0,
<<<<<<< HEAD
	FileInBytes = 1,
	LargeObj = 2
=======
	File = 1
>>>>>>> d01b0b5ea4863ae389b755c38cbe808b8c56ad45
};

class Client
{
	void Stop();
	void Ask();
	void Send(std::string* message);
	Client(Client& other) = delete;
	Client(Client&& other) = delete;
	Client operator=(Client& other) = delete;
	Client& operator=(Client&& other) = delete;
	//connect to a local host
public:
	Client() = default;
	void connect(const std::string& port)
	{
		socket.connect(port);
	};
	void work(std::string* message = nullptr)
	{
		if (m_message == ClientMsg::Continue){
			this->work();
		}
		else if (m_message == ClientMsg::Stop){
			Stop();
		}
		else if (m_message == ClientMsg::Send){
			Send(message);
		}
	}
	void setClientStatus(ClientMsg msg = ClientMsg::Continue 
		, SendOptions sendOpt = SendOptions::SmallData)
	{
		this->m_message = msg;
	}
	~Client()
	{
	}
private:
	ClientMsg m_message = ClientMsg::Continue;
	SendOptions sendOpt;
	zmq::context_t context{ 1 };
	zmq::socket_t socket{ context, zmq::socket_type::req };
};