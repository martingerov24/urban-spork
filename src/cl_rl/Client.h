#pragma once
#include <thread>
#include <chrono>
#include <conio.h>
#include <iostream>
#include "../../cppzmq/zmq.hpp"
#include "../dep/dependencies.h"
#define NOMINMAX
#include <windows.h>

#include <synchapi.h> // this is for windows

class Render
{
public:
	Render() = default;
	Render(Render& other) = delete;
	Render(Render&& other) noexcept;
	Render operator=(Render& other) = delete;
	Render& operator=(Render&& other) noexcept;
	void bind(const std::string&& port);
	void testFuncRecvJob();
	~Render() = default;
private:
	zmq::context_t context{ 1 };
	zmq::socket_t  socket{ context, zmq::socket_type::rep};
};