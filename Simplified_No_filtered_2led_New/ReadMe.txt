Version final du programme. 
Contient la commande en bf avec le capteur seul, le vicon ou avec le couplage des deux mesures. 
Possibilité de faire le calcul du cap  à  l'aplomb.


- Les fichiers <<COM_Prog_Rover.mdl>> et <<init_COM_Prog_Rover.m >> sont liés. 
     C'est le code qui va sur la gumstix.  On exécute le .m qui se charge de compiler le .mdl. C'est dans le .m que 
      les divers parametres sont définis.

- Les fichiers <<QUARC_Prog_Rover.mdl>> et <<init_QUARC_Prog_Rover.m>> sont liés de la même façon que les précédents. Ceux ci s'exécutent sur le PC de contrôl.
    C'est dans le .m par exemple que l'on reporte les paramètres obtenus lors de la calibration.


Lors de l'exécution du modèle <<QUARC_Prog_Rover.mdl>>, les différentes données sont enrégistrées dans le fichier <<Robot_Control_date_hour.mat>>

