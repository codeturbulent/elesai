#ifndef LLMCLIENT_H
#define LLMCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

class LLMClient : public QObject {
    Q_OBJECT

public:
    explicit LLMClient(QObject *parent = nullptr);
    void sendMessage(const QString &message);
    void setApiKey(const QString &apiKey);
    void setApiUrl(const QString &apiUrl);

signals:
    void responseReceived(const QString &response);
    void errorOccurred(const QString &error);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
    QString m_apiKey;
    QString m_apiUrl;
};

#endif // LLMCLIENT_H
