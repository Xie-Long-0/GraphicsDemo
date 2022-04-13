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

	void setAction(xActionPreviewInterface *action);
	qreal scaleFactor() const { return transform().m11(); }
	void resizeScene();

public slots:
	void finishAction();
	void cancelAction();
	void setPixmap(const QPixmap &pixmap);
	void setImage(const QImage &image) { setPixmap(QPixmap::fromImage(image)); }
	void zoomIn();
	void zoomOut();
	void zoomByFactor(qreal factor);

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
