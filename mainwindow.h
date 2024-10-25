// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QGroupBox>
#include <QStackedWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void mostrarInformacionRecurso(const QString &departamento);
    void mostrarLeyenda();
    void mostrarAyuda();
    void mostrarMapa();

private:
    Ui::MainWindow *ui;

    // UI Components
    QLabel *labelInfo;
    QGroupBox *infoBox;
    QStackedWidget *stackedWidget;
    QWidget *paginaInfo;
    QWidget *paginaLeyenda;
    QWidget *paginaAyuda;
    QPushButton *btnVolver;

    // Initialization functions
    void inicializarInterface();
    void configurarEstilos();
    void inicializarRegiones();
    void crearPaginaLeyenda();
    void crearPaginaAyuda();
    void crearPaginaInfo();

    // Data structures
    QMap<QString, QRect> regionesMapa;
    // Nuevo mapa anidado para almacenar múltiples recursos por departamento
    // Formato: Departamento -> (Nombre del Recurso -> Descripción)
    QMap<QString, QMap<QString, QString>> recursosHidricos;
};

#endif // MAINWINDOW_H
