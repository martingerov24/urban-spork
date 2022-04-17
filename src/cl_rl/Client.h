#pragma once
#include <thread>
#include <chrono>
#include <conio.h>

#include "../../cppzmq/zmq.hpp"
#include "../dep/dependencies.h"
//question -> am i able to make a vector of functions and insted of switch cases from the enum
//just [] to the functions(if it makes sense)

class Client
{
	void Ask();
	Result Stop();
	Result Send(const std::string& message);
	Client(Client& other) = delete;
	Client(Client&& other) = delete;
	Client operator=(Client& other) = delete;
	Client& operator=(Client&& other) = delete;
	bool SplitPackage(const std::vector<uint8_t>& package);
	bool LargeDataTransferInBytes(const std::string& file);
	//Send
	bool sendImage(const std::string& imageName);
	bool readingP1Send(const std::string& fileName, int height, int width);
	bool loadAndSend(const std::string& filename, int& width, int& height, int& channels);
public:
	Client() = default;
	void connect(const std::string& port);
	Result Client::setClientStatusAndSend(const ClientMsg msg, const SendOptions sendOpt, const std::string& message);
	~Client();
private:
	ClientMsg m_message = ClientMsg::None;
	SendOptions sendOpt = SendOptions::SmallData;
	zmq::context_t context{ 1 };
	zmq::socket_t socket{ context, zmq::socket_type::req };
	zmq::message_t message;
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