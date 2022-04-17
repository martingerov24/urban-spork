#include "Client.h"
#include <sys/stat.h>

long GetFileSize(std::string * filename)
{
	struct stat stat_buf;
	int rc = stat(filename->c_str(), &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

void Client::Stop()
{
}

void Client::Ask()
{
}
void SmallDataTransfer(std::string * msg)
{

}
<<<<<<< HEAD
std::vector<uint8_t> readingFiles(char* fileName, int height, int width)
{
	FILE* rdFile = fopen(fileName, "rb+");
	std::vector<uint8_t> data;
	if (rdFile == 0) {
		printf("no file found!");
		return data;
	}
	int size = height * width;
	data.resize(size);
	fread(reinterpret_cast<char*>(&data[0]), 2, size, rdFile);
	fclose(rdFile);
	return data;
}

std::vector<uint8_t> load(const std::string& filename, int& width, int& height, int& channels)
{
	unsigned char* img = stbi_load(filename.c_str(), &width, &height, &channels, 1);
	//stbir_resize_uint8(img, width, height, 0, img, width, height, 0, 1);
	if (img == NULL) { throw "the file was not found"; }
	std::vector<uint8_t> image(width * height * channels);
	memcpy(&image[0], img, image.size());
	if (image.empty()) { throw "vector is null"; }
	stbi_image_free(img);
	return image;
}

void sendImage(const std::string& imageName)
{
	int width, height, channels;
	std::vector<uint8_t> image = load(imageName, width, height, channels);
	zmq::message_t request(image.size());
	memcpy(request.data(), (image.data()), (image.size()));
	socket.send(request);
}
=======
>>>>>>> d01b0b5ea4863ae389b755c38cbe808b8c56ad45
void LargeDataTransferInBytes(std::string* file)
{
	FILE* rdfile = fopen(file->c_str(), "r+");
	std::vector<char> data;
	if (rdfile == 0) { throw "no file found!"; }
	long size = GetFileSize(file);
	if (size == -1) {throw "file size is zero!"; }
	data.resize(size);
	fread(reinterpret_cast<char*>(&data[0]), 1, size, rdfile);
	fclose(rdfile);
	return;
}
void Client::Send(std::string * msg)
{
	if (Client::sendOpt == SendOptions::SmallData)
	{

	}
	else if(Client::sendOpt == SendOptions::SmallData)
	{

	}
	Client::m_message = ClientMsg::Continue;
}

