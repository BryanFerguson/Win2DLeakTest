//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

#include "CanvasPage.xaml.h"

using namespace Win2DLeakTest;

using namespace concurrency;
using namespace Platform;
using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace std;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;

MainPage::MainPage()
{
    InitializeComponent();

    FrameworkElement^ grid = ref new Grid();
    TestForLeak(grid, L"Grid (empty)").then(
        [this]()
        {
            FrameworkElement^ canvasVirtualControl = ref new CanvasVirtualControl();
            return TestForLeak(canvasVirtualControl, L"CanvasVirtualControl (removed from parent)");
        }, task_continuation_context::use_current()).then(
        [this]()
        {
            auto canvasVirtualControl = ref new CanvasVirtualControl();
            auto inkCanvas = ref new InkCanvas();
            auto grid = ref new Grid();
            grid->Children->Append(canvasVirtualControl);
            grid->Children->Append(inkCanvas);
            canvasVirtualControl = nullptr;
            inkCanvas = nullptr;
            FrameworkElement^ gridAsFE = grid;
            grid = nullptr;
            return TestForLeak(gridAsFE, L"Grid (containing CanvasVirtualControl child)");
        }, task_continuation_context::use_current());
}

task<void> MainPage::TestForLeak(FrameworkElement^& element, PCWSTR description)
{
    WeakReference weakElement(element);

    hostGrid->Children->Append(element);

    element = nullptr;

    wstring descriptionStr = description;

    concurrency::task_completion_event<void> tce;
    auto dispatcherTimer = ref new DispatcherTimer();

    static const long long timerInterval = 5000000; // 500ms in 100-ns ticks
    dispatcherTimer->Interval = TimeSpan{ timerInterval };
    dispatcherTimer->Tick += ref new EventHandler<Object^>(
        [this, weakElement, descriptionStr, tce, dispatcherTimer](Object^ sender, Object^ e)
        {
            dispatcherTimer->Stop();

            hostGrid->Children->Clear();

            auto dispatcherTimerInner = ref new DispatcherTimer();
            dispatcherTimerInner->Interval = TimeSpan{ timerInterval };
            dispatcherTimerInner->Tick += ref new EventHandler<Object^>(
                [this, weakElement, descriptionStr, tce, dispatcherTimerInner](Object^ sender, Object^ e)
            {
                dispatcherTimerInner->Stop();

                bool leaked = weakElement.Resolve<FrameworkElement>() != nullptr;

                wostringstream message;

                message << textBlock->Text->Data() << descriptionStr << " " <<
                    (leaked ? L"leaked" : L"did not leak") << "\n";

                textBlock->Text = ref new String(message.str().data());

                tce.set();
            });
            dispatcherTimerInner->Start();
        });
    dispatcherTimer->Start();

    return create_task(tce);
}

void Win2DLeakTest::MainPage::NavigateToCanvasPage(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    Frame->Navigate(TypeName(CanvasPage::typeid), nullptr);
}
