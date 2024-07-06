#### Generated code #####
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/generated)

target_include_directories(EInkClock PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources(EInkClock PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/ClockMain.cpp
	${CMAKE_CURRENT_LIST_DIR}/RTC.cpp
	${CMAKE_CURRENT_LIST_DIR}/Display.cpp
	${CMAKE_CURRENT_LIST_DIR}/Power.cpp
	${CMAKE_CURRENT_LIST_DIR}/UI.cpp
	${CMAKE_CURRENT_LIST_DIR}/ClockScreen.cpp
	${CMAKE_CURRENT_LIST_DIR}/SettingsScreen.cpp
	${CMAKE_CURRENT_LIST_DIR}/Input.cpp
)