#include <helpers.h>

// convert a single hex digit character to its integer value (from https://code.google.com/p/avr-netino/)
static unsigned char h2int(char c)
{
    if (c >= '0' && c <= '9') {
        return ((unsigned char)c - '0');
    }
    if (c >= 'a' && c <= 'f') {
        return ((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <= 'F') {
        return ((unsigned char)c - 'A' + 10);
    }
    return (0);
}

// based on https://code.google.com/p/avr-netino/
String urlDecode(String input)
{
    char c;
    String ret = "";

    for (uint8_t t = 0; t < input.length(); t++) {
        c = input[t];
        if (c == '+') c = ' ';
        if (c == '%') {
            t++;
            c = input[t];
            t++;
            c = (h2int(c) << 4) | h2int(input[t]);
        }
        ret.concat(c);
    }
    return ret;
}