#include "mainwindow.h"

MainWindow::MainWindow(const QString& configurationFile, QWidget* parent) : QMainWindow(parent)
{
    if (!m_configurationParser.readConfiguration(configurationFile))
    {
        exitProgram(1);
    }

    auto theme = m_configurationParser.theme();

    m_selectedItemStyle = m_selectedItemStyle.arg(theme.selectedColor);
    m_notSelectedItemStyle = m_notSelectedItemStyle.arg(theme.notSelectedColor);
    m_backgroundStyle = m_backgroundStyle.arg(theme.backgroundColor);

    createItems();

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedHeight(m_size);
    setFixedWidth(m_items.size() * m_size);

    installEventFilter(this);
}

void MainWindow::createItems()
{
    const auto items = m_configurationParser.items();

    for (size_t index = 0; index < items.size(); ++index)
    {
        const auto& item = items.at(index);
        auto& label = m_items.emplace_back(std::make_unique<QLabel>(this));
        label->setGeometry(m_size * index, 0, m_size, m_size);
        label->setPixmap(QPixmap(item.icon).scaled(
                m_iconSize, m_iconSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(!index ? m_selectedItemStyle : m_notSelectedItemStyle);
        label->setProperty("executable", item.program);
        label->setProperty("cliParameters", item.cliParameters);
        label->setProperty("workingDirectory", item.workingDirectory);
        m_layout.addWidget(label.get());
    }

    m_centralWidget.setStyleSheet(m_backgroundStyle);
    m_centralWidget.setLayout(&m_layout);
    setCentralWidget(&m_centralWidget);
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    Q_UNUSED(obj)

    if (event->type() == QEvent::WindowDeactivate)
    {
        exit(0);
    }

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key())
        {
        case Qt::Key_Left:
            decrementIndex();
            break;
        case Qt::Key_Right:
            incrementIndex();
            break;
        case Qt::Key_Tab:
            incrementIndex();
            break;
        case Qt::Key_Return:
            launch();
            break;
        case Qt::Key_Escape:
            exitProgram(0);
            break;
        }
    }
    return false;
}

void MainWindow::incrementIndex()
{
    m_items.at(m_currentIndex)->setStyleSheet(m_notSelectedItemStyle);
    if (++m_currentIndex >= (int) m_items.size())
    {
        m_currentIndex = 0;
    }
    m_items.at(m_currentIndex)->setStyleSheet(m_selectedItemStyle);
}

void MainWindow::decrementIndex()
{
    m_items.at(m_currentIndex)->setStyleSheet(m_notSelectedItemStyle);
    if (--m_currentIndex < 0)
    {
        m_currentIndex = m_items.size() - 1;
    }
    m_items.at(m_currentIndex)->setStyleSheet(m_selectedItemStyle);
}

void MainWindow::exitProgram(int code)
{
    exit(code);
}

void MainWindow::launch()
{
    const auto executable = m_items.at(m_currentIndex)->property("executable").toString();
    const auto cliParameters = m_items.at(m_currentIndex)->property("cliParameters").toString();
    const auto workingDirectory = m_items.at(m_currentIndex)->property("workingDirectory").toString();
    SystemApi::startProcess(executable, cliParameters, workingDirectory);
    exitProgram(0);
}
