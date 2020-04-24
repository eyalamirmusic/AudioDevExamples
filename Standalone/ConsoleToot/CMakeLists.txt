project(ConsoleToot VERSION 0.1)

set (TargetName ${PROJECT_NAME})

juce_add_console_app(${TargetName} PRODUCT_NAME "Console Toot")
juce_generate_juce_header(${TargetName})

target_sources(${TargetName} PRIVATE Source/Main.cpp)

target_compile_definitions(${TargetName} PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0)

target_link_libraries(${TargetName} PRIVATE juce::juce_audio_utils)
