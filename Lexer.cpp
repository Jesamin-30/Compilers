#include "Lexer.h"
#include <cctype>

Lexer::Lexer(string _codigo)
{
    codigo = _codigo;
    posicion = 0;
}

bool Lexer::esFinal()
{
    return posicion >= codigo.length();
}

char Lexer::actual()
{
    return codigo[posicion];
}

char Lexer::avanzar()
{
    char caracter = codigo[posicion];
    posicion++;
    return caracter;
}

void Lexer::ignorarEspacios()
{
    while (!esFinal() && isspace(actual()))
    {
        avanzar();
    }
}

Token Lexer::reconocerNumero()
{
    string lexema = "";
    bool tienePunto = false;
    while (!esFinal())
    {
        if (isdigit(actual()))
        {
            lexema += avanzar();
        }
        else if (actual() == '.')
        {
            tienePunto = true;
            lexema += avanzar();
        }
        else
        {
            break;
        }
    }

    if (tienePunto)
    {
        return {
            TipoToken::LITERAL_REAL,
            lexema};
    }
    else
    {
        return {
            TipoToken::LITERAL_ENTERO,
            lexema};
    }
}

Token Lexer::reconocerIdentificador()
{
    string lexema = "";
    lexema += avanzar();
    while (!esFinal() && (isalnum(actual()) || actual() == '_'))
    {
        lexema += avanzar();
    }
    return {
        TipoToken::IDENTIFICADOR,
        lexema};
}

vector<Token> Lexer::analizar()
{
    vector<Token> tokens;
    while (!esFinal())
    {
        ignorarEspacios();
        if (esFinal())
        {
            break;
        }
        char c = actual();

        // Número entero
        if (isdigit(c))
        {
            tokens.push_back(reconocerNumero());
        }

        // Identificador
        else if (isalpha(c) || c == '_')
        {
            tokens.push_back(reconocerIdentificador());
        }

        // Carácter desconocido
        else
        {
            string lexema = "";
            lexema += avanzar();
            tokens.push_back({TipoToken::DESCONOCIDO,
                              lexema});
        }
    }

    return tokens;
}