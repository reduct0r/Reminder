# ���������� ���� � ������������ ������ ������� �������������
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Reminder/Init)

# ���������� ���� �������� ������ ������� �������������
file(GLOB SOURCES "*.cpp" "*.h")

# �������� ���������� �� ������ ������� �������������
add_library(Init ${SOURCES})
