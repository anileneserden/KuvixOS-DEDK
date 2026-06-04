// src/runtime/Runtime.cpp
#include <stdint.h>

/**
 * g++ derleyicisinin freestanding C++ derlerken ihtiyaç duyduğu 
 * temel runtime (çalışma zamanı) stub fonksiyonları.
 */
extern "C" {

    // Saf sanal bir fonksiyon (pure virtual) çağrıldığında ama gövdesi bulunamadığında
    // derleyicinin panikleyip zıplayacağı yer. Sistemi sonsuz döngüye alıp kilitliyoruz.
    void __cxa_pure_virtual() {
        while (1) {
            asm volatile("hlt");
        }
    }

    // Dinamik nesne yıkıcıları (destructors) için kayıt mekanizması.
    // Biz şu an dinamik bellek yönetimini (new/delete) kernel seviyesinde elle 
    // yöneteceğimiz için bu fonksiyonun sadece 0 dönmesi derleyiciyi tatmin eder.
    int __cxa_atexit(void (*destructor)(void *), void *arg, void *dso_handle) {
        (void)destructor;
        (void)arg;
        (void)dso_handle;
        return 0;
    }

    // DSO (Dynamic Shared Object) tutamacı için boş bir sembol.
    void* __dso_handle = 0;
}