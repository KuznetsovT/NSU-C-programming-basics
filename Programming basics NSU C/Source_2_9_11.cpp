//
//
////Обработка введенного текста
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//struct {
//	const static unsigned BUFF_SIZE = 128;      //по условию данные хранятся в статическом массиве
//	char data[BUFF_SIZE];
//
//} Buffer;   //это будет структура, храняшая считанные данные.
//
//void сlear_buffer();//before reading
//
////...................Corrections..................
////функции коррекции.
//
////функция заменяет все буквы в начале предложения на заглавные заглавные буквы
//void cappital_letter(char * data);
//
////функция удаляет лишние пробелы
//void extra_spaces( char * data);
//
////удаление пробелов перед точкой с запятой
//void semicolor_spaces( char * data);
//
////звращает строку с добавленными пробелами после знаков препинания
//char *add_spaces();
//
////................................................
//
//
//
//
//
//
//int main() {
//	сlear_buffer();
//	fgets(Buffer.data, Buffer.BUFF_SIZE, stdin);
//
//	char * str = add_spaces();
//	cappital_letter(str);
//	extra_spaces(str);
//	semicolor_spaces(str);
//
//	printf("\n%s\n", str);
//	free(str);
//	return 0;
//}
//
//
//
//void сlear_buffer()//before reading
//{
//	for (char *i = Buffer.data; i != Buffer.data + Buffer.BUFF_SIZE; i++) *i = 0;
//}
//
////функция заменяет все буквы в начале предложения на заглавные заглавные буквы
//void cappital_letter(char *data)
//{
//	//B = b + 'A'-'a'
//	bool sentence_closed = true;
//	//первый символ рассмотрим отдельно
//
//	//букву надо заменять если это действительно буква, и если это не заглавная буква, то есть в диапазоне ['a','z']
//	if (*data >= 'a' && *data <= 'z') {
//		*data = *data + 'A' - 'a';
//		sentence_closed = false;
//	}
//
//	//далее рассматриваем остальные символы
//	for (char *i = data+1; i != data + strlen(data); i++) {
//
//		if (sentence_closed && *i >= 'a' && *i <= 'z') {
//			*i =  *i+ 'A' - 'a'; 
//			sentence_closed = false;
//		}
//
//		//назначаем список разделителей
//		if (*i == '.' || *i == '!' || *i == '?' || *i == ';') sentence_closed = true;
//	}
//}
//
//
////функция удаляет лишние пробелы
//void extra_spaces(char * data)
//{
//	char *pos = strpbrk(data, " \t");        //находим первый пробельный символ
//	while (pos != NULL) {
//		char *end = pos;
//		for (; *end == ' ' || *end == '\t'; end++); //находим первый непробельный символ
//
//		strcpy(pos + 1, end);                       //выкидываем лишние пробелы
//		pos = strpbrk(end, " \t");                  //ищем следующий пробел в необследованной области
//	}
//}
//
//
////удаление пробелов перед точкой с запятой
////процесс аналогичен удалению лишних пробелов
//void semicolor_spaces(char * data)
//{
//	char *pos = strchr(data, ';');
//	while (pos != NULL) {
//		char *end = pos - 1;
//		for (; (*end == ' ' || *end == '\t') && end >= data; end--);
//
//		strcpy(end + 1, pos);
//		pos = strchr(end+2, ';');
//	}
//}
//
//
//
////Обязательно высвободить выделенную динамическую память!
//char * add_spaces()
//{
//	char *result = (char *)calloc(2 * Buffer.BUFF_SIZE, sizeof(char));
//	strcpy(result, Buffer.data);
//	char *pos_r = strpbrk(result, ",;:.!?");
//	char *pos_d = strpbrk(Buffer.data, ",;:.!?");
//
//	while (pos_d != NULL && pos_r != NULL) {
//
//		if (*(pos_r + 1) != ' ' || *(pos_r + 1) != '\t') {
//			*(pos_r + 1) = ' ';
//			strcpy(pos_r + 2, pos_d + 1);
//		}
//
//		pos_r = strpbrk(pos_r+1, ",;:.!?");
//		pos_d = strpbrk(pos_d+1, ",;:.!?");
//
//	}
//	return result;
//}
//
//
//
