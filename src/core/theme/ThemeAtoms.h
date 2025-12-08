#ifndef THEMEATOMS_H
#define THEMEATOMS_H

#include <QObject>
#include <QColor>

// ===== COLOR PALETTE =====
// Groupe toutes les couleurs de base
class ColorAtom : public QObject {
    Q_OBJECT
    
    // Backgrounds
    Q_PROPERTY(QColor bgPrimary MEMBER m_bgPrimary NOTIFY changed)
    Q_PROPERTY(QColor bgSecondary MEMBER m_bgSecondary NOTIFY changed)
    Q_PROPERTY(QColor bgTertiary MEMBER m_bgTertiary NOTIFY changed)
    
    // Surface (States)
    Q_PROPERTY(QColor surfPrimary MEMBER m_surfPrimary NOTIFY changed)
    Q_PROPERTY(QColor surfSecondary MEMBER m_surfSecondary NOTIFY changed)
    Q_PROPERTY(QColor surfHover MEMBER m_surfHover NOTIFY changed)
    Q_PROPERTY(QColor surfActive MEMBER m_surfActive NOTIFY changed)
    Q_PROPERTY(QColor surfDisabled MEMBER m_surfDisabled NOTIFY changed)

    // Primary Action
    Q_PROPERTY(QColor primBase MEMBER m_primBase NOTIFY changed)
    Q_PROPERTY(QColor primHover MEMBER m_primHover NOTIFY changed)
    Q_PROPERTY(QColor primActive MEMBER m_primActive NOTIFY changed)
    Q_PROPERTY(QColor primDisabled MEMBER m_primDisabled NOTIFY changed)

    // Text
    Q_PROPERTY(QColor textPrimary MEMBER m_textPrimary NOTIFY changed)
    Q_PROPERTY(QColor textSecondary MEMBER m_textSecondary NOTIFY changed)
    Q_PROPERTY(QColor textTertiary MEMBER m_textTertiary NOTIFY changed)
    Q_PROPERTY(QColor textDisabled MEMBER m_textDisabled NOTIFY changed)
    Q_PROPERTY(QColor textOnPrimary MEMBER m_textOnPrimary NOTIFY changed)

    // Border
    Q_PROPERTY(QColor borderPrimary MEMBER m_borderPrimary NOTIFY changed)
    Q_PROPERTY(QColor borderSecondary MEMBER m_borderSecondary NOTIFY changed)
    Q_PROPERTY(QColor borderFocus MEMBER m_borderFocus NOTIFY changed)
    Q_PROPERTY(QColor borderDisabled MEMBER m_borderDisabled NOTIFY changed)

    // Accent
    Q_PROPERTY(QColor accentBase MEMBER m_accentBase NOTIFY changed)
    Q_PROPERTY(QColor accentHover MEMBER m_accentHover NOTIFY changed)
    Q_PROPERTY(QColor accentActive MEMBER m_accentActive NOTIFY changed)

    // Status
    Q_PROPERTY(QColor statError MEMBER m_statError NOTIFY changed)
    Q_PROPERTY(QColor statErrorHover MEMBER m_statErrorHover NOTIFY changed)
    Q_PROPERTY(QColor statSuccess MEMBER m_statSuccess NOTIFY changed)
    Q_PROPERTY(QColor statSuccessHover MEMBER m_statSuccessHover NOTIFY changed)
    Q_PROPERTY(QColor statWarning MEMBER m_statWarning NOTIFY changed)
    Q_PROPERTY(QColor statWarningHover MEMBER m_statWarningHover NOTIFY changed)
    Q_PROPERTY(QColor statInfo MEMBER m_statInfo NOTIFY changed)
    Q_PROPERTY(QColor statInfoHover MEMBER m_statInfoHover NOTIFY changed)

public:
    explicit ColorAtom(QObject *parent = nullptr) : QObject(parent) {}
    
    // Valeurs par défaut (Dark Theme Legacy)
    QColor m_bgPrimary{"#1e1e1e"};
    QColor m_bgSecondary{"#252525"};
    QColor m_bgTertiary{"#2a2a2a"};

