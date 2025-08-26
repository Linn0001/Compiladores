#include <iostream>
#include <cstring>
#include <fstream>
#include "token.h"
#include "scanner.h"

using namespace std;

// -----------------------------
// Constructor
// -----------------------------
Scanner::Scanner(const char* s): input(s), first(0), current(0) { 
    }

// -----------------------------
// Función auxiliar
// -----------------------------

bool is_white_space(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

// -----------------------------
// nextToken: obtiene el siguiente token
// -----------------------------


Token* Scanner::nextToken() {
    Token* token;

    // Saltar espacios en blanco
    while (current < input.length() && is_white_space(input[current])) 
        current++;

    // Fin de la entrada
    if (current >= input.length()) 
        return new Token(Token::END);

    char c = input[current];
    first = current;

    // Números
    if (isdigit(c)) {
        while (current < input.length() && isdigit(input[current]))
            current++;
            if (current < input.length() && input[current] == '.') {
                current++;
                while (current < input.length() && isdigit(input[current]))
                    current++;
            }

    return new Token(Token::NUM, input, first, current - first);
    }

    if (isalpha(c) && (current + 1 == input.length() || !isalnum(input[current + 1]))) {
        current++;
        return new Token(Token::ALPHA, input, first, current - first);

    }

    if (isalpha(c)) {
        current++;
        while (current < input.length() && isalnum(input[current]))
            current++;
        string lexema = input.substr(first, current - first);
        if (lexema == "sqrt") return new Token(Token::SQRT, input, first, current - first);
        if (lexema == "sin") return new Token(Token::SIN, input, first, current - first);
        if (lexema == "cos") return new Token(Token::COS, input, first, current - first);
        if (lexema == "log") return new Token(Token::LOG, input, first, current - first);
        if (lexema == "pi") return new Token(Token::PI, input, first, current - first);
        if (lexema == "e") return new Token(Token::E, input, first, current - first);
        if (lexema == "tg") return new Token(Token::TG, input, first, current - first);
        if (lexema == "ln") return new Token(Token::LN, input, first, current - first);
        else return new Token(Token::ID, input, first, current - first);
    }


    // Operadores
    else if (strchr("+/-*();", c)) {
        switch (c) {
            case '+': token = new Token(Token::PLUS,  c); break;
            case '-': token = new Token(Token::MINUS, c); break;
            case '*': token = new Token(Token::MUL,   c); break;
            case '/': token = new Token(Token::DIV,   c); break;
            case '(': token = new Token(Token::LPAREN,c); break;
            case ')': token = new Token(Token::RPAREN,c); break;
            case ';': token = new Token(Token::SEMICOLON,c);  break;
        }
        current++;
    }

    // Carácter inválido
    else {
        token = new Token(Token::ERR, c);
        current++;
    }

    return token;
}


/*
Token* Scanner::nextToken() {
    Token* token;
    char c;
    state = 0;
    first = current;;

    while (1) {
        switch (state) {
            case 0: 
                c = nextChar();
                if (c == ' ') { first = current;; state = 0; }
                else if (current >= input.length() ) return new Token(Token::END);
                else if (c == '(') state = 1;
                else if (c == ')') state = 2;
                else if (c == '+') state = 3;
                else if (c == '-') state = 4;
                else if (c == '*') state = 5;
                else if (c == '/') state = 6;
                else if (isdigit(c)) state = 8;
                else if (isalpha(c)) state = 11;
                else return new Token(Token::ERR, c);
                break;

            case 1: return new Token(Token::LPAREN,c);
            case 2: return new Token(Token::RPAREN,c);
            case 3: return new Token(Token::PLUS, c);
            case 4: return new Token(Token::MINUS, c);
            case 5:
                c = nextChar();
                if (c == '*') state = 7;
                else state = 10;
                break;
            case 6: return new Token(Token::DIV, c);
            case 7: return new Token(Token::POW, input, first, current - first);
            case 8:
                c = nextChar();
                if (isdigit(c)) state = 8;
                else state = 9;
                break;
            case 9:
                rollBack();
                return new Token(Token::NUM, input, first, current - first);
            case 10:
                rollBack();
            return new Token(Token::MUL, c);
            case 11:
                c = nextChar();
                if (isalnum(c)) state = 11;
                else state = 12;
                break;
            case 12:
                rollBack();
                string lexema = input.substr(first, current - first);
                if (lexema == "sqrt") return new Token(Token::SQRT, lexema, first, current - first);
                else return new Token(Token::ID, input, first, current - first);
        }
    }
}

*/

void Scanner::rollBack() {
    if (input[current] != '\0')
        current--;
}

char Scanner::nextChar() {
    int c = input[current];
    if (c != '\0') current++;
    return c;
}



// -----------------------------
// Destructor
// -----------------------------
Scanner::~Scanner() { }

// -----------------------------
// Función de prueba
// -----------------------------

void ejecutar_scanner(Scanner* scanner, const string& InputFile) {
    Token* tok;

    // Crear nombre para archivo de salida
    string OutputFileName = InputFile;
    size_t pos = OutputFileName.find_last_of(".");
    if (pos != string::npos) {
        OutputFileName = OutputFileName.substr(0, pos);
    }
    OutputFileName += "_tokens.txt";

    ofstream outFile(OutputFileName);
    if (!outFile.is_open()) {
        cerr << "Error: no se pudo abrir el archivo " << OutputFileName << endl;
        return;
    }

    outFile << "Iniciando Scanner para archivo: " << InputFile << endl << endl;

    while (true) {
        tok = scanner->nextToken();

        if (tok->type == Token::END) {
            outFile << *tok << endl;
            delete tok;
            outFile << "\nScanner exitoso" << endl << endl;
            outFile.close();
            return;
        }

        if (tok->type == Token::ERR) {
            outFile << *tok << endl;
            delete tok;
            outFile << "Caracter invalido" << endl << endl;
            outFile << "Scanner no exitoso" << endl << endl;
            outFile.close();
            return;
        }

        outFile << *tok << endl;
        delete tok;
    }
}
