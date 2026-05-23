#include "SystemController.h"
#include <QRegularExpression>
#include <QDebug>
#include <QTemporaryFile>
#include <QTextStream>

SystemController::SystemController(QObject *parent)
    : QObject(parent), m_process(new QProcess(this)) {}

void SystemController::processCommand(const QString &rawResponse) {
    // Parse <cmd> tags
    QRegularExpression cmdRegex("<cmd>(.*?)</cmd>");
    QRegularExpressionMatchIterator i = cmdRegex.globalMatch(rawResponse);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString command = match.captured(1);
        executeCommand(command);
    }

    // Parse <script> tags
    QRegularExpression scriptRegex("<script>(.*?)</script>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator si = scriptRegex.globalMatch(rawResponse);
    while (si.hasNext()) {
        QRegularExpressionMatch match = si.next();
        QString script = match.captured(1);
        executeScript(script);
    }
}

void SystemController::executeCommand(const QString &command) {
    qDebug() << "Executing command:" << command;
    // For safety, you might want to whitelist commands here
    m_process->startCommand(command);
}

void SystemController::executeScript(const QString &scriptContent) {
    qDebug() << "Executing script...";
    
    QTemporaryFile tempFile;
    if (tempFile.open()) {
        QTextStream out(&tempFile);
        out << scriptContent;
        QString fileName = tempFile.fileName();
        tempFile.close();
        
        // Assuming python for scripts, can be made dynamic
        QProcess::execute("python3", {fileName});
    }
}