    QColor m_surfPrimary{"#2d2d2d"};
    QColor m_surfSecondary{"#353535"};
    QColor m_surfHover{"#3d3d3d"};
    QColor m_surfActive{"#4d4d4d"};
    QColor m_surfDisabled{"#252525"};

    QColor m_primBase{"#0d7377"};
    QColor m_primHover{"#14a0a5"};
    QColor m_primActive{"#0a5b5e"};
    QColor m_primDisabled{"#084648"};

    QColor m_textPrimary{"#ffffff"};
    QColor m_textSecondary{"#b0b0b0"};
    QColor m_textTertiary{"#808080"};
    QColor m_textDisabled{"#666666"};
    QColor m_textOnPrimary{"#ffffff"};

    QColor m_borderPrimary{"#3d3d3d"};
    QColor m_borderSecondary{"#454545"};
    QColor m_borderFocus{"#4a9eff"};
    QColor m_borderDisabled{"#2d2d2d"};

    QColor m_accentBase{"#4a9eff"};
    QColor m_accentHover{"#6bb0ff"};
    QColor m_accentActive{"#2a7edf"};

    QColor m_statError{"#f44336"};
    QColor m_statErrorHover{"#f55a4e"};
    QColor m_statSuccess{"#4caf50"};
    QColor m_statSuccessHover{"#66bb6a"};
    QColor m_statWarning{"#ff9800"};
    QColor m_statWarningHover{"#ffa726"};
    QColor m_statInfo{"#2196f3"};
    QColor m_statInfoHover{"#42a5f5"};

signals:
    void changed();
};

// ===== SIZE ATOM =====
// Dimensions brutes (base 100%)
class SizeAtom : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(int none MEMBER m_none NOTIFY changed)
    Q_PROPERTY(int xxsmall MEMBER m_xxsmall NOTIFY changed)
    Q_PROPERTY(int xsmall MEMBER m_xsmall NOTIFY changed)
    Q_PROPERTY(int small MEMBER m_small NOTIFY changed)
    Q_PROPERTY(int medium MEMBER m_medium NOTIFY changed)
    Q_PROPERTY(int large MEMBER m_large NOTIFY changed)
    Q_PROPERTY(int xlarge MEMBER m_xlarge NOTIFY changed)
    Q_PROPERTY(int xxlarge MEMBER m_xxlarge NOTIFY changed)
    Q_PROPERTY(int xxxlarge MEMBER m_xxxlarge NOTIFY changed)

public:
    explicit SizeAtom(QObject *parent = nullptr) : QObject(parent) {}
    
    int m_none{0};
    int m_xxsmall{2};
    int m_xsmall{4};
    int m_small{5};
    int m_medium{10};
    int m_large{15};
    int m_xlarge{20};
    int m_xxlarge{30};
    int m_xxxlarge{40};

signals:
    void changed();
};

// ===== WEIGHT ATOM =====
class WeightAtom : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(int light MEMBER m_light CONSTANT)
    Q_PROPERTY(int normal MEMBER m_normal CONSTANT)
    Q_PROPERTY(int medium MEMBER m_medium CONSTANT)
    Q_PROPERTY(int semibold MEMBER m_semibold CONSTANT)
    Q_PROPERTY(int bold MEMBER m_bold CONSTANT)

public:
    explicit WeightAtom(QObject *parent = nullptr) : QObject(parent) {}
    
    int m_light{300};
    int m_normal{400};
    int m_medium{500};
    int m_semibold{600};
    int m_bold{700};
};

// ===== ANIMATION ATOM (Nouveau) =====
class AnimationAtom : public QObject {
    Q_OBJECT
    Q_PROPERTY(int instant MEMBER m_instant CONSTANT)
    Q_PROPERTY(int fast MEMBER m_fast CONSTANT)
    Q_PROPERTY(int normal MEMBER m_normal CONSTANT)
    Q_PROPERTY(int slow MEMBER m_slow CONSTANT)

public:
    explicit AnimationAtom(QObject *parent = nullptr) : QObject(parent) {}
    int m_instant{0};
    int m_fast{50};
    int m_normal{150};
    int m_slow{300};
};

#endif // THEMEATOMS_H