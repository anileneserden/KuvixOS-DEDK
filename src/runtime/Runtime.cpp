// src/runtime/Runtime.cpp
#include <stdint.h>

extern "C" {

    void __cxa_pure_virtual() {
        while (1) {
            asm volatile("hlt");
        }
    }

    int __cxa_atexit(void (*destructor)(void *), void *arg, void *dso_handle) {
        (void)destructor;
        (void)arg;
        (void)dso_handle;
        return 0;
    }

    void* __dso_handle = 0;
}