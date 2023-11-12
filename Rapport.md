# Rapport TP3

---
__*Choix d'implémentation*__ 


__structure liste :__
  - Etant donné que la sentinelle existe toujours quand la liste existe j'ai décidé d'utiliser la valeur de la sentinelle pour la taille. Cela permet de gagner 4 octets (ce qui est négligable).
  - présence d'un define pour la size pour y accéder facilement

__structure Sublist :__
  - La structure est uniquement défini dans le .c car elle n'a aucun intérêt pour l'utilisateur et s'il y a accès il risque juste d'invalider les invariants comme la taille par exemple.
  - Toutes les fonctions qui utilisent la sublist sont donc inconnus à l'utilisateur et pas définis dans le .h

__*Description du comportement sur les jeux de tests fournis*__

- Tous les jeux de test ont été validés

__*Analyse personnelle du travail effectué*__

- Il n'y a aucune fuite de mémoire et à ma connaissance aucune erreure.
