#include "SizeValue.h"
#include "core/ThemeManager.h"
#include <cmath>

int SizeValue::scaled() const {
    return static_cast<int>(std::round(m_baseValue * m_manager->scale()));
}