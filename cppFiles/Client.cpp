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

