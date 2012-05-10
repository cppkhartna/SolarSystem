#include "TextureManager.h"
#include "Comet.h"
#include <cstring>
#include <libxml++/libxml++.h>
#include <set>

#define TIME_1970_2000 946684800
#define DAY (1.0/365.0/100.0)
#define JEDAY (365.25*24.0*3600.0*100.0)

using namespace std;
class SolarSystem
{
public:
    SolarSystem ();
    virtual ~SolarSystem ();
    void init();
    void readXML(string filename);
    void parseXML(const xmlpp::Node *node, CelestialBody* p = NULL);
    void nextFrame();
    void addBody(CelestialBody *p);
    void speedUp();
    void slowDown();
    void move();
    void step();
    void stop();
    Text* text;
    time_t getTime();
    double getSpeed();

private:
    /* data */
    std::list< CelestialBody* > Bodies;
    std::set<Glib::ustring> solarTypes;
    std::set<Glib::ustring> drawTypes;
    TextureManager tm;
    double T; //time
    double delta;
    double delta_delta;
    bool moves, steps;
};

double scaleR(double r, CelestialBody* p);
