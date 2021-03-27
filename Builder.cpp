#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Declaracion del builder
class ConversacionBuilder;

class dialogo
{
public:
    friend class ConversacionBuilder;  // el builder puede acceder a los privados

    static ConversacionBuilder make();

    string to_string() const {
        stringstream stream;
        stream << "Profesor:" << inicio
               << "\nEstudiante:" << respuesta
               << "\nProfesor:" << peticion
               << "\nEstudiante:" << final;
        return stream.str();
    }

private:
    dialogo() = default; // restringe la construccion al buider

    string inicio;
    string respuesta;
    string peticion;
    string final;
};

class ConversacionBuilder
{
public:
    ConversacionBuilder& diag1(const string &conv1) {
        d_conversacion.inicio = conv1;
        return *this;
    }

    ConversacionBuilder& diag2(const string &conv2) {
        d_conversacion.respuesta = conv2;
        return *this;
    }

    ConversacionBuilder& diag3(const string &conv3) {
        d_conversacion.peticion = conv3;
        return *this;
    }

    ConversacionBuilder& diag4(const string &conv4) {
        d_conversacion.final = conv4;
        return *this;
    }

    operator dialogo&&() {
        cout << "Se ha realizado un movimiento al builder \n" << endl;
        return std::move(d_conversacion); // notifica el movimiento
    }

private:
    dialogo d_conversacion;
};

ConversacionBuilder dialogo::make()
{
    return ConversacionBuilder();
}

std::ostream& operator <<(std::ostream& stream, const dialogo& email)
{
    stream << email.to_string();
    return stream;
}


int main()
{
    dialogo build1 = dialogo::make().diag1("Cual patron usaron?")
            .diag2("Builder")
            .diag3("Corran el programa")
            .diag4("Este es el programa");

    cout << build1 << endl;

    dialogo build2 = dialogo::make().diag1("Cuantos dialogos aparecen?")
            .diag2("Creo que 8")
            .diag3("Muy pocos no?")
            .diag4("Pues son dos llamadas al builder");

    cout << build2 << endl;
}