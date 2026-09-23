# 5. Les quatre angles du champ de vision (œil gauche) casque VR du commerce

### Casque retenu : Valve Index

D'après les valeurs de champ de vision renvoyées par le runtime OpenXR/SteamVR du Valve Index (structure `XrFovf`, angles en radians convertis en degrés) :

| Angle | Valeur (œil gauche) |
|---|---|
| **Temporal** (vers l'extérieur, tempe) | ≈ **57,0°** |
| **Nasal** (vers l'intérieur, nez) | ≈ **46,4°** |
| **Haut** | ≈ **54,7°** |
| **Bas** | ≈ **54,6°** |

**Source :** valeurs `XrFovf` mesurées sur un Valve Index et publiées sur le forum développeurs Khronos (discussion OpenXR, *"Do these XrFovf values look suspicious/defective to you?"*, community.khronos.org).

Ces angles donnent un champ horizontal total (nasal + temporal) d'environ 103°, un champ vertical d'environ 109°, et une diagonale proche des 130° annoncés commercialement par Valve.

---

### Et avec un champ symétrique de même surface ?

En rendant le champ symétrique (nasal = temporal ≈ 51,7° de chaque côté) tout en conservant la même surface totale, on gagnerait en vision périphérique côté nez (zone déjà limitée optiquement par l'arête nasale et peu utile car en grande partie occultée par le nez lui-même) mais on perdrait autant de degrés côté tempe — précisément la zone qui contribue le plus à la sensation d'immersion et à la vision périphérique utile — donc l'expérience serait globalement moins immersive à surface de rendu égale.
