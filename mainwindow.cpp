// mainwindow.cpp
#include "mainwindow.h" // Incluye el encabezado de la clase MainWindow
#include "ui_mainwindow.h" // Incluye el encabezado generado para la interfaz de usuario
#include <QPushButton> // Incluye la clase QPushButton para trabajar con botones
#include <QMessageBox> // Incluye la clase QMessageBox para mostrar mensajes emergentes

// Constructor de la clase MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) // Llama al constructor de la clase base QMainWindow
    , ui(new Ui::MainWindow) // Inicializa el puntero ui a un nuevo objeto de la interfaz de usuario
{
    ui->setupUi(this); // Configura la interfaz de usuario en la ventana principal
    inicializarRecursos(); // Llama a la función para inicializar los recursos necesarios
    configurarConexiones(); // Llama a la función para configurar las conexiones de señales y slots
}

// Destructor de la clase MainWindow
MainWindow::~MainWindow()
{
    delete ui; // Libera la memoria ocupada por el objeto ui
}

// Método para configurar conexiones de señales y slots
void MainWindow::configurarConexiones()
{
    // Conectar la señal recursoSeleccionado con el slot mostrarInformacionRecurso
    connect(this, &MainWindow::recursoSeleccionado, // Señal emitida cuando se selecciona un recurso
            this, &MainWindow::mostrarInformacionRecurso); // Slot que muestra la información del recurso

    // Conectar botones de cuencas
    QVector<QPushButton*> botonesCuencas = { // Crea un vector de punteros a QPushButton para las cuencas
        ui->cuencaSanJuan, ui->cuencaPatia, // Añade los botones de cuenca
        ui->cuencaMira, ui->cuencaBaudo
    };
    for(auto boton : botonesCuencas) { // Itera sobre cada botón de cuenca
        connect(boton, &QPushButton::clicked, // Conecta la señal clicked del botón
                this, &MainWindow::onBotonRecursoClicked); // Al slot onBotonRecursoClicked
        boton->setProperty("tipo", RecursoHidrico::CUENCA); // Establece una propiedad 'tipo' al botón
    }

    // Conectar botones de represas
    QVector<QPushButton*> botonesRepresas = { // Crea un vector de punteros a QPushButton para las represas
        ui->represaCalima, ui->represaSalvajina, // Añade los botones de represa
        ui->represaAnchicaya
    };
    for(auto boton : botonesRepresas) { // Itera sobre cada botón de represa
        connect(boton, &QPushButton::clicked, // Conecta la señal clicked del botón
                this, &MainWindow::onBotonRecursoClicked); // Al slot onBotonRecursoClicked
        boton->setProperty("tipo", RecursoHidrico::REPRESA); // Establece una propiedad 'tipo' al botón
    }

    // Conectar botones de canales
    QVector<QPushButton*> botonesCanales = { // Crea un vector de punteros a QPushButton para los canales
        ui->canalNaranjo, ui->canalDique, // Añade los botones de canal
        ui->canalPichinde
    };
    for(auto boton : botonesCanales) { // Itera sobre cada botón de canal
        connect(boton, &QPushButton::clicked, // Conecta la señal clicked del botón
                this, &MainWindow::onBotonRecursoClicked); // Al slot onBotonRecursoClicked
        boton->setProperty("tipo", RecursoHidrico::CANAL); // Establece una propiedad 'tipo' al botón
    }
}

// Método llamado cuando se hace clic en un botón de recurso
void MainWindow::onBotonRecursoClicked()
{
    QPushButton* boton = qobject_cast<QPushButton*>(sender()); // Obtiene el botón que emitió la señal
    if (!boton) return; // Si no se puede cast a QPushButton, retorna

    // Obtiene el tipo del recurso a partir de la propiedad del botón
    RecursoHidrico::Tipo tipo = static_cast<RecursoHidrico::Tipo>(
        boton->property("tipo").toInt() // Convierte la propiedad 'tipo' a entero y luego a Tipo
        );

    // Busca el recurso por nombre y tipo utilizando el texto del botón
    const RecursoHidrico* recurso = buscarRecursoPorNombreYTipo(
        boton->text(), tipo // Llama a la función de búsqueda con el texto y tipo
        );

    // Si el recurso se encuentra, emite la señal recursoSeleccionado
    if (recurso) {
        emit recursoSeleccionado(*recurso); // Emite la señal con el recurso encontrado
    }
}

