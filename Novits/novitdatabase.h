#ifndef NOVITDATABASE_H
#define NOVITDATABASE_H

#include <vector>
#include "Novit.h"

class NovitDatabase
{
    public:
        static std::vector<Novit> getAllNovits();
        static Novit getNovitById(int id);
};

#endif // NOVITDATABASE_H
