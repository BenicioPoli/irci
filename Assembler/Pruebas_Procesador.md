# Pruebas-Procesador
# Aclaración

Los Registros que utilizamos nosotros 4 y 5 deberian ser reemplazador por los 14 y 15 que son los $t0 y $t1 si bien los que usamos nosotros $lr0 $lr1 se pueden utilizar apra guardar valores no es recomendable segun la guia de convencion nosotros lo hacemos porque estamos realizando pruebas,ademas de que la primer versión de esta guia fue hecha con esos registros suponiendolos $t0 y $t1,entonces para no rehacer la guia seguiremos utilizando estos registros 4 y 5,que para lo que queremos nos sirve.

# Caso 1

## Descripción
Realizar las Cuatro Operaciones basicas entre dos registros y diferenciar los casos unsigned y signed.

## Instrucciones
- XOR
- LCI
- ORI
- ADD
- SUB
- MUL
- MULH
- MULHU
- MULHSU
- DIV
- DIVU
- REST
- RESTU
  
## Precondiciones
Previamente antes de sumar los registros tengo que cargarles algun valor para eso vamos a usar las instruciones LCI y ORI (osea un registro tendra un valor significativamente mas grande que el otro,ya que en uno cargaremos en la parte superior y otro en la inferior).

Además antes del LCI y ORI haremos un xor de los registros con si mismos para asegurarnos que no tengan basura.

Los registros que usaremos para guardar los valores seran  4 y 5 para guardar los valores que utilizaremos (estos valores los volveremos a utilizar en proximos casos), y usaremos 8 para el resultado de las funciones y ver si es el esperado (y también usaremos 9 en las operaciones en las que necesitemos de dos registros).

Nosotros pondremos siempre el resultado de las operaciones en el mismo registro para simplificar lo que va a ocasionar que se vaya sobre escribiendo por lo que habra que ir viendo r al poner cada instrucción.

## Code
```
XOR 4 4 4 (00000 00100 00100 00100 00000 0 001010) 0x0108400A
XOR 5 5 5 (00000 00101 00101 00101 00000 0 001010) 0x014A500A
LCI 4 4 10000.. (00100 00100 00100 1 1000 0000 0000 0000) 0x21098000 
ORI 5 5 100.. (00110 00101 00101 0 1000 0000 0000 0000) 0x314A8000
ADD 4 5 8 (00000 00100 00101 01000 00000 0 001100) 0x010A800C
SUB 4 5 8 (00000 00100 00101 01000 00000 0 001101) 0x010A800D
MUL 4 5 8 (00000 00100 00101 01000 00000 0 011000) 0x010A8018
MULH 4 5 9 (00000 00100 00101 01001 00000 0 011001) 0x010A9019
MULHU 4 5 9 (00000 00100 00101 01001 00000 0 011010) 0x010A901A
MULHSU 4 5 8 (00000 00100 00101 01000 00000 0 011011) 0x010A801B 
MULHSU 5 4 9 (00000 00101 00100 01001 00000 0 011011) 0x0148901B 
DIV 4 5 8 (00000 00100 00101 01000 00000 0 011100) 0x010A801C
REST 4 5 9 (00000 00100 00101 01001 00000 0 011110) 0x010A901E
DIVU 4 5 8 (00000 00100 00101 01000 00000 0 011101) 0x010A801D
RESTU 4 5 9 (00000 00100 00101 01001 00000 0 011111) 0x010A901F
```

## Postcondiciones
Para ir controlando si el codigo esta funcionando vamos poniendo r a ver si los registros se actualizaron ademas vemos en la consola del procesador si tomo bien la instrucción entre otras cosas.

## Conclusiones
Vemos que las instrucciones anduvieron de 10 y que en SUB al producirse un underflow el procesador maneja este underflow apagando el bit de signo (el MSB) por lo cual el numero es interpretado en forma erronea culpa del subdesbordamiento (la resta nos da como resultado 0x7FFF8000,que es positivo y no negativo,esto porque el negativo que se deberia representar tiene 33 bits lo cual es irrepresentable por nuestra maquina)

