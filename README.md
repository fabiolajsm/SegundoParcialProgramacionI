# Segundo parcial Laboratorio I - Lenguaje C. 
#### Enunciado
<p> Realizar un programa que permita analizar información de ventas de productos almacenadas en un archivo.
El programa deberá iniciar y cargar en una lista los elementos definidos en el archivo data.csv, el cual cuenta con el siguiente formato: 
(Deberá generar el archivo utilizando la página Mockaroo)</p>

ID_Venta;Fecha_Venta;Modelo_Auto;Cantidad;Precio_Unitario;Tarjeta_De_Credito<br>
Ejemplo: 33,16/11/2018,Mustang,1,12567.99,4017959045824

Deberá contar con un menú para dar de alta, baja y modificar las ventas, pudiendo guardar el archivo
de registro de ventas tanto en formato texto como en formato binario.
Deberá contar con una opción del menú “Generar Informe Ventas”, creando un archivo “informes.txt”
con el siguiente formato:
********************
Informe de ventas
********************
- Cantidad de unidades vendidas totales: XX
- Cantidad de ventas por un monto mayor a $10000: XX
- Cantidad de ventas por un monto mayor a $20000: XX
- Cantidad de (Elijan ustedes un modelo) vendidos: XX
********************
#### Requerimientos del desarrollo
• Se deberá crear la entidad “Venta” con todos sus campos correspondientes.<br>
• Se deberá utilizar la biblioteca LinkedList para almacenar las ventas leídas del archivo.<br>
• Se deberá agregar a la biblioteca la función “ll_count()” la cual permitirá contar elementos de la lista bajo algún criterio.<br>
• Se deberá utilizar la función “ll_count( )” para calcular los informes pedidos.<br>
