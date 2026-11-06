cmake_minimum_required(VERSION 3.28)

project(MelatoninTabbedRepro VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 9.0.5
    GIT_SHALLOW TRUE)
FetchContent_Declare(melatonin_inspector
    GIT_REPOSITORY https://github.com/sudara/melatonin_inspector.git
    GIT_TAG 9c483f865854d83fe9873e1c20e3fd772f695f80
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/melatonin_inspector)
FetchContent_MakeAvailable(JUCE melatonin_inspector)

juce_add_gui_app(MelatoninTabbedRepro PRODUCT_NAME "Melatonin Tabbed Repro")
target_sources(MelatoninTabbedRepro PRIVATE Source/Main.cpp)
target_compile_definitions(MelatoninTabbedRepro PRIVATE
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:MelatoninTabbedRepro,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:MelatoninTabbedRepro,JUCE_VERSION>")
target_link_libraries(MelatoninTabbedRepro
    PRIVATE
        juce::juce_gui_extra
        melatonin_inspector
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
