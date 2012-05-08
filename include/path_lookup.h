/* Functions for returning the absolute path of a file based on
 * PATH and DATA variables.
 */
char* resolve_data(char* inputFileName);
char* resolve_path(char* inputFileName);
char* searchVariable(char* inputVariable, char* inputExecutableName);
char* searchPath(char* inputPath, char* inputExecutableName);
