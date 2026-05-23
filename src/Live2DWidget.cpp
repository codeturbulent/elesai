#include "Live2DWidget.h"
#include "Live2DManager.h"

Live2DWidget::Live2DWidget(QWidget *parent)
    : QOpenGLWidget(parent), m_manager(nullptr) {
    
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&Live2DWidget::update));
    m_timer->start(16); // ~60 FPS
}

Live2DWidget::~Live2DWidget() {
    // Manager cleanup
}

void Live2DWidget::initializeGL() {
    initializeOpenGLFunctions();
    
    glEnable(Qt::WA_TranslucentBackground);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // Initialize Live2D Manager here once SDK is present
    // m_manager = new Live2DManager();
    // m_manager->init();
}

void Live2DWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void Live2DWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (m_manager) {
        // m_manager->render();
    }
}