// Método para mostrar la información del recurso seleccionado
void MainWindow::mostrarInformacionRecurso(const RecursoHidrico& recurso)
{
    // Crea un texto HTML para mostrar la información del recurso
    QString infoText = "<div style='text-align: center;'>"; // Inicia un contenedor centrado
    infoText += "<h2>" + recurso.getNombre() + "</h2>"; // Agrega el nombre del recurso en un encabezado
    infoText += "</div>"; // Cierra el contenedor centrado
    infoText += "<div style='text-align: justify;'>"; // Inicia un contenedor justificado
    infoText += "<p>" + recurso.getDescripcion() + "</p>"; // Agrega la descripción del recurso
    infoText += "<p><strong>Datos Técnicos:</strong><br>" + recurso.getDatos().replace("\n", "<br>") + "</p>"; // Agrega datos técnicos, reemplazando saltos de línea con etiquetas <br>
    infoText += "<p><strong>Importancia:</strong><br>" + recurso.getImportancia() + "</p>"; // Agrega la importancia del recurso
    infoText += "</div>"; // Cierra el contenedor justificado

    ui->infoLabel->setText(infoText); // Establece el texto formateado en el label de información
}
// Método para buscar un recurso hídrico por su nombre y tipo
const RecursoHidrico* MainWindow::buscarRecursoPorNombreYTipo(
    const QString& nombre, RecursoHidrico::Tipo tipo) // Parámetros: nombre del recurso y tipo
{
    // Utiliza std::find_if para buscar en la lista de recursos
    auto it = std::find_if(recursos.begin(), recursos.end(),
                           [&](const RecursoHidrico& r) { // Lambda que compara el nombre y el tipo
                               return r.getNombre() == nombre && r.getTipo() == tipo;
                           });

    // Devuelve un puntero al recurso encontrado o nullptr si no se encuentra
    return it != recursos.end() ? &(*it) : nullptr;
}

