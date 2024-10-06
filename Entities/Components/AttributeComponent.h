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

    void applyDamage(float damage = 1.f);

    void restoreHealth(float amount);

private:

    float hp;
};


#endif //SFML_ATTRIBUTECOMPONENT_H
