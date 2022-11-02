#ifndef LOS_D_SD_H_
#define LOS_D_SD_H_

#include "fatfs.h"
#include "string.h"
#include "LOS_D_storage_device.hpp"

class SDCard : public StorageDevice {
	private:
		FATFS fs;
		const char* curOpenFilePath;
		bool hasFileOpen = false;
		FIL curOpenFile;

		uint8_t open(const char* location);

	public:
		SDCard();
		~SDCard();
		bool checkExist(const char* location);
		uint8_t read(const char* location, char data[], size_t size, size_t offset = 0) override;
		uint8_t write(const char* location, const char data[], size_t size, size_t offset = 0) override;
		size_t length(const char* location) override;
		uint8_t cleanup() override;

		static StorageDevice &getInstance();
};

#endif
