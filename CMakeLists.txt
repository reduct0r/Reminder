cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Установка переменных среды
set(SOURCES "Reminder/main.cpp")

# Добавление источников в исполняемый файл проекта
add_executable (Reminder  ${SOURCES})

# Копируем папку с ресерсами (д.с. текстуры) в out
set(RESURSES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/out/build/x64-debug")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources DESTINATION ${RESURSES_DIR})

# Подключение SFML для работы "из коробки"
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third-party/sfml")			# Директория для хранения SFML
set(SFML_URL https://github.com/reduct0r/Compiled-version-of-sfml.git)	# Репозиторий со стабильной динамической версией SFML
set(BRANCH_NAME "master")												# Ветка

# Создать папку назначения, если она не существует
file(MAKE_DIRECTORY ${SFML_DIR})

# Загрузить библиотеку SFML с GitHub
execute_process(COMMAND git clone --branch ${BRANCH_NAME} --single-branch ${SFML_URL} ${SFML_DIR})
message("Успешно")
# Файлы для копирования


if(WIN32)
set(files_to_copy
    ${SFML_DIR}/SFML-2.6.1/bin/openal32.dll
    ${SFML_DIR}/SFML-2.6.1/bin/sfml-audio-d-2.dll
    ${SFML_DIR}/SFML-2.6.1/bin/sfml-graphics-d-2.dll
    ${SFML_DIR}/SFML-2.6.1/bin/sfml-network-d-2.dll
    ${SFML_DIR}/SFML-2.6.1/bin/sfml-system-d-2.dll
    ${SFML_DIR}/SFML-2.6.1/bin/sfml-window-d-2.dll
)
# Копировать dll файлы в build
foreach(file ${files_to_copy})
    file(COPY ${file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
endif()
# Подключение библиотек (КОНФИГРУРАЦИЯ DEBUG!)
target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-graphics-d.lib)
target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-audio-d.lib)
target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-network-d.lib)
target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-system-d.lib)
target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-window-d.lib)

# Заголовочные файлы библиотеки
include_directories(${SFML_DIR}/SFML-2.6.1/include)	