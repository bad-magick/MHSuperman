#include <string>

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *strtrim(char *s)
{
    return rtrim(ltrim(s)); 
}

std::string tolowers(std::string str)
{
    for (int i=0;i<strlen(str.c_str());i++) 
        if (str[i] >= 0x41 && str[i] <= 0x5A) 
            str[i] = str[i] + 0x20;
    return str;
}

std::string replaceChar(std::string str, char ch1, char ch2)
{
  for (int i = 0; i < str.length(); ++i) {
    if (str[i] == ch1)
      str[i] = ch2;
  }

  return str;
}

void gen_random(char *s, const int len)
{
    static const char alphanum[] =
        "0123456789"
		"`~!@#$%^&*()[]{}-_=+,.<>/?\\:;'"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void gen_random(wchar_t *s, const int len)
{
    static const wchar_t alphanum[] =
        L"0123456789"
		L"`~!@#$%^&*()[]{}-_=+,.<>/?\\:;'"
        L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        L"abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

int instr(char *SearchString, char *SearchTerm)
{
    int stringSize = strlen( SearchString );
    int termSize = strlen( SearchTerm );

    if ( termSize > stringSize )
    {
        return 0;
    }

    int numberFound = 0;
//    const char* subString = NULL;

    for ( int i = 0 ; i <= stringSize - termSize; ++i )
    {
        if ( strncmp( &SearchString[ i ], SearchTerm, termSize ) == 0 )
        {
            i += termSize;    // Skip past this term.
            ++numberFound;
        }
    }
    
    return numberFound;
}

unsigned FindInStr(const std::string& src, const std::string& trm)
{
    unsigned numOccurrences = 0;
    size_t loc = 0;
    while (loc < src.size() &&
          (loc = src.find(trm, loc)) != std::string::npos)
    {
        ++numOccurrences;
        ++loc;
    }
    return numOccurrences;
}
