#include "Lexer.h"
#include <cctype>

Lexer::Lexer(string _codigo)
{
    codigo = _codigo;
    posicion = 0;
    linea = 1;
    columna = 1;
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
    // controla salto de linea
    if (caracter == '\n')
    {
        linea++;
        columna = 1;
    }
    else
    {
        columna++;
    }

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

    while (!esFinal() && (isalnum(actual()) || actual() == '_'))
    {
        lexema += avanzar();
    }

    if (esPalabraClave(lexema))
    {
        return {
            TipoToken::PALABRA_CLAVE,
            lexema};
    }

    return {
        TipoToken::IDENTIFICADOR,
        lexema};
}

Token Lexer::reconocerOperador()
{
    string lexema = "";
    lexema += avanzar();
    return {
        TipoToken::OPERADOR,
        lexema};
}

bool Lexer::esPalabraClave(string palabra)
{
    return palabra == "int" || palabra == "float" || palabra == "string" || palabra == "if" || palabra == "else";
}

// error lexico
vector<ErrorLexico> Lexer::obtenerErrores()
{
    return errores;
}

void Lexer::registrarError(string lexema, int lineaError, int columnaError, string mensaje)
{
    ErrorLexico error;
    error.lexema = lexema;
    error.linea = lineaError;
    error.columna = columnaError;
    error.mensaje = mensaje;
    errores.push_back(error);
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

        // Literal entero o real
        if (isdigit(c))
        {
            tokens.push_back(reconocerNumero());
        }

        // Identificador o palabra clave
        else if (isalpha(c) || c == '_')
        {
            tokens.push_back(reconocerIdentificador());
        }

        // Operadores aritméticos
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            tokens.push_back(reconocerOperador());
        }

        // Asignación
        else if (c == '=')
        {
            string lexema = "";
            lexema += avanzar();
            tokens.push_back({TipoToken::ASIGNACION, lexema});
        }

        // Delimitador
        else if (c == ';')
        {
            string lexema = "";
            lexema += avanzar();
            tokens.push_back({TipoToken::DELIMITADOR,
                              lexema});
        }

        // Carácter desconocido - error lexico
        else
        {
            int lineaError = linea;
            int columnaError = columna;

            string lexema = "";
            lexema += avanzar();

            registrarError(
                lexema,
                lineaError,
                columnaError,
                "Caracter no reconocido");

            tokens.push_back({TipoToken::DESCONOCIDO,
                              lexema,
                              lineaError,
                              columnaError});
        }
    }
    return tokens;
}