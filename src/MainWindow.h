#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QMouseEvent>

class Live2DWidget;
class LLMClient;
class ChatOverlay;
class SystemController;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onChatInput();
    void onLLMResponse(const QString &response);
    void onLLMError(const QString &error);

private:
    bool m_dragging = false;
    QPoint m_dragPosition;

    Live2DWidget *m_live2dWidget;
    LLMClient *m_llmClient;
    ChatOverlay *m_chatOverlay;
    SystemController *m_systemController;
};

#endif // MAINWINDOW_H
