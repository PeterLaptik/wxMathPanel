#ifndef POINTSET1_H_INCLUDED
#define POINTSET1_H_INCLUDED

#include "../../include/ipointset.h"

class PointSet1: public IPointSet
{
    public:
        PointSet1()
        {
            points.push_back(GraphPoint(-5,-10));
            points.push_back(GraphPoint(10,0));
            points.push_back(GraphPoint(15,5));
            points.push_back(GraphPoint(25,10));
        }

        virtual std::vector<GraphPoint>& GetPoints(void)
        {
            return points;
        }

        virtual wxString GetName()
        {
            return _T("set 1");
        }

        virtual PointLabelType GetLabels(void)
        {
            return POINT_TYPE_CROSS;
        }

        virtual wxColour GetColour(void)
        {
            return wxColour(0,0,0);
        }

    private:
        std::vector<GraphPoint> points;
};

#endif // POINTSET1_H_INCLUDED
