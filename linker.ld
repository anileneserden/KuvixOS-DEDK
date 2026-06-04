/* linker.ld - KuvixOS DEDK V2 Linker Script */
ENTRY(_start)

SECTIONS
{
    /* * Kodumuzun RAM'de başlayacağı sanal adres. 
     * Tamamen pozisyondan bağımsız (freestanding) veya loader'ın 
     * yükleyeceği dinamik adrese uyum sağlaması için genellikle 0x0'dan başlatılır.
     */
    . = 0x0;

    /* Kod Bölümü (Kodun ilk byte'ında _start olmalı) */
    .text : ALIGN(4)
    {
        *(.text._start)  /* Eğer derleyici özel etiketlediyse önce _start */
        *(.text)
        *(.text.*)
    }

    /* Salt Okunur Veriler (String sabitleri, sabit değişkenler) */
    .rodata : ALIGN(4)
    {
        *(.rodata)
        *(.rodata.*)
    }

    /* Okunabilir/Yazılabilir Ön Tanımlı Veriler (Global değişkenler) */
    .data : ALIGN(4)
    {
        *(.data)
        *(.data.*)
    }

    /* Ön Tanımlı Olmayan Veriler (Hafızada sıfırlanacak global değişkenler) */
    .bss : ALIGN(4)
    {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    }

    /* Geri kalan gereksiz bölümleri atıyoruz (Binary boyutunu küçültmek için) */
    /DISCARD/ :
    {
        *(.comment)
        *(.eh_frame)
        *(.note.GNU-stack)
    }
}