#pragma once
#include <thread>
#include <chrono>
#include <conio.h>
#include <iostream>
#include "../../cppzmq/zmq.hpp"
#include "../src/jsonClass.hpp"
#define NOMINMAX
#include <windows.h>
#include <synchapi.h>
class Render
{
	Render(Render& other) = delete;
	Render operator=(Render& other) = delete;
public:
	Render() = default;
	Render(Render&& other) noexcept;
	void bind(const std::string&& port);
	Render& operator=(Render&& other) noexcept;
	void testFuncRecvJob(std::vector<std::string>& jsons);
	void ConvertStringtoJson(std::vector<std::string>& strings);
	void Init(ImageData& imageData);
	void Init(Camera& camera);
	~Render() = default;
private:
	zmq::context_t context{ 1 };
	JsonFile json;
	zmq::socket_t  socket{ context, zmq::socket_type::rep};
};