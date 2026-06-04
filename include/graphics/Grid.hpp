// include/graphics/Grid.hpp
#pragma once
#include <stdint.h>

struct Point {
    int x;
    int y;
};

class DesktopGrid {
public:
    static void init(int screen_width, int screen_height, int cell_size = 64, int spacing = 20, int top_margin = 40);
    
    static Point get_slot_position(int index);

private:
    static int m_screen_width;
    static int m_screen_height;
    static int m_cell_size;
    static int m_spacing;
    static int m_top_margin;
    static int m_cols;
};