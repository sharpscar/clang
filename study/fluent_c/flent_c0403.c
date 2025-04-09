#include <stdio.h>
#define STRING_SIZE 100
#define MAX_KEYS 40

/* handle for registry keys*/
typedef struct Key* RegKey;

/*Create a new registry key identified via the provided 'key_name' */
RegKey createKey(char* key_name);

/*store the provided 'value' to the provided 'key'*/
void storeValue(Regkey key, char* value);

/*Make the key available for  being read 
(by other functions that are not part of this code example)*/
void publishKey(RegKey key);

struct Key
{
    char key_name[STRING_SIZE];
    char key_value[STRING_SIZE];
};

static struct Key* key_list[MAX_KEYS];

RegKey createKey(char* key_name)
{
    RegKey newKey = calloc(1, sizeof(struct Key));
    strcpy(newKey->key_name, key_name);
    return newKey;
}

void storeValue(RegKey key, char* value)
{
    strcpy(key->key_value, value);
}

void publishKey(RegKey key)
{
    int i;
    for(i=0; i<MAX_KEYS; i++)
    {
        if(key_list[i]==NULL)
        {
            key_list[i]=key;
            return;
        }
    }
}

int main()
{

    return 0;
}