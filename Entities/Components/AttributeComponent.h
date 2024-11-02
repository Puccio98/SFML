#ifndef SFML_ATTRIBUTECOMPONENT_H
#define SFML_ATTRIBUTECOMPONENT_H


class AttributeComponent {
public:
    AttributeComponent();

    explicit AttributeComponent(float hp);

    virtual ~AttributeComponent();

private:
    //Statistiche a caso
    float hpMax;

public:
    float getHpMax() const;

    float getHp() const;

    void applyDamage(float damage = 1.f);

    void restoreHealth(float amount);

    bool isDead() const;

private:

    float hp;
};


#endif //SFML_ATTRIBUTECOMPONENT_H
