//a collection of functions to resolve path variables
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // angle brackets signify library code
// #include "path_lookup.h" // quotes signify your local code
#include <sys/types.h>
#include <stdio.h>

const char* delimToken = ":";
char* qualifiedPath;

//http://stackoverflow.com/questions/612097/how-can-i-get-a-list-of-files-in-a-directory-using-c-or-c
char* searchPath(char* inputPath, char* inputExecutableName)
{
	DIR *directory = opendir(inputPath);
	struct dirent *entry = NULL;
	if (directory == NULL) // if path was invalid
		return NULL; 
	  while((entry = readdir(directory))) /* print all the files and directories within directory */
	  {
		if (strcmp(entry->d_name, inputExecutableName) == 0)  // if the strings are equal
        {
        	closedir(directory); // close the file handle
            qualifiedPath = (char*) malloc(strlen(inputPath) + strlen(inputExecutableName)); // leave one extra space for the /
						strcpy(qualifiedPath, inputPath);
            strcat(qualifiedPath, "/");
            strcat(qualifiedPath, inputExecutableName);
            return qualifiedPath; // return the fully qualified path to the program
        }
	  }
	  closedir(directory);
	return NULL;
}	

char* searchVariable(char* inputVariable, char* inputExecutableName)
{
	//go through the variable path, tokenize, search for inputExecutableName in each path. return the fully qualified path. if not exist, return null
	char* currentPath = strtok(inputVariable, delimToken);
	if(currentPath == NULL) // if we were passed the empty string
		return NULL;

	while(currentPath != NULL) // if the first item returned isn't null, we need to search it
	{
		char* filePath = searchPath(currentPath, inputExecutableName); // search the first item (which should be a path)
		if(filePath != NULL) // if we aren't NULL, then the search was successful
			return filePath; // return the successful search
		currentPath = strtok(NULL, delimToken); // if the search was unsuccessful, get the next path to search
	}
	return NULL;
}

// tests whether or not a file is on the data path.  
char* resolve_data(char* inputExecutableName)
{
	return searchVariable(getenv("DATA"), inputExecutableName); // the dollar sign is a shell sigil
}

char* resolve_path(char* inputExecutableName)
{
	return searchVariable(getenv("PATH"), inputExecutableName);
}
