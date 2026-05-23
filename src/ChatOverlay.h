#ifndef CHATOVERLAY_H
#define CHATOVERLAY_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

class ChatOverlay : public QWidget {
    Q_OBJECT

public:
    explicit ChatOverlay(QWidget *parent = nullptr);
    void setResponse(const QString &text);
    QString getInputText();
    void clearInput();

signals:
    void returnPressed();

private:
    QLineEdit *m_inputField;
    QLabel *m_responseLabel;
};

#endif // CHATOVERLAY_H
