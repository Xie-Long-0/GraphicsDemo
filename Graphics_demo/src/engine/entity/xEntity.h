#pragma once

#include <QGraphicsItem>

class xEntity : virtual public QGraphicsItem
{

public:
	xEntity(QGraphicsItem *parent = nullptr);
	~xEntity();

protected:
	enum {
		ET_Line = UserType + 1,
		ET_Circle,
		ET_Arc,
		ET_Point,
	};

private:

};
