#include <iostream>
#include "token.h"

using namespace std;

// -----------------------------
// Constructores
// -----------------------------

Token::Token(Type type) 
    : type(type), text("") { }

Token::Token(Type type, char c) 
    : type(type), text(string(1, c)) { }

Token::Token(Type type, const string& source, int first, int last) 
    : type(type), text(source.substr(first, last)) { }

// -----------------------------
// Sobrecarga de operador <<
// -----------------------------

// Para Token por referencia
ostream& operator<<(ostream& outs, const Token& tok) {
    switch (tok.type) {
        case Token::PLUS:   outs << "TOKEN(PLUS, \""   << tok.text << "\")"; break;
        case Token::MINUS:  outs << "TOKEN(MINUS, \""  << tok.text << "\")"; break;
        case Token::MUL:    outs << "TOKEN(MUL, \""    << tok.text << "\")"; break;
        case Token::DIV:    outs << "TOKEN(DIV, \""    << tok.text << "\")"; break;
        case Token::NUM:    outs << "TOKEN(NUM, \""    << tok.text << "\")"; break;
        case Token::ID:    outs << "TOKEN(ID, \""    << tok.text << "\")"; break;
        case Token::POW:    outs << "TOKEN(POW, \""    << tok.text << "\")"; break;
        case Token::SQRT:    outs << "TOKEN(SQRT, \""    << tok.text << "\")"; break;
        case Token::LPAREN: outs << "TOKEN(LPAREN, \""    << tok.text << "\")"; break;
        case Token::RPAREN: outs << "TOKEN(RPAREN, \""    << tok.text << "\")"; break;
        case Token::ERR:    outs << "TOKEN(ERR, \""    << tok.text << "\")"; break;
        case Token::SEMICOLON: outs << "TOKEN(SEMICOLON, \""    << tok.text << "\")"; break;
        case Token::FLOAT:   outs  << "TOKEN(FLOAT, \""    << tok.text << "\")"; break;
        case Token::ALPHA:   outs  << "TOKEN(ALPHA, \""    << tok.text << "\")"; break;
        case Token::LOG:   outs  << "TOKEN(LOG, \""    << tok.text << "\")"; break;
        case Token::LN:   outs  << "TOKEN(LN, \""    << tok.text << "\")"; break;
        case Token::SIN:   outs  << "TOKEN(SIN, \""    << tok.text << "\")"; break;
        case Token::COS:   outs  << "TOKEN(COS, \""    << tok.text << "\")"; break;
        case Token::TG:   outs  << "TOKEN(TG, \""    << tok.text << "\")"; break;
        case Token::PI:   outs  << "TOKEN(PI, \""    << tok.text << "\")"; break;
        case Token::E:   outs  << "TOKEN(E, \""    << tok.text << "\")"; break;
        case Token::END:    outs << "TOKEN(END)"; break;
    }
    return outs;
}

// Para Token puntero
ostream& operator<<(ostream& outs, const Token* tok) {
    if (!tok) return outs << "TOKEN(NULL)";
    return outs << *tok;  // delega al otro
}