// main.cpp
#include "mainwindow.h"  // Incluye la definición de la clase MainWindow.
#include <QApplication>  // Incluye la clase QApplication, que gestiona la aplicación Qt.

int main(int argc, char *argv[])  // Función principal que inicia la aplicación.
{
    QApplication a(argc, argv);  // Crea un objeto QApplication, pasando argumentos de línea de comandos.

    MainWindow w;  // Crea una instancia de la clase MainWindow.

    w.show();  // Muestra la ventana principal en la pantalla.

    return a.exec();  // Ejecuta el bucle principal de la aplicación, esperando eventos y gestionándolos.
}
