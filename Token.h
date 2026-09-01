using namespace std;

enum class TipoToken
{
    LITERAL_ENTERO,
    LITERAL_REAL,
    IDENTIFICADOR,
    DESCONOCIDO
};

struct Token
{
    TipoToken tipo;
    string lexema;
};