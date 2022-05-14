#include "Client.h"

Render::Render(Render&& other) noexcept
{
	std::swap(*this, other);
}
Render& Render::operator=(Render&& other) noexcept
{
	if (this != &other)
	{
		std::swap(*this, other);
	}
	return *this;
}
void Render::bind(const std::string&& port)
{
	socket.bind(port);
}

void Render::testFuncRecvJob()
{
	while (true)
	{
		zmq::message_t request;

		//  Wait for next request from client
		socket.recv(&request);
		std::cout << request << std::endl;

		//  Do some 'work'
		Sleep(1);

		//  Send reply back to client
		zmq::message_t reply(10);
		memcpy((void*)reply.data(), "not world", 10);
		socket.send(reply, zmq::send_flags::none);
	}
}