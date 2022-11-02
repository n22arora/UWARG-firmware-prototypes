#include "LOS_D_sd.hpp"

SDCard::SDCard()
{
	/* Mount FatFS to default drive */
	f_mount(&fs, "", 1);
}

uint8_t SDCard::open(const char* location)
{
	uint8_t res = 0;

	if (!(hasFileOpen && strcmp(location, curOpenFilePath) == 0)) {
		if (hasFileOpen) {
			/* The current opened file is NOT the file we are trying to open */
			res = f_close(&curOpenFile);
		}

		if (res == 0) {
			res = f_open(&curOpenFile, location, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
			hasFileOpen = (res == 0);
		}
	}

	return res;
}

bool SDCard::checkExist(const char* location)
{
	uint8_t res = f_open(&curOpenFile, location, FA_READ);

	if (res == 0) {
		res = f_close(&curOpenFile);
	}

	return res == 0;
}

uint8_t SDCard::read(const char* location, char data[], size_t size, size_t offset)
{
	uint8_t res = open(location);

	if (res == 0) {
		res = f_lseek(&curOpenFile, offset);
	}

	if (res == 0) {
		size_t bytes_read;
		res = f_read(&curOpenFile, data, size, &bytes_read);
	}

	return res;
}

uint8_t SDCard::write(const char* location, const char data[], size_t size, size_t offset)
{
	uint8_t res = open(location);

	if (res == 0) {
		res = f_lseek(&curOpenFile, offset);
	}

	if (res == 0) {
		size_t bytes_written;
		res = f_write(&curOpenFile, data, size, &bytes_written);
	}

	return res;
}

size_t SDCard::length(const char* location)
{
	size_t res = open(location);

	if (res == 0) {
		res = f_size(&curOpenFile);
	}

	return res;
}

uint8_t SDCard::cleanup()
{
	uint8_t res = 0;

	if (hasFileOpen) {
		res = f_close(&curOpenFile);
		hasFileOpen = false;
	}

	return res;
}

SDCard::~SDCard()
{
	cleanup();

	/* Dismount FatFS */
	f_mount(NULL, "", 0);
}

StorageDevice& SDCard::getInstance()
{
	static SDCard singleton;
	return singleton;
}
