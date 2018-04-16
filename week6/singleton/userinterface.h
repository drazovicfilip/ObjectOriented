#ifndef USERINTERFACE_H
#define USERINTERFACE_H

class UserInterface{
    public:
        static UserInterface& getInstance(int height, int width);
        int getInterfaceHeight(){ return m_height; }
        int getInterfaceWidth(){ return m_width; }

    // Constructor which can only be called by getInstance()
    protected:
        UserInterface(int height, int width);

    private:
        int m_height;
        int m_width;
};

#endif // USERINTERFACE_H
