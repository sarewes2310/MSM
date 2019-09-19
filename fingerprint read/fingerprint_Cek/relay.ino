void relay_inisialisasi()
{
    pinMode(IN_PIN, OUTPUT);
    digitalWrite(IN_PIN, HIGH);
}
void cek_relay(int i)
{
    if(i == 0)
    {
        digitalWrite(IN_PIN, LOW);
    }
    else
    {
        digitalWrite(IN_PIN, HIGH);
    }
}

void led_inisialisasi(int LED_PIN)
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void cek_led(int LED_PIN, int i)
{
    if(i == 0)
    {
        digitalWrite(LED_PIN, LOW);
    }
    else
    {
        digitalWrite(LED_PIN, HIGH);
    }   
}
