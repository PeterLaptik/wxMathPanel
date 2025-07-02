/*********************************************************************
 * Name:      wxmathpanelpointgraph.h
 * Purpose:   Panel class for interpolated functions plotting by points.
 * Author:    Peter Laptik
 * Created:   2020-10-18
 * Copyright: (c) Peter Laptik
 * Licence:   BSD 2-clause
 ********************************************************************/

#ifndef WXMATHPANELPOINTGRAPH_H
#define WXMATHPANELPOINTGRAPH_H

#include "wxmathpanel.h"
#include "ipointset.h"
#include "interpolation.h"
#include "pointlabel.h"

#ifdef _WINDLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT
#endif

class MathLegend;

// Maximum sets that can be outputed
static const int MAX_CURVES = 10;


/**\brief Class for plotting interpolated curves by points.
*
* Curves to be drawn have to implement the interface IPointSet.
*/
class DLL_EXPORT wxMathPanelPointGraph : public wxMathPanel
{
    public:
        wxMathPanelPointGraph(wxWindow *parent,
                        wxWindowID winid = wxID_ANY,
                        const wxPoint &pos = wxDefaultPosition,
                        const wxSize &size = wxDefaultSize,
                        long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                        const wxString &name = wxPanelNameStr);

        virtual ~wxMathPanelPointGraph();

        // Functions for drafting
        void AddPointSet(IPointSet *f);
        void ClearFunctions(void);
        void SetHighQuality(bool hq = true);
        void SetCurveThickness(int thickness);
        int GetCurveThickness(void) const;
        void SetPointLabelSize(int value);
        int GetPointLabelSize(void) const;
        void ResetLabelSize(void);
        void ShowTails(bool show = true);
        bool GetTailsVisibility(void) const;

        // Legend
        MathLegend* GetLegend(void) const;

        // Drawing functions on wxMathPanel canvas
        void DrawAfter(wxDC &dc);


    protected:
        void EventMouseLeftUp(wxMouseEvent &event);
        void EventMouseLeftDown(wxMouseEvent &event);
        void EventMouseMove(wxMouseEvent &event);
        void EventMouseLeave(wxMouseEvent &event);
        void EventResize(wxSizeEvent &event);

    private:
        inline void DrawFunctions(wxDC &dc);
        inline double CalculateValueFor(const double &x, const double* point_array, const size_t array_size);
        inline PointLabel* GetLabelObject(PointLabelType ptype);
        inline double GetMaxPointX(std::vector<GraphPoint> &vec);
        inline double GetMinPointX(std::vector<GraphPoint> &vec);

        std::vector<IPointSet*> m_pointsets;    // Functions` data
        Polynom m_polinoms;
        int m_thickness;    // curve thickness
        int m_label_size;
        bool m_quality;
        bool m_show_tails;

        // Legend
        MathLegend *m_legend;
        bool m_is_legend_dragging;
        int m_pos_x, m_pos_y;   // position before dragging
};

#endif // WXMATHPANELPOINTGRAPH_H
