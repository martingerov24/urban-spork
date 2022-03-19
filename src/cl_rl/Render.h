#pragma once 
#include <thread>
#include <chrono>
#include <conio.h>
#include "../../cppzmq/zmq.hpp"
#include "../dep/dependencies.h"

/// The whole scene description
struct Scene : Task {
	Scene() = default;
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	int width = 640;
	int height = 480;
	int samplesPerPixel = 2;
	std::string name;
	std::atomic<int> renderedPixels;
	Instancer primitives;
	class Camera camera;
	ImageData image;

	void onBeforeRender() {
		primitives.onBeforeRender();
	}

	void initImage(int w, int h, int spp) {
		image.init(w, h);
		width = w;
		height = h;
		samplesPerPixel = spp;
		camera.aspect = float(width) / height;
	}

	void addPrimitive(PrimPtr primitive) {
		primitives.addInstance(std::move(primitive));
	}

	void render(ThreadManager& tm) {
		runOn(tm);
	}

	void run(int threadIndex, int threadCount) override {
		const int total = width * height;
		const int incrementPrint = total / 100;
		for (int idx = threadIndex; idx < total; idx += threadCount) {
			const int r = idx / width;
			const int c = idx % width;

			Color avg(0);
			for (int s = 0; s < samplesPerPixel; s++) {
				const float u = float(c + randFloat()) / float(width);
				const float v = float(r + randFloat()) / float(height);
				const Ray& ray = camera.getRay(u, v);
				const vec3 sample = raytrace(ray, primitives);
				avg += sample;
			}

			avg /= samplesPerPixel;
			image(c, height - r - 1) = Color(sqrtf(avg.x), sqrtf(avg.y), sqrtf(avg.z));
			const int completed = renderedPixels.fetch_add(1, std::memory_order_relaxed);
			if (completed % incrementPrint == 0) {
				printf("\r%d%% ", int(float(completed) / float(total) * 100));
			}
		}
	}
};

enum class RenderMsg : uint32_t
{
	Get = 0,
	Return = 1,
	Head = 2,
	Connect = 3,
	Delete = 4,
	Options = 5
};

class Render : public Scene
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
			std::cout << "Received " << request.to_string() << std::endl;

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