Vemos también que por como se calcula la multiplicación binaria el procesador se puede ahorrar tener un MULU ya que la parte baja no variara entre signed y unsigned.

Vemos el funcionamiento de unsigned y signed por ejemplo en la misma multiplicación donde al poner unsigned la parte mayor da 0x00004000 contra los 0xFFFFC000 queda al usar signed,esto tambien se ve en la division donde nos da 0xFFFF0000 en el signed y 0x0001000 en el unsigned.

Para probar MULHSU lo que haremos es ver si detecta bien lo de poner unsigned un argumento para eso testearemos usando el registro 4 (con valor negativo) como el signed y luego como el unsigned a ver si el resultado cambia como deberia,vemos lo hace ya que en el registro 8 nos quedo 0xFFFFC000 (lo que corresponde por ser 4 signed) y en el 9 nos quedo 0x00004000 (lo que corresponde por ser 4 unsigned).

Vimos que el resto no da basura da 0 como debe dar en nuestro caso.

# Caso 2

## Descripción
En este caso vamos a intentar mandar una letra h a la pantalla.

## Instrucciones
- ADDI
- SB
  
## Precondiciones
Otra vez haremos que los registros esten en 0 antes de aplicarles cualquier cosa y cargaremos la h en un registro y la dirección del serial de la pantalla 0xFFFFFF00 en otro registro.

Para variar ingresaremos con ADDI los valores en vez de usar ORI y LUI.

Para ADDI necesitamos mas que nunca que el registro este vacio para hacer 0 + el valor que queremos.

ADDI sirve para 16 bits que para h los alcanzan,pero para la direccion del puerto el problema se soluciona facil debido a que el bit 17 (el de significancia posterior a imm) se pone como 1 o 0 significando este si es negativo o positivo el registro para lo cual va a rellenar con 1 si se pone como 1 el bit y con 0 si se pone como 0.

Usaremos los registros 4 y 5 para guardar la dirección del serie y la h.

## Code
```
XOR 4 4 4 (00000 00100 00100 00100 00000 0 001010) 0x0108400A
XOR 5 5 5 (00000 00101 00101 00101 00000 0 001010) 0x014A500A
ADDI 4 4 0xFF00 (00011 00100 00100 1 1111111100000000) 0x1909FF00 
ADDI 5 5 0x0068 (00011 00101 00101 0 0000000001000100) 0x194A0068 
SB 4 5 0 (01011 00100 00101 0 00000000..00) 0x590A0000
```
## Postcondiciones
Para ir controlando otra vez vemos los registros y para ver la h se mando correctamente vemos el picocom.

## Conclusiones
Vimos la comunicación con la interface serie y vemos que funciona bien.

# Caso 3

## Descripción
En este caso veremos todos los branch if a ver si salta cuando corresponde utilizando los registros del caso 1.

## Instrucciones
- BEQ
- BNE
- BLT
- BGE
- BLTU
- BGEU
  
## Precondiciones
Utilizaremos los registros del Caso 1 los cuales asumimos como cargados previamente.

Para que se note el salto utilizaremos un salto de 4 instrucciones.

## Code
```
BEQ 4 5 0x0004 (10000 00100 00101 0 000...0100) 0x810A0004
BNE 4 5 0x0004 (10001 00100 00101 0 000...0100) 0x890A0004
BLT 4 5 0x0004 (10010 00100 00101 0 000...0100) 0x910A0004
BGE 4 5 0x0004 (10011 00100 00101 0 000...0100) 0x990A0004
BLTU 4 5 0x0004 (10100 00100 00101 0 000...0100) 0xA10A0004
BGEU 4 5 0x0004 (10101 00100 00101 0 000...0100) 0xA90A0004
```

