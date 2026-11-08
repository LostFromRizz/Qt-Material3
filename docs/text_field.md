# TextField

`TextField` is a Material 3 text input control with a floating label, supporting item, and optional leading and trailing content. It provides customizable container appearance, colors, corner radii, and spacing, with visual states for focus, validation errors, and disabled interaction.

Text fields are available in two styles:

- **TextField** – Uses a filled container with a bottom indicator.
- **OutlinedTextField** – Uses an outlined container with a floating label and customizable outline.

Both styles share the same text input properties and supporting features.

## Basic Usage

```qml
TextField {
    labelText: "Username"
    placeholderText: "Enter your username"
}
```

For the outlined style:

```qml
OutlinedTextField {
    labelText: "Username"
    placeholderText: "Enter your username"
}
```

## Leading and Trailing Content

Use `leading` and `trailing` to provide components alongside the text input, such as icons or action buttons.

```qml
TextField {
    id: field
    labelText: "Search"
    placeholderText: "Search items"

    leading: Icon {
        name: "search"
    }

    trailing: IconButton {
        icon.name: "close"
        onClicked: field.text = ""
    }
}
```

## Supporting Item

Use `supportingItem` to display additional content below the text field container. It accepts an `Item`, allowing you to provide custom content such as helper text, validation messages, or other components.

```qml
TextField {
    labelText: "Email"
    placeholderText: "name@example.com"

    supportingItem: Text {
        text: "Enter a valid email address"
        font: Theme.typography.bodySmall
    }
}
```

The supporting item is positioned below the container and contributes to the control's overall height. Its implicit height is excluded from `containerHeight`, allowing the container and supporting content to be laid out separately.

## Properties

| Property | Type | Description |
|---|---|---|
| `labelText` | string | Specifies the label displayed inside the text field. The label moves to the top of the container when the field has text or receives focus. |
| `supportingItem` | Item | Specifies the item displayed below the text field container. Its implicit height contributes to the overall height of the control. |
| `leading` | Component | Specifies the component displayed before the text input, such as a leading icon. |
| `trailing` | Component | Specifies the component displayed after the text input, such as a trailing icon or action. |
| `backgroundColor` | color | Controls the background color of the text field container. |
| `indicatorColor` | color | Controls the bottom indicator color according to the enabled, error, and focus states. |
| `labelTextColor` | color | Controls the label color according to the enabled, error, and focus states. |
| `placeholderTextColor` | color | Controls the placeholder text color. |
| `supportingTextColor` | color | Specifies the content color for the supporting item. |
| `leadingContentColor` | color | Specifies the content color for the leading component. |
| `trailingContentColor` | color | Specifies the content color for the trailing component. |
| `hasError` | bool | Indicates whether the input is unacceptable, based on `acceptableInput`. |
| `topLeftRadius` | real | Controls the top-left corner radius of the container. |
| `topRightRadius` | real | Controls the top-right corner radius of the container. |
| `bottomLeftRadius` | real | Controls the bottom-left corner radius of the container. |
| `bottomRightRadius` | real | Controls the bottom-right corner radius of the container. |
| `containerTopPadding` | real | Controls the top padding inside the text field container. |
| `containerBottomPadding` | real | Controls the bottom padding inside the text field container. |
| `containerLeftPadding` | real | Controls the left padding inside the container. The value depends on whether leading content is provided. |
| `containerRightPadding` | real | Controls the right padding inside the container. The value depends on whether trailing content is provided. |
| `spacing` | real | Controls the spacing between the text input and leading or trailing content. |
| `implicitLabelHeight` | real | Read-only implicit height of the label. |
| `implicitLabelWidth` | real | Read-only implicit width of the label. |
| `implicitSupportingItemHeight` | real | Read-only implicit height of the supporting item. |
| `implicitSupportingItemWidth` | real | Read-only implicit width of the supporting item. |
| `implicitLeadingHeight` | real | Read-only implicit height of the leading component. |
| `implicitLeadingWidth` | real | Read-only implicit width of the leading component. |
| `implicitTrailingHeight` | real | Read-only implicit height of the trailing component. |
| `implicitTrailingWidth` | real | Read-only implicit width of the trailing component. |
| `containerHeight` | real | Read-only height of the text field container, excluding the supporting item. |

## OutlinedTextField Properties

`OutlinedTextField` provides two additional properties for customizing its outline:

| Property | Type | Description |
|---|---|---|
| `outlineColor` | color | Controls the outline color according to the enabled, error, and focus states. |
| `outlineWidth` | real | Controls the outline width. It is `2` when the text field has active focus and `1` otherwise. |

## Container Padding

`TextField` does not expose a replaceable `contentItem`. Its text input, placeholder, label, and leading and trailing components are arranged internally.

The standard `topPadding`, `bottomPadding`, `leftPadding`, and `rightPadding` properties are calculated internally to accommodate these elements. Use `containerTopPadding`, `containerBottomPadding`, `containerLeftPadding`, and `containerRightPadding` to customize the spacing inside the text field container.

The supporting item is positioned below the container and contributes separately to the control's overall height.

## Inherited Properties

Both styles are based on `QtQuick.Templates.TextField` and support inherited text input properties, including `text`, `placeholderText`, `acceptableInput`, `validator`, `inputMask`, `maximumLength`, `readOnly`, `echoMode`, `cursorPosition`, and `selectionStart`.

See the [Qt Quick Controls TextField documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-textfield.html) for details.
