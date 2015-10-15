#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


//global variables for maximum permitted 32 bit values
int MAX_DECIMAL_LIMIT = 2147483647;				//maximum permitted 32 bit decimal value
int ASCII_INT_OFFSET = 48;								//used to convert from ASCII int to decimal int
int ASCII_CHAR_LOWER_OFFSET = 87;					//used to convert from ASCII lowercase letter to decimal int
int ASCII_CHAR_UPPER_OFFSET = 55;					//used to convert from ASCII uppercase letter to decimal int
int OCTAL_BASE_EXP = 8;										//base exponential for octal constants
int HEX_BASE_EXP = 16;										//base exponential for hexadecimal constants


//function used to calculate the exponential number(n) when dealing with hex and octal values
int getCurrentExponent (int n, int exponent) {			//n = the base (base 8=octal/base 16=hex)
	int originalNumber = n;														//store the original value
	while (exponent > 1) {
		n *= originalNumber;
		exponent--;
	}
	return n;																					//return the exponential number desired
}


//checks if the number is a valid octal number and if it is <= 17777777777b, by converting it to decimal (base 10)
bool checkOctalConstantValidity (char lexeme[]) {
	int lexLength = strlen(lexeme);					//get the length of the string (the parameter)
	int origLength = lexLength;							//set it as another variable to use as a "while" loop limit counter later
	lexLength -= 2;													//string has array length -1. The 'b' | 'B' is also not required -1.
																					//-1 -1 = -2

	if (lexeme[origLength-1] == 'b' || lexeme[origLength-1] == 'B') {			//origianl octal guards specified

		int i = 0;														//the variable used to access each element of the lexeme char array (string)
		int temp = 0;													//the "" used to calculate the exponent for the current lexeme[i] value
		int octalToInteger = 0;								//the "" used to calculate the decimal representation of that octal constant

		while (i < origLength-1) {						//loop until all elemens have been accessed and converted -> decimal
			if (((int) lexeme[i] - ASCII_INT_OFFSET) <= 7) {

				temp = getCurrentExponent(OCTAL_BASE_EXP, lexLength);					//calculate octal multiple, and store in temp

				if (lexLength > 0) {							//ensure that there are elements left to be traversed
					if (temp != 0) {								//guard to ensure that only 32-bit arithmetic operations occur
						temp *= (((int) lexeme[i]) - ASCII_INT_OFFSET);						//multiply temp by the current decimal to
																																			//calculate the final decimal value
					} else {
						printf("\nArithmetic operation has exceeded permissable parameters.");
						printf("\nError, constant contains too many digits. (Overflow has occurred)");
						printf("\n");
						return false;									//guard actiavted as temp = 0
					}
				} else {
					temp = (((int) lexeme[i]) - ASCII_INT_OFFSET);		//final element. Simply return 1, as the base to power 
																														//0 is simply 1.
				}

				octalToInteger += temp;						//increment the decimal converter by the current temp value
				temp = 0;													//reset temp
				lexLength--;											//decrement the length of the array to be traversed
				i++;															//increment i to esure that the while loop can be escaped
			} else {
				printf("\nError, this lexeme is not a valid octal constant");
				printf("\n");
				return false;				//if this loop is entered, it means that the initial requirements for the constant to
														//exist as an octal number have been violated
			}
		}

		printf("\nLexeme: %s", lexeme);
		printf("\nLexical token (Constant, %d", octalToInteger);
		printf(")");
		printf("\n");						//if all above checks and calculations are complete, print the decimal representation
														//of the octal constant, and by doing so, ALMOST confirm its validity

		if (octalToInteger > MAX_DECIMAL_LIMIT) {
			return false;					//octal constant exceeds the maximum decimal limit
		} else {
			return true;					//final confirmation of the octal constant's validity
		}
	}
	return false;							//the string is not an octal constant. Not appended with 'b' | 'B'
}


