#include <cstdlib>
#include <cstdio>

#include <CL/cl.h>

#define VECTOR_SIZE 100000
#define DEVICE_INDEX 1

void check_error(const char *info, cl_uint err)
{
	if (err == CL_SUCCESS)
	{
		printf("%s SUCCEEDED.\n", info);
	}
	else
	{
		printf("%s FAILED(%d).\n", info, err);
	}
}

int main()
{
	cl_int err;

	char *in = (char *) malloc(VECTOR_SIZE * sizeof(char));
	char *out = (char *) malloc(VECTOR_SIZE * sizeof(char));

	cl_platform_id platform_id;
	cl_device_id device_ids[10];
	cl_context context;
	cl_command_queue cmd_queue;
	cl_mem in_mem = NULL;
	cl_mem out_mem = NULL;

	// Get platform id
	cl_uint ret_num_platforms;
	err = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);

	// Get platform information
	char platform_name[100];
	cl_uint param_value_size_ret;
	err = clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, 100, 
			platform_name, &param_value_size_ret);
	printf("Platform name: %s\n", platform_name);

	// Get devices
	cl_uint num_devices_ret;
	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 10, 
			device_ids, &num_devices_ret);
	printf("%d devices found\n", num_devices_ret);

	// Print devices names
	for (int i = 0; i < num_devices_ret; i++)
	{
		char device_name[100];
		err = clGetDeviceInfo(device_ids[i], CL_DEVICE_NAME, 
				100, device_name, &param_value_size_ret);
		printf("Device name: %s\n", device_name);
	}

	// Create context
	context = clCreateContext(NULL, 1, &device_ids[DEVICE_INDEX], NULL, 
			NULL, &err);
	check_error("Create context", err);

	// Create command queue
	cmd_queue = clCreateCommandQueue(context, device_ids[DEVICE_INDEX], 0, 
			&err);
	check_error("Create command queue", err);
		
	// Create memory
	in_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, VECTOR_SIZE, NULL, 
			&err);
	out_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, VECTOR_SIZE, NULL, 
			&err);
	check_error("Creating buffers", err);

}

