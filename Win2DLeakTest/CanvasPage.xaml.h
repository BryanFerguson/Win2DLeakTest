//
// CanvasPage.xaml.h
// Declaration of the CanvasPage class
//

#pragma once

#include "CanvasPage.g.h"

namespace Win2DLeakTest
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class CanvasPage sealed
	{
	public:
		CanvasPage();
    private:
        void NavigateToMainPage(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void Page_Unloaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
    };
}
