# boumb-esp32

Codage de la boumbe en ESP32.



l'esp doit avoir plusieur CORE.
le core1 c'est `loop()`
le core0 est dedier a tout ce qui est lecture du clavier matriciel et du bornier.
Le tout s'arrete si un fil du bornier est couper ou que temps restant est egale a 0.

Liste du materiel:
- esp32 wroom-32 (avec 2 cores) (https://fr.aliexpress.com/item/1005005704190069.html)
- carte de developpement pour esp (permet de lui donner du 12v) (https://fr.aliexpress.com/item/1005006263369854.html)
- un ecran LCD 2x16 caracteres + module i2c FC113 (https://fr.aliexpress.com/item/1005007015967868.html)
- un pcf8574 (https://fr.aliexpress.com/item/1005005291642973.html)
- clavier matriciel 4x4 (https://fr.aliexpress.com/item/4001135475068.html)
- une bande led ws2812b (garder que 6 leds) (https://fr.aliexpress.com/item/4001322411818.html)
- un module relais 12v (exemple: https://fr.aliexpress.com/item/1005002983784189.html)
- Générateur d'impulsions haute tension (12v) ()https://fr.aliexpress.com/item/1005005881098399.html)
- un abaisseur de tention 12v -> 5v (pour les ws2812b) (https://fr.aliexpress.com/item/1005006777931763.html)
- baterie d'onduleur 12v



## Bizzarerie
pour une raison inconnue le FC113 et et pcf8574 ne sont pas compatible sur le meme i2c.
c'est pour ca dans le code l'ecran et sur le "wire" standard. et le pcf8574 sur un Wire1.
