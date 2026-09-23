D'après le tableau des cinq étapes du chapitre 1, voici ce que j'ai pu retrouver avec des sources vérifiables  et ce que je n'ai pas pu confirmer.

## Tableau avec sources

| Étape | Valeur du chapitre | Valeur mesurée trouvée | Source |
|---|---|---|---|
| Capteurs mesurent le mouvement | 1 à 2 ms | Les IMU (accéléromètre + gyroscope) fonctionnent à 500–1000 Hz, ce qui donne une latence d'échantillonnage individuelle d'environ 1 ms, avec des IMU opérant à des fréquences très élevées rendant leur latence d'échantillon individuelle très basse (~1 ms) | VR & AR Wiki, article « Motion-to-photon latency » |
| Le système transmet la mesure | 1 à 3 ms | **Introuvable isolément.** Les sources publiques regroupent presque toujours la transmission avec le traitement du signal sous une même catégorie (« input processing »຺) | — |
| Votre application décide et dessine | 5 à 11 ms | Un article académique donne un budget de rendu de 2 à 10 ms dans une architecture VR sans fil comparable | « AI Enabled 6G for Semantic Metaverse » (arXiv 2507.19124) |
| Le compositeur assemble | 1 à 2 ms | **Introuvable comme valeur isolée.** Oculus/Meta expose bien une métrique « CompositorLatency » dans son SDK, mais elle mesure la latence totale du time-warp corrigé, pas le temps de composition seul | Meta/Oculus PC SDK, `ovrPerfStatsPerCompositorFrame` |
| L'écran affiche la ligne | 2 à 5 ms | Un article donne un balayage d'affichage de 2 à 16 ms à 60 Hz, selon la technologie employée | « XR-RF Imaging Enabled by Software-Defined Metasurfaces » (arXiv 2209.15436) |

## Ce que je n'ai pas trouvé, 

Pour **la transmission** et **le compositeur**, je n'ai trouvé aucune documentation constructeur ou article donnant une valeur mesurée isolée pour cette étape précise. Les fabricants (Meta, Valve) publient des métriques de latence *totale* ou *cumulée* (motion-to-photon global, compositor latency incluant le time-warp), mais pas de mesure dédiée à la simple transmission des données du capteur au système, ni au simple temps de composition avant affichage. C'est cohérent avec ce que dit l'énoncé : certaines valeurs restent introuvables, et il vaut mieux le dire que d'inventer un chiffre.

