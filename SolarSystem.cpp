#include "SolarSystem.h"
SolarSystem::SolarSystem()
{
    fps = 60.0f;
    delta = DAY; // 1 day
    delta_delta = 2;

    // Time elapsed since J2000
    T = (time(NULL) - TIME_1970_2000)/JEDAY;

    move();

    solarTypes.insert("CelestialBody");
    solarTypes.insert("SolSysBody");
    solarTypes.insert("Comet");
    solarTypes.insert("Satellite");
    drawTypes.insert("Body");
    drawTypes.insert("Rings");
}

void SolarSystem::init()
{
    text = new Text(tm.getTexture("Textures/font.bmp"));
}

SolarSystem::~SolarSystem()
{
    Bodies.clear();
}

void SolarSystem::addBody(CelestialBody *p)
{
    p->setText(text);
    Bodies.push_back(p);
}

void SolarSystem::nextFrame()
{
    if (moves || (!moves && steps))
    {
        //TODO: extend this to actual objects to prevent rotating
        T+=delta/fps;
        if (steps)
            stop();
    }

    if (prompt)
        text->setWScale(WScale);
    else
        text->setWScale(0);

    std::list< CelestialBody* >::iterator it;
    for (it = Bodies.begin(); it != Bodies.end(); ++it)
    {
        (*it)->nextFrame(T);
        (*it)->Draw();
    }

    text->setWScale(1);
    text->setScale(1.0);
    text->setPos(Vector());
}

void SolarSystem::speedUp()
{
    delta *= delta_delta;
}

void SolarSystem::slowDown()
{
    delta /= delta_delta;
}

time_t SolarSystem::getTime()
{
    double tt = T*JEDAY+TIME_1970_2000;
    time_t raw = (int) tt;
    return raw;
}

double SolarSystem::getSpeed()
{
    return delta/DAY;
}

void SolarSystem::setFPS(double fps)
{
    this->fps = fps;
}

void SolarSystem::setWScale(double WScale)
{
    this->WScale = WScale;
}

void SolarSystem::setPrompt(bool prompt)
{
    this->prompt = prompt;
}

void SolarSystem::move()
{
    moves = true;
    steps = false;
}

void SolarSystem::step()
{
    moves = false;
    steps = true;
}

void SolarSystem::stop()
{
    moves = false;
    steps = false;
}

void SolarSystem::readXML(string filename)
{
    xmlpp::DomParser parser;
    parser.parse_file(filename.c_str());

    const xmlpp::Node *root = parser.get_document()->get_root_node();
    parseXML(root);
}

void SolarSystem::parseXML(const xmlpp::Node* node, CelestialBody* p)
{
    //std::cout << std::endl;
    //std::cout << p << std::endl;
    const xmlpp::Node::NodeList items = node->get_children();
    for (auto i = items.begin(); i != items.end(); ++i)
    {
        const xmlpp::Element *elem = dynamic_cast<const xmlpp::Element *>(*i);
        if (elem)
        {
        //std::cout << "Йо, нигга" << std::endl;
            auto type = elem->get_name();
            if (solarTypes.find(type) != solarTypes.end())
            {
                auto name = elem->get_attribute("name")->get_value();
                //std::cout << type << ": " << name << std::endl;
                if (!type.compare("CelestialBody"))
                {
                    CelestialBody* celBody = new CelestialBody();
                    celBody->name = name;
                    addBody(celBody);
                    parseXML(*i, celBody);
                }
                else
                {
                    auto attr = elem->get_attributes();
                    int j=0;
                    double orb[7];
                    for (auto i = ++(attr.begin()); i != attr.end(), j < 7; ++i, ++j)
                    {
                        orb[j] = atof((*i)->get_value().c_str());
                        //std::cout << orb[j] << std::endl;
                    }
                    if (!type.compare("SolSysBody"))
                    {
                        SolSysBody* sysBody = new SolSysBody(orb[0], orb[1], orb[2], orb[3], orb[4], orb[5], orb[6]);
                        sysBody->name = name;
                        addBody(sysBody);
                        parseXML(*i, sysBody);
                    }
                    if (!type.compare("Comet"))
                    {
                        Comet* comBody = new Comet(orb[0], orb[1], orb[2], orb[3], orb[4], orb[5], orb[6]);
                        Tail* tail = new Tail(tm.getTexture("Textures/flare.bmp"));
                        comBody->addTail(tail);
                        addBody(comBody);
                        parseXML(*i, comBody);
                    }
                    if (!type.compare("Satellite"))
                    {
                        Satellite* satBody = new Satellite(orb[0], orb[1], orb[2], orb[3], orb[4], orb[5], orb[6]);
                        satBody->setPlanet(dynamic_cast<SolSysBody*>(p));
                        satBody->name = name;
                        addBody(satBody);
                        parseXML(*i, satBody);
                    }
                }
            }
            if (p)
            {
                if (drawTypes.find(type) != drawTypes.end())
                {
                    auto texture = string((elem->get_attribute("texture")->get_value()).c_str());
                    GLuint tex = tm.getTexture(texture);
                    //std::cout << type << ": " << texture << std::endl;
                    if (!type.compare("Body"))
                    {
                        auto R = elem->get_attribute("radius")->get_value();
                        double r = atof(R.c_str());
                        r = scaleR(r, p);

                        Body* body = new Body(r, tex);
                        //std::cout << r << std::endl;
                        std::cout << p->name << " " << r << std::endl;
                        p->add(body);
                    }
                    if (!type.compare("Rings"))
                    {
                        double r[2];
                        for( int i = 0 ; i < 2 ; i++ )
                        {
                            std::ostringstream oss;
                            std::string text = "r";
                            oss << i+1;
                            text += oss.str();

                            auto R = elem->get_attribute(text)->get_value();
                            r[i] = atof(R.c_str());
                            r[i] = scaleR(r[i], p);
                            //std::cout << r[i] << std::endl;
                        }

                        Rings* rings = new Rings(r[1], r[2], tex);
                        //std::cout << p->name << std::endl;
                        p->add(rings);
                    }
                }
            }
        }
    }
}

double scaleR(double r, CelestialBody* p)
{
    double a = p->getA();
    double scale;
    if (r < 7000)
        scale = r/7000;
    else if (r < 80000)
        scale = r/70000;
    else
        scale = r/100000; //FIXME
    r /= AU; //useless

    double high = 0.08;
    //double a = 1;
    double high_threshold = high*a;
    p->setScale(high_threshold);

    return scale;
}
