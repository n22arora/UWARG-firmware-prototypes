#include "LOS_D_sd.hpp"

int SDCard::init()
{
	return f_mount(&fs, "", 1);
}

int SDCard::open(const char* location)
{
	if (fileOpened && strcmp(location, filePath) == 0) {
		return 0;
	}

	if (fileOpened) {
		int res = f_close(&file);
		if (res != 0) {
			return res;
		}
	}

	int res = f_open(&file, location, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
	fileOpened = (res == 0);

	return res;
}

bool SDCard::checkExist(const char* location)
{
	int res = f_open(&file, location, FA_READ);
	if (res == 0) {
		f_close(&file);
	}

	return res == 0;
}

int SDCard::read(const char* location, uint8_t* data, size_t size, size_t offset)
{
	int res = this->open(location);
	if (res != 0) {
		return res;
	}

	res = f_lseek(&file, offset);
	if (res != 0) {
		return res;
	}

	size_t bytes_read;
	res = f_read(&file, data, size, &bytes_read);

	return res;
}

int SDCard::write(const char* location, uint8_t* data, size_t size, size_t offset)
{
	int res = this->open(location);
	if (res != 0) {
		return res;
	}

	res = f_lseek(&file, offset);
	if (res != 0) {
		return res;
	}

	size_t bytes_written;
	res = f_write(&file, data, size, &bytes_written);

	return res;
}

size_t SDCard::length(const char* location)
{
	int res = this->open(location);
	if (res != 0) {
		return res;
	}

	return f_size(&file);
}

int SDCard::cleanup()
{
	if (fileOpened) {
		f_close(&file);
	}

	return f_mount(NULL, "", 0);
}

StorageDevice& SDCard::getInstance()
{
	static SDCard singleton;
	return singleton;
}
