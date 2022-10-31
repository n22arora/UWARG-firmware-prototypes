#ifndef LOS_D_SD_H_
#define LOS_D_SD_H_

#include "fatfs.h"
#include "string.h"
#include "LOS_D_storage_device.hpp"

class SDCard : StorageDevice {
	private:
		FATFS fs;
		const char* filePath;
		bool fileOpened = false;
		FIL file;

		int open(const char* location);

	public:
		int init() override;
		bool checkExist(const char* location);
		int read(const char* location, uint8_t* data, size_t size, size_t offset = 0) override;
		int write(const char* location, uint8_t* data, size_t size, size_t offset = 0) override;
		size_t length(const char* location) override;
		int cleanup() override;

		static StorageDevice &getInstance();
};

#endif
