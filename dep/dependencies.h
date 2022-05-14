#pragma once 
#include <stdint.h>
const int PackageSize = 5000;
//int ClientCount = 0;
enum class ClientMsg : uint8_t
{
	Send,
	Stop,
	Deactivate,
	None
};
enum class SendOptions : uint8_t
{
	SmallData,
	FileInBytes,
	Image,
	ImageP1,
	Count
};
enum class Result : uint8_t
{
	FailedToSend = 0, 
	Succeeded = 1,
};

enum class JsonSend : uint8_t
{
	InitImage = 0,
	CameraLookAt = 1,
	Count = 2
};