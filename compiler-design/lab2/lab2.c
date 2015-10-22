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
			if ((((int) lexeme[i] - ASCII_INT_OFFSET) <= 7) && (((int) lexeme[i] - ASCII_INT_OFFSET) >= 0)) {

				temp = getCurrentExponent(OCTAL_BASE_EXP, lexLength);					//calculate octal multiple, and store in temp

				if (lexLength > 0) {							//ensure that there are elements left to be traversed
					if (temp != 0) {								//guard to ensure that only 32-bit arithmetic operations occur
						temp *= (((int) lexeme[i]) - ASCII_INT_OFFSET);						//multiply temp by the current decimal to
																																			//calculate the final decimal value
					} else {
						printf("\nArithmetic operation has exceeded permissable parameters.");
						printf("\nError, the converted decimal constant contains too many digits.\n");
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
				printf("\nERROR. This lexeme is not a valid octal constant\n");
				return false;				//if this loop is entered, it means that the initial requirements for the constant to
														//exist as an octal number have been violated
			}
		}

		printf("\nLexeme: %s", lexeme);
		printf("\nLexical token (Constant, %d)\n", octalToInteger);
													//if all above checks and calculations are complete, print the decimal representation
													//of the octal constant, and by doing so, ALMOST confirm its validity
		return true;					//final confirmation of the octal constant's validity

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
						printf("\nError, the converted decimal constant contains too many digits.\n");
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
						printf("\nError, the converted decimal constant contains too many digits.\n");
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
						printf("\nError, the converted decimal constant contains too many digits.\n");
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
				printf("\nERROR. This lexeme is not a valid hexadecimal constant.\n");
				return false;
			}
		}

		//from here, exact same layout as used for octal -> decimal calculations, but with variable "hexToInteger" used
		printf("\nLexeme: %s", lexeme);
		printf("\nLexical token (Constant, %d)\n", hexToInteger);
		return true;						//return the final converted decimal constant here, provided that all error checks have
														//been completed successfully
	}
	return false;
}


//function used to confirm a valid 32-bit decimal value witin the specified guards
bool checkDecimalConstantValidity (char lexeme[]) {
	int lexLength = strlen(lexeme);																//create a temporary character array that will be used to store
																																//a positive representation of 'char lexeme[]' (no '-' prefix),
																																//so that it can be defined within the negative limits
	int i;
	int stringToDecimal = 0;
	char temp[20];

	for (i=0; i<lexLength; i++) {
		if ((int) lexeme[i] != '-') {																//quick check for a negative ('-') at first element of lexeme[]
			if ((int) lexeme[i] - ASCII_INT_OFFSET > 0) {
				stringToDecimal += ((int) lexeme[i] - ASCII_INT_OFFSET);
				if (i != lexLength-1) {
					stringToDecimal *= 10;
				}
			} else {
				return false;
			}
		}
	}

	if (lexeme[0] == '-') {																				//if first element of lexeme[]] is '-' 
		stringToDecimal *= -1;																			//multiply the decimal number by -1
	}

	if (lexeme[0] != '-') {
		if (atoi(lexeme) < 0) {
			printf("\nValue processed is outside the permissable 32-bit range of 2^31 - 1. (Overflow)\n");
			return false;
		} else {
			printf("\nLexeme: %s", lexeme);
			printf("\nLexical token (Constant, %d)\n", stringToDecimal);
			return true;
		}
	} else {
		int j;																											//initialize loop variable j
		for (j=0; j<lexLength-1; j++) {
			temp[j] = lexeme[j+1];
		}

		if (atoi(lexeme) > 0) {
			printf("\nValue processed is outside the permissable 32-bit range of 2^31 - 1. (Overflow)\n");
			return false;
		} else {
			printf("\nLexeme: %s", lexeme);
			printf("\nLexical token (Constant, %d)\n", stringToDecimal);
			return true;
		}
	}
	return false;
}


//user input supported, as well as manual tests to check all possible combinations
int main() {

	char userInput[256];											//define a char array (String) to be assigned as a user input variable	
	printf("Type your lexeme: ");
	fgets(userInput, 256, stdin);							//the user's input
	char * input = strtok(userInput, " \n");

	while (input != NULL) {

		if (strcmp(input, "0") == 0) {
			printf("\nLexeme: %s", input);
			printf("\nLexical token (Constant, %d)\n", 0);
		}

		if (checkHexadecimalConstantValidity(input)) {
			printf("\n");
		} else if (checkOctalConstantValidity(input)) {
			printf("\n");
		} else {
			checkDecimalConstantValidity(input);
			printf("\n");
		}
		input = strtok(NULL, " \n");
	}

	return 0;
}

