cmake_minimum_required(VERSION 3.12)
project(AudioDevExamples)

#Updates or clones JUCE from git, and configures it for subdirectories:
include (CMake/FindJUCE-GIT.cmake)

#adding project folders:
add_subdirectory(Standalone)
add_subdirectory(Plugins)
