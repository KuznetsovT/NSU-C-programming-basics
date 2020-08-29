
//функция считывания из файла



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * getText(FILE *stream, const char * terminator);

char * realloc(char *arr, const size_t arr_size, const size_t resize);


int main() {

	auto str = getText(stdin, "#\n");
	printf("\n%s\n", str);
	free(str);
	return 0;
}






char * getText(FILE * stream, const char * terminator)
{
	size_t allocated = 32, pos = 0;
	char *buff = (char *) calloc(allocated, sizeof(char));

	char letter = fgetc(stream);
	while (!feof(stream) && strchr(terminator, letter) == NULL) {
		buff[pos] = letter; pos++;

		if (pos == allocated) {
			buff = realloc(buff, allocated, allocated * 2);
			allocated *= 2;
		}
		letter = fgetc(stream);
	}

	return buff;

}




char * realloc(char * arr, const size_t arr_size, const size_t resize)
{
	char *re_arr = (char *) calloc(resize, sizeof(char));
	for (char *re_i = re_arr, *i = arr; i != arr + arr_size; i++, re_i++) *re_i = *i;
	free(arr);
	return re_arr;
}
