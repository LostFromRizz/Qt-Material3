# Assets

## Icons

Material 3 ships with the **Material Symbols Rounded** icon font. You can load the font using `FontLoader` and use its glyphs throughout your QML application.

```qml
FontLoader {
    source: "qrc:/icons/MaterialSymbolsRounded.ttf"
}
```

Once loaded, the font can be used by text-based elements through their `font.family` property.

