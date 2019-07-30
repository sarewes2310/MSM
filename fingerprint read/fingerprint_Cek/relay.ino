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
