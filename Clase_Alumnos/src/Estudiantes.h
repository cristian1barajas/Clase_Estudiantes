class Estudiantes
{
public:
    int cc = 0;
    String apellido, nombre, correo;
    int edad;
    float nota1, nota2, nota3, notaFinal;
public:
    //Estudiantes(int, String, String, String, int, float, float, float);
    void registrarEstudiante(int, String, String, String, int, float, float, float);
    String retornarDatos();
    String modificarNotas(float, float, float);
    void consultarNota();
};

/*
Estudiantes::Estudiantes(int _cc_, String _apellido_, String _nombre_, String _correo_, int _edad_, float _nota1_, float _nota2_, float _nota3_)
{
    cc = _cc_;
    apellido = _apellido_;
    nombre = _nombre_;
    correo = _correo_;
    edad = _edad_;
    nota1 = _nota1_;
    nota2 = _nota2_;
    nota3 = _nota3_;
    notaFinal = (nota1 + nota2 + nota3) / 3;
}
*/

void Estudiantes::registrarEstudiante(int _cc_, String _apellido_, String _nombre_, String _correo_, int _edad_, float _nota1_, float _nota2_, float _nota3_) {
    cc = _cc_;
    apellido = _apellido_;
    nombre = _nombre_;
    correo = _correo_;
    edad = _edad_;
    nota1 = _nota1_;
    nota2 = _nota2_;
    nota3 = _nota3_;
    notaFinal = (nota1 + nota2 + nota3) / 3;
}

String Estudiantes::retornarDatos() {
    return String("- " + apellido + " " + nombre + " Nota Final: "  + notaFinal);
}

String Estudiantes::modificarNotas(float _nota1_, float _nota2_, float _nota3_) {
    String mensaje;
    if (_nota1_ > nota1)
    {
        mensaje = "No tienes saldo suficiente";
    }
    return mensaje;
    
    nota1 = _nota1_;
    nota2 = _nota2_;
    nota3 = _nota3_;
    notaFinal = (nota1 + nota2 + nota3) / 3;
}

void Estudiantes::consultarNota() {

}