//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace Win2DLeakTest
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

    private:
        concurrency::task<void> TestForLeak(FrameworkElement^& element, PCWSTR description);
        void NavigateToCanvasPage(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
    };
}
