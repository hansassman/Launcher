#pragma once

#include "systemapi.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

#include <optional>
#include <vector>

class ConfigurationParser : public QObject
{
    Q_OBJECT

public:
    struct Item
    {
        QString icon;
        QString program;
        QString cliParameters;
        QString workingDirectory;
    };

    struct Theme
    {
        QString backgroundColor = "#333333";
        QString selectedColor = "#111111";
        QString notSelectedColor = "#333333";
    };

    explicit ConfigurationParser(QObject* parent = nullptr);

    bool readConfiguration(const QString& configurationFile);
    std::vector<Item> items() const;
    Theme theme() const;

private:
    std::optional<QJsonDocument> readFile(const QString& path);
    bool readItems(const QJsonDocument& file);
    void readTheme(const QJsonDocument& file);
    void readSize(const QJsonDocument& file);

    std::vector<Item> m_items;
    Theme m_theme;
};
