Version final du programme. 
Contient la commande en bf avec le capteur seul, le vicon ou avec le couplage des deux mesures. 
Possibilit� de faire le calcul du cap  �  l'aplomb.


- Les fichiers <<COM_Prog_Rover.mdl>> et <<init_COM_Prog_Rover.m >> sont li�s. 
     C'est le code qui va sur la gumstix.  On ex�cute le .m qui se charge de compiler le .mdl. C'est dans le .m que 
      les divers parametres sont d�finis.

- Les fichiers <<QUARC_Prog_Rover.mdl>> et <<init_QUARC_Prog_Rover.m>> sont li�s de la m�me fa�on que les pr�c�dents. Ceux ci s'ex�cutent sur le PC de contr�l.
    C'est dans le .m par exemple que l'on reporte les param�tres obtenus lors de la calibration.


Lors de l'ex�cution du mod�le <<QUARC_Prog_Rover.mdl>>, les diff�rentes donn�es sont enr�gistr�es dans le fichier <<Robot_Control_date_hour.mat>>

