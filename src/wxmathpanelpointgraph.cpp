#include "wxmathpanelpointgraph.h"
#include "mathlegend.h"

static const int DEFAULT_CURVE_THICKNESS = 2;
static const int MAXIMUM_CURVE_THICKNESS = 5;
static const int DEFAULT_LABEL_THICKNESS = 2;

// Default value used as template to decrease quality for higher perfomance
static const int wxMATHPANEL_TEMPLATE_WIDTH = 640;

// Point label sizes
static const int MATH_PANEL_DEFAULT_LABEL = 8;


/**\brief Default constructor.
* \param parent The parent window.
* \param winid An identifier for the panel. wxID_ANY is taken to mean a default.
* \param pos The panel position.
* \param size The panel size.
* \param style The window style.
* \param name The window name.
*/
wxMathPanelPointGraph::wxMathPanelPointGraph(wxWindow *parent,
                                    wxWindowID winid,
                                    const wxPoint &pos,
                                    const wxSize &size,
                                    long style,
                                    const wxString &name) : wxMathPanel(parent, winid, pos, size, style, name)
{
    Bind(wxEVT_LEFT_DOWN, &wxMathPanelPointGraph::EventMouseLeftDown, this);
    Bind(wxEVT_LEFT_UP, &wxMathPanelPointGraph::EventMouseLeftUp, this);
    Bind(wxEVT_MOTION, &wxMathPanelPointGraph::EventMouseMove, this);
    Bind(wxEVT_LEAVE_WINDOW, &wxMathPanelPointGraph::EventMouseLeave, this);
    Bind(wxEVT_SIZE, &wxMathPanelPointGraph::EventResize, this);
    m_legend = new MathLegend(this);
    m_is_legend_dragging = false;
    m_thickness = DEFAULT_CURVE_THICKNESS;
    m_label_size = MATH_PANEL_DEFAULT_LABEL;
    m_quality = false;
    m_show_tails = true;
}

/**\brief Destructor */
wxMathPanelPointGraph::~wxMathPanelPointGraph()
{
    delete m_legend;
}


/**\brief Adds a class that's keep point sets for drawing.
*
* The class has to implement the IPointSet interface.
* \param f Pointer to IPointSet interface.
*/
void wxMathPanelPointGraph::AddPointSet(IPointSet *f)
{
    m_pointsets.push_back(f);
    m_legend->AppendItem(f->GetName(), f->GetColour(), f->GetLabels());
    this->Refresh();
}

/** \brief Clears point sets list to be drawn.
*/
void wxMathPanelPointGraph::ClearFunctions()
{
    m_pointsets.clear();
    m_legend->ClearItems();
    this->Refresh();
}

/**\brief Sets a quality for the curves drawing.
*
* Default panel quality is set to normal but not to high.
* \param hq Set true if curves have to be drawn on each X-axis pixel.
* If set false X-axis step will depend on panel size and functions quantity. That may cause a low-smoothed curve drawing.
*/
void wxMathPanelPointGraph::SetHighQuality(bool hq)
{
    m_quality = hq;
    this->Refresh();
}

/**\brief Sets a pen thickness for curve drawing.
*\param thickness Thickness value.
*/
void wxMathPanelPointGraph::SetCurveThickness(int thickness)
{
    if(thickness>MAXIMUM_CURVE_THICKNESS)
        return;

    m_thickness = thickness;
    this->Refresh();
}

/**\brief Returns pen thickness for drawing curves.
* \return Thickness value.
*/
int wxMathPanelPointGraph::GetCurveThickness() const
{
    return m_thickness;
}

/**\brief Sets label size for points.
* \param value Label size in pixels.
*/
void wxMathPanelPointGraph::SetPointLabelSize(int value)
{
    m_label_size = value;
    this->Refresh();
}

/**\brief Returns point label size.
* \return Label size in pixels.
*/
int wxMathPanelPointGraph::GetPointLabelSize() const
{
    return m_label_size;
}

/**\brief Resets label sizes to default.
*/
void wxMathPanelPointGraph::ResetLabelSize()
{
    m_label_size = MATH_PANEL_DEFAULT_LABEL;
    this->Refresh();
}

/**\brief Sets visibility of curve outside of the points set.
* \param show Visibility value.
*/
void wxMathPanelPointGraph::ShowTails(bool show)
{
    m_show_tails = show;
    this->Refresh();
}

/**\brief Returns visibility of a curves tails.
* \return Visibility value.
*/
bool wxMathPanelPointGraph::GetTailsVisibility() const
{
    return m_show_tails;
}

/**\brief Returns a legend object.
* \return Pointer to the legend.
*/
MathLegend* wxMathPanelPointGraph::GetLegend() const
{
    return m_legend;
}

/**\brief Draws curves and legend */
void wxMathPanelPointGraph::DrawAfter(wxDC &dc)
{
    this->DrawFunctions(dc);
    m_legend->Refresh(dc);
}

