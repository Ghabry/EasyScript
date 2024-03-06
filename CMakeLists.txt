cmake_minimum_required(VERSION 3.13...3.24 FATAL_ERROR)

project(easyscript VERSION 0.1 LANGUAGES CXX)

# C++20 is required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Source Files
add_library(easyscript_lib OBJECT
	src/easyscript/all_commands.h
	src/easyscript/binding.h
	src/easyscript/commands/call_common_event.h
	src/easyscript/commands/change_face_graphic.cpp
	src/easyscript/commands/change_face_graphic.h
	src/easyscript/commands/change_gold.cpp
	src/easyscript/commands/change_gold.h
	src/easyscript/commands/command_base.h
	src/easyscript/commands/label.cpp
	src/easyscript/commands/label.h
	src/easyscript/commands/message_options.cpp
	src/easyscript/commands/message_options.h
	src/easyscript/commands/play_bgm.cpp
	src/easyscript/commands/play_bgm.h
	src/easyscript/commands/play_sound.cpp
	src/easyscript/commands/play_sound.h
	src/easyscript/commands/show_choice.cpp
	src/easyscript/commands/show_choice.h
	src/easyscript/commands/show_message.cpp
	src/easyscript/commands/show_message.h
	src/easyscript/commands/trigger_event_at.h
	src/easyscript/commands/unknown_command.cpp
	src/easyscript/commands/unknown_command.h
	src/easyscript/commands/unknown_branch_command.cpp
	src/easyscript/commands/unknown_branch_command.h
	src/easyscript/event_command.cpp
	src/easyscript/event_command.h
	src/easyscript/forward.h
	src/easyscript/from_command.cpp
	src/easyscript/from_command.h
	src/easyscript/parameter.cpp
	src/easyscript/parameter.h
	src/easyscript/state.h
	src/easyscript/types.cpp
	src/easyscript/types.h
	src/easyscript/utils.cpp
	src/easyscript/utils.h
)

add_executable(${PROJECT_NAME}
	src/main.cpp
)

# Include directories
target_include_directories(easyscript_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(liblcf REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC easyscript_lib liblcf::liblcf)
