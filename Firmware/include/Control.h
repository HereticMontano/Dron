class Control
{
private:
public:
    struct ControlDirection
    {
        // Left stick
        float throttle = 0.0f;
        float yaw = 0.0f;

        // Right Stick:
        float pitch = 0.0f;
        float roll = 0.0f;
    };

    void Init();
    ControlDirection ReadDirecction();
};
