#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool load_config(const char *path, Config *cfg) {
    FILE *fp = fopen(path, "r");
    if (!fp) return false;

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "server=", 7) == 0) {
            strncpy(cfg->server, line + 7, sizeof(cfg->server) - 1);
            cfg->server[strcspn(cfg->server, "\r\n")] = 0;
        } else if (strncmp(line, "port=", 5) == 0) {
            cfg->port = atoi(line + 5);
        } else if (strncmp(line, "autofill=", 9) == 0) {
            cfg->autofill = atoi(line + 9) != 0;
        } else if (strncmp(line, "theme=", 6) == 0) {
            if (strstr(line, "dark")) cfg->theme = THEME_DARK;
            else cfg->theme = THEME_LIGHT;
        }
    }

    fclose(fp);
    return true;
}

bool save_config(const char *path, Config cfg) {
    FILE *fp = fopen(path, "w");
    if (!fp) return false;

    fprintf(fp, "server=%s\n", cfg.server);
    fprintf(fp, "port=%d\n", cfg.port);
    fprintf(fp, "autofill=%d\n", cfg.autofill ? 1 : 0);
    fprintf(fp, "theme=%s\n", cfg.theme == THEME_DARK ? "dark" : "light");

    fclose(fp);
    return true;
}
