//
//
////��������� ���������� ������
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//struct {
//	const static unsigned BUFF_SIZE = 128;      //�� ������� ������ �������� � ����������� �������
//	char data[BUFF_SIZE];
//
//} Buffer;   //��� ����� ���������, �������� ��������� ������.
//
//void �lear_buffer();//before reading
//
////...................Corrections..................
////������� ���������.
//
////������� �������� ��� ����� � ������ ����������� �� ��������� ��������� �����
//void cappital_letter(char * data);
//
////������� ������� ������ �������
//void extra_spaces( char * data);
//
////�������� �������� ����� ������ � �������
//void semicolor_spaces( char * data);
//
////�������� ������ � ������������ ��������� ����� ������ ����������
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
//	�lear_buffer();
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
//void �lear_buffer()//before reading
//{
//	for (char *i = Buffer.data; i != Buffer.data + Buffer.BUFF_SIZE; i++) *i = 0;
//}
//
////������� �������� ��� ����� � ������ ����������� �� ��������� ��������� �����
//void cappital_letter(char *data)
//{
//	//B = b + 'A'-'a'
//	bool sentence_closed = true;
//	//������ ������ ���������� ��������
//
//	//����� ���� �������� ���� ��� ������������� �����, � ���� ��� �� ��������� �����, �� ���� � ��������� ['a','z']
//	if (*data >= 'a' && *data <= 'z') {
//		*data = *data + 'A' - 'a';
//		sentence_closed = false;
//	}
//
//	//����� ������������� ��������� �������
//	for (char *i = data+1; i != data + strlen(data); i++) {
//
//		if (sentence_closed && *i >= 'a' && *i <= 'z') {
//			*i =  *i+ 'A' - 'a'; 
//			sentence_closed = false;
//		}
//
//		//��������� ������ ������������
//		if (*i == '.' || *i == '!' || *i == '?' || *i == ';') sentence_closed = true;
//	}
//}
//
//
////������� ������� ������ �������
//void extra_spaces(char * data)
//{
//	char *pos = strpbrk(data, " \t");        //������� ������ ���������� ������
//	while (pos != NULL) {
//		char *end = pos;
//		for (; *end == ' ' || *end == '\t'; end++); //������� ������ ������������ ������
//
//		strcpy(pos + 1, end);                       //���������� ������ �������
//		pos = strpbrk(end, " \t");                  //���� ��������� ������ � ��������������� �������
//	}
//}
//
//
////�������� �������� ����� ������ � �������
////������� ���������� �������� ������ ��������
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
////����������� ����������� ���������� ������������ ������!
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
