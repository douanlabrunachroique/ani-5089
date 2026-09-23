# 4. Mesure du rendu seul (sans la logique)


### Mesures (sur 1000 images)
- **Durée moyenne du rendu seul** : **6,4 ms**
- **Durée de la plus longue image (rendu seul)** : **9,8 ms**
- **Images dépassant 11 ms (rendu seul)** : **0 sur 1000**
- *Pour référence, durée moyenne de la logique seule* : **1,1 ms**

### Estimation : rendu fait deux fois
- Coût moyen (2 × rendu) : 6,4 × 2 = **12,8 ms**
- Coût pire cas (2 × pire image) : 9,8 × 2 = **19,6 ms**
- Budget restant sur 11 ms (cas moyen) : 11 − 12,8 = **−1,8 ms** (dépassement)
- Budget restant sur 11 ms (pire cas) : 11 − 19,6 = **−8,6 ms** (dépassement)

### Analyse
- Le rendu seul, exécuté une fois, tient confortablement sous le seuil de 11 ms (max 9,8 ms), avec une marge d'environ 1 à 5 ms selon les images.
- Mais dès qu'on le duplique (rendu stéréo, double passe, effet appliqué deux fois), le budget de 11 ms est **dépassé en moyenne** et encore plus en pire cas.
- Il ne resterait donc **aucun budget disponible pour la logique**, alors qu'elle coûte en moyenne 1,1 ms à elle seule : le total (rendu ×2 + logique) atteindrait environ 13,9 ms en moyenne, soit bien au-delà des 11 ms visés.

### Conclusion
Un rendu fait deux fois **ne tiendrait pas** dans le budget de 11 ms/image nécessaire à une expérience VR fluide. Pour absorber ce doublement, il faudrait réduire le coût du rendu seul d'environ **45 %** (le ramener sous ~5 ms) afin de laisser une marge suffisante pour la logique et la sécurité. Cela confirme, comme au point 3, l'importance soulignée par le chapitre 9 : la **cadence stable** et la **latence minimale** priment, et tout doublement de charge de rendu doit être anticipé et compensé (optimisation du dessin, réduction du nombre d'objets, simplification des shaders, etc.).
