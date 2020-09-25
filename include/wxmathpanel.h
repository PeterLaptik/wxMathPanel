#ifndef WXMATHPANEL_H
#define WXMATHPANEL_H

#include <wx/panel.h>
#include <wx/dcclient.h>
#include <math.h>
#include <vector>
#include <map>


class wxMathPanel: public wxPanel
{
    public:
        ///\name Constructors and destructor
        wxMathPanel(wxWindow *parent,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL | wxSIMPLE_BORDER,
                    const wxString &name = wxPanelNameStr);

        virtual ~wxMathPanel();

        ///\name Scaling
        void ZoomIn(void);
        void ZoomOut(void);
        void SetBorders(const double &left, const double &top, const double &right, const double &bottom);
        void GetBorders(double *left, double *top, double *right, double *bottom) const;

        ///\name Restraints
        void SetRestraints(const double &left_border, const double &top_border, const double &right_border, const double &bottom_border);
        void GetRestraints(double *left, double *top, double *right, double *bottom) const;
        void ResetRestraints(void);

        ///\name Behavior
        void Freeze(void);      // make screen non-scalable and non-movable
        void UnFreeze(void);    // make screen scalable and movable
        void SetMovable(bool is_movable = true);
        bool GetMovable(void) const;
        void SetScalable(bool is_scalable = true);  // both axises
        void SetScalable(bool is_scalable_x, bool is_scalable_y);
        void GetScalable(bool *is_scalable_x, bool *is_scalable_y) const;

        ///\name View
        void SetLogarithmic(bool x_axis, bool y_axis);
        void ShowLabels(bool x_labels, bool y_labels);
        void ShowNetLines(bool show_x, bool show_y);
        void ShowMiddleLines(bool show_x, bool show_y);

        void GetIsLogarithmic(bool *x_axis, bool *y_axis) const;
        void GetLabelsVisibility(bool *x_labels, bool *y_labels) const;
        void GetNetLinesVisibility(bool *show_x, bool *show_y) const;
        void GetMiddleLinesVisibility(bool *show_x, bool *show_y) const;

        ///\name Numeric values
        void SetBaseNumber(int base_number);    // for both axises
        void SetBaseNumber(int x_base_number, int y_base_number);
        void GetBaseNumber(int *x_base_number, int *y_base_number) const;
        void SetLogMinValue(double value);
        double GetLogMinValue() const;

        ///\name Colours
        void SetAxisColour(const wxColour &colour);
        void SetNetLinesColour(const wxColour &colour);
        void SetLabelColour(const wxColour &colour);
        wxColour GetAxisColour(void) const;
        wxColour GetNetLinesColour(void) const;
        wxColour GetLabelColour(void) const;

        ///\name Text
        void SetAxisNames(wxString xname, wxString yname);
        void GetAxisNames(wxString *xname, wxString *yname) const;

        ///\name Drawing
        // Mock for subclasses` after-drawing
        // The method is being called each time in the end of 'EventPaint'
        virtual void DrawAfter(wxDC &dc);

        ///\name Scaling and coordinates
        double GetLinearScaleX(void) const;
        double GetLinearScaleY(void) const;
        double GetLogStepFor(double x_point);
        // Translate coordinates from real values to the canvas values
        void TranslateCoordinates(double &x, double &y);
        void TranslateXCoordinate(double &x);
        void TranslateYCoordinate(double &y);
        /// \}

    protected:


    private:
        // Events
        void EventPaint(wxPaintEvent &event);
        void EventResize(wxSizeEvent &event);
        void EventMouseLeftButtonDown(wxMouseEvent &event);
        void EventMouseLeftButtonUp(wxMouseEvent &event);
        void EventMouseMove(wxMouseEvent &event);
        void EventMouseWheel(wxMouseEvent &event);

        // Default drawing routines
        void DrawAxises(wxDC &dc);
        void DrawNetworkHorizontal(wxDC &dc);
        void DrawNetworkLogHorizontal(wxDC &dc);
        void DrawNetworkVertical(wxDC &dc);
        void DrawNetworkLogVertical(wxDC &dc);
        void CheckBorders(wxDC &dc);

        // Sub-routines for logarithmic axises scales
        void SetLogarithmicX(bool is_logarithmic);
        void SetLogarithmicY(bool is_logarithmic);

        // Panel size
        // Changes each time when the panel is being resized
        double m_height, m_width;

        // Screen position
        double m_border_left;
        double m_border_right;
        double m_border_top;
        double m_border_bottom;

        // Screen restraints
        // The screen cannot be scaled or moved to border values out of restraints
        struct BordersRestraints
        {
            double left, right, top, bottom;
        } m_restraints;

        // View
        bool m_is_x_logarithmic, m_is_y_logarithmic;
        bool m_show_axises;
        bool m_show_x_net_lines, m_show_y_net_lines;
        bool m_show_x_middle_lines, m_show_y_middle_lines;
        bool m_show_x_labels, m_show_y_labels;
        int m_min_line_margin;      // minimum margin in pixels between two lines
        wxString m_xname, m_yname;  // axises names

        // Numeric restraints
        int m_base_number_vertical, m_base_number_horizontal;
        double m_minimum_log_value;

        // Colours
        wxColour m_colour_axis;
        wxColour m_colour_net_lines;
        wxColour m_colour_label;

        // Canvas behavior
        double m_x, m_y;                // mouse coordinates over panel
        double m_start_x, m_start_y;    // mouse coordinates on dragging start (when mouse left button has been pressed)
        bool m_is_movable;              // can screen be dragged by mouse
        bool m_is_scalable, m_is_scalable_x, m_is_scalable_y;   // can screen be scaled by mouse wheel
        bool m_is_dragging;             // true if mouse left button is clicked

        // Switching logarithmic <-> linear
        // Last left/bottom position for switching between logarithmic/linear scales
        // Makes able to return correct left/bottom border values if switched to the linear scale from the logarithmic one
        double m_was_resized_x, m_was_resized_y;    // resets last state after resize
        double m_last_left_border, m_last_bottom_border, m_last_right_border, m_last_top_border;    // last states
};

#endif // WXMATHPANEL_H