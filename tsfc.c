#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void createScriptRunnable(char *pathScript);
int stringFoundInRC(char *rcPath, char *tsCommando);
void writeOnRC(const char *homeDir, char *scriptPath, char *rc); 

int main(void){ 
	const char *homeDirectory = getenv("HOME");
	const char *fileName = "/Public/tsfc.sh";
	char *scriptPath = (char *)malloc(strlen(homeDirectory) + strlen(fileName) + 1);
	strcpy(scriptPath, homeDirectory);
	strcat(scriptPath, fileName); 
	createScriptRunnable(scriptPath);
	writeOnRC(homeDirectory, scriptPath, "/.bashrc");
	printf("------------------------------\n");
	writeOnRC(homeDirectory, scriptPath, "/.zshrc");
	return(0);
}

void createScriptRunnable(char *pathScript) {
	FILE *file;
	// Open the file for writing
    file = fopen(pathScript, "w");
    if (file == NULL) {
        perror("Error opening file");
    }else {
		printf("file opened correctly\n");
	}

	//make the file that we created executable TO-DO change file path
	char *comandPT1 = "chmod +x ";
	char *fullCommand = (char *)malloc(strlen(comandPT1) + strlen(pathScript) + 1);
	strcpy(fullCommand, comandPT1);
	strcat(fullCommand, pathScript);
	int result = system(fullCommand);
    if (result != 0) {
        perror("Error changing file permissions");
    } else {
		printf("file is now executable");
	}
	fprintf(file, "CURR_FILE=$PWD/$1\nNEW_FILE=${CURR_FILE::-3}\ntsc $CURR_FILE\nnode $NEW_FILE\nrm -f ${NEW_FILE}.js\n");
    // Close the file
    fclose(file);
}

//for this function i got the code from https://www.codingunit.com/c-tutorial-searching-for-strings-in-a-text-file
int Search_in_File(char *fname, char *str) {
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	
	if((fp = fopen(fname, "r")) == NULL) {
		printf("file not found\n");
		return(-1);
	}

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			printf("A match found on line: %d\n", line_num);
			printf("\n%s\n", temp);
			find_result++;
			return 1;
		}
		line_num++;
	}
	if(find_result == 0) {
		printf("\nOk, no match found.\n");
		return 0;
	}

	//Close the file if still open.
	if(fp) {
		fclose(fp);
	}
   	return 0;
}

void writeOnRC(const char *homeDir, char *scriptPath, char *rc) {
	char *rc_path = (char *)malloc(strlen(homeDir) + strlen(rc));
	strcpy(rc_path, homeDir);
	strcat(rc_path, rc);
	char tsCommand[30];
	sprintf(tsCommand, "alias tsfc='%s'", scriptPath);
	int commandFound = Search_in_File(rc_path, tsCommand); 
	sprintf(tsCommand, "\nalias tsfc='%s'", scriptPath);
	if (commandFound == 1) {
		printf("%s already ready!\n", rc);
	} else if(commandFound == 0) {
		printf("\n%s\n", rc_path);
		system("cd ~");
		FILE *shrc = fopen(rc_path, "a");
		if (shrc == NULL) {
			char notFoundRC[30];
			sprintf(notFoundRC, "\n %s not found", rc);
			perror(notFoundRC);
		}else {
			// Write the new command to .shrc
			if (fputs(tsCommand, shrc) == EOF) {
				perror("Error writing to .shrc");
				fclose(shrc);
			}
			printf("%s is now ok\n", rc);
			fclose(shrc);
		}

	char *rcUpdateCommand = (char *)malloc(strlen("source ") + strlen(rc_path) + 1);
	strcpy(rcUpdateCommand, "source ");
	strcat(rcUpdateCommand, rc_path);
	int result = system(rcUpdateCommand);
	if (result) {
		perror("one day i'll fix this error");
	}
	free(rc_path);
	free(rcUpdateCommand);
	} 
}