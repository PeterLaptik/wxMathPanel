#include "../include/wxmathpanelgraph.h"

static const int DEFAULT_CURVE_THICKNESS = 2;
static const int MAXIMUM_CURVE_THICKNESS = 5;

// Default value used as template to decrease quality for higher performance
static const int wxMATHPANEL_TEMPLATE_WIDTH = 640;


/**\brief Default constructor.
* \param parent The parent window.
* \param winid An identifier for the panel. wxID_ANY is taken to mean a default.
* \param pos The panel position.
* \param size The panel size.
* \param style The window style.
* \param name The window name.
*/
wxMathPanelGraph::wxMathPanelGraph(wxWindow *parent,
                                    wxWindowID winid,
                                    const wxPoint &pos,
                                    const wxSize &size,
                                    long style,
                                    const wxString &name) : wxMathPanel(parent, winid, pos, size, style, name)
{
    Bind(wxEVT_LEFT_DOWN, &wxMathPanelGraph::EventMouseLeftDown, this);
    Bind(wxEVT_LEFT_UP, &wxMathPanelGraph::EventMouseLeftUp, this);
    Bind(wxEVT_MOTION, &wxMathPanelGraph::EventMouseMove, this);
    Bind(wxEVT_LEAVE_WINDOW, &wxMathPanelGraph::EventMouseLeave, this);
    Bind(wxEVT_SIZE, &wxMathPanelGraph::EventResize, this);
    m_legend = new MathLegend();
    m_is_legend_dragging = false;
    m_thickness = DEFAULT_CURVE_THICKNESS;
    m_quality = false;
}

/**\brief Destructor */
wxMathPanelGraph::~wxMathPanelGraph()
{
    delete m_legend;
}


/**\brief Adds a class for function drawing.
*
* The class has to implement the IDrawableFunction interface.
* \param f Pointer to IDrawableFunction interface.
*/
void wxMathPanelGraph::AddFunction(IDrawableFunction *f)
{
    m_functions.push_back(f);
    m_legend->AppendItem(f->GetName(), f->GetColour(), POINT_TYPE_NOLABEL);
    this->Refresh();
}

/** \brief Clears function list to be drawn.
*/
void wxMathPanelGraph::ClearFunctions()
{
    m_functions.erase(m_functions.begin(), m_functions.end());
    m_legend->ClearItems();
    this->Refresh();
}

/**\brief Sets a quality for the curves drawing.
*
* Default panel quality is set to normal but not to high.
* \param hq Set true if curves have to be drawn on each X-axis pixel.
* If set false X-axis step will depend on panel size and functions quantity. That may cause a low-smoothed curve drawing.
*/
void wxMathPanelGraph::SetHighQuality(bool hq)
{
    m_quality = hq;
    this->Refresh();
}

/**\brief Sets a pen thickness for curve drawing.
*\param thickness Thickness value.
*/
void wxMathPanelGraph::SetCurveThickness(int thickness)
{
    if(thickness>MAXIMUM_CURVE_THICKNESS)
        return;

    m_thickness = thickness;
    this->Refresh();
}

/**\brief Returns pen thickness for drawing curves.
* \return Thickness value.
*/
int wxMathPanelGraph::GetCurveThickness() const
{
    return m_thickness;
}

/**\brief Returns a legend object.
* \return Pointer to the legend.
*/
MathLegend* wxMathPanelGraph::GetLegend() const
{
    return m_legend;
}

/**\brief Draws curves and legend */
void wxMathPanelGraph::DrawAfter(wxDC &dc)
{
    this->DrawFunctions(dc);
    m_legend->Refresh(dc);
}

