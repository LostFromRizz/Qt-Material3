set(INTERNALS_PLUGIN "${PROJECT_NAME}_internals")

list(APPEND INTERNALS_COLLECTIONS_SOURCES
	collections/slice.h 
)
list(APPEND INTERNAL_SOURCES 
	minternals.h minternals.cpp 
	progress_indicator_common.h
	linear_progress_indicator.h linear_progress_indicator.cpp
	linear_wavy_progress_indicator.h linear_wavy_progress_indicator.cpp
	circular_progress_indicator.h circular_progress_indicator.cpp
	circular_wavy_progress_indicator.h circular_wavy_progress_indicator.cpp
	utils.h utils.cpp
	icon_data.h icon_data_private.h icon_data.cpp
	elevation.h elevation.cpp
)

list(APPEND INTERNAL_QML_FILES
	SurfacePrivate.qml InteractiveSurface.qml 
	Ripple.qml Icon.qml IconLabel.qml 
	SliderTrackImpl.qml OutlinedTextFieldBackgroundImpl.qml 
	TextFieldSupportingText.qml DefaultFontProvider.qml
	AbstractFloatingActionButtonMenu.qml
	Spacer.qml VerticalSpacer.qml
	QuickShapeRect.qml ShadowElevation.qml
	AbstractStyledMenu.qml MenuItemIconLabel.qml
	SearchBarInputField.qml
)

qt6_add_qml_module(${INTERNALS_PLUGIN}
	URI "${PROJECT_NAME}.internals"
	# STATIC 
	SHARED
	VERSION  1.0 
	DEPENDENCIES QtQuick QtQuick.Effects
	SOURCES 
		${INTERNAL_SOURCES}       
		${INTERNALS_COLLECTIONS_SOURCES}
	QML_FILES ${INTERNAL_QML_FILES} 
	OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/internals
)

target_link_libraries(${INTERNALS_PLUGIN} PRIVATE Qt6::Quick Qt6::Gui Qt6::Qml)
target_include_directories(${INTERNALS_PLUGIN}
    PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/collections
	${CMAKE_CURRENT_SOURCE_DIR}
)


