#include "print_hex.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <menu.h>
typedef struct file_s
{
	struct stat sb;
	size_t len;
	FILE* fp;
	uint8_t* buf;
	char* name;
} file_t;

static void finish(int sig)
{
	endwin();
	exit(sig);
}

file_t* create_file(char* filename)
{
	if(filename == NULL)
	{
		fprintf(stderr, "Error filename equals NULL!");
		return NULL;
	}

	file_t* file = calloc(1, sizeof(file_t));

	if(stat(filename, &file->sb) != 0)
	{
		perror("Error retrieving file information with stat");
		free(file);
		return NULL;
	}

	file->len = file->sb.st_size;
	file->fp = fopen(filename,"rb");

	if(file->fp == NULL)
	{
		perror("Error opening file");
		free(file);
		return NULL;
	}

	file->buf = calloc(1,file->len);

	if(file->len != fread(file->buf, 1, file->len, file->fp))
	{
		perror("Error reading file");
		fclose(file->fp);
		free(file->buf);
		free(file);
		return NULL;
	}

	file->name = strdup(filename);

	return file;
}

bool destroy_file(file_t* file)
{

	free(file->name);
	free(file->buf);
	free(file);
	if(fclose(file->fp) == EOF)
	{
		perror("Error closing file");
		return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	int status = 0;
	int num = 0;
	int hex_val = 0;
	uint8_t tuple_len = 8;

	if(argc < 3)
	{
		fprintf(stderr, "Not enough arguments\n");
		exit(EXIT_FAILURE);
	}

	signal(SIGINT, finish);
	initscr();
	nonl();
	cbreak();
	keypad(stdscr, TRUE);
	scrollok(stdscr, TRUE);
	//echo();
	
	refresh();

	if(has_colors())
	{
		start_color();
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		init_pair(5, COLOR_CYAN, COLOR_BLACK);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_WHITE, COLOR_BLACK);
	}
	
	file_t* file = create_file(argv[1]);

	int ch = '\0';
	tuple_len = (uint8_t)strtouq(argv[2],NULL,0);

	print_hex_data(file->buf, file->len, 16 , tuple_len);

	if(!destroy_file(file))
		finish(EXIT_FAILURE);
	finish(EXIT_SUCCESS);
}

