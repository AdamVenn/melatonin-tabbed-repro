#include "juce_graphics/juce_graphics.h"
#include <juce_gui_extra/juce_gui_extra.h>
#include <melatonin_inspector/melatonin_inspector.h>

class MainComponent final : public juce::Component
{
public:
    MainComponent()
    {
        tabs.addTab("One", juce::Colours::grey, new juce::Label({}, "Tab one"), true);
        tabs.addTab("Two", juce::Colours::darkgrey, new juce::Label({}, "Tab two"), true);
        tabs.addTab("Three", juce::Colours::darkgrey, new juce::Label({}, "Tab three"), true);
        addAndMakeVisible(tabs);
        setSize(600, 400);
        inspector.setVisible(true);
    }

    void resized() override
    {
        tabs.setBounds(getLocalBounds());
    }

private:
    juce::TabbedComponent tabs{ juce::TabbedButtonBar::TabsAtTop };
    melatonin::Inspector inspector{ *this };
};

class MainWindow final : public juce::DocumentWindow
{
public:
    explicit MainWindow(const juce::String& name) :
        DocumentWindow(name, juce::Colours::black, allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent, true);
        setResizable(true, false);
        centreWithSize(getWidth(), getHeight());
        setVisible(true);
    }

    void closeButtonPressed() override
    {
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }
};

class ReproApplication final : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return JUCE_APPLICATION_NAME_STRING; }
    const juce::String getApplicationVersion() override { return JUCE_APPLICATION_VERSION_STRING; }

    void initialise(const juce::String&) override
    {
        window = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override
    {
        window.reset();
    }

private:
    std::unique_ptr<MainWindow> window;
};

START_JUCE_APPLICATION(ReproApplication)
