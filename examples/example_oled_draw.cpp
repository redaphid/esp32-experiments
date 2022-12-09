uint8_t pikachu_width = 128;
uint8_t pikachu_height = 64;
uint8_t pikachu_bits[128*64];
void drawPikachu(OLEDDisplay *display)
{
for (int i = 0; i < 128*64; i++)
{
  pikachu_bits[i] = 255;
}
  display->drawXbm(0, 0, pikachu_width, pikachu_height, pikachu_bits);
}
