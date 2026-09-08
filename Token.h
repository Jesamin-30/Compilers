using namespace std;

enum class TipoToken
{
    LITERAL_ENTERO,
    LITERAL_REAL,
    IDENTIFICADOR,
    DESCONOCIDO,
    //-------
    PALABRA_CLAVE,
    OPERADOR,
    ASIGNACION,
    DELIMITADOR
};

struct Token
{
    TipoToken tipo; 
    string lexema; 

    int linea;
    int columna;
};

struct ErrorLexico
{
    string lexema;
    int linea;
    int columna;
    string mensaje;
};