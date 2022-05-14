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

void Render::testFuncRecvJob(std::vector<std::string>& jsons)
{
	int count = static_cast<int>(JsonSend::Count);
	jsons.resize(static_cast<int>(JsonSend::Count));
	for (int i = 0; i < (int)JsonSend::Count; i++)
	{
		zmq::message_t request;

		//  Wait for next request from client
		socket.recv(&request);
		std::cout << request << std::endl;
		jsons[i] = request.to_string();
		//  Do some 'work'
		Sleep(1);

		//  Send reply back to client
		zmq::message_t reply(10);
		memcpy((void*)reply.data(), "not world", 10);
		socket.send(reply, zmq::send_flags::none);
	}
}

void Render::ConvertStringtoJson(std::vector<std::string>& strings)
{
	for (int i = 0; i < (int)JsonSend::Count; i++)
	{
		json.jsonRecieve(strings[i]);
	}
}

void Render::Init(ImageData& imageData)
{
	json.initImageData(imageData);
}

void Render::Init(Camera& camera)
{
	json.initCameraLookAt(camera);
}