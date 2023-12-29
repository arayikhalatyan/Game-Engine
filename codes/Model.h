#ifndef MODEL_H
#define MODEL_H
#include <memory>

#include "Controller.h"
#include "View.h"
using std::unique_ptr;


class Model {
   public:
    virtual void go() = 0;
    virtual ~Model() = default;
};
#endif
