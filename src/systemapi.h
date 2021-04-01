#pragma once

#include <QObject>
#include <QProcess>

class SystemApi : public QObject
{
public:
    static void startProcess(const QString& command,
            const QString& cliParameters,
            const QString& workingDirectory);
};
