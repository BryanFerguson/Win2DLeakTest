//
// CanvasPage.xaml.cpp
// Implementation of the CanvasPage class
//

#include "pch.h"
#include "CanvasPage.xaml.h"

#include "MainPage.xaml.h"

using namespace Win2DLeakTest;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

CanvasPage::CanvasPage()
{
	InitializeComponent();
}


void Win2DLeakTest::CanvasPage::NavigateToMainPage(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    Frame->Navigate(TypeName(MainPage::typeid), nullptr);
}


void Win2DLeakTest::CanvasPage::Page_Unloaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    //m_canvasVirtualControl->RemoveFromVisualTree();
}
