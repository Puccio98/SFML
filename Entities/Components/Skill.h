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

    void update() const;
};


#endif //SFML_SKILL_H
