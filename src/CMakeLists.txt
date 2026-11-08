add_subdirectory(internals)

list(APPEND MATERIAL_SOURCES
    colorscheme.h colorscheme.cpp
    typography.h typography.cpp
    motionspecs.h motionspecs.cpp
    theme.h theme.cpp
    material.h material.cpp
    material_shapes.h material_shapes.cpp
    polygon_painter.h polygon_painter.cpp
)

list(APPEND MATERIAL_QML_FILES
    Action.qml
    ButtonGroup.qml
    Spacer.qml
    SearchBar.qml
    ScrollIndicator.qml
    SplitButtonLayout.qml
    Badge.qml
    Menu.qml
    MenuItem.qml
    VerticalSpacer.qml
    CarouselView.qml
    CarouselItem.qml
    Card.qml
    Dialog.qml
    DialogButtonBox.qml
    FilledCard.qml
    ElevatedCard.qml
    OutlinedCard.qml
    Button.qml
    SegmentedButton.qml
    ElevatedButton.qml
    FilledButton.qml
    FilledTonalButton.qml
    OutlinedButton.qml
    TextButton.qml
    IconButton.qml
    Label.qml
    ToolTip.qml
    RichToolTip.qml
    Divider.qml
    ButtonGroupLayout.qml
    Surface.qml
    ListItem.qml
    SegmentedListItem.qml
    Icon.qml
    Slider.qml
    TopAppBar.qml
    TextField.qml
    OutlinedTextField.qml
    FloatingActionButton.qml
    FloatingActionMenuButton.qml
    FloatingActionButtonMenu.qml
    FloatingActionButtonMenuItem.qml
    Scaffold.qml
    LinearProgressIndicator.qml
    LinearWavyProgressIndicator.qml
    LoadingIndicator.qml
    ContainedLoadingIndicator.qml
    CircularProgressIndicator.qml
    CircularWavyProgressIndicator.qml
    Popup.qml
    Switch.qml
    SwitchDelegate.qml
)

list(APPEND MATERIAL_SHAPES_SOURCES
	shapes/corner_rounding.h shapes/point.h
	shapes/cubic.h shapes/cubic.cpp
	shapes/cubic_location.h shapes/cubic_location.cpp
	shapes/float_mapping.h shapes/float_mapping.cpp
	shapes/progressable_feature.h shapes/utils.h
	shapes/shapes_features.h shapes/shapes_features.cpp
	shapes/rounded_polygon.h shapes/rounded_polygon.cpp
	shapes/polygon_measure.h shapes/polygon_measure.cpp
	shapes/feature_mapping.h shapes/feature_mapping.cpp
	shapes/morph.h shapes/morph.cpp
	shapes/painting.h shapes/painting.cpp
)

qt6_add_qml_module(${PROJECT_NAME}
    URI "${PROJECT_NAME}"
    VERSION 1.0
    DEPENDENCIES QtQuick QtQuick.Templates ${PROJECT_NAME}.internals
    IMPORTS ${PROJECT_NAME}.internals
    SOURCES
        ${MATERIAL_SOURCES}
	${MATERIAL_SHAPES_SOURCES}
    QML_FILES
        ${MATERIAL_QML_FILES}
    OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/Material3
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/internals
    ${CMAKE_CURRENT_SOURCE_DIR}/shapes
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Gui
    Qt6::Quick
    Qt6::Qml
    Qt6::Core
    Qt6::QuickControls2
    ${INTERNALS_PLUGIN}
)
