#include "configurationparser.h"

ConfigurationParser::ConfigurationParser(QObject* parent) : QObject(parent)
{
}

bool ConfigurationParser::readConfiguration(const QString& configurationFile)
{
    auto configuration = readFile(configurationFile);

    if (!configuration.has_value())
    {
        return false;
    }

    if (!readItems(configuration.value()))
    {
        return false;
    }

    readTheme(configuration.value());
    return true;
}

std::vector<ConfigurationParser::Item> ConfigurationParser::items() const
{
    return m_items;
}

ConfigurationParser::Theme ConfigurationParser::theme() const
{
    return m_theme;
}

std::optional<QJsonDocument> ConfigurationParser::readFile(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        return std::nullopt;
    }
    return QJsonDocument::fromJson(file.readAll());
}

bool ConfigurationParser::readItems(const QJsonDocument& file)
{
    auto array = file.object().value("items").toArray();

    if (array.isEmpty())
    {
        return false;
    }

    for (const auto& item : array)
    {
        const auto obj = item.toObject();
        const auto icon = obj.value("icon").toString();
        const auto program = obj.value("executable").toString();
        const auto cliParameters = obj.value("cliParameters").toString();
        const auto workingDirectory = obj.value("workingDirectory").toString();
        m_items.push_back(Item{icon, program, cliParameters, workingDirectory});
    }
    return true;
}

void ConfigurationParser::readTheme(const QJsonDocument& file)
{
    auto theme = file.object().value("theme").toObject();
    m_theme.backgroundColor = theme.value("background-color").toString(m_theme.backgroundColor);
    m_theme.selectedColor = theme.value("selected-color").toString(m_theme.selectedColor);
    m_theme.notSelectedColor = theme.value("not-selected-color").toString(m_theme.notSelectedColor);
}