## Postcondiciones
Si funciono en este caso se ve en la consola porque nos va a decir que saltamos al pc tanto y si vemos que avanzamos un pc nada más es que no aplicaba el salto.

## Conclusiones
Vemos que en nuestro caso por como se calcula el salto deberia estar saltando 0x14 cada vez que deberia saltar (esto porque PC + 4 + (4*4) = PC + 0x14). Vemos en los distintos casos que el salto es realizado de forma correcta.Ej:

PC: 0x0 -> 0x14

PC: 0x04 -> 0x18

Salta en BNE,BLT,BGEU lo cual corresponde por los valores en los registros.

# Caso 4

## Descripción
Hacer las operaciones booleanas entre los registros.

## Instrucciones
- AND
- OR
- NOR
  
## Precondiciones
Vamos a usar los mismos registros 4 y 5 del caso 1 pero le vamos a añadir al registro 4 un 1 en el mismo bit que tiene un uno el 5 esto para poder probar el add mejor,para esto vamos a usar un ORI en el que usamos el LUI.

## Code
```
ORI 4 4 100.. (00110 00100 00100 0 1000 0000 0000 0000) 0x31088000
AND 4 5 8 (00000 00100 00101 01000  00000 0 001000) 0x010A8008
OR 4 5 8  (00000 00100 00101 01000  00000 0 001001) 0x010A8009
NOR 4 5 8 (00000 00100 00101 01000  00000 0 001011) 0x010A800B
```

## Postcondiciones
Analizamos con r los registros luego de realizar los operaciones.

## Conclusiones
Vemos que el codigo funciono el and devuelve lo que esta almacenado en el registro 5 el or devuelve el registro 4 completo y el nor devuelve 0x7FFF7FFF que es lo que corresponde que mande.

Se pueden realizar correctamente operaciones booleanas en el procesador.

# Caso 5

## Descripción
Ver si dos Registros son menores y como cambia en signed y unsigned en estas comparaciones,tambien probar lo mismo con imms.

## Instrucciones
- SLT
- SLTU
- SLTI
- SLTIU
  
## Precondiciones
Utilizaremos los registros del caso 1, que los tomaremos como seteados previamente,y para hacer la comparacion con los imm utilizaremos el registro 4 por tener un contenido negativo.

Utilizaremos para guardar los valores los registros 8 y 9 utilizamos dos para poder comparar en cada caso el signed con el unsigned.

Vamos a comparar en las tipo I con una imagen cero para hacer más facil el analisis.

## Code
```
SLT 4 5 8 (00000 00100 00101 01000 000000 001110) 0x010A800E
SLTU 4 5 9 (00000 00100 00101 01001 000000 001111) 0x010A900F
SLTI 4 8 0 (10110 00100 01000 0 00000..000) 0xB1100000 
SLTIU 4 9 0  (10111 00100 01001 0 00000..000) 0xB9120000
```

## Postcondiciones
Vemos con el comando r al ejecutar cada instruccion si el registro  8 o 9 se pusieron en 1 o 0.

## Conclusiones
Vemos que anda bien ya que en el caso de SLT devuelve un 1 que esta bien porque 4 es menor pero en el caso del unsigned devuelve 0 porque el registro 4 se vuelve positivo y es mayor.

Lo mismo con las tipo I al comparar con la imagen 0 el registro 4 en signed devuelve 1 porque R4 tiene un valor negativo ahora si hacemos unsigned el R4 pasa a tener un valor positivo gigante por lo que se devuelve 0.

# Caso 6

## Descripción
Vamos a probar si las cuatro instrucciones de JUMP andan correctamente y el pc salta donde debe saltar.

## Instrucciones
- J
- JAL
- JALX
- JR
- JALR
- JALRX

## Precondiciones
Se recomienda empezar con el pc en 0 para una mejor visualización.

