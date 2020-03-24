#ifndef POWERIO_H
#define POWERIO_H

class PowerIO : public MathIO {
    MathIO _base;
    MathIO _exp;
    bool _compact;
    std::vector<bool> _renderBuff;

    public:
        PowerIO(MathIO* base, MathIO* exp);

        int getWidth();
        int getHeight();
        std::vector<bool> getRender();
        void setCompactMode(bool compact);
}

#endif
