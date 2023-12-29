#ifndef VIEW_H
#define VIEW_H

class View {
   public:
    virtual void init() = 0;
    virtual void clear() = 0;
    virtual void close() = 0;
    virtual ~View() = default;
};
#endif
