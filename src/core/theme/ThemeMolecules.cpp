#include "ThemeMolecules.h"
#include "core/ThemeManager.h"
#include <cmath>

// Helper inline pour éviter la répétition
inline int scaled(int raw, qreal scale) {
    return static_cast<int>(std::round(raw * scale));
}

// ===== SURFACE MOLECULE =====
SurfaceMolecule::SurfaceMolecule(ColorAtom* colorAtom, SizeAtom* sizeAtom,
                                 ThemeManager* manager, QObject *parent)
    : QObject(parent), m_colorAtom(colorAtom), m_sizeAtom(sizeAtom), m_manager(manager)
{
}

int SurfaceMolecule::spacingNone() const { 
    return scaled(m_sizeAtom->m_none, m_manager->scale()); 
}
int SurfaceMolecule::spacingXxsmall() const { 
    return scaled(m_sizeAtom->m_xxsmall, m_manager->scale()); 
}
int SurfaceMolecule::spacingXsmall() const { 
    return scaled(m_sizeAtom->m_xsmall, m_manager->scale()); 
}
int SurfaceMolecule::spacingSmall() const { 
    return scaled(m_sizeAtom->m_small, m_manager->scale()); 
}
int SurfaceMolecule::spacingMedium() const { 
    return scaled(m_sizeAtom->m_medium, m_manager->scale()); 
}
int SurfaceMolecule::spacingLarge() const { 
    return scaled(m_sizeAtom->m_large, m_manager->scale()); 
}
int SurfaceMolecule::spacingXlarge() const { 
    return scaled(m_sizeAtom->m_xlarge, m_manager->scale()); 
}
int SurfaceMolecule::spacingXxlarge() const {
    return scaled(m_sizeAtom->m_xxlarge, m_manager->scale());
}
int SurfaceMolecule::spacingXxxlarge() const {
    return scaled(m_sizeAtom->m_xxxlarge, m_manager->scale());
}

int SurfaceMolecule::radiusNone() const {
    return 0;
}
int SurfaceMolecule::radiusSmall() const { 
    return scaled(4, m_manager->scale()); 
}
int SurfaceMolecule::radiusMedium() const { 
    return scaled(6, m_manager->scale()); 
}
int SurfaceMolecule::radiusLarge() const { 
    return scaled(12, m_manager->scale()); 
}
int SurfaceMolecule::radiusXlarge() const {
    return scaled(16, m_manager->scale());
}
int SurfaceMolecule::radiusRound() const {
    return scaled(999, m_manager->scale());
}

// ===== FONT MOLECULE =====
FontMolecule::FontMolecule(ColorAtom* colorAtom, WeightAtom* weightAtom,
                           SizeAtom* sizeAtom, ThemeManager* manager, 
                           QObject *parent)
    : QObject(parent), m_colorAtom(colorAtom), m_weightAtom(weightAtom),
      m_sizeAtom(sizeAtom), m_manager(manager)
{
}

int FontMolecule::sizeXsmall() const { 
    return scaled(10, m_manager->scale()); 
}
int FontMolecule::sizeSmall() const { 
    return scaled(11, m_manager->scale()); 
}
int FontMolecule::sizeMedium() const { 
    return scaled(13, m_manager->scale()); 
}
int FontMolecule::sizeLarge() const { 
    return scaled(16, m_manager->scale()); 
}
int FontMolecule::sizeXlarge() const { 
    return scaled(18, m_manager->scale()); 
}
int FontMolecule::sizeXxlarge() const { 
    return scaled(24, m_manager->scale()); 
}
int FontMolecule::sizeXxxlarge() const {
    return scaled(32, m_manager->scale());
}
int FontMolecule::sizeTitle() const {
    return sizeXlarge();
}

// ===== BORDER MOLECULE =====
BorderMolecule::BorderMolecule(ColorAtom* colorAtom, SizeAtom* sizeAtom,
                               ThemeManager* manager, QObject *parent)
    : QObject(parent), m_colorAtom(colorAtom), m_sizeAtom(sizeAtom), m_manager(manager)
{
}

int BorderMolecule::widthThin() const { 
    return scaled(1, m_manager->scale()); 
}
int BorderMolecule::widthMedium() const { 
    return scaled(2, m_manager->scale()); 
}
int BorderMolecule::widthThick() const { 
    return scaled(3, m_manager->scale()); 
}