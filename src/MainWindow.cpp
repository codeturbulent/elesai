#include "MainWindow.h"
#include "Live2DWidget.h"
#include "LLMClient.h"
#include "ChatOverlay.h"
#include "SystemController.h"
#include <QApplication>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    
    // Set frameless and transparent attributes
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    
    // Set initial size
    resize(400, 700);
    
    // Set Live2DWidget as central widget
    m_live2dWidget = new Live2DWidget(this);
    setCentralWidget(m_live2dWidget);

    // Initialize Chat Overlay
    m_chatOverlay = new ChatOverlay(this);
    m_chatOverlay->show();

    // Initialize LLM Client
    m_llmClient = new LLMClient(this);
    m_llmClient->setApiUrl("https://api.openai.com/v1/chat/completions"); 
    m_llmClient->setApiKey("YOUR_API_KEY_HERE"); 

    // Initialize System Controller
    m_systemController = new SystemController(this);

    // Connections
    connect(m_chatOverlay, &ChatOverlay::returnPressed, this, &MainWindow::onChatInput);
    connect(m_llmClient, &LLMClient::responseReceived, this, &MainWindow::onLLMResponse);
    connect(m_llmClient, &LLMClient::errorOccurred, this, &MainWindow::onLLMError);
}

MainWindow::~MainWindow() {}

void MainWindow::onChatInput() {
    QString text = m_chatOverlay->getInputText();
    if (!text.isEmpty()) {
        m_chatOverlay->setResponse("Thinking...");
        m_llmClient->sendMessage(text);
        m_chatOverlay->clearInput();
    }
}

void MainWindow::onLLMResponse(const QString &response) {
    m_chatOverlay->setResponse(response);
    
    // Parse and execute system commands
    m_systemController->processCommand(response);
}

void MainWindow::onLLMError(const QString &error) {
    m_chatOverlay->setResponse("Error: " + error);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    if (m_chatOverlay) {
        m_chatOverlay->setGeometry(10, height() - 150, width() - 20, 140);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragging = true;
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    m_dragging = false;
    event->accept();
}
