#ifndef CANLISTENER_H
#define CANLISTENER_H

#include <linux/can.h>
#include <string>
#include <vector>

#define ALLCHANNELS -100

class CanListener
{
private:
    // general information about what it needs to read
    std::string description;

    // channel to listen
    std::vector<int> on;
public:

    virtual void update(struct can_frame frame) = 0;

    CanListener(std::string _d, std::vector<int> _on) : description{_d}, on{_on}{};
    ~CanListener() = default;
};

// Test class
class CanPrintAll : public CanListener{
private:
public:
    void update(struct can_frame frame) override;

    CanPrintAll();
    ~CanPrintAll() = default;
};

#endif // CANLISTENER_H
