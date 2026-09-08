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

    case TipoToken::PALABRA_CLAVE:
        return "PALABRA_CLAVE";

    case TipoToken::OPERADOR:
        return "OPERADOR";

    case TipoToken::ASIGNACION:
        return "ASIGNACION";

    case TipoToken::DELIMITADOR:
        return "DELIMITADOR";

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

    vector<ErrorLexico> errores = lexer.obtenerErrores();
    cout << "\n-------- ERRORES LEXICOS --------\n";

    if (errores.empty())
    {
        cout << "No se encontraron errores lexicos." << endl;
    }
    else
    {
        for (ErrorLexico error : errores)
        {
            cout << "Lexema: " << error.lexema << endl;
            cout << "Linea: " << error.linea << endl;
            cout << "Columna: " << error.columna << endl;
            cout << "Mensaje: " << error.mensaje << endl;
            cout << "----------------------" << endl;
        }
    }

    return 0;
}

// int edad = 20;
// float promedio = nota1 + 15.5;
// x = 10 @ 2;
// int resultado = nota1 * 2 + 10;