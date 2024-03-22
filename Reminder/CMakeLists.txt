# CMakeList.txt: проект CMake для Reminder; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Reminder "Reminder.cpp" "Reminder.h")

if (CMAKE_VERSION VERSION_GREATER 3.8)
  set_property(TARGET Reminder PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
