#pragma once

#include "configurationparser.h"
#include "systemapi.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>

#include <memory>
#include <vector>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(const QString& configurationFile, QWidget* parent = nullptr);
    virtual bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void createItems();
    void incrementIndex();
    void decrementIndex();
    void exitProgram(int code);
    void launch();

    ConfigurationParser m_configurationParser;
    QHBoxLayout m_layout;
    QWidget m_centralWidget;
    std::vector<std::unique_ptr<QLabel>> m_items;

    int m_currentIndex = 0;

    QString m_backgroundStyle = "QWidget {background-color : %0;}";
    QString m_selectedItemStyle = "QLabel {background-color : %0;}";
    QString m_notSelectedItemStyle = "QLabel {background-color : %0}";

    static constexpr uint m_size = 200;
    static constexpr uint m_iconSize = m_size * 0.8;
};
