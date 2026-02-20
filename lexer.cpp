// lexer.cpp
// Minimal lexer for the language example:
//
// proc main(argc: u64, argv: []string){}
//
// This is ONLY the lexer layer.
// It converts characters -> tokens.
// No parsing, no grammar trees, no semantics.

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <sstream>

#include <cstdio>

enum class TokenKind {
    Illegal,
    EndOfFile,

    Identifier,
    Number,
    String,

    // keywords
    Proc, // proc
    Let, // let
    DebugPrint, //debug_print

    // punctuation
    LParen,     // (
    RParen,     // )
    LBrace,     // {
    RBrace,     // }
    LBracket,   // [
    RBracket,   // ]
    Colon,      // :
    Comma,      // ,
    Semicolon,  // ;
    Assign      // =
};

struct Token {
    TokenKind kind;
    std::string literal;
};

static std::unordered_map<std::string, TokenKind> keywords = {
    {"proc", TokenKind::Proc},
    {"let",  TokenKind::Let},
    {"debug_print", TokenKind::DebugPrint},
};

TokenKind lookupIdentifier(const std::string& ident) {
    auto it = keywords.find(ident);
    if (it != keywords.end()) return it->second;
    return TokenKind::Identifier;
}

struct Lexer {
    std::string input;
    size_t position = 0;
    size_t readPosition = 0;
    char ch = 0;

    Lexer(const std::string& src) : input(src) {
        readChar();
    }

    void readChar() {
        if (readPosition >= input.size()) ch = 0;
        else ch = input[readPosition];
        position = readPosition;
        readPosition++;
    }

    void skipWhitespace() {
        while (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r') {
            readChar();
        }
    }

    std::string readIdentifier() {
        size_t start = position;
        while (std::isalnum(ch) || ch == '_') {
            readChar();
        }
        return input.substr(start, position - start);
    }

    std::string readNumber() {
        size_t start = position;
        while (std::isdigit(ch)) {
            readChar();
        }
        return input.substr(start, position - start);
    }

    std::string readString() {
        // assume current char == '"'
        readChar(); // skip opening quote
        size_t start = position;

        while (ch != '"' && ch != 0) {
            readChar();
        }

        std::string out = input.substr(start, position - start);
        readChar(); // skip closing quote
        return out;
    }

    Token nextToken() {
        skipWhitespace();

        Token tok;

        switch (ch) {
            case '(':
                tok = {TokenKind::LParen, "("};
                readChar();
                return tok;

            case ')':
                tok = {TokenKind::RParen, ")"};
                readChar();
                return tok;

            case '{':
                tok = {TokenKind::LBrace, "{"};
                readChar();
                return tok;

            case '}':
                tok = {TokenKind::RBrace, "}"};
                readChar();
                return tok;

            case '[':
                tok = {TokenKind::LBracket, "["};
                readChar();
                return tok;

            case ']':
                tok = {TokenKind::RBracket, "]"};
                readChar();
                return tok;

            case ':':
                tok = {TokenKind::Colon, ":"};
                readChar();
                return tok;

            case ',':
                tok = {TokenKind::Comma, ","};
                readChar();
                return tok;

            case ';':
                tok = {TokenKind::Semicolon, ";"};
                readChar();
                return tok;

            case '=':
                tok = {TokenKind::Assign, "="};
                readChar();
                return tok;

            case '"': {
                std::string str = readString();
                return {TokenKind::String, str};
            }

            case 0:
                return {TokenKind::EndOfFile, ""};

            default:
                if (std::isalpha(ch) || ch == '_') {
                    std::string ident = readIdentifier();
                    return {lookupIdentifier(ident), ident};
                }

                if (std::isdigit(ch)) {
                    std::string num = readNumber();
                    return {TokenKind::Number, num};
                }

                tok = {TokenKind::Illegal, std::string(1, ch)};
                readChar();
                return tok;
        }
    }
};

std::string kindToString(TokenKind k) {
    switch (k) {
        case TokenKind::Illegal: return "Illegal";
        case TokenKind::EndOfFile: return "EOF";
        case TokenKind::Identifier: return "Identifier";
        case TokenKind::Number: return "Number";
        case TokenKind::String: return "String";
        case TokenKind::Proc: return "Proc";
        case TokenKind::Let: return "Let";
        case TokenKind::LParen: return "LParen";
        case TokenKind::RParen: return "RParen";
        case TokenKind::LBrace: return "LBrace";
        case TokenKind::RBrace: return "RBrace";
        case TokenKind::LBracket: return "LBracket";
        case TokenKind::RBracket: return "RBracket";
        case TokenKind::Colon: return "Colon";
        case TokenKind::Comma: return "Comma";
        case TokenKind::Semicolon: return "Semicolon";
        case TokenKind::Assign: return "Assign";
        case TokenKind::DebugPrint: return "DebugPrint";
        default: return "Unknown";
    }
}

std::string read_entire_file(const std::string& filepath) {
    std::ifstream file(filepath.c_str());
    std::stringstream buffer;

    buffer << file.rdbuf();
    std::string str = buffer.str();

    return str;
}

int main() {
    Lexer lexer{read_entire_file("main.at")};

    while (true) {
        Token tok = lexer.nextToken();
        std::cout << kindToString(tok.kind) << " : " << tok.literal << "\n";
        if (tok.kind == TokenKind::EndOfFile) break;
    }
}

