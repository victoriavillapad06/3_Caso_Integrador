//
// Created by victo on 26/11/2024.
//
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

// Colores de consola para destacar el texto.
struct ColorConsole {
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
    static constexpr auto reset = "\033[0m"; // Restablece los colores.
};

// Simulación de un cuadro de texto donde se despliega el contenido del archivo.
struct ConsoleBox {
    void new_text() {
        // Simula inicialización del cuadro de texto
        cout << "[ConsoleBox] Nuevo texto inicializado." << endl;
    }
    void set_text(const string &text) {
        // Muestra el texto en el cuadro de texto
        cout << "[ConsoleBox] Contenido cargado:" << endl;
        cout << text << endl;
    }
};

// Instancia global de ConsoleBox.
ConsoleBox *consoleBox = new ConsoleBox; // Supongamos que ya está inicializado.

// Función para cargar un script desde un archivo dado.
void load_script(const char* filename, bool show_script = false) {
    if (!filename || *filename == '\0') {
        cerr << "Error: nombre de archivo vacío o nulo." << endl;
        return;
    }

    // Abre el archivo en modo binario para manejar cualquier tipo de contenido.
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: no se pudo abrir el archivo '" << filename << "'." << endl;
        return;
    }

    // Lee todo el contenido del archivo en una cadena.
    string script((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // Verifica si hubo un error al leer el archivo.
    if (file.bad()) {
        cerr << "Error: ocurrió un problema al leer el archivo." << endl;
        return;
    }

    // Muestra el contenido en la consola si `show_script` es verdadero.
    if (show_script) {
        cout << ColorConsole::fg_blue << ColorConsole::bg_white;
        cout << script << ColorConsole::reset << endl;
    }

    // Simula cargar el texto en un cuadro de texto.
    consoleBox->new_text();
    consoleBox->set_text(script);
}

// Función para solicitar el nombre del archivo al usuario y cargarlo.
void load_script() {
    cout << "Ingrese el nombre del archivo: ";
    string filename;
    getline(cin, filename); // Permite nombres con espacios.

    if (filename.empty()) {
        cerr << "Error: el nombre del archivo no puede estar vacío." << endl;
        return;
    }

    // Llama a la función sobrecargada para cargar el archivo.
    load_script(filename.c_str(), true);
}

// Programa principal para probar las funciones.
int main() {
    try {
        // Llama a la función sin argumentos para probar la interacción con el usuario.
        load_script();

        // Opcionalmente, puedes probar con un archivo específico.
        // load_script("example.txt", true);
    } catch (const exception &e) {
        cerr << "Excepción no manejada: " << e.what() << endl;
    } catch (...) {
        cerr << "Excepción desconocida capturada." << endl;
    }

    return 0;
}
