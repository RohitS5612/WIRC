#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef enum {
    THEME_LIGHT,
    THEME_DARK
} Theme;

typedef struct {
    char server[128];
    int port;
    bool autofill;
    Theme theme;
} Config;

bool load_config(const char *path, Config *cfg);
bool save_config(const char *path, Config cfg);

#endif
