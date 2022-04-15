#pragma once
#include <thread>
#include <chrono>
#include <conio.h>

#include "../../cppzmq/zmq.hpp"
#include "../dep/dependencies.h"

class Client
{
	void Stop();
	void Ask();
	void Send(const std::string& message);
	Client(Client& other) = delete;
	Client(Client&& other) = delete;
	Client operator=(Client& other) = delete;
	Client& operator=(Client&& other) = delete;
	void sendImage(const std::string& imageName);
public:
	Client() = default;
	void connect(const std::string& port);
	void work(const ClientMsg msg, const std::string& message);
	void setClientStatus(const ClientMsg msg, const SendOptions sendOpt);
	void Client::setClientStatus(const ClientMsg msg);
	void Client::setClientStatus(const ClientMsg msg, const SendOptions sendOpt, const std::string & message);

	~Client() = default;
private:
	ClientMsg m_message = ClientMsg::Continue;
	SendOptions sendOpt = SendOptions::SmallData;
	zmq::context_t context{ 1 };
	zmq::socket_t socket{ context, zmq::socket_type::req };
};

class Render
{
public:
	Render() = default;
	Render(Render& other) = delete;
	Render(Render&& other) noexcept
	{
		std::swap(*this, other);
	}
	Render operator=(Render& other) = delete;
	Render& operator=(Render&& other) noexcept
	{
		if (this != &other)
		{
			std::swap(*this, other);
		}
		return *this;
	}
	void bind(const std::string&& port)
	{
		socket.bind(port);
	}
	void testFuncRecvJob()
	{
		const std::string data{ "World" };

		for (int i = 0; i < 10; i++)
		{
			zmq::message_t request;

			// receive a request from client
			socket.recv(request, zmq::recv_flags::none);
			//std::cout << "Received " << request.to_string() << std::endl;

			// simulate work
			std::this_thread::sleep_for(std::chrono::seconds(1));

			// send the reply to the client
			socket.send(zmq::buffer(data), zmq::send_flags::none);
		}
	}
	~Render()
	{
	}
private:
	zmq::context_t context{ 1 };
	zmq::socket_t  socket{ context, zmq::socket_type::rep };
};