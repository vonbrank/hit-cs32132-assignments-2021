#ifndef TYPE_CPP
#define TYPE_CPP

class Type
{
public:
    static bool isAlpha(char c);
    static bool isDigit(char c);
    static bool charCompare(char a, char b);
    static char toLower(char c);
    static char toUpper(char c);
};

bool Type::isAlpha(char c)
{
    bool res = false;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        res = true;
    return res;
}

bool Type::isDigit(char c)
{
    bool res = false;
    if (c >= '0' && c <= '9')
        res = true;
    return res;
}

bool Type::charCompare(char a, char b)
{
    if (!((isAlpha(a) || isDigit(b)) && (isAlpha(b) || isDigit(b))))
        return a < b;
    if (isAlpha(a) && isAlpha(b))
    {
        if (toLower(a) == toLower(b))
            return a < b;
        else
            return toLower(a) < toLower(b);
    }
    else if (isDigit(a) && isDigit(b))
    {
        return a < b;
    }
    else if (isDigit(a) && isAlpha(b))
    {
        return true;
    }
    else if (isAlpha(a) && isDigit(b))
    {
        return false;
    }
    return false;
}

char Type::toLower(char c)
{
    if (!isAlpha(c))
        return c;
    if (c >= 'A' && c <= 'Z')
        c = c - 'A' + 'a';
    return c;
}

char Type::toUpper(char c)
{
    if (!isAlpha(c))
        return c;
    if (c >= 'a' && c <= 'z')
        c = c - 'a' + 'A';
    return c;
}

#endif