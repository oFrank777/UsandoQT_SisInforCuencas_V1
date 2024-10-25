// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QFont>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inicializarInterface();
    inicializarRegiones();
    configurarEstilos();
}

void MainWindow::inicializarInterface()
{
    setWindowTitle("Recursos Hídricos del Perú");
    setMinimumSize(1200, 800);

    // Widget central con layout horizontal
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Panel izquierdo para el mapa
    QWidget *leftPanel = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    // Mapa
    ui->labelMapa = new QLabel;
    QPixmap mapa(":/imagenes/mapa_peru.png");
    ui->labelMapa->setPixmap(mapa.scaled(700, 900, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->labelMapa->setStyleSheet("QLabel { border: 3px solid #34495e; border-radius: 15px; padding: 10px; background-color: white; }");
    leftLayout->addWidget(ui->labelMapa);

    // Panel derecho
    QWidget *rightPanel = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    // Título principal
    QLabel *titulo = new QLabel("Recursos Hídricos del Perú");
    titulo->setStyleSheet(
        "QLabel { "
        "   color: #2c3e50; "
        "   font-size: 28px; "
        "   font-weight: bold; "
        "   padding: 10px; "
        "   border-bottom: 2px solid #3498db; "
        "   margin-bottom: 15px; "
        "}"
        );
    titulo->setAlignment(Qt::AlignCenter);
    rightLayout->addWidget(titulo);

    // Botones de navegación
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QPushButton *btnMapa = new QPushButton("Información");
    QPushButton *btnLeyenda = new QPushButton("Leyenda");
    QPushButton *btnAyuda = new QPushButton("Ayuda");

    btnMapa->setCursor(Qt::PointingHandCursor);
    btnLeyenda->setCursor(Qt::PointingHandCursor);
    btnAyuda->setCursor(Qt::PointingHandCursor);

    connect(btnMapa, &QPushButton::clicked, this, &MainWindow::mostrarMapa);
    connect(btnLeyenda, &QPushButton::clicked, this, &MainWindow::mostrarLeyenda);
    connect(btnAyuda, &QPushButton::clicked, this, &MainWindow::mostrarAyuda);

    buttonLayout->addWidget(btnMapa);
    buttonLayout->addWidget(btnLeyenda);
    buttonLayout->addWidget(btnAyuda);
    rightLayout->addLayout(buttonLayout);

    // StackedWidget para cambiar contenido
    stackedWidget = new QStackedWidget;

    // Crear páginas
    crearPaginaInfo();
    crearPaginaLeyenda();
    crearPaginaAyuda();

    rightLayout->addWidget(stackedWidget);

    // Configurar layout principal
    mainLayout->addWidget(leftPanel, 3);
    mainLayout->addWidget(rightPanel, 2);
}

void MainWindow::crearPaginaInfo()
{
    paginaInfo = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(paginaInfo);

    infoBox = new QGroupBox("Información del Recurso");
    QVBoxLayout *infoLayout = new QVBoxLayout(infoBox);

    labelInfo = new QLabel("Seleccione un departamento en el mapa");
    labelInfo->setWordWrap(true);
    labelInfo->setStyleSheet(
        "QLabel { "
        "   font-size: 16px; "
        "   line-height: 1.6; "
        "   color: #2c3e50; "
        "   padding: 10px; "
        "}"
        );

    infoLayout->addWidget(labelInfo);
    layout->addWidget(infoBox);

    stackedWidget->addWidget(paginaInfo);
}

void MainWindow::crearPaginaLeyenda()
{
    paginaLeyenda = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(paginaLeyenda);

    QScrollArea *scrollArea = new QScrollArea;
    QWidget *contenido = new QWidget;
    QVBoxLayout *contenidoLayout = new QVBoxLayout(contenido);

    QString estiloSeccion =
        "QLabel { "
        "   font-size: 20px; "
        "   font-weight: bold; "
        "   color: #ffffff; "
        "   padding: 10px; "
        "   border-bottom: 2px solid #3498db; "
        "   margin-top: 15px; "
        "}";

    QString estiloItem =
        "QLabel { "
        "   font-size: 16px; "
        "   color: #ffffff; "
        "   padding: 5px 15px; "
        "   line-height: 1.4; "
        "}";

    // Cuencas actualizadas
    QLabel *tituloCuencas = new QLabel("🌊 Cuencas Principales");
    tituloCuencas->setStyleSheet(estiloSeccion);
    contenidoLayout->addWidget(tituloCuencas);

    QLabel *cuencas = new QLabel(
        "• Cuenca del Vilcanota-Urubamba (Cusco)\n"
        "• Cuenca Amazónica (Loreto)\n"
        "• Cuenca del Rímac (Lima)\n"
        "• Cuenca del Titicaca (Puno)"
        );
    cuencas->setStyleSheet(estiloItem);
    contenidoLayout->addWidget(cuencas);

    // Represas actualizadas
    QLabel *tituloRepresas = new QLabel("💧 Represas Importantes");
    tituloRepresas->setStyleSheet(estiloSeccion);
    contenidoLayout->addWidget(tituloRepresas);

    QLabel *represas = new QLabel(
        "• Represa Gallito Ciego (Cajamarca)\n"
        "• Represa Condoroma (Arequipa)\n"
        "• Represa Poechos (Piura)\n"
        "• Represa Lagunillas (Puno)"
        );
    represas->setStyleSheet(estiloItem);
    contenidoLayout->addWidget(represas);

    // Canales actualizados
    QLabel *tituloCanales = new QLabel("➡️ Canales Principales");
    tituloCanales->setStyleSheet(estiloSeccion);
    contenidoLayout->addWidget(tituloCanales);

    QLabel *canales = new QLabel(
        "• Canal Miguel Checa (Piura)\n"
        "• Canal CHAVIMOCHIC (La Libertad)\n"
        "• Canal Chotano (Cajamarca)\n"
        "• Canal Huachipa (Lima)"
        );
    canales->setStyleSheet(estiloItem);
    contenidoLayout->addWidget(canales);

    scrollArea->setWidget(contenido);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; }");
    layout->addWidget(scrollArea);

    stackedWidget->addWidget(paginaLeyenda);
}

void MainWindow::crearPaginaAyuda()
{
    paginaAyuda = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(paginaAyuda);

    QLabel *tituloAyuda = new QLabel("Guía de Uso");
    tituloAyuda->setStyleSheet(
        "QLabel { "
        "   font-size: 24px; "
        "   font-weight: bold; "
        "   color: #000000; "
        "   padding: 10px; "
        "   border-bottom: 2px solid #3498db; "
        "}"
        );
    layout->addWidget(tituloAyuda);

    QLabel *instrucciones = new QLabel(
        "1. Navegación por el Mapa:\n"
        "   • Haga clic en cualquier departamento del mapa para ver sus recursos hídricos\n"
        "   • La información se mostrará en el panel derecho\n\n"
        "2. Uso de los Botones:\n"
        "   • Información: Vuelve a la vista principal\n"
        "   • Leyenda: Muestra todos los recursos disponibles\n"
        "   • Ayuda: Muestra esta guía de uso\n\n"
        "3. Tipos de Recursos:\n"
        "   • Cuencas: Principales fuentes de agua\n"
        "   • Represas: Almacenamiento y control de agua\n"
        "   • Canales: Distribución y riego"
        );
    instrucciones->setStyleSheet(
        "QLabel { "
        "   font-size: 18px; "
        "   color: #000000; "
        "   padding: 20px; "
        "   padding: 10px; "
        "   line-height: 1.6; "
        "   border-bottom: 2px solid #3498db; "
        "}"
        );
    instrucciones->setWordWrap(true);
    layout->addWidget(instrucciones);

    stackedWidget->addWidget(paginaAyuda);
}

void MainWindow::configurarEstilos()
{
    setStyleSheet(
        "QMainWindow { "
        "   background-color: #ecf0f1; "
        "}"
        "QPushButton { "
        "   background-color: #3498db; "
        "   color: white; "
        "   border: none; "
        "   padding: 10px 20px; "
        "   border-radius: 5px; "
        "   font-size: 16px; "
        "   font-weight: bold; "
        "   min-width: 120px; "
        "}"
        "QPushButton:hover { "
        "   background-color: #2980b9; "
        "}"
        "QPushButton:pressed { "
        "   background-color: #2473a6; "
        "}"
        "QGroupBox { "
        "   background-color: white; "
        "   border-radius: 10px; "
        "   padding: 15px; "
        "   font-size: 18px; "
        "   font-weight: bold; "
        "   color: #2c3e50; "
        "   border: 2px solid #bdc3c7; "
        "}"
        "QScrollArea { "
        "   background-color: white; "
        "   border-radius: 10px; "
        "}"
        );
}

void MainWindow::inicializarRegiones()
{
    // Coordenadas actualizadas para mejor precisión
    regionesMapa = {
        {"Cusco", QRect(400, 480, 80, 60)}, //
        {"Puno", QRect(530, 580, 80, 60)}, //
        {"Loreto", QRect(230, 80, 180, 140)}, //
        {"Piura", QRect(80, 180, 80, 60)},//
        {"Lima", QRect(230, 480, 70, 60)},//
        {"La Libertad", QRect(110, 280, 80, 60)}, //
        {"Cajamarca", QRect(100, 130, 80, 60)}, //
        {"Arequipa", QRect(430, 630, 120, 80)} //
    };

    // Estructura de datos modificada para manejar múltiples recursos por departamento
    recursosHidricos = {
        {"Cusco", {
                      {"CUENCA DEL VILCANOTA-URUBAMBA",
                       "Extensión: 58,735 km²\n"
                       "Principales afluentes: Río Vilcanota, Río Urubamba\n"
                       "Uso principal: Agrícola y generación eléctrica\n"
                       "Población beneficiada: Más de 1 millón de habitantes"}
                  }},

        {"Loreto", {
                       {"CUENCA AMAZÓNICA",
                        "Extensión: 950,000 km²\n"
                        "Principales ríos: Amazonas, Marañón, Ucayali\n"
                        "Navegabilidad: 365 días al año\n"
                        "Importancia: Principal fuente hídrica del país"}
                   }},

        {"Lima", {
                     {"CUENCA DEL RÍMAC",
                      "Extensión: 3,503 km²\n"
                      "Caudal promedio: 31.5 m³/s\n"
                      "Uso principal: Abastecimiento poblacional\n"
                      "Beneficiarios: 10 millones de habitantes"},
                     {"CANAL HUACHIPA",
                      "Longitud: 27.1 km\n"
                      "Capacidad: 10 m³/s\n"
                      "Área beneficiada: 25,000 hectáreas\n"
                      "Uso principal: Agua potable y riego"}
                 }},

        {"Puno", {
                     {"CUENCA DEL TITICACA",
                      "Extensión: 56,270 km²\n"
                      "Altitud: 3,812 msnm\n"
                      "Profundidad máxima: 281 m\n"
                      "Importancia: Mayor lago navegable de Sudamérica"},
                     {"REPRESA LAGUNILLAS",
                      "Capacidad: 585 millones de m³\n"
                      "Altura: 108 metros\n"
                      "Área irrigada: 28,000 hectáreas\n"
                      "Uso principal: Riego y energía"}
                 }},

        {"Arequipa", {
                         {"REPRESA DE CONDOROMA",
                          "Capacidad: 285 millones de m³\n"
                          "Altura: 85 metros\n"
                          "Uso: Riego y energía\n"
                          "Beneficia: Valle de Majes y Siguas"}
                     }},

        {"Cajamarca", {
                          {"REPRESA GALLITO CIEGO",
                           "Capacidad: 573 millones de m³\n"
                           "Altura: 105 metros\n"
                           "Área de embalse: 14.5 km²\n"
                           "Beneficia: Valle Jequetepeque"},
                          {"CANAL CHOTANO",
                           "Longitud: 44.5 km\n"
                           "Capacidad: 13 m³/s\n"
                           "Área irrigada: 30,000 hectáreas\n"
                           "Cultivos: Arroz y caña de azúcar"}
                      }},

        {"Piura", {
                      {"CANAL MIGUEL CHECA",
                       "Longitud: 79 km\n"
                       "Capacidad: 19 m³/s\n"
                       "Área irrigada: 45,000 hectáreas\n"
                       "Cultivos principales: Arroz, algodón, maíz"},
                      {"REPRESA POECHOS",
                       "Capacidad: 1,000 millones de m³\n"
                       "Altura: 48 metros\n"
                       "Área irrigada: 150,000 hectáreas\n"
                       "Beneficiarios: 200,000 habitantes"}
                  }},

        {"La Libertad", {
                            {"CANAL CHAVIMOCHIC",
                             "Longitud: 154 km\n"
                             "Capacidad: 85 m³/s\n"
                             "Área beneficiada: 144,385 hectáreas\n"
                             "Beneficiarios: 150,000 habitantes"}
                        }}
    };
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = ui->labelMapa->mapFrom(this, event->pos());

    for (auto it = regionesMapa.begin(); it != regionesMapa.end(); ++it) {
        if (it.value().contains(pos)) {
            mostrarInformacionRecurso(it.key());
            break;
        }
    }
}

void MainWindow::mostrarInformacionRecurso(const QString &departamento)
{
    if (recursosHidricos.contains(departamento)) {
        stackedWidget->setCurrentWidget(paginaInfo);

        // Construir el texto combinado para todos los recursos del departamento
        QString infoCompleta;
        const auto &recursos = recursosHidricos[departamento];

        for (auto it = recursos.begin(); it != recursos.end(); ++it) {
            if (it != recursos.begin()) {
                infoCompleta += "\n\n" + QString(40, '-') + "\n\n";  // Separador entre recursos
            }
            infoCompleta += it.key() + "\n\n" + it.value();
        }

        labelInfo->setText(infoCompleta);
        infoBox->setTitle("Recursos Hídricos de " + departamento);

        // Ajustar el estilo para mejor legibilidad
        labelInfo->setStyleSheet(
            "QLabel { "
            "   font-size: 16px; "
            "   line-height: 1.6; "
            "   color: #2c3e50; "
            "   padding: 10px; "
            "   background-color: #f8f9fa; "
            "   border-radius: 5px; "
            "}"
            );
    }
}

void MainWindow::mostrarLeyenda()
{
    stackedWidget->setCurrentWidget(paginaLeyenda);
}

void MainWindow::mostrarAyuda()
{
    stackedWidget->setCurrentWidget(paginaAyuda);
}

void MainWindow::mostrarMapa()
{
    stackedWidget->setCurrentWidget(paginaInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}