Para las tipo I nostros usaremos el registro 15 en el cual vamos a guardar previamente el valor 0x4 osea que en los tipo I deberiamos saltar igual que en las J.

## Code

```
J 0x02 (00001 00 0...0010) 0x08000002 
JAL 0x02 (00001 01 0...0010) 0x0A000002 
JALX 0 0x02 (00001 100 0...0010) 0x0C000002 (Guarda siempre en el registro 3)
JR 15 0x02 (00010 01111 00 00...0010) 0x13C00002 
JALR 15 0x02 (00010 01111 01 00...010) 0x13D00002
JALRX 15 0X02 (00010 01111 1 01 00...010) 0x13E80002 (Guarda siempre en el registro 3)
```

## Postcondiciones

Para ver si las tipo J funcionaron hay que ver si salta adonde debe,con ese salto que pusimos el pc debe saltar  a 0x0C
Y además al ejecutar los JAL se debe poder ver con r que el registro correspondiente guarde el valor del proximo pc

Y en las tipo I lo mismo

## Conclusiones

Vemos que en J saltamos 0x0C cada vez ejemplo:

PC: 0x0 -> 0x0C

PC: 0x04 -> 0x10

Esto coincide con la formula de PC + 4 + 4*2.

Vemos que JAL hace los mismos saltos pero guardando en el registro 1 donde iba a saltar si no era por el salto.
En PC 0x00 -> 0x04 y en PC 0x04 -> 0x08

En JALX lo mismo pero guardando en el registro 3

Vemos que JR funciona bien estemos en el pc que estemos vamos a saltar a 0x0C que es la suma entre 0x04 y la imagen extendida,JALR salta al mismo lugar y guarda en R1 adonde iba a saltar sino era por el salto,JALRX lo mismo guardando en el registro 3.

# Caso 7

## Descripción
En este caso vamos a ver las funciones que tienen que ver con el desplazamiento de bits.

## Instrucciones
- SLL
- SRL
- SRA
- SLLR
- SRLR
- SRAR
  
## Precondiciones
Para desplazar vamos a necesitar un valor que desplazar nosotros vamos a usar el valor de R4 que seteamos en el caso 4 es decir 0x80008000 sabiendo que en binario el 8 es 1000. Es importante usar este valor para ver como
se trata a los negativos.

Además debemos guardar en un registro algun valor para podes hacer el desplazamiento, como para desplazar se toman los bits de menor relevancia y para simplificar el movimiento vamos a cargar en un registro un simple 2 utilizando ORI, esto lo haremos en el registro 6 y vamos a limpiar el registro previamente para no tener basura.

Guardaremos los resultados en los registros 8, 9 y 10.

## Code
```
XOR 6 6 6  (00000 00110 00110 00110 00000 0 001010) 0x018C600A
ORI 6 6 2  (00110 00110 00110 0 0000 0000 0000 0010) 0x398C0002
SLL 0 4 8 aux:2  (00000 00000 00100 01000 00010 0 000000) 0x00088100  
SRL 0 4 9 aux:2  (00000 00000 00100 01001 00010 0 000010) 0x00089102
SRA 0 4 10 aux:2 (00000 00000 00100 01010 00010 0 000011) 0x0008A103
SRA 0 5 10 aux:2 (00000 00000 00101 01010 00010 0 000011) 0x000AA103
SLLR 6 4 8  (00000 00110 00100 01000 00000 0 000100) 0x01888004
SRLR 6 4 9  (00000 00110 00100 01001 00000 0 000110) 0x01889006
SRAR 6 4 10 (00000 00110 00100 01010 00000 0 000111) 0x0188A007
SRAR 6 5 10 (00000 00110 00101 01010 00000 0 000111) 0x018AA007
```

## Postcondiciones
Al ejecutar cada paquete de SLL ver en r si el valor del registro coincide con lo que se busca.

