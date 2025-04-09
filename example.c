#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
#define MAX_LINE_LENGTH 256 
#define MAX_RECORDS 100 
 
// Define a struct to hold the data 
typedef struct { 
    int id; 
    char name[50]; 
    float score; 
} Record; 
 
// Function to read CSV file and populate an array of structs 
int read_csv(const char *filename, Record records[], int max_records) { 
    FILE *file = fopen(filename, "r"); 
    if (!file) { 
        perror("Could not open file"); 
        return -1; // Error opening file 
    } 
 
    char line[MAX_LINE_LENGTH]; 
    int count = 0; 
 
    // Read each line from the CSV file 
    while (fgets(line, sizeof(line), file) && count < max_records) { 
        // Tokenize the line to extract the data 
        char *token = strtok(line, ","); 
        if (token) { 
            records[count].id = atoi(token); // Convert string to int 
        } 
 
        token = strtok(NULL, ","); 
        if (token) { 
            strncpy(records[count].name, token, sizeof(records[count].name)); 
            records[count].name[strcspn(records[count].name, "\n")] = 0; // Remove newline 
        } 
 
        token = strtok(NULL, ","); 
        if (token) { 
            records[count].score = atof(token); // Convert string to float 
        } 
 
        count++; 
    } 
 
    fclose(file); 
    return count; // Return the number of records read 
} 
 
// Main function to demonstrate reading from a CSV 
int main() { 
    Record records[MAX_RECORDS]; 
    int num_records = read_csv("data.csv", records, MAX_RECORDS); 
 
    if (num_records < 0) { 
        return 1; // Error reading file 
    } 
 
    // Print the records read from the CSV 
    for (int i = 0; i < num_records; i++) { 
        printf("ID: %d, Name: %s, Score: %.2f\n", records[i].id, records[i].name, records[i].score); 
    } 
 
    return 0; 
} 