#pragma once

#include <QObject>

class xInterCircle;
class xInterArc;

/**
 * @brief ģ����㡢ʶ�������Ĵ���
*/
class RecognizeHandler : public QObject
{
	Q_OBJECT

public:
	explicit RecognizeHandler(QObject *parent = nullptr);
	~RecognizeHandler();

public slots:
	void calcCircle(xInterCircle *ie);
	void calcArc(xInterArc *ie);

signals:
	void calcDone(bool suc);

private:
};
