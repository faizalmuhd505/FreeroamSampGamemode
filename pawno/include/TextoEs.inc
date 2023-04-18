/*=================================================||
||     Textos en espanol en GameText y Texdraw     ||
||                       BY                        ||
||                 Tribisk_Transk                  ||
||=================================================*/
#include <a_samp>

stock EStexto(text[])
{
    new TextoES[256];
    for(new i; i < strlen(text); i++)
    {
        switch(text[i])
        {
            case 'Ú', 'ú': TextoES[i] = 'ª';
            case 'Í', 'í': TextoES[i] = '¢';
            case 'Ó', 'ó': TextoES[i] = '¦';
            case 'É', 'é': TextoES[i] = 'ž';
            case 'Á', 'á': TextoES[i] = '˜';
            case 'Ñ', 'ñ': TextoES[i] = '®';
            case '¿': TextoES[i] = '¯';
            case '¡': TextoES[i] = '^';
            default: TextoES[i] = text[i];
        }
    }
    return TextoES;
}
/*=================================================||
||     Textos en espanol en GameText y Texdraw     ||
||                       BY                        ||
||                 Tribisk_Transk                  ||
||=================================================*/
