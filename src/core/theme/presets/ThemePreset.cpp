#include "ThemePreset.h"

ThemePreset::ThemePreset(const QString& themeName, ThemeManager* manager)
    : name(themeName)
{
    colors = new ThemeColors(nullptr);
    spacing = new ThemeSpacing(manager, nullptr);
    font = new ThemeFont(manager, nullptr);
    border = new ThemeBorder(manager, nullptr);
    size = new ThemeSize(manager, nullptr);
    transition = new ThemeTransition(nullptr);
    components = new ThemeComponents(manager, nullptr);
}

ThemePreset::~ThemePreset() {
    delete colors;
    delete spacing;
    delete font;
    delete border;
    delete size;
    delete transition;
    delete components;
}

void ThemePreset::loadFromJson(const QJsonObject& json) {
    if (json.contains("name")) name = json["name"].toString();
    if (json.contains("colors")) colors->loadFromJson(json["colors"].toObject());
    if (json.contains("spacing")) spacing->loadFromJson(json["spacing"].toObject());
    if (json.contains("font")) font->loadFromJson(json["font"].toObject());
    if (json.contains("border")) border->loadFromJson(json["border"].toObject());
    if (json.contains("size")) size->loadFromJson(json["size"].toObject());
    if (json.contains("transition")) transition->loadFromJson(json["transition"].toObject());
    if (json.contains("components")) components->loadFromJson(json["components"].toObject());
}

QJsonObject ThemePreset::toJson() const {
    QJsonObject json;
    json["name"] = name;
    json["version"] = "3.0";
    json["colors"] = colors->toJson();
    json["spacing"] = spacing->toJson();
    json["font"] = font->toJson();
    json["border"] = border->toJson();
    json["size"] = size->toJson();
    json["transition"] = transition->toJson();
    json["components"] = components->toJson();
    return json;
}

void ThemePreset::copyFrom(const ThemePreset* other) {
    name = other->name;
    colors->copyFrom(other->colors);
    spacing->copyFrom(other->spacing);
    font->copyFrom(other->font);
    border->copyFrom(other->border);
    size->copyFrom(other->size);
    transition->copyFrom(other->transition);
    components->copyFrom(other->components);
}