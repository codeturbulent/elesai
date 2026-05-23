#include "LLMClient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>

LLMClient::LLMClient(QObject *parent)
    : QObject(parent), m_networkManager(new QNetworkAccessManager(this)) {
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &LLMClient::onReplyFinished);
}

void LLMClient::setApiKey(const QString &apiKey) {
    m_apiKey = apiKey;
}

void LLMClient::setApiUrl(const QString &apiUrl) {
    m_apiUrl = apiUrl;
}

void LLMClient::sendMessage(const QString &message) {
    if (m_apiUrl.isEmpty()) {
        emit errorOccurred("API URL is not set.");
        return;
    }

    QNetworkRequest request(m_apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_apiKey).toUtf8());

    QJsonObject root;
    root["model"] = "gpt-3.5-turbo"; // Default model

    QJsonArray messages;
    QJsonObject systemMessage;
    systemMessage["role"] = "system";
    systemMessage["content"] = "You are a helpful AI assistant in the form of a cute waifu mascot. "
                                "You can also control the computer if asked. Format commands like <cmd>command</cmd>.";
    messages.append(systemMessage);

    QJsonObject userMessage;
    userMessage["role"] = "user";
    userMessage["content"] = message;
    messages.append(userMessage);

    root["messages"] = messages;

    QJsonDocument doc(root);
    m_networkManager->post(request, doc.toJson());
}

void LLMClient::onReplyFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        QJsonObject root = doc.object();
        QJsonArray choices = root["choices"].toArray();
        if (!choices.isEmpty()) {
            QString content = choices[0].toObject()["message"].toObject()["content"].toString();
            emit responseReceived(content);
        } else {
            emit errorOccurred("Empty response from AI.");
        }
    } else {
        emit errorOccurred(reply->errorString());
    }
    reply->deleteLater();
}
