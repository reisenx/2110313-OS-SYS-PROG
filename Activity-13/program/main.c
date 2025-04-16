#include <stdio.h>
#include <stdlib.h>

int main() {
    // Get Environment variables
    char* user = getenv("secret_user");
    // Output
    if (user) { printf("Hello, %s\n", user); }
    else { printf("Hello, Tendou Arisu\n"); }
    return 0;
}