## Conclusiones
Al hacer SLL del valor nos dio 0x00020000, lo cual esta bien coincide con mover el bit del 8 dos lugares, lo que si el numero se volvio positivo en el mundo de los signed.

Luego al hacer SRL del valor nos dio 0x20002000 lo cual tambien esta bien coincide con mover dos bits los bits del 8,lo que si otra vez el numero se volvio positivo en el mundo de los signed.

Ahora al hacer SRA del valor nos dio 0xE0002000 lo cual coincide con mover los bits del 8 dos lugares y autocompletar con 1 los bits de MSB dependiendo cuanto nos movemos.

Por lo cual entre SRA y SRL nos damos cuenta de una muy importante diferencia mientras SRL rellena los MSB nuevos con 0, SRA lo hace con 1 lo cual nos permite mantener el signo en nuestro caso del numero negativo.

Para ver si los 1 eran por ser negativo o era siempre probamos con el registro 5 en el cual teniamos 0x00008000 y vemos que dio 0x00002000 por lo cual esto es algo importante y nos hace concluir que el SRA siempre mantiene el signo.

Podemos concluir que SRL se usaria para unsigneds y SRA para signeds.

Haciendo las SLLR obtuvimos los mismos resultados (esto porque usamos de R lo mismo que habiamos usado param) asi que concluimos que los Shift funcionan bien en el procesador.

# Caso 8

## Descripción
Vamos a probar subir cosas a memoria y cargarlas en otro registro.

## Instrucciones
- SW
- LW
- SH
- LH
- LHU
- SB
- LB
- LBU
  
## Precondiciones
Vamos a usar la dirección de memoria 0x010 y vamos a asumir que estamos en una estructura de 4kb.

Vamos a usar para cargar un registro que tiene un 1 en el MSB un 1 en el LSB y un 1 a la mitad (en el bit de mayor relevancia del quinto digito hexa), este registro lo vamos a formar con el LCI del caso 1 y con un ORI esto en el registro 4,este registro lo cargaremos en memoria de distintas formas y luego para sacarlo usaremos los registros 8 y 9, y vamos a usar el registro source 0 para que la dirección sea unicamente el offset (asumimos 0 como limpio).

## Code
```
LCI 4 4 10000.. (00100 00100 00100 1 1000 0000 0000 0000) 0x21098000
ORI 4 4 100..01 (00110 00100 00100 0 1000 0000 0000 0001) 0x31088001
SW 0 4 0x10 (01001 00000 00100 0 00000...010000) 0x48080010
LW 0 8 0x10 (01000 00000 01000 0 00000...010000) 0x40100010
SH 0 4 0x10  (01010 00000 00100 0 0000...010000) 0x50080010
LH 0 8 0x10  (01100 00000 01000 0 0000...010000) 0x60100010
LHU 0 9 0x10 (01101 00000 01001 0 0000...010000) 0x68120010
SB 0 4 0x10 (01011 00000 00100 0 0000....010000) 0x58080010
LB 0 8 0x10 (01110 00000 01000 0 0000....010000) 0x70100010
LBU 0 9 0x10 (01111 00000 01001 0 0000...010000) 0x78120010
```

## Postcondiciones
Verificar en los registros si se guardo el valor correctamente. Y tambien ver en la consolita si se ejecutaron los comandos correctos.


## Conclusiones
Vemos SW y LW funcionan porque luego de su ejecución R8 quedo igual que R4, no existe SWU porque es innecesario se carga todo el numero asi que no puede haber confusión en los signos.

Vemos que LH nos rellena con 1 los bits de mayor valor, esto pasa porque nuestro numero tiene en la parte mas baja de bit de mayor valor un 1 entonces rellena con 1 para mantener el signo, esto con LHU no pasa nos rellana con 0 de valor esto porque LHU toma como que todo es positivo.

