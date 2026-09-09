# Arquitectura-del-Computador-br-menor


Me fue solicitado en el sorteo de numeros la instrucción br menor

Esta instrucción funciona de la siguiente manera se le pasan dos registros R1 y R2 y si R1 < R2 salta hacia donde le indica la constante que se le manda con la función. Por lo entendido de la clase la instrucción se forma con el Codigo de operación,R1,R2 y la constante,ocupando cada una de las partes cuatro bits.

En circuitverse realize un circuito en el cual ingresas un numero de 16 bits el cual lo dividiremos en las cuatro partes antes mencionadas de la siguiente forma.
Los cuatro bits mas significativos son el CO,los siguientes cuatro y cuatro bits son los dos registros y los otros cuatro bits la constante.

Lo que hacemos es extraemos con un bus los bits y con los cuatro del CO hacemos un and,este and va a ir conectado a unos multiplexores que usaremos de control (debido a que si el CO es incorrecto no deberia pasar nada).

Conectaremos en un multiplexor cada registro en el puerto 1 y en el puerto 0 conectaremos un 0000 (esto debido a que no podemos dejar un puerto del multiplexor vacio)

La constante la usaremos mas adelante.

Esto que sacamos va a ir a la caja negra del banco de memoria a los puertos de control de los multiplexores A y B asi A y B seran sacados de los registros que se indican en los bits.

Esto se usara en la ALU la cual la tenemos seteada en 110 para que reste los valores,esto debido a que a partir del resultado de la resta sabremos si A < B

Aca tenemos una especie de bache debido a que el br lo que hara es con el resultado sacara unas flags que son N Z y V las cuales se activan si el numero es negativo,cero o si hay overflow respectivamente.El problema es que a mi no me corresponde hacer esas flags es trabajo de otro compañero pero como necesitamos estas flags porque a partir de estas se saca el resultado lo que haremos es no hacer anda con el resultado de la ALU y poner manualmente las flags como adaptación temporal.

Ahora analizemos los valores de los flags y como me determinan si el numero es menor o no

Las relaciones son las siguientes si yo resto dos numeros y nos da cero osea Z 1 son iguales asi que no hay salto,
Z sera 0 en todas las otras instancias, si N 0 y V 0 bueno todo salio bien el numero dio positivo por lo que suponemos que A > B, esto porque si resto dos negativos o dos positivos si son mayores siempre daran positivo.
Si tengo N 1 V 0 es que reste dos numeros y dio negativo porque o reste dos positivos o dos negativos y A es menor que B por lo que el resultado dara que tengo que saltar.
Antes de seguir vamos a aclarar que si V  es 1 es que hay overflow porque el resultado de N va a ser mentira porque como hubo overflow se afecto el numero de mayor significancia,esto va a pasar al trabajar con numeros muy grandes
Entonces si N 0 y V 1 N es mentira por lo que A < B, si N 1 V1 N es mentira por lo que  A > B

Entonces como vemos Z al final no importa siendo 0 o 1 no nos cambia la vida en nuestra operacion importa el N y V 
Ahora en la siguiente tabla resumiremos todo y Z representara si tengo que saltar o no.
```text
N V Z
0 0 0
0 1 1
1 0 1
1 1 0
```

Esto se resuelve con un xor,como se ve en la tabla, y el resultado dira si tenemos que saltar o no

Para esto haremos otra adaptación y conectaremos este xor a otro multiplexor, y esta vez en el puerto 1 del multiplexor colocaremos la constante que sacamos al inicio y si el xor da 1 saltaremos a esa constante (en realidad esa constante representa algo que nos lleva adonde hay que saltar pero aca lo resumiremos a que saltamos a la constante),si no es 1 el xor se supone que no hay que saltar seguimos el camino normal como aca no lo conocemos vamos a devolver un numero que ingresaremos a mano en el puerto 0 del multiplexor.
