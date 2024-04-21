cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Reminder)

# Добавление источников в исполняемый файл проекта
set(project Reminder)

# Установка переменных среды
include_directories(${CMAKE_SOURCE_DIR}/Reminder/Sections/Settings)

set(SOURCES
        "Reminder/main.cpp"
        "Reminder/Init/init.cpp"
        "Reminder/Sections/WelcomeScreen/Welcome_screen.cpp"
        "Reminder/UI Animations/UI_anims.cpp"
        "Reminder/Database/Database.cpp"
)

set(HEADERS
        "Reminder/Init/H_Init.h"
        "Reminder/Sections/Settings/H_settings.h"
        "Reminder/Reminder.h"
        "Reminder/Database/Database.cpp"
        "Reminder/Database/Database.h"
)

# Файлы для копирования
if(WIN32)
    add_executable (Reminder ${SOURCES} ${HEADERS})

    # Копируем папку с ресурсами в out
    set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/out/build/x64-debug")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources DESTINATION ${RESOURCES_DIR})

    # Подключение SFML для работы "из коробки"
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third-party/sfml") # Директория для хранения SFML
    set(SFML_URL https://github.com/reduct0r/Compiled-version-of-sfml.git) # Репозиторий со стабильной динамической версией SFML
    set(BRANCH_NAME "master") # Ветка

    # Создать папку назначения, если она не существует
    file(MAKE_DIRECTORY ${SFML_DIR})

    # Загрузить библиотеку SFML с GitHub
    execute_process(
            COMMAND git clone --branch ${BRANCH_NAME} --single-branch ${SFML_URL} ${SFML_DIR}
            RESULT_VARIABLE GIT_RESULT
    )

    # Проверка результата выполнения команды git clone
    if (GIT_RESULT EQUAL "0")
        message("Git clone successfull!")
    else ()
        message("Git cloning failed!")
    endif ()

    set(files_to_copy
            ${SFML_DIR}/SFML-2.6.1/bin/openal32.dll
            ${SFML_DIR}/SFML-2.6.1/bin/sfml-audio-d-2.dll
            ${SFML_DIR}/SFML-2.6.1/bin/sfml-graphics-d-2.dll
            ${SFML_DIR}/SFML-2.6.1/bin/sfml-network-d-2.dll
            ${SFML_DIR}/SFML-2.6.1/bin/sfml-system-d-2.dll
            ${SFML_DIR}/SFML-2.6.1/bin/sfml-window-d-2.dll
    )

    # Копировать dll файлы в build
    foreach (file ${files_to_copy})
        file(COPY ${file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endforeach ()

    # Заголовочные файлы библиотеки
    include_directories(${SFML_DIR}/SFML-2.6.1/include)

    # Подключение библиотек (КОНФИГРУРАЦИЯ DEBUG!)
    target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-graphics-d.lib)
    target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-audio-d.lib)
    target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-network-d.lib)
    target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-system-d.lib)
    target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-window-d.lib)

    message("Successful!")

elseif (APPLE)
    # Setting sources lists
    set(${project}_SOURCE_LIST ${${project}_SOURCES})

    # Coping textures in build directory
    set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources DESTINATION ${RESOURCES_DIR})

    # Adding executable files
    add_executable(${project} ${SOURCES} ${HEADERS})

    # Finding SFML components
    find_package(SFML COMPONENTS graphics audio REQUIRED)

    # Setting openssl libraries
    set(OPENSSL_LIBRARIES
            /opt/homebrew/lib/libssl.3.dylib
            /opt/homebrew/lib/libssl.a
            /opt/homebrew/lib/libssl.dylib
            /opt/homebrew/lib/libcrypto.3.dylib
            /opt/homebrew/lib/libcrypto.a
            /opt/homebrew/lib/libcrypto.dylib
    )

    # Setting json libraries
    set(JSON_LIBRARIES
            /opt/homebrew/lib/libjsoncpp.25.dylib
            /opt/homebrew/lib/libjsoncpp.dylib
    )

    # Setting postre libraries
    set(POSTGRESQL_LIBRARIES
            /opt/homebrew/lib/libpqxx-7.9.dylib
            /opt/homebrew/lib/libpqxx.dylib
    )

    # Setting SFML include dirs
    set(SFML_INCLUDE_DIRS /opt/homebrew/include/)

    # Setting SFML libraries
    set(SFML_LIBRARIES /opt/homebrew/lib/libsfml-audio.dylib
            /opt/homebrew/lib/libsfml-graphics.dylib
            /opt/homebrew/lib/libsfml-network.dylib
            /opt/homebrew/lib/libsfml-system.dylib
            /opt/homebrew/lib/libsfml-window.dylib
    )

    # Adding include_directories
    include_directories(${SFML_INCLUDE_DIRS})

    # Connecting libraries
    target_link_libraries(${project} ${POSTGRESQL_LIBRARIES})
    target_link_libraries(${project} ${SFML_LIBRARIES})
    target_link_libraries(${project} ${JSON_LIBRARIES})
    target_link_libraries(${project} ${OPENSSL_LIBRARIES})

    message("Successful!")
endif ()
