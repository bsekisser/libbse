template <class T>
static T generic_access(T* data, T* write)
{
	if(write)
		*data = *write;

	return(*data);
}
