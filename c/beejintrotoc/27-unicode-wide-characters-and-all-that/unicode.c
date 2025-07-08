#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>

void unicode_in_c() {
    printf("\u20AC\n\U0001D4D1\n");
}

void multibyte_chars() {
}

void wide_chars() {
    setlocale(LC_ALL, "");

    char *mb_string = "The cost is \u20ac1.23";
    size_t mb_len = strlen(mb_string);

    wchar_t wc_string[128];

    size_t wc_len = mbstowcs(wc_string, mb_string, 128);
    printf("multibyte \"%s\" (%zu bytes)\n", mb_string, mb_len);
    printf("wide char: \"%ls\" (%zu characters, %zu bytes)\n", wc_string, wc_len, sizeof(wchar_t) * wc_len);

    char mb_string_from_wc[128];
    size_t mb_string_from_wc_len = wcstombs(mb_string_from_wc, wc_string, 128);
    printf("multibyte from wc: \"%s\" (%zu bytes)", mb_string_from_wc, mb_string_from_wc_len);
}

int main() {
    // unicode_in_c();
    wide_chars();
}
