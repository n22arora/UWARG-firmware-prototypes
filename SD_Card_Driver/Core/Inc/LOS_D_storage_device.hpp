#ifndef LOS_D_STORAGE_DEVICE_HPP_
#define LOS_D_STORAGE_DEVICE_HPP_

class StorageDevice {
	public:
		/* Initialize the storage device */
		virtual int init() = 0;

		/* Read bytes from a location with an optional offset */
		virtual int read(uint8_t* data, size_t size, const char* location, size_t offset = 0) = 0;

		/* Write bytes from a location with an optional offset */
		virtual int write(uint8_t* data, size_t size, const char* location, size_t offset = 0) = 0;

		/* Returns the length of the data at a location */
		virtual size_t length(const char* location) = 0;

		/* Clean up the storage device after I/O operations */
		virtual int cleanup() = 0;
};

#endif