Vemos que en LB, LBU carga el mismo valor en los registros 0x01 esto es porque si tomamos solo los ultimos 8 bits de nuestro numero es positivo entonces en tanto signed como unsigned es igual.

# Caso 9

## Descripción
En este caso vamos a seguir probando la carga y descarga en memoria pero a través de los Store y Load indexed.

## Instrucciones
- SWX
- SHX
- SBX
- LHX
- LHUX
- LBX
- LBUX
- LWX
  
## Precondiciones
Aca la dirección de memoria va a depender de la suma de dos registros entonces lo que vamos a hacer es cargar en un registro el numero 0x010 utilizando ORI y vamos a sumarlo con el registro 0, este 0x010 lo subiremos en el registro 5.

Vamos a utilizar el mismo registro 4 que utilizamos en el caso anterior.

Y para los load vamos a utilizar los registros 8 y 9.

## Code
```
LCI 4 4 10000.. (00100 00100 00100 1 1000 0000 0000 0000) 0x21098000
ORI 4 4 100..01 (00110 00100 00100 0 1000 0000 0000 0001) 0x31088001
ORI 5 5 000.10000 (00110 00101 00101 0 0000 0000 0001 0000) 0x314A0010
SWX 0 4 5 (00000 00000 00100 00101 00000 0 010101) 0x00085015 
LWX 0 8 5 (00000 00000 01000 00101 00000 0 010100) 0x00105014
SHX 0 4 5 (00000 00000 00100 00101 00000 0 010110) 0x00085016 
LHX 0 8 5  (00000 00000 01000 00101 00000 0 010000) 0x00105010
LHUX 0 9 5 (00000 00000 01001 00101 00000 0 010001) 0x00125011
SBX 0 4 5  (00000 00000 00100 00101 00000 0 010111) 0x00085017 
LBX 0 8 5  (00000 00000 01000 00101 00000 0 010010) 0x00105012
LBUX 0 9 5 (00000 00000 01001 00101 00000 0 010011) 0x00125013
```

## Postcondiciones
Verificar en los registros si se guardo el valor correctamente. Y tambien ver en la consolita si se ejecutaron los comandos correctos.

## Conclusiones
Al ejecutar LWX nos queda R8 = R4 por lo que funciona bien.

Vemos que LHX nos rellena con 1 los bits MSB debido a que el bit MSB de los 16 cargados es 1 por lo que el numero es negativo, y vemos que LHUX nos carga con 0 porque toma que el numero es positivo, este es el funcionamiento esperado asi que esta bien.

Al ejecutar LBX y LBUX nos carga el mismo valor que es un simple 0x01 en hexa por lo que andan bien.

Como los LOAD andan bien entonces podemos asumir que los STORE funcionan correctamente.

# Caso 10

## Descripción
En este caso vamos a hacer una prueba adicional sobre LBX y LB debido a que antes lo probamos unicamente con positivos vamos a ver si a los negativos los trata bien.

## Instrucciones
- LB
- LBX
  
## Precondiciones
Para esta prueba vamos a usar el mismo R5 del caso anterior y vamos a cargar en R4 con un ORI un 0x80 (esto sobre el valor que ya tiene R4 es decir no lo limpiamos previamente).

## Code
```
ORI 4 4 0x80 (00110 00100 00100 0 0000 0000 1000 0000) 0x31088080
SB 0 4 0x10 (01011 00000 00100 0 0000....010000) 0x58080010
LB 0 8 0x10 (01110 00000 01000 0 0000...010000) 0x70100010
LBX 0 9 5 (00000 00000 01001 00101 00000 0 010010) 0x00125012
```

## Postcondiciones
Verificamos valores de los registros.

## Conclusiones
Vemos que ambas instrucciones devuelven lo mismo 0x81 autocompletado con F lo que seria el valor de los 8 LSB de R4 autocompletado con 1 en los 24 bits de mayor relevancia por ser negativo, por lo que confirmamos que LB y LBX detectan bien ambos signos.

