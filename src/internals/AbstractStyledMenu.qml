import QtQuick
import QtQuick.Templates as T

T.Menu {
    enum Style {
        Vibrant,
        Standard
    }

    virtual property int style
}
