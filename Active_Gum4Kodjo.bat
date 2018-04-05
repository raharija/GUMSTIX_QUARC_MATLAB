cd C:\Windows\System32



netsh wlan set hostednetwork mode=allow ssid="Gum_kodjo" key="biorobotique" keyUsage=persistent

netsh interface ip set address "Connexion r‚seau sans fil 2" static 192.168.137.3 255.255.255.0 192.168.137.3 1

netsh wlan start hostednetwork 


pause