// Método para inicializar los recursos hídricos
void MainWindow::inicializarRecursos()
{
    // Inicializar Cuencas
    recursos.append(RecursoHidrico( // Agrega un recurso hídrico de tipo CUENCA
        "Cuenca del Río San Juan", // Nombre
        RecursoHidrico::CUENCA, // Tipo
        "La cuenca del río San Juan está ubicada en el departamento del Chocó. Es una de las cuencas más caudalosas y biodiversas del Pacífico. Esta región está caracterizada por su alta pluviosidad y su importancia ecológica, siendo un refugio para una gran cantidad de especies endémicas.",
        "• Extensión: 15,000 km²\n• Caudal medio: 2,550 m³/s\n• Longitud del río: 380 km\n•Ubicación: Departamento del Chocó\n• Altitud: 100-400 m sobre el nivel del mar",
        "Principal fuente hídrica del Chocó y una de las regiones más biodiversas del mundo, vital para los locales que dependen de la pesca y la agricultura."
        ));

    recursos.append(RecursoHidrico(
        "Cuenca del Río Patía",
        RecursoHidrico::CUENCA,
        "Es la cuenca más grande del Pacífico colombiano, ubicada en los departamentos de Cauca y Nariño. Se caracteriza por su relevancia agrícola y como fuente de agua para los locales. El río Patía es conocido por su longitud y por ser un importante afluente de la región, utilizado tanto para riego como para la pesca.",
        "• Extensión: 24,000 km²\n• Longitud: 400 km\n• Caudal medio: 1,290 m³/s\n• Principales afluentes: Mayo, Juanambú\n• Población dependiente: 1 millón de habitantes",
        "Vital para la agricultura, pesca y sostenimiento de las poblaciones en el suroccidente colombiano, además de su importancia cultural en la región."
        ));

    recursos.append(RecursoHidrico(
        "Cuenca del Río Mira",
        RecursoHidrico::CUENCA,
        "La cuenca del río Mira se encuentra en el suroccidente colombiano, en los departamentos de Nariño y Esmeraldas, compartida con Ecuador. Se destaca por su biodiversidad y su uso en la agricultura, especialmente en el cultivo de palma africana y banano.",
        "• Extensión: 11,200 km²\n• Longitud: 145 km\n• Caudal medio: 820 m³/s\n• Principales afluentes: Guiza, Esmita\n• Población dependiente: 300,000 habitantes",
        "Es crucial para la agricultura en la región y el sustento de las comunidades rurales en la frontera entre Colombia y Ecuador."
        ));

    recursos.append(RecursoHidrico(
        "Cuenca del Río Baudó",
        RecursoHidrico::CUENCA,
        "Ubicada en el departamento del Chocó, la cuenca del río Baudó es de gran importancia ecológica por su biodiversidad y las comunidades indígenas que dependen de sus aguas. La región está aislada y cuenta con uno de los mayores índices de pluviosidad del mundo.",
        "• Extensión: 8,000 km²\n• Longitud: 225 km\n• Caudal medio: 1,100 m³/s\n• Precipitación media: 7,000 mm/año\n• Población dependiente: 50,000 habitantes",
        "Vital para las comunidades indígenas locales y como reserva ecológica que alberga especies endémicas del Pacífico colombiano."
        ));

    // Inicializar Represas
    recursos.append(RecursoHidrico(
        "Represa Calima",
        RecursoHidrico::REPRESA,
        "Construida en 1966, la Represa Calima se encuentra en el departamento del Valle del Cauca. Esta infraestructura es clave para la generación de energía hidroeléctrica y ha impulsado el desarrollo del turismo en la región. Sus aguas son utilizadas tanto para recreación como para la irrigación de cultivos cercanos.",
        "• Capacidad: 581 millones m³\n• Altura de la presa: 115 m\n• Área del embalse: 1,934 ha\n• Potencia instalada: 132 MW\n• Ubicación: Valle del Cauca, Colombia",
        "Es crucial para la generación eléctrica en el suroccidente, además de ser un lugar turístico con actividades como la navegación y pesca deportiva."
        ));

    recursos.append(RecursoHidrico(
        "Represa Salvajina",
        RecursoHidrico::REPRESA,
        "La Represa Salvajina, construida en 1985, está ubicada sobre el río Cauca. Su función principal es la regulación del caudal del río para evitar inundaciones en la región del Valle del Cauca. Además, es una fuente importante de energía hidroeléctrica y un recurso vital para las comunidades circundantes.",
        "• Capacidad: 875 millones m³\n• Altura: 148 m\n• Longitud de la corona: 400 m\n• Potencia instalada: 270 MW\n• Año de construcción: 1985",
        "Fundamental para la generación hidroeléctrica y el control de inundaciones, garantizando el bienestar de las comunidades en su área de influencia."
        ));

    recursos.append(RecursoHidrico(
        "Represa Alto Anchicayá",
        RecursoHidrico::REPRESA,
        "La Represa Alto Anchicayá es una importante infraestructura hidroeléctrica ubicada en el departamento del Valle del Cauca. Esta represa es fundamental para el abastecimiento de agua potable, control de inundaciones y la generación de energía en la región.",
        "• Capacidad: 481 millones m³\n• Altura de la presa: 78 m\n• Potencia instalada: 120 MW\n• Año de construcción: 1955\n• Controla la cuenca alta del río Anchicayá",
        "Clave para la regulación del caudal del río Anchicayá, contribuyendo a evitar inundaciones y abastecer de agua potable a las poblaciones cercanas."
        ));

    // Inicializar Canales
    recursos.append(RecursoHidrico(
        "Canal Naranjo",
        RecursoHidrico::CANAL,
        "El Canal Naranjo es una obra de infraestructura que conecta el río Patía con el río Sanquianga, permitiendo el desvío de aguas para mejorar el control hídrico en la región. Su construcción ha sido clave para el desarrollo de zonas agrícolas y la prevención de inundaciones.",
        "• Longitud: 1.3 km\n• Ancho promedio: 18 m\n• Caudal desviado: 100-200 m³/s\n• Año de construcción: 1973\n• Ubicación: Departamento de Nariño, Colombia",
        "Ha modificado significativamente la dinámica hídrica regional, beneficiando a agricultores y poblaciones aledañas."
        ));

    recursos.append(RecursoHidrico(
        "Canal del Dique",
        RecursoHidrico::CANAL,
        "Este canal artificial conecta la bahía de Cartagena con el río Magdalena, permitiendo una vía de navegación clave para el comercio y el transporte. Además, cumple una función importante en el control de inundaciones y el suministro de agua a las regiones cercanas.",
        "• Longitud: 115 km\n• Ancho: 100 m\n• Profundidad: 2.5 m\n• Caudal medio: 540 m³/s\n Función principal: Navegación y control hídrico",
        "Vital para el transporte de mercancías y la navegación, además de su importancia en el manejo de aguas en el Caribe colombiano."
        ));

    recursos.append(RecursoHidrico(
        "Canal Pichindé",
        RecursoHidrico::CANAL,
        "El Canal Pichindé es una obra menor utilizada principalmente para el riego de cultivos en la región del Valle del Cauca. Su construcción ha sido clave para la expansión agrícola en la zona.",
        "• Longitud: 5 km\n• Ancho promedio: 10 m\n• Caudal desviado: 50-70 m³/s\n• Año de construcción: 1960\n• Ubicación: Valle del Cauca, Colombia",
        "Es esencial para la agricultura local, permitiendo un riego eficiente de los cultivos en la región."
        ));
}
