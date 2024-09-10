# boumb-esp32

Codage de la boumbe en ESP32.



l'esp doit avoir plusieur CORE.
le core1 c'est `loop()`
le core0 est dedier a tout ce qui est lecture du clavier matriciel et du bornier.
Le tout s'arrete si un fil du bornier est couper ou que temps restant est egale a 0.

Liste du materiel:
- esp32 wroom-32 (avec 2 cores)
- carte de developpement pour esp (permet de lui donner du 12v)
- un ecran LCD 2x16 caracteres + module i2c FC113
- un pcf 8574
- clavier matriciel 4x4
- une bande led ws2812b (garder que 6 leds)
- un module relais 12v (exemple: https://fr.aliexpress.com/item/1005002983784189.html)
- Générateur d'impulsions haute tension (12v)
- baterie d'onduleur 12v


## Bizzarerie
pour une raison inconnue le FC113 et et pcf8574 ne sont pas compatible sur le meme i2c.
c'est pour ca dans le code l'ecran et sur le "wire" standard. et le pcf8574 sur un Wire2.
