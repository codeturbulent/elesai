#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <QObject>
#include <QString>
#include <QProcess>

class SystemController : public QObject {
    Q_OBJECT

public:
    explicit SystemController(QObject *parent = nullptr);
    void processCommand(const QString &rawResponse);

private:
    void executeCommand(const QString &command);
    void executeScript(const QString &scriptContent);

private:
    QProcess *m_process;
};

#endif // SYSTEMCONTROLLER_H
