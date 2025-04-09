#include <stdio.h>
/* error codes returned by this registry */
typedef enum
{
    OK,
    OUT_OF_MEMORY,
    INVALID_KEY,
    INVALID_STRING,
    STRING_TOO_LONG,
    CANNOT_ADD_KEY
}RegError;

/* Handle for registry keys */
typedef struct Key* RegKey;

/* Create a new registry key identified via the provided 'key_name' 
Returns OK if no problem occurs, 
INVALID_KEY if the 'key' parameter is NULL
INVLID_STRING if 'key_name' is NULL
STRING_TOO_LONG if key_name  is too long
OUT_OF_MEMORY if no memory resources are available

*/
RegError createKey(char* key_name, RegKey* key);


/** Stroe the provided 'value' to the provided 'key'. 
 * Returns OK if no problem occurs, 
 * INVALID_KEY if the key parameter is null,
 * INVALID_STRING if value is NULL or 
 * STRING_TOO_LONG if value is too long
*/
RegError storeValue(RegKey key, char* value);

// if the registry is full and no more keys can be published
RegError publishKey(RegKey key);
int main()
{

}