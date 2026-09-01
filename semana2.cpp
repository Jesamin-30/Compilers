#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{

    string codigo;

    cout << "Ingrese una instruccion: ";
    getline(cin, codigo);

    int i = 0;

    while (i < codigo.length())
    {

        char caracter = codigo[i];

        // 1. Ignorar espacios
        if (caracter == ' ')
        {
            i++;
        }

        // 2. Reconocer numeros
        else if (isdigit(caracter))
        {
            string numero = "";
            while (i < codigo.length() && (isdigit(codigo[i]) || codigo[i]=='.'))
            {
                numero = numero + codigo[i];
                i++;
            }

            cout << "<NUMERO, " << numero << ">" << endl;
        }

        // 3. Reconocer identificadores
        else if (isalpha(caracter))
        {
            string identificador = "";
            while (i < codigo.length() && isalnum(codigo[i]))
            {
                identificador = identificador + codigo[i];
                i++;
            }
            cout << "<IDENTIFICADOR, " << identificador << ">" << endl;
        }
        // Caracter que todavía no reconocemos
        else
        {
            i++;
        }
    }

    return 0;
}