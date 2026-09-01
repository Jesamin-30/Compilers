#include <iostream>
#include <vector>
#include "Lexer.h"

using namespace std;

string nombreToken(TipoToken tipo)
{
    switch (tipo)
    {
    case TipoToken::LITERAL_ENTERO:
        return "LITERAL_ENTERO";
    case TipoToken::LITERAL_REAL:
        return "LITERAL_REAL";
    case TipoToken::IDENTIFICADOR:
        return "IDENTIFICADOR";
    case TipoToken::DESCONOCIDO:
        return "DESCONOCIDO";
    }
    return "";
}

int main()
{
    string codigo;
    cout << "Ingrese codigo: ";
    getline(cin, codigo);
    Lexer lexer(codigo);
    vector<Token> tokens = lexer.analizar();
    cout << "--------TOKENS ENCONTRADOS---------\n";
    for (Token token : tokens)
    {
        cout
            << "<"
            << nombreToken(token.tipo)
            << ", "
            << token.lexema
            << ">"
            << endl;
    }

    return 0;
}