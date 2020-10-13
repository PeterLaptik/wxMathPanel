 /********************************************************************
 * Purpose:   MathPanelPointGraph sample
 * Author:    Peter Laptik
 * Created:   2020-10-04
 ********************************************************************/

#include "DemoInterpolationApp.h"

//(*AppHeaders
#include "DemoInterpolationMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(DemoInterpolationApp);

bool DemoInterpolationApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	DemoInterpolationFrame* Frame = new DemoInterpolationFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
