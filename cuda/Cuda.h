#pragma once
#define THREADS_PER_BLOCK 1024
#define getGlobalID(X) (blockIdx.x * blockDim.x + threadIdx.x)
#include "cuda_runtime.h"
#include "cuda/std/cmath"
#include "device_launch_parameters.h"
#include "nvtx3/nvToolsExt.h"
#include <vector>
#include <cassert>
#include <chrono>

class Cuda
{
public:
	Cuda() = default;
	Cuda(const int& height, const int& width, cudaError_t cudaStatus)
		:height(height), width(width)
		, d_data(nullptr), d_result(nullptr), cudaStatus(cudaStatus){}
	__host__
		void memoryAllocation(cudaStream_t& providedStream, int size);
	__host__
		void standardMemoryAllocation(cudaStream_t& providedStream, int sizeInBytes, int resultSize);
	__host__
		void uploadToDevice(cudaStream_t& providedStream, const std::vector<uint16_t>& data);

	__host__
		void uploadToDevice(cudaStream_t& providedStream, const std::vector<float>& data, int size);
	__host__
		void download(cudaStream_t& providedStream, std::vector<uint8_t>& h_Data, int size);
	//__host__
	//	void rawValue(cudaStream_t& providedStream);
	__host__
		void sync(cudaStream_t& providedStream);
	
	void outPutFile(std::vector<uint8_t>& h_cpy);
	__host__
		~Cuda();

public:
	uint8_t* d_result;
protected:
	int height, width;
	uint16_t* d_data;
	cudaError_t cudaStatus;
};
