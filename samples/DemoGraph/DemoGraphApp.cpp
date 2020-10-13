/*********************************************************************
 * Purpose:   MathPanelGraph sample to demonstrate functions plotting
 * Author:    Peter Laptik
 * Created:   2020-09-13
 ********************************************************************/

#include "DemoGraphApp.h"

//(*AppHeaders
#include "DemoGraphMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(DemoGraphApp);

bool DemoGraphApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	DemoGraphFrame* Frame = new DemoGraphFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
