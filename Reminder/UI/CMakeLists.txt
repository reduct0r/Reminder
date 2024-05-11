# Добавление пути к заголовочным файлам текущей поддиректории
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Reminder/Init)

# Добавление всех исходных файлов текущей поддиректории
file(GLOB SOURCES "*.cpp" "*.h")

# Создание библиотеки из файлов текущей поддиректории
add_library(UI ${SOURCES})