// Draws functions from a list using appropriate colours
void wxMathPanelPointGraph::DrawFunctions(wxDC &dc)
{
    double border_left, border_right, border_top, border_bottom;
    bool is_logarithmic_x, is_logarithmic_y;

    if(m_pointsets.size()<1)
        return; // no functions to draw

    int INCREMENTOR = 1;    // value that increments steps during curve drawing to keep performance
    int dc_width = dc.GetSize().GetWidth();

    if(!m_quality)
    {
        INCREMENTOR = dc_width > wxMATHPANEL_TEMPLATE_WIDTH ?
                        dc_width/wxMATHPANEL_TEMPLATE_WIDTH*(m_pointsets.size()/2)
                        : m_pointsets.size()/2;
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
    size_t position = 0;
    double *value_array;
    PointLabelType ptype;
    PointLabel *m_label = NULL;
    for(std::vector<IPointSet*>::iterator it=m_pointsets.begin(); it!=m_pointsets.end(); ++it)
    {
        // Get values list
        std::vector<GraphPoint> values = (*it)->GetPoints();
        int POINT_MAX = GetMaxPointX(values);
        int POINT_MIN = GetMinPointX(values);

        // Define point labels type
        m_label = GetLabelObject(ptype = (*it)->GetLabels());

        // Get a polynomial equation
        position = 0;
        m_polinoms.SetCount(values.size());
        wxPen label_pen((*it)->GetColour(), DEFAULT_LABEL_THICKNESS);
        dc.SetPen(label_pen);
        dc.SetBrush(wxBrush((*it)->GetColour()));
        for(std::vector<GraphPoint>::iterator it=values.begin(); it!=values.end(); ++it)
        {
            panel_x = (*it).x;
            panel_y = (*it).y;
            m_polinoms.SetPoint(panel_x, panel_y, position++);

            // Draw labels
            TranslateCoordinates(panel_x, panel_y);
            if(panel_x<=0)
                continue;

            if(m_label!=NULL)
                m_label->Draw(dc, panel_x, panel_y);
        }
        m_polinoms.Calculate();
        value_array = m_polinoms.GetPolynomialArray();

        // Set colour for the curve
        wxPen pen((*it)->GetColour(), m_thickness);
        dc.SetPen(pen);

        // Start function value
        double x = ((POINT_MIN > border_left)&&(!m_show_tails)) ? POINT_MIN : border_left;

        panel_prev_x = x;
        panel_prev_y = CalculateValueFor(panel_prev_x, value_array, position);

        if(x>border_right)
            continue;   // out of canvas

        // Translate real coordinates to panel coordinates
        TranslateCoordinates(panel_prev_x, panel_prev_y);

        // Draw by lines to keep smooth curves
        for(; x<border_right; x+=(step*INCREMENTOR))
        {
            if((!m_show_tails)&&(x>POINT_MAX))
                break;

            panel_x = x;
            panel_y = CalculateValueFor(x, value_array, position);

            // Translate real coordinates to panel coordinates
            TranslateCoordinates(panel_x, panel_y);

            // Draw micro-line
            dc.DrawLine(panel_prev_x, panel_prev_y, panel_x, panel_y);

            // Remember the points as a last ones
            panel_prev_x = panel_x;
            panel_prev_y = panel_y;
            if(is_logarithmic_x)
                step = GetLogStepFor(x);    // recompute step for logarithmic axis
        }

        if(m_label!=NULL)
            delete m_label;
    }
}

//
// Event handling
// Routines for legend dragging

/** Makes a legend able to be dragged if mouse left button is pressed down and mouse pointer is over the legend */
void wxMathPanelPointGraph::EventMouseLeftDown(wxMouseEvent &event)
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
void wxMathPanelPointGraph::EventMouseLeftUp(wxMouseEvent &event)
{
    m_is_legend_dragging = false;
    wxMathPanel::EventMouseLeftButtonUp(event);
}

/** Moves a legend if it is able to be dragged or calls super-class 'mouse move'-event */
void wxMathPanelPointGraph::EventMouseMove(wxMouseEvent &event)
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
void wxMathPanelPointGraph::EventResize(wxSizeEvent &event)
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


double wxMathPanelPointGraph::CalculateValueFor(const double &x, const double* point_array, const size_t array_size)
{
    double result = 0;
    for(size_t i=0; i<array_size; i++)
    {
        result += (point_array[i]*pow(x, i));
    }
    return result;
}

// Find minimum X-value for points
double wxMathPanelPointGraph::GetMaxPointX(std::vector<GraphPoint> &vec)
{
    double result = 0;
    for(std::vector<GraphPoint>::iterator it=vec.begin(); it!=vec.end(); ++it)
    {
        if((*it).x > result)
            result = (*it).x;
    }
    return result;
}

// Find maximum X-value for points
double wxMathPanelPointGraph::GetMinPointX(std::vector<GraphPoint> &vec)
{
    double result = 0;
    for(std::vector<GraphPoint>::iterator it=vec.begin(); it!=vec.end(); ++it)
    {
        if((*it).x < result)
            result = (*it).x;
    }
    return result;
}

// Create label object
PointLabel* wxMathPanelPointGraph::GetLabelObject(PointLabelType ptype)
{
    PointLabel* label = NULL;

    switch(ptype)
        {
            case POINT_TYPE_CIRCLE:
                label = new PointLabelCircle(m_label_size);
                break;
            case POINT_TYPE_SQUARE:
                label = new PointLabelSquare(m_label_size);
                break;
            case POINT_TYPE_TRIANGLE:
                label = new PointLabelTriangle(m_label_size);
                break;
            case POINT_TYPE_CROSS:
                label = new PointLabelCross(m_label_size);
                break;
            case POINT_TYPE_NOLABEL:
                label = NULL;
                break;
        }
    return label;
}

/** Cancels legend dragging if mouse is out the panel */
void wxMathPanelPointGraph::EventMouseLeave(wxMouseEvent &event)
{
    m_is_legend_dragging = false;
    wxMathPanel::EventMouseLeave(event);
}
