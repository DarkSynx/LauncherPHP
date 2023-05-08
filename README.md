# LauncherPHP
"LauncherPHP" embarque php.exe et un script puis execute va créé php.exe dans le dossier ./php. "LauncherPHP" embeds php.exe and a script then execute will create php.exe in the ./php folder

utilisez se projet avec Dev-C++ portable 6.3 (https://sourceforge.net/projects/embarcadero-devcpp/files/v6.3/Embarcadero_Dev-Cpp_6.3_TDM-GCC_9.2_Portable.7z/download)

Etape 1: ouvrir le projet avec "Dev-C++ portable 6.3"
![image](https://user-images.githubusercontent.com/9467611/236879963-b68eebfb-7710-4934-bf3b-8ec2833849a1.png)

Etape 2: pour le faire avec votre version de php rendez-vous dans le dossier "exeTobin"
déposé votre php.exe version x.y.z puis revenez dans le dossier d'avant du projet 
et executez "generate_header_php.bat" : cela vas créé "php.h" et "php.cpp" dans le dossier du projet

Etape 3: modifier le fichier "script.php" dans le dossier du projet avec votre code sans les balises PHP "<?php"

Etape 4: compiler le projet "Launcher.exe" là ou se trouvera "Launcher.exe" il devra y avoir le dossier "php/" ou vous y rajouterez les dll necessaire 
à son execution. 


--------

Step 1: open the project with "Dev-C++ portable 6.3"

Step 2: to do it with your version of php go to the "exeTobin" folder deposited your php.exe version xyz then return to the folder before the project and execute "generate_header_php.bat": this will create "php .h" and "php.cpp" in the project folder

 Step 3: edit the "script.php" file in the project folder with your code without the PHP "<?php" tags

 Step 4: compile the "Launcher.exe" project where "Launcher.exe" will be located, there must be the "php/" folder where you will add the dlls necessary for its execution.

