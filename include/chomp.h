/* If the input string ends in a newline character ('\n'), a new string
 * is returned with the contents of the old string up until the final newline.
 * Otherwise the original string is returned unmodified.
 */
#include <string.h>

char *chomp(char *str)
{
	if(str[strlen(str)] == '\n']) // if the last character in the string is a newline character
	{
		char* ptrToNewLine = strrchr(str);
		*ptrToNewLine = '\0'; // replace the last newline with the null terminator character, thus truncating the string
	}
}

char* chomp2(char* inputString) // this chomp actually follows steven's directions
{
	if(inputString[strlen(inputString)] == '\n') // detect the string that ends in a newline
	{
		char[] newString = new char[strlen(str)-1]; // allocate memory for a new string to length-1 of the last string
		for(int x =0; x < strlen(inputString); x++)
			newString[x] = *inputString[x]; // copy the string contents over
		inputString = newString; // assign the pointer to the new value
	}
	return inputString; // return the inputString pointer, modified only if the original string ended in a newline
}