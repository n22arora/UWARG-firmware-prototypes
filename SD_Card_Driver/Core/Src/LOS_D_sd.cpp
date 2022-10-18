#include "LOS_D_sd.hpp"

SDCard::SDCard(const char* mount_path, int* result) : path(mount_path)
{
	*result = f_mount(&fs, path, 1);
}

SDCard::~SDCard()
{
	f_mount(NULL, path, 0);
}

int SDCard::fopen(SD_FILE* fp, const char* file_path, const char* mode)
{
	return f_open(fp, file_path, posix_to_fatfs_flag(mode));
}

int SDCard::fclose(SD_FILE* fp)
{
	return f_close(fp);
}

size_t SDCard::fread(void* buffer, size_t size, size_t count, SD_FILE* fp)
{
	size_t bytes_read;
	int fres = f_read(fp, buffer, size * count, &bytes_read);

	return fres == FR_OK ? bytes_read : 0;
}

size_t SDCard::fwrite(void* buffer, size_t size, size_t count, SD_FILE* fp)
{
	size_t bytes_written;
	int fres = f_write(fp, buffer, size * count, &bytes_written);

	return fres == FR_OK ? bytes_written : 0;
}

int SDCard::fseek(SD_FILE* fp, long offset, int origin)
{
	int res;

	switch (origin) {
		case LOS_SEEK_CUR:
			res = f_lseek(fp, f_tell(fp) + offset);
			break;
		case LOS_SEEK_END:
			res = f_lseek(fp, f_size(fp) + offset);
			break;
		default:
			if (origin < 0) {
				res = FR_INT_ERR;
			} else {
				res = f_lseek(fp, origin + offset);
			}
			break;
	}

	return res;
}

long SDCard::ftell(SD_FILE* fp)
{
	return f_tell(fp);
}

char* SDCard::fgets(char* str, int count, SD_FILE* fp)
{
	return f_gets(str, count, fp);
}

int SDCard::fputs(const char* str, SD_FILE* fp)
{
	return f_puts(str, fp);
}
