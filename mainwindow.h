// mainwindow.h
#ifndef MAINWINDOW_H  // Evita la inclusión múltiple de este archivo de encabezado.
#define MAINWINDOW_H

#include <QMainWindow>  // Incluye la clase QMainWindow de Qt, que es la base para crear ventanas principales.
#include "recursohidrico.h"  // Incluye la definición de la clase RecursoHidrico.

QT_BEGIN_NAMESPACE  // Comienza el bloque de espacio de nombres para evitar conflictos.
namespace Ui { class MainWindow; }  // Declara la clase Ui::MainWindow, que se generará a partir del archivo .ui.
QT_END_NAMESPACE  // Termina el bloque de espacio de nombres.

class MainWindow : public QMainWindow  // Define la clase MainWindow que hereda de QMainWindow.
{
    Q_OBJECT  // Macro de Qt que habilita las características de metaprogramación de Qt, como señales y ranuras.

public:
    MainWindow(QWidget *parent = nullptr);  // Constructor que recibe un puntero al widget padre (opcional).
    ~MainWindow();  // Destructor de la clase MainWindow.

signals:  // Sección donde se declaran las señales de la clase.
    void recursoSeleccionado(const RecursoHidrico& recurso);  // Señal emitida cuando se selecciona un recurso.

private slots:  // Sección donde se declaran las ranuras (métodos que responden a señales).
    void onBotonRecursoClicked();  // Ranura que se activa cuando se hace clic en un botón relacionado con recursos.
    void mostrarInformacionRecurso(const RecursoHidrico& recurso);  // Ranura para mostrar información del recurso seleccionado.

private:  // Sección privada donde se declaran los miembros de la clase.
    Ui::MainWindow *ui;  // Puntero a la interfaz de usuario generada por Qt Designer.
    QVector<RecursoHidrico> recursos;  // Vector que almacena una lista de objetos RecursoHidrico.
    void inicializarRecursos();  // Método para inicializar la lista de recursos.
    void configurarConexiones();  // Método para configurar las conexiones entre señales y ranuras.
    const RecursoHidrico* buscarRecursoPorNombreYTipo(const QString& nombre, RecursoHidrico::Tipo tipo);  // Método para buscar un recurso por su nombre y tipo.
};

#endif // MAINWINDOW_H  // Fin de la directiva de inclusión condicional.
