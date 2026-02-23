#include<iostream>
#include<string.h>
#include<vector>
#include"lexer.cpp"
#include<fstream>
#include<unordered_map>
#include<cctype>

using namespace std;

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z');
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

bool isIdentifierStart(char c) {
    return isLetter(c) || c == '_';
}

bool isIdentifierChar(char c) {
    return  isIdentifierStart(c) || isDigit(c);
}
unordered_map<string, KeywordKind> keywordTable = {
    {"proc", Keyword_proc},
    {"include", Keyword_include},
    {"let", Keyword_let},
    {"debug_print", Keyword_debug_print},
    {"struct", Keyword_struct},
    {"enum", Keyword_enum},
    {"if", Keyword_if},
    {"else", Keyword_else},
    {"while", Keyword_while},
    {"for", Keyword_for},
    {"do", Keyword_do},
};
unordered_map<string, TypeKind> typeTable = {
    {"u8", Type_u8},
    {"u16", Type_u16},
    {"u32", Type_u32},
    {"u64", Type_u64},
    {"i8", Type_i8},
    {"i16", Type_i16},
    {"i32", Type_i32},
    {"i64", Type_i64},
    {"f32", Type_f32},
    {"f64", Type_f64},
    {"char8", Type_char8},
    {"char16", Type_char16},
    {"char32", Type_char32},
};
vector<Token> lexFile(const string& text) {
    vector<Token> tokens;

    int i = 0;
    int n = text.length();

    while (i < n) {

        char lookahead = text[i];

        if (isspace(lookahead)){
            i++;
            continue;
        }

        if (isIdentifierStart(lookahead)) {

            string ident = "";

            while (i < n && isIdentifierChar(text[i])) {
                ident += text[i];
                i++;
            }

            Token tok;

            auto kw = keywordTable.find(ident);
            auto ty = typeTable.find(ident);

            if (kw != keywordTable.end()) {
                tok.token_kind = Tok_Keyword;
                tok.keyword_kind = kw->second;
            }
            else if (ty != typeTable.end()) {
                tok.token_kind = Tok_type;
                tok.type_kind = ty->second;
            }
            else {
                tok.token_kind = Tok_Identifier;

            }

            tok.literal = ident;
            tokens.push_back(tok);
        }

        //else if for number checking

        else if (isDigit(lookahead)) {
            std::string number = "";
            bool seenDot = false;

            while (i < n) {
                char c = text[i];

                if (isDigit(c)) {
                    number += c;
                    i++;
                }
                else if (c == '.' && !seenDot) {
                    seenDot = true;
                    number += c;
                    i++;
                }
                else break;
            }

            tokens.push_back(Token(Tok_Number, number));
        }


        else {

            if (lookahead=='=' && i+1<n && text[i+1]=='=') {
                    tokens.push_back(Token(Tok_CompEqual,"=="));
                    i+=2; continue;
                }
            if (lookahead=='<' && i+1<n && text[i+1]=='=') {
                tokens.push_back(Token(Tok_CompLessThanEqual,"<="));
                i+=2; continue;
            }
            if (lookahead=='>' && i+1<n && text[i+1]=='=') {
                tokens.push_back(Token(Tok_CompGreaterThanEqual,">="));
                i+=2; continue;
            }
            if (lookahead=='!' && i+1<n && text[i+1]=='=') {
                tokens.push_back(Token(Tok_CompNotEqual,"!="));
                i+=2; continue;
            }
            switch (lookahead) {
                case '+': tokens.push_back(Token(Tok_Add, "+")); break;
                case '-': tokens.push_back(Token(Tok_Sub, "-")); break;
                case '(': tokens.push_back(Token(Tok_LParen,"(")); break;
                case ')': tokens.push_back(Token(Tok_RParen,")")); break;
                case '{': tokens.push_back(Token(Tok_LBrace,"{")); break;
                case '}': tokens.push_back(Token(Tok_RBrace,"}")); break;
                case '[': tokens.push_back(Token(Tok_LBracket,"[")); break;
                case ']': tokens.push_back(Token(Tok_RBracket,"]")); break;
                case ':': tokens.push_back(Token(Tok_Colon,":")); break;
                case ',': tokens.push_back(Token(Tok_Comma,",")); break;
                case ';': tokens.push_back(Token(Tok_Semicolon,";")); break;
                case '=': tokens.push_back(Token(Tok_Equal,"=")); break;
                case '@': tokens.push_back(Token(Tok_At,"@")); break;
                case '*': tokens.push_back(Token(Tok_Star,"*")); break;
                case '!': tokens.push_back(Token(Tok_Negate,"!")); break;
                default: break;
            }

            i++;
        }
    }

    return tokens;
}
int main() {

    ifstream file("main.at");

    string content = "";
    string line;

    while (getline(file, line)) {
        content += line + '\n';
    }



    vector<Token> ans = lexFile(content);
    for (auto it: ans){
        std::cout << it.literal << endl;
    }


    return 0;
}