# Caso 11

## Descripción
En este caso vamos a probar las operaciones booleanas de tipo L.

## Instrucciones
- ANDI
- ANI/H
- ORI/H
- XORI/H
  
## Precondiciones
Para esta prueba vamos a setear el R4 en 0xF000F0F0 y usaremos imms distintos dependiendo de las operaciones. Los resultados los guardaremos en el R8,R9 y R10 

## Code
```
ANDI 4 8 0xF000 (00100 00100 01000 0 1111 0000 0000 0000) 0x2110F000 
ANI  4 9 0xF000 (00101 00100 01001 0 1111 0000 0000 0000) 0x2912F000 
ANH  4 10 0xF000 (00101 00100 01010 1 1111 0000 0000 0000) 0x2915F000 
ORI  4 8 0xF00F (00110 00100 01000 0 1111 0000 0000 1111) 0x3110F00F
ORIH 4 9 0xF00F (00110 00100 01001 1 1111 0000 0000 1111) 0x3113F00F
XORI 4 8 0xF000 (00111 00100 01000 0 1111 0000 0000 0000) 0x3910F000
XORH 4 9 0xF000 (00111 00100 01001 1 1111 0000 0000 0000) 0x3913F000
```

## Postcondiciones
Analizamos con r los registros luego de cada instrucción a ver si su valor condice con la operación realizada.

## Conclusiones
Vemos que ANDI devuelve unicamente 0xF000 esto porque no mantiene la parte de arriba solo hace and con la de abajo,en cambio ANI mantiene la parte de arriba intacta y devuelve 0xF0F0F000 y ANH mantiene la parte de abajo intacta y hace and con la de arriba (a diferencia de las dos anteriores que hacian con la parte de abajo), por lo que deuvelve 0xF000F0F0.


Vemos con los OR también funcionan ya que salen todas las F del hexa de R4 + una F adicional,en el caso de ORI esta aparece en el hexa de menor relevancia y en el caso de ORIH aparece en el cuarto hexa de mayor relevancia (por lo que respeta el bit de h la instrucción).

Además los XOR funcionan debido a que elimina una F en la operación,XOR elimina la F que esta en la posición 5 hexa y en XORI la primera (debido a que XOR elimina lugares donde hay dos 1), por lo cual la instrucción tiene el comportamiento esperado y detecta la h.

# Caso 12

## Descripción
En este caso vamos a probar las instrucciones de rotación

## Instrucciones
- RLC
- RLCR

## Precondiciones
Para esta prueba vamos a setear el Registro R4 en 0x60000000, R5 en 0x01 y R6 en 0x02.

## Code
```
RLC 4 8 1 (00000 00000 00100 01000 00001 0 000001) 0x00088081
RLC 4 9 2 (00000 00000 00100 01001 00010 0 000001) 0x00089101
RLCR 5 4 8 (00000 00101 00100 01000 00000 0 000101) 0x01488005
RLCR 6 4 9 (00000 00110 00100 01001 00000 0 000101) 0x01889005
```

## Postcondiciones
Verificar como siempre en r que los registros sufran las modificaciones correspondientes,y ver en la consola si se ejecuto la instrucción correcta

## Conclusiones

Vemos que en el primer RLC que movimos un lugar obtuvimos de resultado 0xC0000000 lo cual corresponde ya que en el hexa de mayor valor pasamos de 0110 a 1100 debido al movimiento de un bit.

Luego en el segundo RLC que movimos dos lugares obuvimos de resultado 0x80000001 lo cual corresponde porque movimos dos lugares los bits por lo que en el hexa de mayor valor pasamos de 0110 a 1000 y el 1 que quedo afuera paso al oro lado por lo que el digito hexa de mayor valor se transformo en un 1.

Al ejecutar RLCR con los mismos números obtuvimos los mismos resultados por lo que ambas instrucciones funcionan.
 

