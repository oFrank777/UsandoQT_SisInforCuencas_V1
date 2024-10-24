#ifndef RECURSOHIDRICO_H  // Evita la inclusión múltiple de este archivo de encabezado.
#define RECURSOHIDRICO_H

#include <QString>  // Incluye la clase QString de Qt, que se utiliza para manejar cadenas de texto.

class RecursoHidrico {  // Define la clase RecursoHidrico que representa un recurso hídrico.
public:
    enum Tipo {  // Define un enumerador para los diferentes tipos de recursos hídricos.
        CUENCA,  // Tipo cuenca.
        REPRESA,  // Tipo represa.
        CANAL    // Tipo canal.
    };

    // Constructor que inicializa los atributos de la clase.
    RecursoHidrico(const QString& nombre, Tipo tipo, const QString& descripcion,
                   const QString& datos, const QString& importancia);

    // Métodos de acceso (getters) para obtener los atributos de la clase.
    QString getNombre() const { return nombre; }  // Devuelve el nombre del recurso.
    QString getDescripcion() const { return descripcion; }  // Devuelve la descripción del recurso.
    QString getDatos() const { return datos; }  // Devuelve los datos del recurso.
    QString getImportancia() const { return importancia; }  // Devuelve la importancia del recurso.
    Tipo getTipo() const { return tipo; }  // Devuelve el tipo del recurso.

private:  // Sección privada donde se declaran los miembros de la clase.
    QString nombre;  // Almacena el nombre del recurso.
    Tipo tipo;  // Almacena el tipo del recurso (como enumerador).
    QString descripcion;  // Almacena la descripción del recurso.
    QString datos;  // Almacena datos adicionales sobre el recurso.
    QString importancia;  // Almacena la importancia del recurso.
};

#endif // RECURSOHIDRICO_H  // Fin de la directiva de inclusión condicional.
