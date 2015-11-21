#ifndef _UNITEXT_H

#include <stdint.h>
#include <wchar.h>

#define UNITEXT_LANG_EN  0
#define UNITEXT_LANG_JP  1
#define UNITEXT_LANG_MAX 2

#define UNITEXT_FONT_NORMAL 0
#define UNITEXT_FONT_ITALIA 1
#define UNITEXT_FONT_MAX 2

extern void unitext_set_font(uint8_t lang, uint8_t font);

extern uint8_t unitext_get_lang(void);

extern void unitext_print(wchar_t *text, uint16_t x, uint16_t y);

#endif
