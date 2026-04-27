#ifndef ESTADISTICA_H
#define ESTADISTICA_H

class Estadistica {
private:
    int goles;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int minutos;

public:
    Estadistica();
    ~Estadistica();

    Estadistica& operator+=(const Estadistica& statsPartido);

    void actualizarStats(int golesNuevos, int asistNuevas, int amarillasNuevas, int rojasNuevas, int minsNuevos);
    void setGoles(int _goles);

    int getGoles() const;
    int getAsistencias() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getMinutos() const;
};
#endif // ESTADISTICA_H