//checks if the number is a valid hexadecimal number and if it is <= 7FFFFFFFh by converting it to decimal (base 10) 
bool checkHexadecimalConstantValidity (char lexeme[]) {
	int lexLength = strlen(lexeme);
	int origLength = lexLength;
	lexLength -= 2;

	if (lexeme[origLength-1] == 'h' || lexeme[origLength-1] == 'H') {				//origianl hexadecimal guards specified

		int i = 0;
		int temp = 0;
		int hexToInteger = 0;

		while (i < origLength-1) {

			if ((int) lexeme[i] - ASCII_INT_OFFSET >= 0 &&
					(int) lexeme[i] - ASCII_INT_OFFSET <= 9) {		//integer check [0 -> 9]

				temp = getCurrentExponent(HEX_BASE_EXP, lexLength);			//same calculations, with the appropraite parameters

				if (lexLength > 0) {
					if (temp != 0) {
						temp *= (((int) lexeme[i]) - ASCII_INT_OFFSET);
					} else {
						printf("\nArithmetic operation has exceeded permissable parameters.");
						printf("\nError, constant contains too many digits. (Overflow has occurred)");
						printf("\n");
						return false;
					}
				} else {
					temp = (((int) lexeme[i]) - ASCII_INT_OFFSET);
				}

				hexToInteger += temp;
				temp = 0;
				lexLength--;
				i++;

			}
			else if ((int) lexeme[i] - ASCII_CHAR_LOWER_OFFSET >= 10 &&
					(int) lexeme[i] - ASCII_CHAR_LOWER_OFFSET <= 15) {		//character check [a -> f]

				temp = getCurrentExponent(HEX_BASE_EXP, lexLength);

				if (lexLength > 0) {
					if (temp != 0) {
						temp *= (((int) lexeme[i]) - ASCII_CHAR_LOWER_OFFSET);
					} else {
						printf("\nArithmetic operation has exceeded permissable parameters.");
						printf("\nError, constant contains too many digits. (Overflow has occurred)");
						printf("\n");
						return false;
					}
				} else {
					temp = (((int) lexeme[i]) - ASCII_CHAR_LOWER_OFFSET);
				}

				hexToInteger += temp;
				temp = 0;
				lexLength--;
				i++;

			}
			else if ((int) lexeme[i] - ASCII_CHAR_UPPER_OFFSET >= 10 &&
					(int) lexeme[i] - ASCII_CHAR_UPPER_OFFSET <= 15) {		//character check [A -> F]

				temp = getCurrentExponent(HEX_BASE_EXP, lexLength);

				if (lexLength > 0) {
					if (temp != 0) {
						temp *= (((int) lexeme[i]) - ASCII_CHAR_UPPER_OFFSET);
					} else {
						printf("\nArithmetic operation has exceeded permissable parameters.");
						printf("\nError, constant contains too many digits. (Overflow has occurred)");
						printf("\n");
						return false;
					}
				} else {
					temp = (((int) lexeme[i]) - ASCII_CHAR_UPPER_OFFSET);
				}

				hexToInteger += temp;
				temp = 0;
				lexLength--;
				i++;

			} else {
				printf("\nError, this lexeme is not a valid hexadecimal constant");
				printf("\n");
				return false;
			}
		}

		//from here, exact same layout as used for octal -> decimal calculations, but with variable "hexToInteger" used
		printf("\nLexeme: %s", lexeme);
		printf("\nLexical token (Constant, %d", hexToInteger);
		printf(")");
		printf("\n");

		if (hexToInteger > MAX_DECIMAL_LIMIT) {
			return false;
		} else {
			return true;						//return the final converted decimal constant here, provided that all error checks have
															//been completed successfully
		}
	}
	return false;
}


//function used to confirm a valid 32-bit decimal value witin the specified guards
bool checkDecimalConstantValidity (char lexeme[]) {
	int lexLength = strlen(lexeme);
	int i;
	int stringToDecimal = 0;

	for (i=0; i<lexLength; i++) {
		stringToDecimal += ((int) lexeme[i] - ASCII_INT_OFFSET);
		if (i != lexLength-1) {
			stringToDecimal *= 10;
		}
	}

	if (stringToDecimal > MAX_DECIMAL_LIMIT) {
		return false;
	} else {
		printf("\nLexeme: %s", lexeme);
		printf("\nLexical token (Constant, %d", stringToDecimal);
		printf(")");
		printf("\n");
		return true;
	}
}


//user input supported, as well as manual tests to check all possible combinations
int main() {

	char userInput[20];									//define a char array (String) to be assigned as a user input variable	
	printf("Type your lexeme: ");
	scanf("%s", userInput);							//the user's input

	//a few quick manual tests relevant to the commented sections of code below.
	char lex1[] = "4096";								//is a lexeme
	char lex2[] = "4321056b";						//is a lexeme
	char lex3[] = "4321056h";						//is a lexeme
	char lex4[] = "123456789h";					//is NOT a lexeme
	char lex5[] = "4321086b";						//is NOT a lexeme
	char lex6[] = "7ff329h";						//is a lexeme
	char lex7[] = "324FA2Bh";						//is a lexeme

	// bool test = checkOctalConstantValidity(lex2);
	// printf("%s", test ? "true" : "false");
	// printf("\n");

	// bool test2 = checkOctalConstantValidity(lex5);
	// printf("%s", test2 ? "true" : "false");
	// printf("\n");

	// bool test3 = checkHexadecimalConstantValidity(lex3);
	// printf("%s", test3 ? "true" : "false");
	// printf("\n");

	// bool test4 = checkHexadecimalConstantValidity(lex4);
	// printf("%s", test4 ? "true" : "false");
	// printf("\n");

	// bool test5 = checkHexadecimalConstantValidity(lex6);
	// printf("%s", test5 ? "true" : "false");
	// printf("\n");

	// bool test6 = checkHexadecimalConstantValidity(lex7);
	// printf("%s", test6 ? "true" : "false");
	// printf("\n");

	if (checkHexadecimalConstantValidity(userInput)) {
		printf("\n");
	} else if (checkOctalConstantValidity(userInput)) {
		printf("\n");
	} else {
		checkDecimalConstantValidity(userInput);
		printf("\n");
	}

	return 0;
}

