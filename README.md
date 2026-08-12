# 3x0c3t_BO4RD_Diag

Diagnostic hardware et interface de test pour la **3x0c3t BO4RD**.

Projet développé pour **ESP8266 NodeMCU** avec :

- écran TFT ILI9341
- tactile XPT2046
- carte MicroSD
- WiFi
- fonctions système

---

# V3

La version **V3** introduit une architecture modulaire destinée à séparer clairement :

- l'interface utilisateur
- l'affichage
- le tactile
- la carte SD
- le WiFi
- les fonctions système
- la configuration
- le diagnostic matériel

L'objectif est de pouvoir ajouter progressivement de nouvelles fonctions sans mélanger la gestion matérielle et l'interface graphique.

---

# Matériel

| Fonction | Matériel |
|---|---|
| Microcontrôleur | ESP8266 NodeMCU |
| Écran | TFT ILI9341 |
| Résolution | 240 × 320 pixels |
| Interface écran | SPI |
| Tactile | XPT2046 |
| Stockage | MicroSD |
| Réseau | WiFi intégré ESP8266 |

---

# Architecture générale

L'interface est organisée autour d'écrans standardisés.

```text
3x0c3t_BO4RD
│
├── Écran 0
│   └── Splash Screen
│
├── Écran 1
│   └── Main
│       │
│       ├── ECRAN
│       ├── TACTILE
│       ├── CARTE SD
│       ├── WIFI
│       ├── SYSTEME
│       └── REBOOT
│
├── Écran 2
│   └── Diagnostic écran
│
├── Écran 3
│   └── Diagnostic tactile
│
├── Écran 4
│   └── Diagnostic carte SD
│
├── Écran 5
│   └── Diagnostic WiFi
│
└── Écran système
    ├── Informations
    ├── Configuration
    └── Reboot