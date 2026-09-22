#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"

using namespace std;

class Parser
{
private:
    vector<Token> tokens;
    int posicion;

    // Devuelve true si ya no quedan tokens
    bool esFinal();

    // Devuelve el token que estamos analizando
    Token actual();

    // Comprueba si el token actual es del tipo esperado
    bool coincidir(TipoToken tipo);

    // No terminales de nuestra gramática
    bool tipo();
    bool valor();
    bool declaracion();

public:
    Parser(vector<Token> tokens);

    // Inicia el análisis sintáctico
    bool analizar();
    void error(string esperado);
};

#endif