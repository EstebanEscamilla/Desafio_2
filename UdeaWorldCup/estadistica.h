#ifndef ESTADISTICA_H
#define ESTADISTICA_H

class Estadistica{
private:
    int goles;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int minutos;
public:

    Estadistica();          //Constructor
    ~Estadistica();         //Destructor

    // Metodo para actualizar stats
    void actualizarStats(int golesNuevos, int asistNuevas, int amarillasNuevas, int rojasNuevas, int minsNuevos);
    void setGoles(int _goles);

    // Getters para consultar los atributos
    int getGoles();
    int getAsistencias();
    int getTarjetasAmarillas();
    int getTarjetasRojas();
    int getMinutos();
};
#endif // ESTADISTICA_H