// Draws functions from a list using appropriate colours
void wxMathPanelGraph::DrawFunctions(wxDC &dc)
{
    double border_left, border_right, border_top, border_bottom;
    bool is_logarithmic_x, is_logarithmic_y;

    if(m_functions.empty())
        return; // no functions to draw

    int INCREMENTOR = 1;    // value that increments steps during curve drawing
    int dc_width = dc.GetSize().GetWidth();

    if(!m_quality)
    {
        INCREMENTOR = dc_width > wxMATHPANEL_TEMPLATE_WIDTH ?
                        dc_width/wxMATHPANEL_TEMPLATE_WIDTH*(m_functions.size()/2)
                        : m_functions.size()/2;
    }

    if(INCREMENTOR<1)
        INCREMENTOR = 1;

    // Get canvas metrics
    GetBorders(border_left, border_top, border_right, border_bottom);
    GetIsLogarithmic(is_logarithmic_x, is_logarithmic_y);

    double step = GetLinearScaleX();    // define real scale steps to draw pixel by pixel

    // Coordinates to draw point
    double panel_x, panel_y;

    // Previous drawn point
    // Curve is being drawn as an array of a small lines (lines steps equal to resolution of the canvas)
    // Each line goes from a previous point to the current point to make curve smoothed without interruptions
    double panel_prev_x, panel_prev_y;

    // Draw functions from function list
    for(std::vector<IDrawableFunction*>::iterator it=m_functions.begin(); it!=m_functions.end(); ++it)
    {
        // Set colour for the curve
        wxPen pen((*it)->GetColour(), m_thickness);
        dc.SetPen(pen);

        // Initialize start values
        // Do not use point if std::exception has occurred
        // Find first function value without exception
        double x = border_left;

        while(true)
        {
            panel_prev_x = x;
            try
            {
                panel_prev_y = (*it)->Calculate(panel_prev_x);
            }
            catch (std::exception &e)
            {
                if(x>border_right)
                    break;

                if(is_logarithmic_x)
                    step = GetLogStepFor(x);    // recompute step for a logarithmic axis

                x+=step*INCREMENTOR;
                continue;
            }
            break;
        }

        if(x>border_right)
            continue;   // out of canvas

        // Translate real coordinates to panel coordinates
        TranslateCoordinates(panel_prev_x, panel_prev_y);

        // Draw by lines to keep smooth curves
        // Start from first valid x-value computed before / x-value without exception
        bool exception_flag = false;
        for(; x<border_right; x+=(step*INCREMENTOR))
        {
            panel_x = x;

            // Draw nothing if an exception has been thrown from the function
            try
            {
                panel_y = (*it)->Calculate(x);
            }
            catch (std::exception &e)
            {
                exception_flag = true;
                if(is_logarithmic_x)
                    step = GetLogStepFor(x);    // recompute step for logarithmic axis

                continue;   // do not draw line
            }

            // Translate real coordinates to panel coordinates
            TranslateCoordinates(panel_x, panel_y);

            // First point after exception: make as a start point
            // Clear last point before the curve was broken:
            // make this point as a last point (start point for a new micro-line) and do not draw line
            if(exception_flag==true)
            {
                exception_flag = false;
                panel_prev_x = panel_x;
                panel_prev_y = panel_y;
                if(is_logarithmic_x)
                    step = GetLogStepFor(x);    // recompute step for logarithmic axis

                continue;
            }

            // Draw micro-line
            dc.DrawLine(panel_prev_x, panel_prev_y, panel_x, panel_y);

            // Remember the points as a last ones
            panel_prev_x = panel_x;
            panel_prev_y = panel_y;
            if(is_logarithmic_x)
                step = GetLogStepFor(x);    // recompute step for logarithmic axis
        }
    }
}

//
// Event handling
// Routines for legend dragging

/** Makes a legend able to be dragged if mouse left button is pressed down and mouse pointer is over the legend */
void wxMathPanelGraph::EventMouseLeftDown(wxMouseEvent &event)
{
    int x, y, width, height;

    m_pos_x = event.GetX();
    m_pos_y = event.GetY();
    m_legend->GetMetrics(x, y, width, height);

    // Check whether arrow is over the legend
    if(!((m_pos_x >= x)
       &&(m_pos_x <= x + width)
       &&(m_pos_y >= y)
       &&(m_pos_y <= y + height))
       ||(!m_legend->GetVisible())
       ||(!m_legend->GetMovable()))
    {
        wxMathPanel::EventMouseLeftButtonDown(event);
        return;
    }

    m_is_legend_dragging = true;
}

/** Cancels dragging on mouse left button released */
void wxMathPanelGraph::EventMouseLeftUp(wxMouseEvent &event)
{
    m_is_legend_dragging = false;
    wxMathPanel::EventMouseLeftButtonUp(event);
}

/** Moves a legend if it is able to be dragged or calls super-class 'mouse move'-event */
void wxMathPanelGraph::EventMouseMove(wxMouseEvent &event)
{
    int pos_x, pos_y, width, height;

    if(!m_is_legend_dragging)
    {
        wxMathPanel::EventMouseMove(event);
        return;
    }

    m_legend->GetMetrics(pos_x, pos_y, width, height);
    int delta_x = m_pos_x - event.GetX();
    int delta_y = m_pos_y - event.GetY();
    int x = pos_x - delta_x;
    int y = pos_y - delta_y;

    // Check border intersections
    wxSize panel_size = this->GetSize();
    if(x + width > panel_size.x)
        x = panel_size.x - width;

    if(y + height > panel_size.y)
        y = panel_size.y - height;

    if(x<0)
        x = 0;

    if(y<0)
        y = 0;

    m_legend->SetPosition(x, y);
    m_pos_x = event.GetX();
    m_pos_y = event.GetY();
    this->Refresh();
}

/** Moves legend on resize if necessary */
void wxMathPanelGraph::EventResize(wxSizeEvent &event)
{
    int pos_x, pos_y, legend_width, legend_height;
    int width = this->GetSize().GetWidth();
    int height = this->GetSize().GetHeight();
    m_legend->GetMetrics(pos_x, pos_y, legend_width, legend_height);

    int x = pos_x;
    int y = pos_y;

    // Check border intersections
    if(x + legend_width > width)
        x = width - legend_width;

    if(y + legend_height > height)
        y = height - legend_height;

    if(x<0)
        x = 0;

    if(y<0)
        y = 0;

    m_legend->SetPosition(x, y);
    wxMathPanel::EventResize(event);
}

/** Cancels legend dragging if mouse is out the panel */
void wxMathPanelGraph::EventMouseLeave(wxMouseEvent &event)
{
    m_is_legend_dragging = false;
    wxMathPanel::EventMouseLeave(event);
}
