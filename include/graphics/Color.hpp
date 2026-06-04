// include/graphics/Color.hpp
#pragma once
#include <stdint.h>

namespace Color {
    // 32-bit ARGB Renk Sabitleri
    const uint32_t Transparent = 0x00000000;
    const uint32_t Black       = 0xFF000000;
    const uint32_t White       = 0xFFFFFFFF;
    const uint32_t Red         = 0xFFFF0000;
    const uint32_t Green       = 0xFF00FF00;
    const uint32_t Blue        = 0xFF0000FF;
    
    // KuvixOS V2 Kurumsal Renk Paleti (Örnek Tasarım)
    const uint32_t Background  = 0xFF1A2B3C; // Kuvix Gece Mavisi
    const uint32_t Panel       = 0xFF243447; // Hafif açık panel rengi
    const uint32_t Text        = 0xFFE1E8ED; // Göz yormayan beyaz
    const uint32_t Accent      = 0xFF3B82F6; // Odaklanma mavisi
}