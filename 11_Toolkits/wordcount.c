#include <stdio.h>
#include <glib.h>
#include <string.h>

void handler(gpointer, gpointer, gpointer);

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("pass filename into argv\n");
        return 1;
    }
    gchar *data;
    if(g_file_get_contents(argv[1], &data, NULL, NULL) == 0) {
        printf("bad filename\n");
        return 1;
    }
    gchar **lines, **words, **it_1, **it_2;
    GHashTable *dict = g_hash_table_new(g_str_hash, g_str_equal);
    lines = g_strsplit(data, "\n", -1);
    for(it_1 = lines; *it_1 != NULL; ++it_1) {
        words = g_strsplit(*it_1, " ", -1);
        for(it_2 = words; *it_2 != NULL; ++it_2) {
            if(strlen(*it_2) <= 80) {
                gpointer tmp = g_hash_table_lookup(dict, *it_2);
                if(tmp == NULL) {
                    g_hash_table_insert(dict, *it_2, (void*)1);
                } else {
                    g_hash_table_replace(dict, *it_2, tmp + 1);
                }
            }
        }
    }
    printf("printing word counts:\n");
    g_hash_table_foreach(dict, handler, "%s: %d\n");
    return 0;
}

void handler(gpointer key, gpointer val, gpointer format_str) {
    printf(format_str, key, val);
    return;
}
