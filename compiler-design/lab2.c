#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//global variables for maximum permitted 32 bit values
int MAX_INT_LIMIT = 2147483647;			//maximum permitted 32 bit decimal value
int ASCII_INT_OFFSET = 48;					//used to convert from ASCII int to decimal int
int ASCII_CHAR_LOWER_OFFSET = 87;		//used to convert from ASCII lowercase letter to decimal int
int ASCII_CHAR_UPPER_OFFSET = 55;		//used to convert from ASCII uppercase letter to decimal int


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

	if (lexeme[origLength-1] == 'b' || lexeme[origLength-1] == 'B') {

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
					if (temp != 0) {
						temp *= (((int) lexeme[i]) - ASCII_INT_OFFSET);
						// printf("\n***IMPORTANT TEMP: %d", temp);
						// printf("\n");
					} else {
						printf("\n***TEMP is zero due to overflow: %d", temp);
						printf("\n");
						return false;
					}
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
				printf("\n***** INVALID (1) OCT *****");
				printf("\n");
				return false;
			}
		}

		printf("\n**********Converted Integer: %d", octalToInteger);
		//printf("\n");
		printf("\n");

		if (octalToInteger > MAX_INT_LIMIT) {
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

	if (lexeme[origLength-1] == 'h' || lexeme[origLength-1] == 'H') {

		int i = 0;
		int temp = 0;
		int hexToInteger = 0;

		while (i < origLength-1) {

			if ((int) lexeme[i] - ASCII_INT_OFFSET >= 0 &&
					(int) lexeme[i] - ASCII_INT_OFFSET <= 9) {

				temp = getCurrentExponent(16, lexLength);

				if (lexLength > 0) {
					if (temp != 0) {
						temp *= (((int) lexeme[i]) - ASCII_INT_OFFSET);
						// printf("\n***IMPORTANT TEMP: %d", temp);
						// printf("\n");
					} else {
						printf("\n***TEMP is zero due to overflow: %d", temp);
						printf("\n");
						return false;
					}
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
				// printf("\n***EXPONENTIAL TEMP: %d", temp);
				// printf("\n");

				if (lexLength > 0) {
					if (temp != 0) {
						temp *= (((int) lexeme[i]) - ASCII_CHAR_LOWER_OFFSET);
						// printf("\n***IMPORTANT TEMP: %d", temp);
						// printf("\n");
					} else {
						printf("\n***TEMP is zero due to overflow: %d", temp);
						printf("\n");
						return false;
					}
				} else {
					temp = (((int) lexeme[i]) - ASCII_CHAR_LOWER_OFFSET);
				}

				// printf("\n***TEMP: %d", temp);
				// printf("\n");
				hexToInteger += temp;
				temp = 0;
				lexLength--;
				i++;

			}
			else if ((int) lexeme[i] - ASCII_CHAR_UPPER_OFFSET >= 10 &&
					(int) lexeme[i] - ASCII_CHAR_UPPER_OFFSET <= 15) {

				temp = getCurrentExponent(16, lexLength);
				// printf("\n***EXPONENTIAL TEMP: %d", temp);
				// printf("\n");

				if (lexLength > 0) {
					if (temp != 0) {
						temp *= (((int) lexeme[i]) - ASCII_CHAR_UPPER_OFFSET);
						// printf("\n***IMPORTANT TEMP: %d", temp);
						// printf("\n");
					} else {
						printf("\n***TEMP is zero due to overflow: %d", temp);
						printf("\n");
						return false;
					}
				} else {
					temp = (((int) lexeme[i]) - ASCII_CHAR_UPPER_OFFSET);
				}

				// printf("\n***TEMP: %d", temp);
				// printf("\n");
				hexToInteger += temp;
				temp = 0;
				lexLength--;
				i++;

			} else {
				printf("\n***** INVALID (2) HEX *****");
				printf("\n");
				return false;
			}
		}

		printf("\n**********Converted Integer: %d", hexToInteger);
		//printf("\n");
		printf("\n");

		if (hexToInteger > MAX_INT_LIMIT) {
			printf("\n### Me (1) ###");
			printf("\n");
			return false;
		} else {
			return true;
		}
	}
	printf("\n### Me (2) ###");
	printf("\n");
	return false;
}




int main() {

	char userInput[20];
	printf("Type your lexeme: ");
	scanf("%s", userInput);

	char lex1[] = "4096";					//is a lexeme
	char lex2[] = "4321056b";			//is a lexeme
	char lex3[] = "4321056h";			//is a lexeme
	char lex4[] = "123456789h";		//is NOT a lexeme
	char lex5[] = "4321086b";			//is NOT a lexeme
	char lex6[] = "7ff329h";			//is a lexeme
	char lex7[] = "324FA2Bh";			//is a lexeme

	// bool test = checkOctalConstantValidity(lex2);
	// printf("%s", test ? "true" : "false");
	// printf("\n");
	// printf("\n");

	// bool test2 = checkOctalConstantValidity(lex5);
	// printf("%s", test2 ? "true" : "false");
	// printf("\n");
	// printf("\n");

	// bool test3 = checkHexadecimalConstantValidity(lex3);
	// printf("%s", test3 ? "true" : "false");
	// printf("\n");
	// printf("\n");

	// bool test4 = checkHexadecimalConstantValidity(lex4);
	// printf("%s", test4 ? "true" : "false");
	// printf("\n");
	// printf("\n");

	// bool test5 = checkHexadecimalConstantValidity(lex6);
	// printf("%s", test5 ? "true" : "false");
	// printf("\n");
	// printf("\n");

	// bool test6 = checkHexadecimalConstantValidity(lex7);
	// printf("%s", test6 ? "true" : "false");
	// printf("\n");
	// printf("\n");

	if (checkHexadecimalConstantValidity(userInput) == true) {
		bool testUserInput = checkHexadecimalConstantValidity(userInput);
		printf("%s", testUserInput ? "true" : "false");
		printf("\n");
		printf("\n");
	} else {
		bool testUserInput = checkOctalConstantValidity(userInput);
		printf("%s", testUserInput ? "true" : "false");
		printf("\n");
		printf("\n");
	}


	return 0;
}

