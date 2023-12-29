#ifndef CONTROLLER_H
#define CONTROLLER_H
class Controller {   
   public:
    virtual int get_input() = 0;
    virtual ~Controller() = default;   
};
#endif
