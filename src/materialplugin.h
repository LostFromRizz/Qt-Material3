#include <QtCore/qtsymbolmacros.h>
#include <QtQml/qqmlextensionplugin.h>

QT_DECLARE_EXTERN_SYMBOL_VOID(qml_register_types_Material)

Q_IMPORT_QML_PLUGIN(Material_internalsPlugin)

class MaterialPlugin : public QQmlEngineExtensionPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)

public:
  MaterialPlugin(QObject *parent = nullptr)
      : QQmlEngineExtensionPlugin(parent) {

    QT_KEEP_SYMBOL(qml_register_types_Material);
  }

  void initializeEngine(QQmlEngine *engine, const char *uri) override;
};

// #include "materialplugin.moc"
