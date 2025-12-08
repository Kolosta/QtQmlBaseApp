#ifndef THEMEMOLECULES_H
#define THEMEMOLECULES_H

#include <QObject>
#include <QColor>
#include "ThemeAtoms.h"

class ThemeManager;

// ===== SURFACE (Background + Spacing + Radius) =====
class SurfaceMolecule : public QObject {
    Q_OBJECT
    // Accès aux couleurs brutes
    Q_PROPERTY(ColorAtom* color READ color CONSTANT)
    
    // Spacing Scalé
    Q_PROPERTY(int spacingNone READ spacingNone NOTIFY changed)
    Q_PROPERTY(int spacingXxsmall READ spacingXxsmall NOTIFY changed)
    Q_PROPERTY(int spacingXsmall READ spacingXsmall NOTIFY changed)
    Q_PROPERTY(int spacingSmall READ spacingSmall NOTIFY changed)
    Q_PROPERTY(int spacingMedium READ spacingMedium NOTIFY changed)
    Q_PROPERTY(int spacingLarge READ spacingLarge NOTIFY changed)
    Q_PROPERTY(int spacingXlarge READ spacingXlarge NOTIFY changed)
    Q_PROPERTY(int spacingXxlarge READ spacingXxlarge NOTIFY changed)
    Q_PROPERTY(int spacingXxxlarge READ spacingXxxlarge NOTIFY changed)

    // Radius Scalé
    Q_PROPERTY(int radiusNone READ radiusNone NOTIFY changed)
    Q_PROPERTY(int radiusSmall READ radiusSmall NOTIFY changed)
    Q_PROPERTY(int radiusMedium READ radiusMedium NOTIFY changed)
    Q_PROPERTY(int radiusLarge READ radiusLarge NOTIFY changed)
    Q_PROPERTY(int radiusXlarge READ radiusXlarge NOTIFY changed)
    Q_PROPERTY(int radiusRound READ radiusRound NOTIFY changed)

public:
    explicit SurfaceMolecule(ColorAtom* colorAtom, SizeAtom* sizeAtom, 
                             ThemeManager* manager, QObject *parent = nullptr);
    
    ColorAtom* color() const { return m_colorAtom; }
    
    int spacingNone() const;
    int spacingXxsmall() const;
    int spacingXsmall() const;
    int spacingSmall() const;
    int spacingMedium() const;
    int spacingLarge() const;
    int spacingXlarge() const;
    int spacingXxlarge() const;
    int spacingXxxlarge() const;

    int radiusNone() const;
    int radiusSmall() const;
    int radiusMedium() const;
    int radiusLarge() const;
    int radiusXlarge() const;
    int radiusRound() const;

signals:
    void changed();

private:
    ColorAtom* m_colorAtom;
    SizeAtom* m_sizeAtom;
    ThemeManager* m_manager;
};

// ===== FONT (Size + Weight + Color) =====
class FontMolecule : public QObject {
    Q_OBJECT
    Q_PROPERTY(ColorAtom* color READ color CONSTANT)
    Q_PROPERTY(WeightAtom* weight READ weight CONSTANT)
    
    // Sizes Scalées
    Q_PROPERTY(int sizeXsmall READ sizeXsmall NOTIFY changed)
    Q_PROPERTY(int sizeSmall READ sizeSmall NOTIFY changed)
    Q_PROPERTY(int sizeMedium READ sizeMedium NOTIFY changed)
    Q_PROPERTY(int sizeLarge READ sizeLarge NOTIFY changed)
    Q_PROPERTY(int sizeXlarge READ sizeXlarge NOTIFY changed)
    Q_PROPERTY(int sizeXxlarge READ sizeXxlarge NOTIFY changed)
    Q_PROPERTY(int sizeXxxlarge READ sizeXxxlarge NOTIFY changed)
    Q_PROPERTY(int sizeTitle READ sizeTitle NOTIFY changed) // Alias pratique

public:
    explicit FontMolecule(ColorAtom* colorAtom, WeightAtom* weightAtom,
                          SizeAtom* sizeAtom, ThemeManager* manager, 
                          QObject *parent = nullptr);
    
    ColorAtom* color() const { return m_colorAtom; }
    WeightAtom* weight() const { return m_weightAtom; }
    
    int sizeXsmall() const;
    int sizeSmall() const;
    int sizeMedium() const;
    int sizeLarge() const;
    int sizeXlarge() const;
    int sizeXxlarge() const;
    int sizeXxxlarge() const;
    int sizeTitle() const;

signals:
    void changed();
private:
    ColorAtom* m_colorAtom;
    WeightAtom* m_weightAtom;
    SizeAtom* m_sizeAtom;
    ThemeManager* m_manager;
};

// ===== BORDER =====
class BorderMolecule : public QObject {
    Q_OBJECT
    
    // Theme.border.color.primary
    Q_PROPERTY(ColorAtom* color READ color CONSTANT)
    
    // Theme.border.width.thin (scalé)
    Q_PROPERTY(int widthNone READ widthNone NOTIFY changed)
    Q_PROPERTY(int widthThin READ widthThin NOTIFY changed)
    Q_PROPERTY(int widthMedium READ widthMedium NOTIFY changed)
    Q_PROPERTY(int widthThick READ widthThick NOTIFY changed)

public:
    explicit BorderMolecule(ColorAtom* colorAtom, SizeAtom* sizeAtom,
                           ThemeManager* manager, QObject *parent = nullptr);
    
    ColorAtom* color() const { return m_colorAtom; }
    
    int widthNone() const { return 0; }
    int widthThin() const;
    int widthMedium() const;
    int widthThick() const;

signals:
    void changed();

private:
    ColorAtom* m_colorAtom;
    SizeAtom* m_sizeAtom;
    ThemeManager* m_manager;
};

// ===== ANIMATION MOLECULE =====
class AnimationMolecule : public QObject {
    Q_OBJECT
    Q_PROPERTY(int instant READ instant CONSTANT)
    Q_PROPERTY(int fast READ fast CONSTANT)
    Q_PROPERTY(int normal READ normal CONSTANT)
    Q_PROPERTY(int slow READ slow CONSTANT)

public:
    explicit AnimationMolecule(AnimationAtom* animAtom, QObject *parent = nullptr) 
        : QObject(parent), m_atom(animAtom) {}

    int instant() const { return m_atom->m_instant; }
    int fast() const { return m_atom->m_fast; }
    int normal() const { return m_atom->m_normal; }
    int slow() const { return m_atom->m_slow; }

private:
    AnimationAtom* m_atom;
};

#endif // THEMEMOLECULES_H