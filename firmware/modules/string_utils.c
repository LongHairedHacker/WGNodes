#include <stdio.h>
#include <string.h>

#include "osapi.h"

#include "string_utils.h"

int parse_lines(char* str, char** lines, int line_count)  {
	char* line;
	int pos = 0;

	os_memset(lines, 0, line_count * sizeof(char*));

	line = strtok(str, "\n");
	while(line != NULL && pos < line_count) {
		lines[pos] = line;
		pos++;
		line = strtok(NULL, "\n");
	}

	return pos;
}

