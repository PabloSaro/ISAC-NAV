setInterval("location.reload()",40000);

var latitud =40.438988;
var longitud =-3.680357;

function comenzar(){
	var miboton=document.getElementById("calcula_error");
	miboton.addEventListener("click", dist, false);
	
}
function dist(){
	navigator.geolocation.getCurrentPosition(mostrar_posicion);

}
function mostrar_posicion(posicion){
	var ubicación=document.getElementById("ubicación");
	latitud =posicion.coords.latitude;
	longitud =posicion.coords.longitude;
	map.setView(new L.LatLng(latitud, longitud), 16);
	L.marker([latitud,longitud], {icon: redIcon} ,{ draggable: true }).bindPopup("<b> GOOGLE POS </b> <br>Lat:" + latitud +" <br>Lon:"+ longitud).openPopup().addTo(map); 
}

var redIcon = L.icon({
    iconUrl: 'Gmarker2.png',
    shadowUrl: 'Gmarker2.png',

    iconSize:     [23, 40], // size of the icon
    shadowSize:   [0, 0], // size of the shadow
    iconAnchor:   [22, 94], // point of the icon which will correspond to marker's location
    shadowAnchor: [0, 0],  // the same for the shadow
    popupAnchor:  [-3, -76] // point from which the popup should open relative to the iconAnchor
});

var greenIcon = L.icon({
    iconUrl: 'Gmarker3.png',
    shadowUrl: 'Gmarker3.png',

    iconSize:     [40, 40], // size of the icon
    shadowSize:   [0, 0], // size of the shadow
    iconAnchor:   [22, 94], // point of the icon which will correspond to marker's location
    shadowAnchor: [0, 0],  // the same for the shadow
    popupAnchor:  [-3, -76] // point from which the popup should open relative to the iconAnchor
});




window.addEventListener("load", comenzar, false);

var map = L.map('map').setView([latitud, longitud], 16); 
L.tileLayer('http://{s}.tile.stamen.com/toner/{z}/{x}/{y}.png',  
{  
	   attribution: 'Tiles by <a href="http://mapc.org">MAPC</a>,   Data by <a href=" http://mass.gov/mgis ">MassGIS</a>'  
	   ,maxZoom : 17,  
	   minZoom : 9  
   }).addTo(map);


function mostrarHora(){
    momentoActual = new Date();
    hora = momentoActual.getHours();
    minuto = momentoActual.getMinutes();
    segundo = momentoActual.getSeconds();

    horaImpresa = "Ultima Actualización: " + hora + " : " + minuto + " : " + segundo;
    //SALIDA
    document.getElementById('mostrarHora').innerHTML = horaImpresa;
}