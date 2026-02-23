enum TokenKind {
    Tok_Illegal,
    Tok_EndOfFile,

    Tok_Identifier,
    Tok_Number,
    Tok_String,

    Tok_Keyword,
    Tok_type,
    Tok_CompEqual,
    Tok_CompLessThan,
    Tok_CompGreaterThan,
    Tok_CompLessThanEqual,
    Tok_CompGreaterThanEqual,
    Tok_CompNotEqual,
    Tok_Negate,

    Tok_LParen,     // (
    Tok_RParen,     // )
    Tok_LBrace,     // {
    Tok_RBrace,     // }
    Tok_LBracket,   // [
    Tok_RBracket,   // ]
    Tok_Colon,      // :
    Tok_Comma,      // ,
    Tok_Semicolon,  // ;
    Tok_Equal,      // =
    Tok_At,
    Tok_Star,
    Tok_Add,
    Tok_Sub,
    Tok_Dquote
};

enum TypeKind {
    Type_u8,
    Type_u16,
    Type_u32,
    Type_u64,
    Type_i8,
    Type_i16,
    Type_i32,
    Type_i64,
    Type_f32,
    Type_f64,
    Type_char8,
    Type_char16,
    Type_char32,
};

enum KeywordKind {
    Keyword_proc,
    Keyword_include,
    Keyword_let,
    Keyword_debug_print,
    Keyword_struct,
    Keyword_enum,
    Keyword_if,
    Keyword_else,
    Keyword_while,
    Keyword_for,
    Keyword_do,
};

struct Token {
    TokenKind token_kind;

    union {
        KeywordKind keyword_kind;
        TypeKind type_kind;
    };

    std::string literal;

    Token() {
        token_kind = Tok_Illegal;
        keyword_kind = Keyword_proc;     }

    Token(TokenKind k, const std::string& lit)
        : token_kind(k), literal(lit)
    {
        keyword_kind = Keyword_proc;    }
};

