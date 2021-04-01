#include "systemapi.h"
#include <QDebug>
void SystemApi::startProcess(const QString& command, const QString& cliParameters, const QString& workingDirectory)
{
    qDebug() << command << cliParameters;
    QProcess p;
    p.setProgram(command);

    if (!cliParameters.isEmpty())
        p.setArguments(cliParameters.split(" "));

    if (!workingDirectory.isEmpty())
        p.setWorkingDirectory(workingDirectory);

    p.startDetached();
}
