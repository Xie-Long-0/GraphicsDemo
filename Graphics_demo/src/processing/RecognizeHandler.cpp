#include "RecognizeHandler.h"
#include <QThread>

#include "xInterCircle.h"
#include "xCircle.h"
#include "xRegCircle.h"

RecognizeHandler::RecognizeHandler(QObject *parent)
	: QObject(parent)
{
}

RecognizeHandler::~RecognizeHandler()
{
}

void RecognizeHandler::calcCircle(xInterCircle *ic)
{
	if (ic == nullptr)return;

	auto e = ic->getBindEntity();
	if (e == nullptr) return;

	if (e->parentEntity())
		e = e->parentEntity();

	// ģ�����
	QThread::msleep(300);

	if (e->type() == xCircle::Type)
	{
		auto c = static_cast<xCircle *>(e);
		static bool sucess = true;

		if (sucess)
		{
			// TEST
			c->setRadius(c->radius() + 20);

			ic->setText(QString("Circle R: %1").arg(c->radius()));

			c->setStatus(xDef::ES_MeasureOK);
			c->setStyle(xDef::S_Measured);
			ic->setStatus(xDef::ES_MeasureOK);
			ic->setStyle(xDef::S_TxtMeasured);

			emit calcDone(true);
		}
		else
		{
			ic->setText(QString("Measure Failed"));

			c->setStatus(xDef::ES_MeasureFailed);
			c->setStyle(xDef::S_Failed);
			ic->setStatus(xDef::ES_MeasureFailed);
			ic->setStyle(xDef::S_TxtFailed);

			emit calcDone(false);
		}
		sucess = !sucess;
	}
	else if (e->type() == xRegCircle::Type)
	{
		auto c = static_cast<xRegCircle *>(e);
		auto data = c->circleData();
		static bool sucess = true;
		
		if (sucess)
		{
			// TEST
			data.setRadius(data.radius() + 20);
			c->setSubCircle(data);
			ic->setText(QString("RegCircle R: %1").arg(data.radius()));

			// ���󶨶����л������ɵ�Բ
			ic->bindEntity(c->subCircle());

			c->setStatus(xDef::ES_MeasureOK);
			c->setStyle(xDef::S_RegMeasured);
			ic->setStatus(xDef::ES_MeasureOK);
			ic->setStyle(xDef::S_TxtMeasured);

			emit calcDone(true);
		}
		else
		{
			ic->setText(QString("Measure Failed"));
			
			// ʧ��ʱ�󶨵���ΧԲ
			ic->bindEntity(c);
			// ������Բ
			c->hideSubCircle();
			c->showThis();

			c->setStatus(xDef::ES_MeasureFailed);
			c->setStyle(xDef::S_RegFailed);
			ic->setStatus(xDef::ES_MeasureFailed);
			ic->setStyle(xDef::S_TxtFailed);

			emit calcDone(false);
		}
		sucess = !sucess;
	}
}
