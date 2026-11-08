import QtQuick
import QtQuick.Templates as T
import Material3
import Material3.internals

T.Label {
    id: control
    color: Theme.contentColor

    Binding {
        when: control.parent instanceof DefaultFontProvider
        value: {
            if (control.parent instanceof DefaultFontProvider) {
                return (control.parent as DefaultFontProvider).font;
            }
        }
    }
}
