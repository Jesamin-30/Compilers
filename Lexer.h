#include <vector>
#include "Token.h"

using namespace std;

class Lexer
{
private:
    string codigo;
    int posicion;
    bool esFinal();
    char actual();
    char avanzar();
    void ignorarEspacios();
    Token reconocerNumero();
    Token reconocerIdentificador();
public:
    Lexer(string codigoFuente);
    vector<Token> analizar();
};