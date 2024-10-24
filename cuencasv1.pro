QT       += core gui  # Agrega los módulos core y gui de Qt al proyecto.

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  # Si la versión de Qt es mayor que 4, agrega el módulo widgets.

CONFIG += c++17  # Configura el proyecto para usar el estándar C++17.

SOURCES += \  # Lista de archivos fuente que forman parte del proyecto.
    main.cpp \  # Archivo principal del programa.
    mainwindow.cpp \  # Implementación de la clase MainWindow.
    recursohidrico.cpp  # Implementación de la clase RecursoHidrico.

HEADERS += \  # Lista de archivos de encabezado que definen las clases y funciones.
    mainwindow.h \  # Encabezado de la clase MainWindow.
    recursohidrico.h  # Encabezado de la clase RecursoHidrico.

FORMS += \  # Lista de archivos de interfaz de usuario en formato .ui.
    mainwindow.ui  # Definición de la interfaz gráfica de la ventana principal.

# Reglas predeterminadas para la implementación.
qnx: target.path = /tmp/$${TARGET}/bin  # Para el sistema operativo QNX, establece la ruta de destino para la instalación.
else: unix:!android: target.path = /opt/$${TARGET}/bin  # Para sistemas Unix (excluyendo Android), establece una ruta de destino diferente.
!isEmpty(target.path): INSTALLS += target  # Si la ruta de destino no está vacía, agrega una regla de instalación para el objetivo.

RESOURCES +=  # Sección para incluir archivos de recursos (imágenes, iconos, etc.). Actualmente no se especifica ninguno.

DISTFILES += \  # Archivos que se incluirán en la distribución del proyecto.
    README.md  # Archivo de documentación que proporciona información sobre el proyecto.
