# chatbot-cpp
mini proyecto y semestral de cpp
http universidad: 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
tema seleccionado:Asistente de Recomendaciones de Juegos
- Sugiere juegos según género, plataforma o gustos del usuario.
- crear el build con:
-  mkdir build
-  cd build
-  cmake -G "MinGW Makefiles" .. O cmake -G "Unix Makefiles" ..
-  cmake --build .
- agregar el include, src, resources si no estan
-  mkdir include
-  mkdir src
-  mkdir resources/json
aqui provocara un conflicto
aqui sufri el conflicto
## Licencia

Este proyecto usa el framework [Qt](https://www.qt.io) bajo la licencia **LGPL v3**.  
Qt es propiedad de The Qt Company y se distribuye bajo los términos de la [GNU Lesser General Public License, versión 3](LICENSE_QT_LGPL).

Este proyecto en sí está licenciado bajo [MIT](LICENSE) (o la licencia que prefieras).

De acuerdo con la LGPL v3:
- Las bibliotecas de Qt se enlazan dinámicamente con esta aplicación.  
- Los usuarios pueden reemplazar o actualizar las bibliotecas Qt por versiones compatibles.  
- No se han modificado las bibliotecas Qt originales.

#video para instalar qtcreator en windows
https://www.youtube.com/watch?v=x9XeCq9tOI0
#como inicializar proyecto
1. abra qt creator
2. eliga abrir proyecto
3. abra CMakeLists.txt
4. elija el kit desktop o parecido y la casilla debug
5. dele a ejecutar y espera que se construya.
6. la primera vez el db estara vacio, debe llevar la copia DataBase_ChatBot.db de recursos a la siguiente ruta
-linux: .local/share/ChatBot/DataBase_ChatBot.db
-windox: C:\Users\<Usuario>\AppData\Local\ChatBot\DataBase_ChatBot.db
7. ya deberia fucionar en caso contrario contacteme.
