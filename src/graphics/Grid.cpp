#include <graphics/Grid.hpp>

int DesktopGrid::m_screen_width = 0;
int DesktopGrid::m_screen_height = 0;
int DesktopGrid::m_cell_size = 0;
int DesktopGrid::m_spacing = 0;
int DesktopGrid::m_top_margin = 0;
int DesktopGrid::m_cols = 0;

void DesktopGrid::init(int screen_width, int screen_height, int cell_size, int spacing, int top_margin) {
    m_screen_width = screen_width;
    m_screen_height = screen_height;
    m_cell_size = cell_size;
    m_spacing = spacing;
    m_top_margin = top_margin;
    
    int slot_size = m_cell_size + m_spacing;
    
    m_cols = (m_screen_width - m_spacing) / slot_size;
}

Point DesktopGrid::get_slot_position(int index) {
    Point p = {0, 0};
    int slot_size = m_cell_size + m_spacing;
    
    int col = index % m_cols;
    int row = index / m_cols;
    
    p.x = m_spacing + (col * slot_size);
    p.y = m_top_margin + m_spacing + (row * slot_size);
    
    return p;
}