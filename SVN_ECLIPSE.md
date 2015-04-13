Hola gente.. les mando las direcciones del repositorio y plug-in para eclipse del SVN..
Sino tienen el eclipse, bajansen el eclipse Europa con el plugin de c++.. solamente lo descargas lo descomprimis y lo ejecutas.. muy facil.. http://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/20071103/eclipse-cpp-europa-fall2-linux-gtk.tar.gz

El plugin para el svn se llama subclipse:
aca le paso las instrucciones de como instalarlo.
http://subclipse.tigris.org/install.html

usarlo es facil..
le adjunto una guia de como empezar a usarlo conectarse, bajar y subir archivos pero la idea basica es:

creen en su workspace la siguiente estructura de directorio:
ej:
/home/sebas/workspace/PacMan/trunk/

y cuando abren el aclipse eligan trabajar en el workspace de esa ruta.

Luego..
Una vez que instalaron el subclipse:
1) abrir la perspectiva de svn (esta en el manual)
2) conectar al repositorio de google con la siguiente info:
direccion: https://pacmantaller.googlecode.com/svn/trunk/
username scamjayi
pws: z4f4c2r8

3) hacer un checkout del proyecto.

La idea que la estructura de directorio sea la siguiente:

/home/sebas/workspace/PacMan/trunk/
> server/
> > source/

> cliente/
> > source/
Repositorio en google:
http://code.google.com/p/pacmantaller/

Cualquier duda me consultan..
Ya en el repositorio esta subido el server..
Saludos