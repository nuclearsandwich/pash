//a collection of functions to resolve path variables
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // angle brackets signify library code
#include "../include/path_lookup.h" // quotes signify you	r local code
#include <sys/types.h>
#include <stdio.h>

const char* delimToken = ":";

//http://stackoverflow.com/questions/612097/how-can-i-get-a-list-of-files-in-a-directory-using-c-or-c
char* searchPath(char* inputPath, char* inputExecutableName)
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir (inputPath);
	if (dir != NULL) 
	{
	  while ((ent = readdir (dir)) != NULL)
	  {
		if (strlen(ent->d_name) == strlen(inputPath) && !strcmp(ent->d_name, inputExecutableName))  // if the length of the current file and the name are the same
        {
        	(void)closedir(dir); // close the file handle
            return ent->d_name; // return the current file name
        }
	  }
	  closedir(dir);
	} 
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