#include "SolarSystem.h"
SolarSystem::SolarSystem()
{
    delta = 1.0f/6000.0f;
    delta_delta = 10;

    solarTypes.insert("CelestialBody");
    solarTypes.insert("SolSysBody");
    solarTypes.insert("Comet");
    solarTypes.insert("Satellite");
    drawTypes.insert("Body");
}

SolarSystem::~SolarSystem()
{
    Bodies.clear();
}

void SolarSystem::addBody(CelestialBody *p)
{
    Bodies.push_back(p);
}

void SolarSystem::nextFrame()
{
    T+=delta;

    std::list< CelestialBody* >::iterator it;
    for (it = Bodies.begin(); it != Bodies.end(); ++it)
    {
        (*it)->nextFrame(T);
        (*it)->Draw();
    }
}

void SolarSystem::speedUp()
{
    delta *= delta_delta;
}

void SolarSystem::slowDown()
{
    delta /= delta_delta;
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
    const xmlpp::Node::NodeList items = node->get_children();
    for (auto i = items.begin(); i != items.end(); ++i)
    {
        const xmlpp::Element *elem = dynamic_cast<const xmlpp::Element *>(*i);
        if (elem)
        {
            auto type = elem->get_name();
            if (solarTypes.find(type) != solarTypes.end())
            {
                auto name = elem->get_attribute("name")->get_value();
                std::cout << type << ": " << name << std::endl;
                if (!type.compare("CelestialBody"))
                {
                    CelestialBody* celBody = new CelestialBody();
                    addBody(celBody);
                    parseXML(*i, celBody);
                }
                else
                {
                    auto attr = elem->get_attributes();
                    int j=0;
                    double orb[7];
                    for (auto i = attr.begin()++; i != attr.end(), j < 7; ++i, ++j)
                    {
                        orb[j] = atof((*i)->get_value().c_str());
                    }
                    if (!type.compare("SolSysBody"))
                    {
                        SolSysBody* sysBody = new SolSysBody(orb[0], orb[1], orb[2], orb[3], orb[4], orb[5], orb[6]);
                        addBody(sysBody);
                        parseXML(*i, sysBody);
                    }
                    if (!type.compare("Comet"))
                    {
                        Comet* comBody = new Comet(orb[0], orb[1], orb[2], orb[3], orb[4], orb[5], orb[6]);
                        addBody(comBody);
                        parseXML(*i, comBody);
                    }
                    if (!type.compare("Satellite"))
                    {
                        Satellite* satBody = new Satellite(orb[0], orb[1], orb[2], orb[3], orb[4], orb[5], orb[6]);
                        satBody->setPlanet(dynamic_cast<SolSysBody*>(p));
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
                    std::cout << type << ": " << texture << std::endl;
                    if (type == "Body")
                    {
                        auto R = elem->get_attribute("radius")->get_value();
                        Body* body = new Body(atof(R.c_str()), tex);
                        p->add(body);
                    }
                }
            }
        }
    }
}
