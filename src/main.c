#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern const char _binary_build_so_raw_so_start;
extern const char _binary_build_so_raw_so_end;

int main(int argc, char **argv) {
    int tmp_f;
    char tmp_name[] = "/tmp/qtextract-XXXXXX-lib.so";
    if ((tmp_f = mkstemps(tmp_name, 7)) == -1) {
        fprintf(stderr, "Failed to open temporary file\n");
        return -1;
    }
    ssize_t w_num;
    const char *start = &_binary_build_so_raw_so_start;
    const char *end = &_binary_build_so_raw_so_end;
    do {
        w_num = write(tmp_f, start, end-start+1);
        if (w_num == -1) {
            fprintf(stderr, "Failed to write to temporary file\n");
            return -1;
        }
        start += w_num;
    } while (w_num != 0);
    close(tmp_f);
    setenv("LD_PRELOAD", tmp_name, 1);
    char *app_name = "/opt/zoom/zoom";
    execl(app_name, app_name, (char *) NULL);
    fprintf(stderr, "Failed to start application\n");
    return 0;
}
