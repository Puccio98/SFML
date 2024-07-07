#ifndef SFML_SKILL_H
#define SFML_SKILL_H


class Skill {
private:
    int level;
    int exp;
    int expNext;

public:
    Skill();

    virtual ~Skill();

    void update();
};


#endif //SFML_SKILL_H
