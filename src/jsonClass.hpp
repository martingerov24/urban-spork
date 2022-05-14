#pragma once 
#include "../dep/dependencies.h"
#include "../src/third_party/jsoncpp.hpp"
#include <Image.hpp>
#include "camera.hpp"

struct JsonFile
{
	// in reserve i have added 5 jsons
	JsonFile()
	{
		premadeJsons.resize((int)JsonSend::Count);
	};
	void jsonRecieve(std::string& json)
	{
		premadeJsons[count] = nlohmann::json::parse(json.c_str());
		std::cout << premadeJsons[count].dump().c_str() << "\n";
		count++;
	}
	void initImageData(ImageData & imageData)
	{
		nlohmann::json tmp = premadeJsons[static_cast<int>(JsonSend::InitImage)];
		int w = tmp["width"].get<int>();
		imageData.init(tmp["width"], tmp["height"]);
	}
	void initCameraLookAt(Camera & camera)
	{
		nlohmann::json tmp = premadeJsons[static_cast<int>(JsonSend::CameraLookAt)];
		vec3 lookFrom(tmp["lookFromX"], tmp["lookFromY"], tmp["lookFromZ"]);
		vec3 lookAt(tmp["lookAtX"], tmp["lookAtY"], tmp["lookAtZ"]);
		camera.lookAt(tmp["verticalFov"], lookFrom, lookAt);
	}
	~JsonFile() = default;
private:
	int count = 0;
	std::vector<nlohmann::json> premadeJsons;
};