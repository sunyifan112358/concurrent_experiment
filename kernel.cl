__kernel void vector_copy(
	__global char *in,
	__global char *out)
{
	int i = get_global_id(0);
	out[i] = in[i];
}
