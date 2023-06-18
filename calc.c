#include <stdio.h>

int main() {
    int a = 10;
	
    /* for loop execution */
    for(a = 10; a > 0; a--){
        char op;
        double first, second;
        printf("Enter an operator (+, -, *, /): \n");
        scanf("\n %c", &op); // Note the space before %c to consume the newline character
        printf("Enter two operands: \n");
        scanf("\n%lf %lf", &first, &second , "\n");

        switch (op) {
            case '+':
                printf("\n%.1lf + %.1lf = %.1lf\n", first, second, first + second , "\n");
                break;
            case '-':
                printf("\n%.1lf - %.1lf = %.1lf\n", first, second, first - second , "\n");
                break;
            case '*':
                printf("\n%.1lf * %.1lf = %.1lf\n", first, second, first * second , "\n");
                break;
            case '/':
                printf("\n%.1lf / %.1lf = %.1lf\n", first, second, first / second , "\n");
                break;
            // operator doesn't match any case constant
            default:
                printf("Error! operator is not correct\n");
        }
    }

    return 0;
}

