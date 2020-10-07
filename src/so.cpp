#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <QtCore/QDirIterator>
#include <QtCore/QDebug>

void start_catch();

extern "C" {
    int __libc_start_main(int (*main) (int, char * *, char * *), int argc, char * * ubp_av, void (*init) (void), void (*fini) (void), void (*rtld_fini) (void), void (* stack_end)) {
        start_catch();
        exit(0);
    }
}

void start_catch() {
    QDirIterator iter(":", QDirIterator::Subdirectories);
    while (iter.hasNext()) {
        qDebug() << iter.next();
    }
    remove(getenv("LD_PRELOAD"));
}
