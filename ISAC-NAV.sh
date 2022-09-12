echo "Lanzando ISAC-NAV"
echo "limpiando ejecuciones pasadas"
make clean
rm Antenas.txt
rm ./Representacion/js/Antenas.js
echo "Calculando desviación del Dongle"
cd /home/blzns/kalibrate-rtl/src
./kal -s GSM900 > /home/blzns/ISAC-NAV/V4/Proyecto/Rastreo.txt
Chanel=$(awk '/chan:/ {print $2;exit}' /home/blzns/ISAC-NAV/V4/Proyecto/Rastreo.txt)
echo Se ha encontrado el canal $Chanel

./kal -c $Chanel > /home/blzns/ISAC-NAV/V4/Proyecto/Error.txt
Error=$(awk '/error:/ {print $4;exit}' /home/blzns/ISAC-NAV/V4/Proyecto/Error.txt)
Error=${Error%.*}
echo El error del dispositivo es $Error
cd /home/blzns/ISAC-NAV/V4/Proyecto
echo "Compilando el programa"
make
echo "Abriendo la web"
firefox --kiosk Representacion/index.html &
while true
do
	echo "Lanzando GRGSM"
	grgsm_scanner -b GSM900 -p $Error > Antenas.txt
	cat Antenas.txt
	echo "Lanzando ISAC-NAV"
	./ISAC-NAV
	
done
