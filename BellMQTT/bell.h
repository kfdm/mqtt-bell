class Bell
{
public:
    Bell(uint8_t reqPin) : PIN(reqPin)
    {
        pinMode(PIN, OUTPUT);
    };

    void ring()
    {
        digitalWrite(PIN, HIGH);
        delay(100);
        digitalWrite(PIN, LOW);
    }

private:
    const uint8_t PIN;
};
