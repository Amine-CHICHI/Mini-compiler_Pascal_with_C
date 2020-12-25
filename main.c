#include "Lexer.c"
#include <stdio.h>
// <> sawbha rh ghalta blast !=
const char *fileName = "program.pascal";
const char *lexer_fileName = "lexer_output.txt";

int main()
{

    program = fopen(fileName, "r");
    tokens_out_file = fopen(lexer_fileName, "w");
    if (program == NULL)
    {
        perror("Error while opening the pascal file");
        exit(1);
    }
    if (tokens_out_file == NULL)
    {
        perror("Error while opening the output tokens file");
        exit(1);
    }
    NextChar();
    do
    {
        getToken();
        printf("hahue prev : %s_Token ----> New token : %s\n", prevToken.value, currentToken.value);
        // printf("%s_TOKEN -----> %s ---> %d\n", currentToken.name, currentToken.value, currentToken.code);
        // fprintf(tokens_out_file, "%s_TOKEN -----> %s\n", currentToken.name, currentToken.value);
    } while (!feof(program));

    return 1;
}