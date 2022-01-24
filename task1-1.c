#include <stdlib.h>
#include <stdio.h>

int main() {

    printf("User_ID = %d\n", getuid());
    printf("Group_ID = %d\n", getgid());

    return 0;
}