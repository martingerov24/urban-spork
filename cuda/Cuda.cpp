#include "Cuda.h"


__host__
void Cuda::memoryAllocation(cudaStream_t& providedStream, int size)
{
	cudaStatus = cudaMallocAsync((void**)&d_data, (size + 2) * sizeof(uint16_t), providedStream);
	assert(cudaStatus == cudaSuccess && "cudaMalloc failed!");

	cudaStatus = cudaMallocAsync((void**)&d_result, sizeof(uint8_t) * size * 4, providedStream);
	assert(cudaStatus == cudaSuccess && "cudaMalloc failed!");
}

__host__
void Cuda::standardMemoryAllocation(cudaStream_t& providedStream, int sizeInBytes, int resultSize)
{
	cudaStatus = cudaMallocAsync((void**)&d_data, sizeInBytes, providedStream);
	assert(cudaStatus == cudaSuccess && "cudaMalloc failed!");

	cudaStatus = cudaMallocAsync((void**)&d_result, resultSize, providedStream);
	assert(cudaStatus == cudaSuccess && "cudaMalloc failed!");
}

__host__
void Cuda::uploadToDevice(cudaStream_t& providedStream, const std::vector<uint16_t>& data)
{
	if (data.size() == 0) { throw "the vector is empty"; }
	cudaStatus = cudaMemcpyAsync(d_data, data.data(), sizeof(uint16_t) * data.size(), cudaMemcpyHostToDevice, providedStream);
	assert(cudaStatus == cudaSuccess && "not able to trainsfer data, between host and device");
}

__host__
void Cuda::uploadToDevice(cudaStream_t& providedStream, const std::vector<float>& data, int size)
{
	cudaStatus = cudaMemcpyAsync(d_data, data.data(), size, cudaMemcpyHostToDevice, providedStream);
	assert(cudaStatus == cudaSuccess && "not able to trainsfer data, between host and device");
}

__host__
void Cuda::download(cudaStream_t& providedStream, std::vector<uint8_t>& h_Data, int size)
{
	cudaStatus = cudaMemcpyAsync(h_Data.data(), d_result, sizeof(uint8_t) * size, cudaMemcpyDeviceToHost, providedStream);
	assert(cudaStatus == cudaSuccess && "not able to transfer device to host!");
}

__host__
void Cuda::sync(cudaStream_t& providedStream)
{
	cudaStatus = cudaStreamSynchronize(providedStream);
	assert(cudaStatus == cudaSuccess && "synchronize problem");
}

void Cuda::outPutFile(std::vector<uint8_t>& h_cpy)
{
	FILE* fileWr;
	fileWr = fopen("writingFile.ppm", "w+");
	fprintf(fileWr, "%s %d %d %d ", "P6", width, height, 255);
	fclose(fileWr);

	fileWr = fopen("writingFile.ppm", "ab+");
	fwrite(reinterpret_cast<const char*>(&h_cpy[0]), 1, sizeof(uint8_t) * width * height * 3, fileWr);
	fclose(fileWr);
	fileWr = nullptr;
}
__host__
Cuda::~Cuda()
{
	cudaFree(d_data);// it was said to -> cudaFree ( void* devPtr )Frees memory on the device.
}