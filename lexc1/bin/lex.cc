#include <vector>
#include <cctype>
#include <iostream>
#include <string>
#include <cstdlib>

typedef enum TokenType
{
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_ID
} TokenType;

class Token
{
protected:
    TokenType id;
    std::string value;
public:
    Token(TokenType id, std::string value);
    TokenType getType();
    std::string getValue();
};

Token::Token(TokenType id, std::string value)
{
    this->id = id;
    this->value = value;
}

TokenType Token::getType()
{
    return this->id;
}

std::string Token::getValue()
{
    return this->value;
}

class Lexer
{
protected:
    std::vector<Token> tokens;
    std::string input;
public:
    Lexer(std::string input);
    void lex();
    void run();
    void printTokens();
    void printTokenType(TokenType tokenType);
};

Lexer::Lexer(std::string input) {
    this->tokens = std::vector<Token>();
    this->input = input;
}

void Lexer::printTokenType(TokenType tokenType)
{
    if (tokenType == TOKEN_PLUS)
    {
        std::cout << "PLUS";
    } else if (tokenType == TOKEN_NUMBER)
    {
        std::cout << "NUMBER";
    } else if (tokenType == TOKEN_ID)
    {
        std::cout << "ID";
    }
}

void Lexer::printTokens()
{
    for (auto token : this->tokens)
    {
        this->printTokenType(token.getType());
        std::cout << ", ";
        if (token.getValue() == "") {
            std::cout << "NONE" << std::endl;
        } else {
            std::cout << token.getValue() << std::endl;
        }
    }
}

void Lexer::lex()
{
    int begin = 0;
    int forward;
    std::string buf;
    for (begin = 0; begin < this->input.length(); begin)
    {
        char c = this->input[begin];
        if (c == '+') {
            Token t(
                TOKEN_PLUS,
                ""
            );
            this->tokens.push_back(t);
            begin++;
        } else if (isdigit(c)) {
            buf.append(std::string(1,c));
            int n = 1;
            forward = begin + n;
            for (forward; forward < this->input.length(); forward)
            {
                char thenext = this->input[forward];
                if (isdigit(thenext)) {
                    buf.append(std::string(1, thenext));
                    n++;
                    forward = begin+n;
                } else {
                    break;
                }
            }
            Token t(TOKEN_NUMBER, buf);
            this->tokens.push_back(t);
            buf = "";
            begin = begin + n;
        } else if (isalpha(c)) {
            buf.append(std::string(1,c));
            int n = 1;
            forward = begin + n;
            for (forward; forward < this->input.length(); forward)
            {
                char nex = this->input[forward];
                if (isalnum(nex)) {
                    buf.append(std::string(1, nex)); 
                    n++;
                    forward = begin+n;
                } else {
                    break;
                }
            }
            Token t(TOKEN_ID, buf);
            this->tokens.push_back(t);
            buf = "";
            begin = begin + n;
        } else if (isspace(c)) {
            begin++;
        } else {
            std::cout << "unknown token" << std::endl;
            exit(1);
        }
    }
}

void Lexer::run()
{
    this->lex();
    std::cout << "INPUT:" << std::endl;
    std::cout << this->input << std::endl;
    std::cout << "OUTPUT:" << std::endl;
    this->printTokens();
}

int main()
{
    std::string input = "demo + 2121 + 212 + abc123 + 4";
    Lexer lexer(input);
    lexer.run();
    return 0;
}
