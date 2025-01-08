#include <stdio.h>
#include <stdlib.h>

// Function to read the contents of the file
char *readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    // Move to the end of the file to determine the file size
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content
    char *content = malloc(length + 1);
    if (!content) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    fread(content, 1, length, file);
    content[length] = '\0';  // Null-terminate the string

    fclose(file);
    return content;
}

int main() {
    const char *filename = "interpreter.js";
    char *code = readFile(filename);
    if (!code) {
        return 1;
    }

    // Create a temporary file to store the code
    FILE *tempFile = tmpfile();
    if (!tempFile) {
        perror("Failed to create temporary file");
        free(code);
        return 1;
    }

    // Write the code to the temporary file
    fprintf(tempFile, "%s", code);
    free(code);

    // Rewind the temporary file to the beginning
    fseek(tempFile, 0, SEEK_SET);

    // Create a pipe to communicate with the JavaScript interpreter
    FILE *pipe = popen("node interpreter.js", "w");
    if (!pipe) {
        perror("Failed to open pipe");
        fclose(tempFile);
        return 1;
    }

    // Write the code from the temporary file to the interpreter
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), tempFile)) > 0) {
        fwrite(buffer, 1, bytesRead, pipe);
    }

    // Close the temporary file and the pipe
    fclose(tempFile);
    pclose(pipe);

    return 0;
}
