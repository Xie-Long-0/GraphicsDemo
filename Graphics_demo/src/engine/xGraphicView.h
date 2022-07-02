#pragma once

#include <QGraphicsView>

class xActionInterface;
class xActionPreviewInterface;
class xActionDefault;

class xGraphicView : public QGraphicsView
{
	Q_OBJECT

public:
	xGraphicView(QGraphicsScene *scene, QWidget *parent);
	~xGraphicView();

	// 设置新的Action，将会把上一个Action结束并释放
	void setAction(xActionPreviewInterface *action);
	// 返回视图缩放比例
	qreal scaleFactor() const noexcept { return transform().m11(); }
	// 调整缩放大小到自适应界面
	void resizeScene();

public slots:
	void finishAction();
	void cancelAction();
	void setPixmap(const QPixmap &pixmap);
	void setImage(const QImage &image) { setPixmap(QPixmap::fromImage(image)); }
	void zoomIn();
	void zoomOut();
	void zoomByFactor(qreal factor);

signals:
	// 可用于接收图元计算任务返回的结果并传到上层界面
	void calcFinished(bool suc);

private:
	void mousePressEvent(QMouseEvent *e) override;
	void mouseMoveEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void wheelEvent(QWheelEvent *e) override;
	void keyPressEvent(QKeyEvent *e) override;
	void mouseDoubleClickEvent(QMouseEvent *e) override;
	void onScaleChanged();

private:
	xActionPreviewInterface *m_action = nullptr;
	xActionDefault *m_default = nullptr;
	QGraphicsPixmapItem *m_pixmap = nullptr;
	qreal m_initFactor = 0.0;
};
