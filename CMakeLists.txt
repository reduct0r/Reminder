set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Reminder)

# Установка переменных среды
include_directories(${CMAKE_SOURCE_DIR}/Reminder/Sections/Settings)
set(SOURCES
        "Reminder/main.cpp"
        "Reminder/Init/init.cpp"
        "Reminder/Sections/WelcomeScreen/Welcome_screen.cpp"
        "Reminder/UI/UI_anims.cpp"
        "Reminder/UI/TextBox.cpp"
        "Reminder/Sections/Main menu/MainMenu.cpp" 
        "Reminder/Sections/Settings/Settings.cpp"
        "Reminder/UI/Button.cpp"
        "Reminder/State.cpp"
        "Reminder/Sections/Main menu/MainMenuState.cpp"
)
set(HEADERS
        "Reminder/Init/H_Init.h"
        "Reminder/Sections/Settings/H_settings.h"
        "Reminder/UI/TextBox.h"
        "Reminder/Sections/WelcomeScreen/H_Welcome_screen.h"
        "Reminder/Sections/Main menu/MainMenu.h" 
        "Reminder/UI/DropDownList.h"
        "Reminder/UI/Button.h" 
        "Reminder/State.h"
        "Reminder/Sections/Main menu/MainMenuState.h" 
)

# Добавление источников в исполняемый файл проекта
set(project Reminder)

if(WIN32)
    add_executable (Reminder ${SOURCES} ${HEADERS})

    # Копируем папку с ресурсами в out
    set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/out/build/x64-debug")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources DESTINATION ${RESOURCES_DIR})

    # Подключение SFML для работы "из коробки"
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third-party/sfml")            # Директория для хранения SFML
    set(SFML_URL https://github.com/reduct0r/Compiled-version-of-sfml.git)  # Репозиторий со стабильной динамической версией SFML
    set(BRANCH_NAME "master")                                               # Ветка

    # Создать папку назначения, если она не существует
    file(MAKE_DIRECTORY ${SFML_DIR})

    # Загрузить библиотеку SFML с GitHub
    execute_process(
            COMMAND git clone --branch ${BRANCH_NAME} --single-branch ${SFML_URL} ${SFML_DIR}
            RESULT_VARIABLE GIT_RESULT
    )

    # Проверка результата выполнения команды git clone
    if (GIT_RESULT EQUAL "0")
        message("Успешно!")
    else ()
        message("Не удалось выполнить команду git clone.")
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

    # Подключение библиотек (КОНФИГРУРАЦИЯ DEBUG!)
    target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-graphics-d.lib)
    target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-audio-d.lib)
    target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-network-d.lib)
    target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-system-d.lib)
    target_link_libraries(Reminder ${SFML_DIR}/SFML-2.6.1/lib/sfml-window-d.lib)

    # Заголовочные файлы библиотеки
    include_directories(${SFML_DIR}/SFML-2.6.1/include)

    find_package(PostgreSQL REQUIRED)
    find_package(libpqxx CONFIG REQUIRED)
    find_package(jsoncpp CONFIG REQUIRED)

    target_link_libraries(Reminder PostgreSQL::PostgreSQL)
    target_link_libraries(Reminder libpqxx::pqxx)
    target_link_libraries(Reminder JsonCpp::JsonCpp)

elseif (APPLE)
    find_package(SFML COMPONENTS graphics audio REQUIRED)

    set(SFML_INCLUDE_DIRS /opt/homebrew/include/)

    set(SFML_LIBRARIES /opt/homebrew/lib/libsfml-audio.dylib
            /opt/homebrew/lib/libsfml-graphics.dylib
            /opt/homebrew/lib/libsfml-network.dylib
            /opt/homebrew/lib/libsfml-system.dylib
            /opt/homebrew/lib/libsfml-window.dylib
    )

    message(SFML_INCLUDE_DIRS="${SFML_INCLUDE_DIRS}")
    message(SFML_LIBRARIES="${SFML_LIBRARIES}")

    include_directories(${SFML_INCLUDE_DIRS})
    set(${project}_SOURCE_LIST ${${project}_SOURCES})

    add_executable(${project} ${SOURCES} ${HEADERS})

    target_link_libraries(${project} ${SFML_LIBRARIES})
endif ()
