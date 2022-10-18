#ifndef LOS_D_SD_H_
#define LOS_D_SD_H_

#include "fatfs.h"
#include "string.h"

typedef FIL SD_FILE;

const int LOS_SEEK_SET = 0;
const int LOS_SEEK_CUR = -1;
const int LOS_SEEK_END = -2;

class SDCard {
public:
	SDCard(const char* mount_path, int* error);
	~SDCard();

	int fopen(SD_FILE* fp, const char* file_path, const char* mode);
	int fclose(SD_FILE* fp);
	size_t fread(void* buffer, size_t size, size_t count, SD_FILE* fp);
	size_t fwrite(void* buffer, size_t size, size_t count, SD_FILE* fp);
	int fseek(SD_FILE* fp, long offset, int origin);
	long ftell(SD_FILE* fp);
	char* fgets(char* str, int count, SD_FILE* fp);
	int fputs(const char* str, SD_FILE* fp);

private:
	FATFS fs;
	const char* path;

	static BYTE posix_to_fatfs_flag(const char* mode)
	{
		if (strcmp(mode, "r") == 0) {
			return FA_READ;
		} else if (strcmp(mode, "r+") == 0) {
			return FA_READ | FA_WRITE;
		} else if (strcmp(mode, "w") == 0) {
			return FA_CREATE_ALWAYS | FA_WRITE;
		} else if (strcmp(mode, "w+") == 0) {
			return FA_CREATE_ALWAYS | FA_WRITE | FA_READ;
		} else if (strcmp(mode, "a") == 0) {
			return FA_OPEN_APPEND | FA_WRITE;
		} else if (strcmp(mode, "a+") == 0) {
			return FA_OPEN_APPEND | FA_WRITE | FA_READ;
		} else if (strcmp(mode, "wx") == 0) {
			return FA_CREATE_NEW | FA_WRITE;
		} else if (strcmp(mode, "w+x") == 0) {
			return FA_CREATE_NEW | FA_WRITE | FA_READ;
		}

		return 0;
	}
};

#endif
