#include "ChatOverlay.h"

ChatOverlay::ChatOverlay(QWidget *parent)
    : QWidget(parent) {
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    m_responseLabel = new QLabel("Hello! Type something below to talk to me.", this);
    m_responseLabel->setWordWrap(true);
    m_responseLabel->setStyleSheet("color: white; background-color: rgba(0, 0, 0, 150); padding: 10px; border-radius: 5px;");
    
    m_inputField = new QLineEdit(this);
    m_inputField->setPlaceholderText("Say something...");
    m_inputField->setStyleSheet("background-color: rgba(255, 255, 255, 200); padding: 5px; border-radius: 3px;");
    
    layout->addWidget(m_responseLabel);
    layout->addWidget(m_inputField);
    layout->addStretch();
    
    connect(m_inputField, &QLineEdit::returnPressed, this, &ChatOverlay::returnPressed);
    
    // Transparent background for the widget itself
    setAttribute(Qt::WA_TranslucentBackground);
}

void ChatOverlay::setResponse(const QString &text) {
    m_responseLabel->setText(text);
}

QString ChatOverlay::getInputText() {
    return m_inputField->text();
}

void ChatOverlay::clearInput() {
    m_inputField->clear();
}
