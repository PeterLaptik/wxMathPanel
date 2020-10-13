 /*********************************************************************
 * Purpose:   MathLegend sample for MathPanel and sub-classes
 * Author:    Peter Laptik
 * Created:   2020-09-27
 ********************************************************************/

#include "DemoLegendApp.h"

//(*AppHeaders
#include "DemoLegendMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(DemoLegendApp);

bool DemoLegendApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	DemoLegendFrame* Frame = new DemoLegendFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
