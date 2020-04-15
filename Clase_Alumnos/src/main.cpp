#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Estudiantes.h>

#define INDEX 100

char auth[] = "H9fCjQrQJOFJMgFkcafoi0eL124cYQCJ";
char ssid[] = "BotLAB";
char pass[] = "80808080";

int contEstudiantes, contTeclaEnter = 0;
int _cc, _edad, _opcion;
String _apellido, _nombre, _correo;
float _nota1, _nota2, _nota3;

WidgetTerminal terminal(V1);
Estudiantes baseDatos[INDEX];

void reset() {
  terminal.println("");
  terminal.print("             ");
  for (int i = 0; i < 4; i++) {
    terminal.print("*");
    terminal.flush();
    delay(500);
  }
  terminal.print("Thanks...!");
  terminal.flush();
  for (int i = 0; i < 4; i++) {
    terminal.print("*");
    terminal.flush();
    delay(500);
  }
}

void menu() {
  terminal.clear();
  terminal.println(F("       |****************************|"));
  terminal.println(F("       |**|      Bienvenidos     |**|"));
  terminal.println(F("       |**|         Menu         |**|"));
  terminal.println(F("       |****************************|"));
  terminal.println("");
  terminal.println("Seleccione una de las siguientes opciones:");
  terminal.println("1.- Registrar estudiante");
  terminal.println("2.- Imprimir estudiantes");
  terminal.println("3.- Buscar estudiante");
  terminal.println("4.- Modificar notas de un estudiante");
  terminal.println("5.- Salir");
  terminal.flush();
}

BLYNK_WRITE(V1) {
  String i = param.asStr();
  contTeclaEnter++;
  switch (contTeclaEnter)
  {
  case 1:
    _opcion = i.toInt();
    switch (_opcion)
    {
    case 1:
      terminal.println(" ");
      terminal.println("       ***Registro de estudiantes***");
      terminal.println("Ingrese el numero de documento: ");
      terminal.flush();
      break;
    case 2:
      terminal.println("Imprimiendo estudiantes");
      for (int i = 0; i < INDEX; i++) {
        if (baseDatos[i].cc == 0) {
          break;
        }
        String datos = baseDatos[i].retornarDatos();
        terminal.println(datos);
        terminal.flush();
      }
      contTeclaEnter = 0;
      reset();
      menu();
      break;
    case 3:
      terminal.println("Buscar Estudiante");
      terminal.println("Indique el numero de documento por favor: ");
      break;
    case 4:
      terminal.println("Edicion de notas");
      terminal.println("Indique el numero de documento por favor: ");
      break;
    case 5:
      terminal.println("Salida inminente!");
      contTeclaEnter = 0;
      reset();
      menu();
      break;
    default:
      terminal.println("Opcion invalida");
      contTeclaEnter = 0;
      reset();
      menu();
      break;
    }
    terminal.flush();
    break;
  case 2:
    _cc = i.toInt(); 
    if (_opcion == 1) {
      terminal.println("Apellido: ");
      terminal.flush();
      break;
    } else if (_opcion == 3) {
      for (int i = 0; i < INDEX; i++) {
        if (_cc == baseDatos[i].cc) {
          String datos = baseDatos[i].retornarDatos();
          terminal.println(datos);
          terminal.flush();
          reset();
          menu();
          contTeclaEnter = 0;
          break;
        } else if (i == INDEX - 1)
        {
          terminal.println("Lo siento!");
          terminal.println("El estudiante no existe");
          terminal.flush();
          reset();
          menu();
          contTeclaEnter = 0;
        }
      }
    } else if (_opcion == 4) {
        terminal.println("Ingrese nota 1:");
        terminal.flush();
    }
    break;
  case 3:
    if (_opcion == 1) {
      _apellido = i;
      terminal.println("Nombre: ");
      terminal.flush();
    } else if (_opcion == 4) {
      _nota1 = i.toFloat();
      terminal.println("Ingrese nota 2:");
      terminal.flush();
    }
    break;
  case 4:
    if (_opcion == 1) {
      _nombre = i;
      terminal.println("Edad: ");
      terminal.flush();
    } else if (_opcion == 4) {
        _nota2 = i.toFloat();
        terminal.println("Ingrese nota 3:");
        terminal.flush();
    }
    break;
  case 5: 
    if (_opcion == 1) {
      _edad = i.toInt();
      terminal.println("Correo: ");
      terminal.flush();
    } else if (_opcion == 4) {
        _nota3 = i.toFloat();
        for (int i = 0; i < INDEX; i++) {
        if (_cc == baseDatos[i].cc) {
          baseDatos[i].modificarNotas(_nota1, _nota2, _nota3);
          //baseDatos[i].nota1 = _nota1; Esto ya no vá, se invoca el metodo modificar notas... 
          //baseDatos[i].nota2 = _nota2; ya lo probe y funciona OK...!
          //baseDatos[i].nota3 = _nota3;
          String datos = baseDatos[i].retornarDatos();
          terminal.println(datos);
          terminal.flush();
          reset();
          menu();
          contTeclaEnter = 0;
          break;
        } else if (i == INDEX - 1)
        {
          terminal.println("Lo siento!");
          terminal.println("El estudiante no existe");
          terminal.flush();
          reset();
          menu();
          contTeclaEnter = 0;
        }
      }
    }
    break;
  case 6:
    _correo = i;
    terminal.println("Nota 1: ");
    terminal.flush();
    break;
  case 7:
    _nota1 = i.toFloat();
    terminal.println("Nota 2: ");
    terminal.flush();
    break;
  case 8:
    _nota2 = i.toFloat();
    terminal.println("Nota 3: ");
    terminal.flush();
    break;
  case 9:
    _nota3 = i.toFloat();
    terminal.println("Registrando estudiante!");
    baseDatos[contEstudiantes].registrarEstudiante(_cc, _apellido, _nombre, _correo, _edad, _nota1, _nota2, _nota3);
    terminal.println("Gracias el estudiante ha sido registrado con exito");
    terminal.println("en la posición " + String(contEstudiantes)+ " de la base de datos");
    reset();
    menu();
    contEstudiantes++;
    contTeclaEnter = 0;
    terminal.flush();
    break;
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  terminal.clear();
  menu();
}

void loop() {
  Blynk.run();
}