# :page_facing_up: papeos-guias :pencil2:
## Como leer
Las guías del repositorio se encuentran en archivos markdown (.md), solamente los README.md se "abren" automáticamente, el resto debes abrirlos tú

### Índices
Cada .md tiene un índice con links a los cabezales del archivo
![ejemplo_indice](./sources/indice.png)

### PDFs grandes
Los PDFs más extensos tienen un botón para mostrár más páginas que en algunos casos es difícil de ver
![more_pages_pdf](sources/more_pages.png)


<h2>
    <div align="center">
        <img src="./sources/USACHIN/IA/IA_59.png" width="300"/>
    </div>
    Tengo un aporte y quiero subirlo
</h2>


### 1. Fork + Pull request
Como dice arriba

<img src="./sources/USACHIN/IA/IA_61.png" width="200"/>

### 2. Enviar aporte por correo
Envía tu aporte a ignacio.lara.v@usach.cl y lucas.mesias@usach.cl, incluye en el asunto `papeos-guias`

### 3. Únete a OsUsach
Los miembros de OsUsach pueden pushear al repositorio libremente

<img src="./sources/USACHIN/IA/IA_1.png" width="200"/>


## Sources
Las carpetas [sources](./sources/) se usan para guardar imágenes que luego se importan en los archivos markdown (.md)
### Como agregar más iconos:
![Ejemplo](./sources/ejemplo_icons.png)
- ir a https://simpleicons.org/
- descargar el .svg, dejarlo en la carpeta sources correspondiente
- agregar los atributos `width="16" fill="{color}"`
- cambiar el ancho (o alto con height), 16 encaja con el tamaño de texto por defecto
- copiar el color correspondiente al ícono y ponerlo en fill
- agregar el icono a tu .md:
    - `![<texto_alternativo>](<path>)`
    - `![Git Logo](./sources/git.svg)`
    - ![Git Logo](./sources/git.svg)