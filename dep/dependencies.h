#pragma once 
#include <stdint.h>
enum class ClientMsg : uint8_t
{
	Send,
	Stop,
	Continue,
	Deactivate,
	Count
};
enum class SendOptions : uint8_t
{
	SmallData,
	FileInBytes,
	LargeObj,
	Count
};