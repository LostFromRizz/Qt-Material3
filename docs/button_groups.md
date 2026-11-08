# ButtonGroupLayout

`ButtonGroupLayout` arranges buttons horizontally using a `RowLayout`. It creates buttons from a list of `Action` objects and applies shape and width changes.

## Basic usage

`actions` is the **default property**, so `Action` objects can be declared directly inside `ButtonGroupLayout` without explicitly assigning them to `actions`.

```qml
ButtonGroupLayout {
    Action {
        text: "Cut"
        icon.name: "content-cut"
    }

    Action {
        text: "Copy"
        icon.name: "content-copy"
    }

    Action {
        text: "Paste"
        icon.name: "content-paste"
    }
}
```

By default, `delegate` uses `FilledButton` to create each button. You can customize the appearance by assigning a different button component to `delegate`.

```qml
ButtonGroupLayout {
    delegate: TonalButton {}

    Action {
        text: "Edit"
    }

    Action {
        text: "Share"
    }
}
```

## Group types

The `exclusive` property determines whether the group is exclusive or non-exclusive.

### Exclusive group

Set `exclusive: true` to enable exclusive selection. Only one button can be checked at a time. The buttons also use exclusive spacing.

```qml
ButtonGroupLayout {
    exclusive: true

    Action {
        text: "Day"
        checkable: true
        checked: true
    }

    Action {
        text: "Week"
        checkable: true
    }

    Action {
        text: "Month"
        checkable: true
    }
}
```

Use an exclusive group when the user must choose one option from a set, such as a view mode or a mutually exclusive selection.

### Non-exclusive group

Set `exclusive: false`, which is the default, to allow buttons to be checked independently. The buttons use `Material.buttonGroupSpacingSmall` for their spacing.

```qml
ButtonGroupLayout {
    exclusive: false

    Action {
        text: "Bold"
        checkable: true
    }

    Action {
        text: "Italic"
        checkable: true
    }

    Action {
        text: "Underline"
        checkable: true
    }
}
```

Use a non-exclusive group when multiple options can be selected simultaneously, such as text-formatting controls.

## Layout and overflow

`ButtonGroupLayout` arranges its buttons horizontally using an internal `RowLayout`. When `maximumWidth` is finite and the buttons exceed that width, the layout attempts to remove trailing buttons and display the configured `overflowIndicator`.

```qml
ButtonGroupLayout {
    maximumWidth: 320

    overflowIndicator: IconButton {
        icon.name: "more-vert"
    }

    Action {
        text: "Open"
    }

    Action {
        text: "Save"
    }

    Action {
        text: "Share"
    }

    Action {
        text: "Export"
    }
}
```

The overflow indicator is optional. If buttons are removed to fit the available width and no indicator is configured, those buttons will not be represented by an overflow button.

## Properties

| Property | Type | Description |
| --- | --- | --- |
| `actions` | `list<Action>` | **Default.** The list of actions used to create buttons. Actions can be declared directly inside the group. |
| `delegate` | `Component` | The component used to create each button. Defaults to `FilledButton`. |
| `exclusive` | `bool` | Controls grouping behavior. `true` enables exclusive selection and exclusive spacing; `false` enables independent selection. Defaults to `false`. |
| `checkedButton` | `AbstractButton` | **Read-only.** An alias to the internal group's `checkedButton`. |
| `buttons` | `list<AbstractButton>` | **Read-only.** An alias to the internal button group's button list, including the overflow indicator when it participates in the group. |
| `spacing` | `real` | The horizontal spacing between buttons. Defaults to `2` when exclusive and `Material.buttonGroupSpacingSmall` otherwise. |
| `maximumWidth` | `real` | The maximum width used when calculating overflow. Defaults to `Number.POSITIVE_INFINITY`. |
| `overflowIndicator` | `AbstractButton` | An optional button displayed when some actions cannot fit within `maximumWidth`. |
| `expandRatio` | `real` | Controls the width expansion amount during the press animation. Defaults to `0.15`. |
| `implicitOverflowIndicatorWidth` | `real` | **Read-only.** The overflow indicator's implicit width, or `0` when no indicator exists. |
| `implicitOverflowIndicatorHeight` | `real` | **Read-only.** The overflow indicator's implicit height, or `0` when no indicator exists. |

## Signals

### `clicked(button)`

Emitted when a button in the internal group is clicked. The `button` argument provides the clicked `AbstractButton`.

```qml
ButtonGroupLayout {
    exclusive: true

    onClicked: button => {
        console.log("Clicked:", button.text)
    }

    Action {
        text: "First"
    }

    Action {
        text: "Second"
    }
}
```


## ButtonGroup

[`ButtonGroup`](https://doc.qt.io/qt-6/qml-qtquick-controls-buttongroup.html) is a non-visual component that manages button exclusivity and checked states. Unlike `ButtonGroupLayout`, it does not arrange buttons or provide layout animations and overflow handling.

Use `ButtonGroup` when you need to manage a group of buttons in a more complex layouts without the default animations provided by `ButtonGroupLayout`.

### Basic usage

The `buttons` property accepts a list of buttons to manage. In this example, `layout.children` is filtered to exclude the `Repeater` itself, leaving the buttons created by the repeater.

```qml
ColumnLayout {
    id: layout

    ButtonGroup {
        buttons: layout.children.filter(x => x !== repeater)
    }

    Repeater {
        id: repeater
        model: 5

        delegate: FilledButton {
            Layout.alignment: Qt.AlignVCenter

            required property int index

            text: index
            checkable: true
        }
    }
}
```

### Exclusivity

Like `ButtonGroupLayout`, `ButtonGroup` supports exclusive and non-exclusive selection through its `exclusive` property.

- **Exclusive:** Only one button can be checked at a time.
- **Non-exclusive:** Multiple buttons can be checked independently.

Refer to the [Qt ButtonGroup documentation](https://doc.qt.io/qt-6/qml-qtquick-controls-buttongroup.html) for the complete list of properties and signals.

### When to use ButtonGroup

Use `ButtonGroup` when you need to manage checked states and exclusivity while controlling the layout and animations yourself. Since it is non-visual, it does not handle button arrangement, overflow, or width-expansion animations.

This is particularly useful for exclusive button groups. According to Material 3 guidelines, selecting a button in an exclusive group should change its shape rather than its width. Although `ButtonGroupLayout` supports this behavior, it also introduces width-expansion animations when buttons are pressed, which may not be desirable in this context. Using `ButtonGroup` lets you implement the intended shape transitions without the additional width changes.
