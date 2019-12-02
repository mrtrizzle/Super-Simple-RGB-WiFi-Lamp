DEFINE_GRADIENT_PALETTE( WeddingDayBlues_gp) {
0,7,192,153,
63,255,68,0,
128,255,0,46,
190,255,68,0,
255,7,192,153};

DEFINE_GRADIENT_PALETTE( Blue_Cyan_Yellow_gp ) {
    0,   0,  0,255,
   63,   0, 55,255,
  127,   0,255,255,
  191,  42,255, 45,
  255, 255,255,  0};

class ModeGradient : public ModeBase
{
private:
    //TProgmemRGBGradientPalettePtr gGradientPalettes[];
    std::vector<TProgmemRGBGradientPalettePtr> gGradientPalettes = {WeddingDayBlues_gp, Blue_Cyan_Yellow_gp};
    uint8_t gCurrentPaletteNumber = 0;
    CRGBPalette16 gCurrentPalette = CRGBPalette16( CRGB::Black );
    CRGBPalette16 gTargetPalette = CRGBPalette16( gGradientPalettes[0] );
    int rainbowStartHue   = 0;
    int rainbowSpeed      = 10;
    int rainbowBri        = 100;
    float rainbowAddedHue = 0;
    void scrollPalette( CRGB* ledarray, uint16_t numleds, const CRGBPalette16& gCurrentPalette){
      static uint8_t startindex = 0;
      startindex--;
      fill_palette( ledarray, numleds, startindex, (256 / numleds) + 1, gCurrentPalette, 255, LINEARBLEND);
      }
      
public:
    ModeGradient() {}
    
    virtual void render() {
        EVERY_N_SECONDS( 5 ) {
          gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPalettes.size());
          Serial.println(gCurrentPaletteNumber);
          gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
          }
          
       EVERY_N_MILLISECONDS(40) {
        nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 24);
      }

      
       EVERY_N_MILLISECONDS(100) {
         scrollPalette( ledString, NUM_LEDS, gCurrentPalette);
       }
    

        //FastLED.setBrightness(255);
    }

    virtual void applyConfig(JsonVariant& settings) {
        settings["Hue"] = rainbowStartHue = settings["Hue"] | rainbowStartHue;
        settings["Speed"] = rainbowSpeed = settings["Speed"] | rainbowSpeed;
        settings["Brightness"] = rainbowBri = settings["Brightness"] | rainbowBri;
    }
};
