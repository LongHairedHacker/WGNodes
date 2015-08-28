#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int parse_lines(char* str, char** lines, int line_count)  {
	char* line;
	int pos = 0;

	memset(lines, 0, line_count * sizeof(char*));

	line = strtok(str, "\n");
	while(line != NULL && pos < line_count) {
		lines[pos] = line;
		pos++;
		line = strtok(NULL, "\n");
	}

	return pos;
}


int main(int argc, const char* argv[]) {

	char msg[] = "1234\n42\n23\nleer\nnope";
	char* lines[4];

	printf("msg: %s\n", msg);


	int count = parse_lines(msg, lines, 4);
	printf("Parsed %d lines\n", count);

	printf("str h: %s\n", lines[0]);
	printf("str s: %s\n", lines[1]);
	printf("str v: %s\n", lines[2]);

	printf("foo: %s\n", lines[3]);

	return 0;
}
