#include "Parser.h"
#include <iostream>

using namespace std;
// Constructor
Parser::Parser(vector<Token> tokens)
{

    this->tokens = tokens;
    posicion = 0;
}

// Verifica si terminamos de analizar
bool Parser::esFinal()
{

    return posicion >= tokens.size();
}

// Obtiene el token actual
Token Parser::actual()
{

    return tokens[posicion];
}

// Comprueba si el token actual
// corresponde al tipo esperado
bool Parser::coincidir(TipoToken tipoEsperado)
{
    if (!esFinal() &&
        actual().tipo == tipoEsperado)
    {

        posicion++;

        return true;
    }

    return false;
}

// ---------------------------------
// Tipo → int | float
// ---------------------------------

bool Parser::tipo()
{
    if (esFinal())
    {
        return false;
    }

    if (actual().tipo == TipoToken::PALABRA_CLAVE)
    {

        if (actual().lexema == "int" ||
            actual().lexema == "float")
        {

            posicion++;

            return true;
        }
    }
    return false;
}

// ---------------------------------
// Valor → NUM | REAL | ID
// ---------------------------------

bool Parser::valor()
{

    if (esFinal())
    {
        return false;
    }

    if (coincidir(TipoToken::LITERAL_ENTERO))
    {
        return true;
    }

    if (coincidir(TipoToken::LITERAL_REAL))
    {
        return true;
    }

    if (coincidir(TipoToken::IDENTIFICADOR))
    {
        return true;
    }

    return false;
}

// ---------------------------------
// Declaracion → Tipo ID = Valor ;
// ---------------------------------

bool Parser::declaracion()
{
    // Tipo
    if (!tipo())
    {
        error("int o float");
        return false;
    }

    // ID
    if (!coincidir(TipoToken::IDENTIFICADOR))
    {
        error("IDENTIFICADOR");
        return false;
    }

    // =
    if (!coincidir(TipoToken::ASIGNACION))
    {
        error("'='");
        return false;
    }

    // Valor
    if (!valor())
    {
        error("NUM, REAL o IDENTIFICADOR");
        return false;
    }

    // ;
    if (!coincidir(TipoToken::DELIMITADOR))
    {
        error("';'");
        return false;
    }

    return true;
}

// ---------------------------------
// Iniciar análisis sintáctico
// ---------------------------------

bool Parser::analizar()
{
    if (!declaracion())
    {
        return false;
    }

    // Verificamos que no sobren tokens
    if (!esFinal())
    {

        cout << "Error sintactico: "
             << "existen tokens adicionales."
             << endl;

        return false;
    }
    return true;
}

void Parser::error(string esperado)
{
    if (!esFinal())
    {
        cout << "Error sintactico en linea "
             << actual().linea
             << ", columna "
             << actual().columna
             << ": se esperaba "
             << esperado
             << ", pero se encontro '"
             << actual().lexema
             << "'."
             << endl;
    }
    else
    {
        cout << "Error sintactico: "
             << "se esperaba "
             << esperado
             << ", pero se llego al final de la entrada."
             << endl;
    }
}