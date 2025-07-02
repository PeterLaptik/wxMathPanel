/*********************************************************************
 * Name:      wxmathpanelgraph.h
 * Purpose:   Panel class for functions plotting by equation.
 * Author:    Peter Laptik
 * Created:   2020-10-18
 * Copyright: (c) Peter Laptik
 * Licence:   BSD 2-clause
 ********************************************************************/

#ifndef WXMATHPANELGRAPH_H
#define WXMATHPANELGRAPH_H

#include "wxmathpanel.h"
#include "ifunction.h"
#include <vector>

#ifdef _WINDLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT
#endif

class MathLegend;

/**\brief Class for drawing curves by equations.
*
* Functions to be drawn have to implement the interface IDrawableFunction.
*/
class DLL_EXPORT wxMathPanelGraph : public wxMathPanel
{
    public:
        wxMathPanelGraph(wxWindow *parent,
                        wxWindowID winid = wxID_ANY,
                        const wxPoint &pos = wxDefaultPosition,
                        const wxSize &size = wxDefaultSize,
                        long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                        const wxString &name = wxPanelNameStr);

        virtual ~wxMathPanelGraph();

        // Functions for drafting
        void AddFunction(IDrawableFunction *f);
        void ClearFunctions(void);
        void SetHighQuality(bool hq = true);
        void SetCurveThickness(int thickness);
        int GetCurveThickness(void) const;
        void SetManualStep(int step);
        void ResetManualStep(void);

        // Margins
        void SetUseMargins(bool use_margins = true);
        bool GetUseMargins(void) const;

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

        std::vector<IDrawableFunction*> m_functions;    // Functions` data
        int m_thickness;    // curve thickness
        bool m_quality;
        int m_manual_step;
        bool m_has_margins;

        // Legend
        MathLegend *m_legend;
        bool m_is_legend_dragging;
        int m_pos_x, m_pos_y;   // position before dragging
};

#endif // WXMATHPANELGRAPH_H
