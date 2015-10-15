#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int MAX_INT_LIMIT = 2147483647;
int ASCII_INT_OFFSET = 48;
int ASCII_CHAR_LOWER_OFFSET = 87;
int ASCII_CHAR_UPPER_OFFSET = 65;


// 
int getCurrentExponent (int n, int exponent) {
	int originalNumber = n;
	while (exponent > 1) {
		n *= originalNumber;
		exponent--;
	}
	return n;
}


// 
bool checkOctalConstantValidity (char lexeme[]) {
	int lexLength = strlen(lexeme);
	int origLength = lexLength;
	lexLength -= 2;
	// printf("\n***lexLength: %d", lexLength);
	// printf("\n");

	if (lexeme[origLength-1] == ('b' | 'B')) {

		int i = 0;
		int temp = 0;
		int octalToInteger = 0;

		while (i < origLength-1) {
			if (((int) lexeme[i] - ASCII_INT_OFFSET) <= 7) {
				// printf("\n***(int) lexeme[i] - ASCII_INT_OFFSET: %d", (int) lexeme[i] - ASCII_INT_OFFSET);
				// printf("\n");
				// printf("\n***lexLength: %d", lexLength);
				// printf("\n");
				temp = getCurrentExponent(8, lexLength);

				if (lexLength > 0) {
					temp *= (((int) lexeme[i]) - ASCII_INT_OFFSET);
					// printf("\n***IMPORTANT TEMP: %d", temp);
					// printf("\n");
				} else {
					temp = (((int) lexeme[i]) - ASCII_INT_OFFSET);
				}

				// printf("\n***TEMP: %d", temp);
				// printf("\n");
				octalToInteger += temp;
				temp = 0;
				lexLength--;
				i++;
			} else {
				printf("\n***** INVALID *****");
				printf("\n");
				return false;
			}
		}

		printf("\n**********Converted Integer: %d", octalToInteger);
		printf("\n");
		printf("\n");

		if (octalToInteger >= MAX_INT_LIMIT) {
			return false;
		} else {
			return true;
		}
	}
	return false;
}





// 
bool checkHexadecimalConstantValidity (char lexeme[]) {
	int lexLength = strlen(lexeme);
	int origLength = lexLength;
	lexLength -= 2;

	if (lexeme[origLength-1] == ('h' | 'H')) {

		int i = 0;
		int temp = 0;
		int hexToInteger = 0;

		while (i < origLength-1) {
			if ((int) lexeme[i] - ASCII_INT_OFFSET >= 0 &&
					(int) lexeme[i] - ASCII_INT_OFFSET <= 9) {

				temp = getCurrentExponent(16, lexLength);

				if (lexLength > 0) {
					temp *= (((int) lexeme[i]) - ASCII_INT_OFFSET);
					// printf("\n***IMPORTANT TEMP: %d", temp);
					// printf("\n");
				} else {
					temp = (((int) lexeme[i]) - ASCII_INT_OFFSET);
				}

				// printf("\n***TEMP: %d", temp);
				// printf("\n");
				hexToInteger += temp;
				temp = 0;
				lexLength--;
				i++;

			}
			else if ((int) lexeme[i] - ASCII_CHAR_LOWER_OFFSET >= 10 &&
					(int) lexeme[i] - ASCII_CHAR_LOWER_OFFSET <= 15) {
					// (((int) lexeme[i] - ASCII_CHAR_UPPER_OFFSET >= 10 &&
					// (int) lexeme[i] - ASCII_CHAR_UPPER_OFFSET <= 15)) {

				temp = getCurrentExponent(16, lexLength);

				if (lexLength > 0) {
					temp *= (((int) lexeme[i]) - ASCII_CHAR_LOWER_OFFSET);
					// printf("\n***IMPORTANT TEMP: %d", temp);
					// printf("\n");
				} else {
					temp = (((int) lexeme[i]) - ASCII_CHAR_LOWER_OFFSET);
				}

				// printf("\n***TEMP: %d", temp);
				// printf("\n");
				hexToInteger += temp;
				temp = 0;
				lexLength--;
				i++;

			} else {
				printf("\n***** INVALID *****");
				printf("\n");
				return false;
			}
		}

		printf("\n**********Converted Integer: %d", hexToInteger);
		printf("\n");
		printf("\n");

		if (hexToInteger >= MAX_INT_LIMIT) {
			return false;
		} else {
			return true;
		}
	}
	return false;
}




int main() {
	char lex1[] = "4096";					//is a lexeme
	char lex2[] = "4321056b";			//is a lexeme
	char lex3[] = "4321056h";			//is a lexeme
	char lex4[] = "123456789h";		//is NOT a lexeme
	char lex5[] = "4321086b";			//is NOT a lexeme

	bool test = checkOctalConstantValidity(lex2);
	printf("%s", test ? "true" : "false");
	printf("\n");
	printf("\n");

	bool test2 = checkOctalConstantValidity(lex5);
	printf("%s", test2 ? "true" : "false");
	printf("\n");
	printf("\n");

	bool test3 = checkHexadecimalConstantValidity(lex3);
	printf("%s", test3 ? "true" : "false");
	printf("\n");
	printf("\n");


	return 0;
}

