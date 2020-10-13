#ifndef POINTSET4_H_INCLUDED
#define POINTSET4_H_INCLUDED

class PointSet4: public IPointSet
{
    public:
        PointSet4()
        {
            points.push_back(GraphPoint(-50, -50));
            points.push_back(GraphPoint(10, -20));
            points.push_back(GraphPoint(30, -15));
            points.push_back(GraphPoint(150, -100));
        }

        virtual std::vector<GraphPoint>& GetPoints(void)
        {
            return points;
        }

        virtual wxString GetName()
        {
            return _T("set 4");
        }

        virtual PointLabelType GetLabels(void)
        {
            return POINT_TYPE_CIRCLE;
        }

        virtual wxColour GetColour(void)
        {
            return *wxCYAN;
        }

    private:
        std::vector<GraphPoint> points;
};

#endif // POINTSET4_H_INCLUDED
