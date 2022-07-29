#include "xUtils.h"

QPainterPath StrokeShapeFromPath(const QPainterPath &path, double width)
{
	if (path.isEmpty() || width < 0.001)
		return path;

	QPainterPathStroker ps;
	ps.setCapStyle(Qt::FlatCap);
	ps.setJoinStyle(Qt::BevelJoin);
	ps.setWidth(width);
	return ps.createStroke(path);
}

double DistancePoint2Line(const QPointF &p, const QLineF &line)
{
	const auto v1 = p - line.p1();
	const auto v2 = line.p2() - line.p1();
	const double S = v1.x() * v2.y() - v1.y() * v2.x();
	const double l = line.length();
	if (l > 0.000001)
		return qAbs(S / l);
	return -1.0;
}

double AnglePoint2Point(const QPointF &p1, const QPointF &p2, bool reverseY) noexcept
{
	const qreal dx = p2.x() - p1.x();
	const qreal dy = p2.y() - p1.y();
	const qreal rdy = reverseY ? -dy : dy;

	const qreal theta = std::atan2(rdy, dx);

	const qreal theta_normalized = theta < 0 ? theta + M_2PI : theta;

	if (qFuzzyCompare(theta_normalized, M_2PI))
		return 0.0;
	else
		return theta_normalized;
}

bool AngleIsBetween(double srcAngle, double sa, double alen) noexcept
{
	double ea = sa + alen;
	if (alen < 0) std::swap(sa, ea);
	const double da = NormalizeAngle(ea - sa);
	return da >= NormalizeAngle(srcAngle - sa) || da >= NormalizeAngle(ea - srcAngle);
}
