#include "FileSplit.h"

int atoi(char* str) {
	int result = 0;
	for (int i = 0; i < strlen(str); i++) {
		result = result * 10 + str[i] - '0';
	}
	return result;
}

int isNumber(char* str) {
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] < '0' || str[i] > '9') {
			return 0;
		}
	}
	return 1;
}