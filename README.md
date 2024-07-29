# boumb-esp32

Codage de la boumbe en ESP32.

le code du clavier matriciel a été deporter dans un PIC 18f628A.
ce dernier doit comuniquer en Serial avec l''esp.

l'esp doit avoir plusieur CORE.
le core1 c'est `loop()`
le core0 est dedier a tout ce qui est lecture de RX0 et du bornier.
Le tout s'arrete si un fikl du bornier est couper
