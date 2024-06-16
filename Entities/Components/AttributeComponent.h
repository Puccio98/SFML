#ifndef SFML_ATTRIBUTECOMPONENT_H
#define SFML_ATTRIBUTECOMPONENT_H


class AttributeComponent {
public:
    AttributeComponent();

    virtual ~AttributeComponent();

private:
    //Statistiche a caso
    float hpMax;
public:
    float getHpMax() const;

    float getHp() const;

private:
    float hp;
};


#endif //SFML_ATTRIBUTECOMPONENT_H
