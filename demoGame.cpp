#include <stdio.h>
#include <iostream>

int main() {
    int health = 100;
    std::cout << "Health value is: " << health << std::endl;
    std::cout << "Health variable address: " << &health << std::endl;

    getc(stdin);// block the code from running
    health -= 100;
    if (health <= 0) {
        std:: cout << "You are dead | health: " << health << std::endl;
    }
    else { // health > 0
        std:: cout << "You survived | health: " << health << std::endl;
    }
    getc(stdin);// block the code from running
}