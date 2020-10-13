#ifndef POINTSET3_H_INCLUDED
#define POINTSET3_H_INCLUDED

class PointSet3: public IPointSet
{
    public:
        PointSet3()
        {
            points.push_back(GraphPoint(0, 0));
            points.push_back(GraphPoint(30, 20));
        }

        virtual std::vector<GraphPoint>& GetPoints(void)
        {
            return points;
        }

        virtual wxString GetName()
        {
            return _T("set 3");
        }

        virtual PointLabelType GetLabels(void)
        {
            return POINT_TYPE_SQUARE;
        }

        virtual wxColour GetColour(void)
        {
            return *wxBLUE;
        }

    private:
        std::vector<GraphPoint> points;
};

#endif // POINTSET3_H_INCLUDED
